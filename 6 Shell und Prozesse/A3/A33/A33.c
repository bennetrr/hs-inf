#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../sem_helpers.c"
#include "../shm_helpers.c"

static constexpr int MINUTE = 1;
static constexpr int APPLICATION_COUNT = 5;
static constexpr size_t QUEUE_SIZE = 5;
static constexpr int PRINTER_COUNT = 2;
static constexpr int TOTAL_CHILD_PROCESS_COUNT = APPLICATION_COUNT + PRINTER_COUNT + 1;

static constexpr int SHARED_MEMORY_KEY = 0x19496CF8; // This is 424242424 in hex because ipcs displays keys in hex
static constexpr int PRINTING_JOBS_SHM_KEY = 0x19E38E0A;
static constexpr int PENDING_JOBS_MUTEX_SEM_KEY = 0x1A7DAF1C;
static constexpr int PENDING_JOBS_FREE_SEM_KEY = 0x1B17D02E;
static constexpr int PENDING_JOBS_WAITING_SEM_KEY = 0x1BB1F140;
static constexpr int PRINTER_READY_SEM_KEY = 0x1C4C1252;
static constexpr int PRINTER_BUSY_SEM_KEY = 0x1CE63364;

static bool should_terminate = false;

void loop_signal_handler(const int signal) {
    printf("Child process %d: Received signal %d\n", getpid(), signal);
    should_terminate = true;
}

void main_signal_handler(const int signal) {
    printf("Main: Received signal %d\n", signal);
}

int rand_range(const int min, const int max) {
    return min + rand() % (max - min + 1);
}

struct PrintJob {
    int pageCount;
    int data;
};

struct Queue {
    size_t write_pos;
    size_t read_pos;
    size_t count;
    struct PrintJob items[QUEUE_SIZE];
};

// Initializes the queue
void queue_init(struct Queue *queue) {
    queue->write_pos = 0;
    queue->read_pos = 0;
    queue->count = 0;
}

// Puts an item into the queue. Returns 0 on success, or -1 if the queue is full (in true UNIX fashion)
int queue_put(struct Queue *queue, const struct PrintJob item) {
    if (queue->count >= QUEUE_SIZE) {
        return -1;
    }

    queue->items[queue->write_pos] = item;
    queue->write_pos = (queue->write_pos + 1) % QUEUE_SIZE;
    queue->count++;
    return 0;
}

// Gets the first item from the queue and puts it into dest. Returns 0 on success, or -1 if the queue is empty
int queue_get(struct Queue *queue, struct PrintJob *dest) {
    if (queue->count <= 0) {
        return -1;
    }

    *dest = queue->items[queue->read_pos];
    queue->read_pos = (queue->read_pos + 1) % QUEUE_SIZE;
    queue->count--;
    return 0;
}

int spooler() {
    // Initialization
    printf("Spooler: Started with PID %d\n", getpid());
    printf("Spooler: Initializing\n");

    int exit_code = 0;
    int pending_jobs_shm_handle = -1;
    struct Queue *pending_jobs = nullptr;
    int printing_jobs_shm_handle = -1;
    struct PrintJob *printing_jobs = nullptr;
    int pending_jobs_mutex = -1;
    int pending_jobs_free = -1;
    int pending_jobs_waiting = -1;
    int printer_ready = -1;
    int printer_busy = -1;
    int current_printer_id = 0;

    struct sigaction sa;
    sa.sa_handler = loop_signal_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    if (sigaction(SIGINT, &sa, nullptr) == -1) {
        perror("Spooler: Could not install SIGINT handler");
        exit_code = 1;
        goto exit;
    }
    if (sigaction(SIGTERM, &sa, nullptr) == -1) {
        perror("Spooler: Could not install SIGTERM handler");
        exit_code = 1;
        goto exit;
    }

    pending_jobs_shm_handle = shm_create(SHARED_MEMORY_KEY, sizeof(struct Queue));
    if (pending_jobs_shm_handle == -1) {
        perror("Spooler: Could not create pending jobs queue shared memory");
        exit_code = 1;
        goto exit;
    }
    pending_jobs = shm_attach(pending_jobs_shm_handle);
    if ((intptr_t) pending_jobs == -1) {
        perror("Spooler: Could not attach pending jobs queue shared memory");
        exit_code = 1;
        pending_jobs = nullptr;
        goto exit;
    }
    queue_init(pending_jobs);

    printing_jobs_shm_handle = shm_create(PRINTING_JOBS_SHM_KEY, sizeof(struct PrintJob[PRINTER_COUNT]));
    if (printing_jobs_shm_handle == -1) {
        perror("Spooler: Could not create printing jobs shared memory");
        exit_code = 1;
        goto exit;
    }
    printing_jobs = shm_attach(printing_jobs_shm_handle);
    if ((intptr_t) printing_jobs == -1) {
        perror("Spooler: Could not attach printing jobs shared memory");
        exit_code = 1;
        printing_jobs = nullptr;
        goto exit;
    }

    pending_jobs_mutex = sem_create(PENDING_JOBS_MUTEX_SEM_KEY);
    if (pending_jobs_mutex == -1) {
        perror("Spooler: Could not create pending jobs mutex semaphore");
        exit_code = 1;
        goto exit;
    }
    if (sem_set(pending_jobs_mutex, 1) == -1) {
        perror("Spooler: Could not initialize pending jobs mutex semaphore");
        exit_code = 1;
        goto exit;
    }

    pending_jobs_free = sem_create(PENDING_JOBS_FREE_SEM_KEY);
    if (pending_jobs_free == -1) {
        perror("Spooler: Could not create pending jobs free semaphore");
        exit_code = 1;
        goto exit;
    }
    if (sem_set(pending_jobs_free, QUEUE_SIZE) == -1) {
        perror("Spooler: Could not initialize pending jobs free semaphore");
        exit_code = 1;
        goto exit;
    }

    pending_jobs_waiting = sem_create(PENDING_JOBS_WAITING_SEM_KEY);
    if (pending_jobs_waiting == -1) {
        perror("Spooler: Could not create pending jobs waiting semaphore");
        exit_code = 1;
        goto exit;
    }
    if (sem_set(pending_jobs_waiting, 0) == -1) {
        perror("Spooler: Could not initialize pending jobs waiting semaphore");
        exit_code = 1;
        goto exit;
    }

    printer_ready = semset_create(PRINTER_READY_SEM_KEY, PRINTER_COUNT);
    if (printer_ready == -1) {
        perror("Spooler: Could not create printer ready semaphore");
        exit_code = 1;
        goto exit;
    }
    if (semset_set_all(printer_ready, (unsigned short[]){0, 0}) == -1) {
        perror("Spooler: Could not initialize printer ready semaphore");
        exit_code = 1;
        goto exit;
    }

    printer_busy = semset_create(PRINTER_BUSY_SEM_KEY, PRINTER_COUNT);
    if (printer_busy == -1) {
        perror("Spooler: Could not create printer busy semaphore");
        exit_code = 1;
        goto exit;
    }
    if (semset_set_all(printer_busy, (unsigned short[]){0, 0}) == -1) {
        perror("Spooler: Could not initialize printer busy semaphore");
        exit_code = 1;
        goto exit;
    }

    printf("Spooler: Initialized\n");

    // Main loop
    while (!should_terminate) {
        printf("Spooler: Waiting for pending print jobs\n");
        if (sem_wait(pending_jobs_waiting) == -1) {
            // EINTR means the wait operation was interrupted by a signal
            if (errno == EINTR && should_terminate) {
                break;
            }
            perror("Spooler: Could not wait for pending print jobs");
            exit_code = 2;
            break;
        }

        printf("Spooler: Waiting for printer %d to be available\n", current_printer_id);
        if (semset_wait(printer_ready, current_printer_id) == -1) {
            if (errno == EINTR && should_terminate) {
                break;
            }
            perror("Spooler: Could not wait for printer");
            exit_code = 2;
            break;
        }

        printf("Spooler: Waiting for access to pending jobs queue\n");
        if (sem_wait(pending_jobs_mutex) == -1) {
            if (errno == EINTR && should_terminate) {
                break;
            }
            perror("Spooler: Could not wait for access to pending jobs queue");
            exit_code = 2;
            break;
        }
        struct PrintJob current_job;
        if (queue_get(pending_jobs, &current_job) == -1) {
            printf("Spooler: Could not get first item of pending jobs queue: Queue is empty\n");
            exit_code = 2;
            break;
        }
        printing_jobs[current_printer_id] = current_job;
        if (sem_signal(pending_jobs_mutex) == -1) {
            perror("Spooler: Could not release access to pending jobs queue");
            exit_code = 2;
            break;
        }
        printf(
            "Spooler: Wrote print job to printer %d (data: %d, pages: %d)\n",
            current_printer_id,
            current_job.data,
            current_job.pageCount);

        printf("Spooler: Signaling free slot in pending job queue\n");
        if (sem_signal(pending_jobs_free) == -1) {
            perror("Spooler: Could not signal a free space in pending job queue");
            exit_code = 2;
            break;
        }

        printf("Spooler: Signaling new print job to printer %d\n", current_printer_id);
        if (semset_signal(printer_busy, current_printer_id) == -1) {
            perror("Spooler: Could not signal new job to printer");
            exit_code = 2;
            break;
        }

        current_printer_id = (current_printer_id + 1) % PRINTER_COUNT;
    }

    // Cleanup
exit:
    printf("Spooler: Cleaning up resources\n");

    if (pending_jobs != nullptr && shm_detach(pending_jobs) == -1) {
        perror("Spooler: Could not detach pending jobs queue shared memory");
    }
    if (pending_jobs_shm_handle != -1 && shm_delete(pending_jobs_shm_handle) == -1) {
        perror("Spooler: Could not delete pending jobs queue shared memory");
    }

    if (printing_jobs != nullptr && shm_detach(printing_jobs) == -1) {
        perror("Spooler: Could not detach printing jobs shared memory");
    }
    if (printing_jobs_shm_handle != -1 && shm_delete(printing_jobs_shm_handle) == -1) {
        perror("Spooler: Could not delete printing jobs shared memory");
    }

    if (pending_jobs_mutex != -1 && sem_delete(pending_jobs_mutex) == -1) {
        perror("Spooler: Could not delete pending jobs mutex semaphore");
    }

    if (pending_jobs_free != -1 && sem_delete(pending_jobs_free) == -1) {
        perror("Spooler: Could not delete pending jobs free semaphore");
    }

    if (pending_jobs_waiting != -1 && sem_delete(pending_jobs_waiting) == -1) {
        perror("Spooler: Could not delete pending jobs waiting semaphore");
    }

    if (printer_ready != -1 && sem_delete(printer_ready) == -1) {
        perror("Spooler: Could not delete printer ready semaphore");
    }

    if (printer_busy != -1 && sem_delete(printer_busy) == -1) {
        perror("Spooler: Could not delete printer busy semaphore");
    }

    printf("Spooler: Exiting with code %d (PID was %d)\n", exit_code, getpid());
    return exit_code;
}

int printer(const int printer_id) {
    // Initialization
    printf("Printer %d: Started with PID %d\n", printer_id, getpid());
    printf("Printer %d: Initializing\n", printer_id);

    int exit_code = 0;
    struct PrintJob *printing_jobs = nullptr;

    struct sigaction sa;
    sa.sa_handler = loop_signal_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    if (sigaction(SIGINT, &sa, nullptr) == -1) {
        char perror_msg[128];
        snprintf(perror_msg, sizeof(perror_msg), "Printer %d: Could not install SIGINT handler", printer_id);
        perror(perror_msg);
        exit_code = 1;
        goto exit;
    }
    if (sigaction(SIGTERM, &sa, nullptr) == -1) {
        char perror_msg[128];
        snprintf(perror_msg, sizeof(perror_msg), "Printer %d: Could not install SIGTERM handler", printer_id);
        perror(perror_msg);
        exit_code = 1;
        goto exit;
    }

    const int printing_jobs_shm_handle = shm_get_handle(PRINTING_JOBS_SHM_KEY);
    if (printing_jobs_shm_handle == -1) {
        char perror_msg[128];
        snprintf(perror_msg, sizeof(perror_msg), "Printer %d: Could not get printing jobs shared memory", printer_id);
        perror(perror_msg);
        exit_code = 1;
        goto exit;
    }
    printing_jobs = shm_attach(printing_jobs_shm_handle);
    if ((intptr_t) printing_jobs == -1) {
        char perror_msg[128];
        snprintf(
            perror_msg,
            sizeof(perror_msg),
            "Printer %d: Could not attach printing jobs shared memory",
            printer_id);
        perror(perror_msg);
        exit_code = 1;
        printing_jobs = nullptr;
        goto exit;
    }

    const int printer_ready = sem_get_handle(PRINTER_READY_SEM_KEY);
    if (printer_ready == -1) {
        char perror_msg[128];
        snprintf(perror_msg, sizeof(perror_msg), "Printer %d: Could not get printer ready semaphore", printer_id);
        perror(perror_msg);
        exit_code = 1;
        goto exit;
    }

    const int printer_busy = sem_get_handle(PRINTER_BUSY_SEM_KEY);
    if (printer_busy == -1) {
        char perror_msg[128];
        snprintf(perror_msg, sizeof(perror_msg), "Printer %d: Could not get printer busy semaphore", printer_id);
        perror(perror_msg);
        exit_code = 1;
        goto exit;
    }

    printf("Printer %d: Initialized\n", printer_id);

    // Main loop
    printf("Printer %d: Ready\n", printer_id);
    if (semset_signal(printer_ready, printer_id) == -1) {
        char perror_msg[128];
        snprintf(perror_msg, sizeof(perror_msg), "Printer %d: Could not signal readiness", printer_id);
        perror(perror_msg);
        exit_code = 1;
        goto exit;
    }

    while (!should_terminate) {
        printf("Printer %d: Waiting for job\n", printer_id);
        if (semset_wait(printer_busy, printer_id) == -1) {
            if (errno == EINTR && should_terminate) {
                break;
            }
            char perror_msg[128];
            snprintf(perror_msg, sizeof(perror_msg), "Printer %d: Could not wait for job", printer_id);
            perror(perror_msg);
            exit_code = 2;
            break;
        }
        const struct PrintJob print_job = printing_jobs[printer_id];

        // Printing: 1 Minute / page
        for (int page = 0; page < print_job.pageCount; page++) {
            printf("Printer %d: Printing page %d (data: %d)\n", printer_id, page, print_job.data);

            if (sleep(1 * MINUTE) != 0 && should_terminate) {
                printf("Printer %d: Could not sleep\n", printer_id);
                break;
            }
        }

        printf("Printer %d: Finished printing\n", printer_id);
        if (semset_signal(printer_ready, printer_id) == -1) {
            char perror_msg[128];
            snprintf(perror_msg, sizeof(perror_msg), "Printer %d: Could not signal readiness", printer_id);
            perror(perror_msg);
            exit_code = 2;
            break;
        }
    }

    // Cleanup
exit:
    printf("Printer %d: Cleaning up resources\n", printer_id);

    if (printing_jobs != nullptr && shm_detach(printing_jobs) == -1) {
        char perror_msg[128];
        snprintf(
            perror_msg,
            sizeof(perror_msg),
            "Printer %d: Could not detach printing jobs shared memory",
            printer_id);
        perror(perror_msg);
    }

    printf("Printer %d: Exiting with code %d (PID was %d)\n", printer_id, exit_code, getpid());
    return exit_code;
}

// Sends a print job to the spooler. Returns 0 on success or -1 on error
int print(const struct PrintJob print_job) {
    // Initialization
    const pid_t pid = getpid();
    printf("print() for application %d: Initializing\n", pid);

    int exit_code = 0;
    struct Queue *pending_jobs = nullptr;

    const int pending_jobs_shm_handle = shm_get_handle(SHARED_MEMORY_KEY);
    if (pending_jobs_shm_handle == -1) {
        char perror_msg[128];
        snprintf(
            perror_msg,
            sizeof(perror_msg),
            "print() for application %d: Could not get pending jobs queue shared memory",
            pid);
        perror(perror_msg);
        exit_code = -1;
        goto exit;
    }
    pending_jobs = shm_attach(pending_jobs_shm_handle);
    if ((intptr_t) pending_jobs == -1) {
        char perror_msg[128];
        snprintf(
            perror_msg,
            sizeof(perror_msg),
            "print() for application %d: Could not attach pending jobs queue shared memory",
            pid);
        perror(perror_msg);
        exit_code = -1;
        pending_jobs = nullptr;
        goto exit;
    }

    const int pending_jobs_mutex = sem_get_handle(PENDING_JOBS_MUTEX_SEM_KEY);
    if (pending_jobs_mutex == -1) {
        char perror_msg[128];
        snprintf(
            perror_msg,
            sizeof(perror_msg),
            "print() for application %d: Could not get pending jobs mutex semaphore",
            pid);
        perror(perror_msg);
        exit_code = -1;
        goto exit;
    }

    const int pending_jobs_free = sem_get_handle(PENDING_JOBS_FREE_SEM_KEY);
    if (pending_jobs_free == -1) {
        char perror_msg[128];
        snprintf(
            perror_msg,
            sizeof(perror_msg),
            "print() for application %d: Could not get pending jobs free semaphore",
            pid);
        perror(perror_msg);
        exit_code = -1;
        goto exit;
    }

    const int pending_jobs_waiting = sem_get_handle(PENDING_JOBS_WAITING_SEM_KEY);
    if (pending_jobs_waiting == -1) {
        char perror_msg[128];
        snprintf(
            perror_msg,
            sizeof(perror_msg),
            "print() for application %d: Could not get pending jobs waiting semaphore",
            pid);
        perror(perror_msg);
        exit_code = -1;
        goto exit;
    }

    printf("print() for application %d: Initialized\n", pid);

    // Main function
    printf("print() for application %d: Waiting for free slot in pending jobs queue\n", pid);
    if (sem_wait(pending_jobs_free) == -1) {
        char perror_msg[128];
        snprintf(
            perror_msg,
            sizeof(perror_msg),
            "print() for application %d: Could not wait for free slot in pending jobs queue",
            pid);
        perror(perror_msg);
        exit_code = -1;
        goto exit;
    }

    printf("print() for application %d: Waiting for access to pending jobs queue\n", pid);
    if (sem_wait(pending_jobs_mutex) == -1) {
        char perror_msg[128];
        snprintf(
            perror_msg,
            sizeof(perror_msg),
            "print() for application %d: Could not wait for access to pending jobs queue",
            pid);
        perror(perror_msg);
        exit_code = -1;
        goto exit;
    }

    if (queue_put(pending_jobs, print_job) == -1) {
        printf("print() for application %d: Could not put job into queue: Queue is full\n", pid);
        exit_code = -1;
        goto exit;
    }

    if (sem_signal(pending_jobs_mutex) == -1) {
        char perror_msg[128];
        snprintf(
            perror_msg,
            sizeof(perror_msg),
            "print() for application %d: Could not release access for pending jobs queue",
            pid);
        perror(perror_msg);
        exit_code = -1;
        goto exit;
    }
    printf("print() for application %d: Wrote print job to queue\n", pid);

    printf("print() for application %d: Signaling waiting print job to spooler\n", pid);
    if (sem_signal(pending_jobs_waiting) == -1) {
        char perror_msg[128];
        snprintf(
            perror_msg,
            sizeof(perror_msg),
            "print() for application %d: Could not signal new job to spooler",
            pid);
        perror(perror_msg);
        exit_code = -1;
        goto exit;
    }

    // Cleanup
exit:
    printf("print() for application %d: Cleaning up resources\n", pid);

    if (pending_jobs != nullptr && shm_detach(pending_jobs) == -1) {
        char perror_msg[128];
        snprintf(
            perror_msg,
            sizeof(perror_msg),
            "print() for application %d: Could not detach pending jobs queue shared memory",
            pid);
        perror(perror_msg);
    }

    printf("print() for application %d: Returning with %s\n", pid, exit_code == 0 ? "success" : "failure");
    return exit_code;
}

int application(int application_id) {
    const pid_t pid = getpid();
    printf("Application %d: Started with PID %d\n", application_id, pid);

    struct PrintJob print_job;
    print_job.pageCount = rand_range(2, 6);
    print_job.data = rand();

    printf(
        "Application %d: Printing job with %d pages and data of %d\n",
        application_id,
        print_job.pageCount,
        print_job.data);

    if (print(print_job) == -1) {
        printf("Application %d: Error while printing\n", application_id);
        printf("Application %d: Exiting with code 1 (PID was %d)\n", application_id, pid);
        return 1;
    }

    printf("Application %d: Finished printing\n", application_id);
    printf("Application %d: Exiting with code 0 (PID was %d)\n", application_id, pid);
    return 0;
}

int main(void) {
    printf("Main: Started with PID %d\n", getpid());

    struct sigaction sa;
    sa.sa_handler = main_signal_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    if (sigaction(SIGINT, &sa, nullptr) == -1) {
        perror("Main: Could not install SIGINT handler");
        return 1;
    }
    if (sigaction(SIGTERM, &sa, nullptr) == -1) {
        perror("Main: Could not install SIGTERM handler");
        return 1;
    }

    sranddev(); // Initializes the random number generator with a random seed

    printf("Main: Starting spooler\n");
    const pid_t spooler_pid = fork();
    if (spooler_pid == -1) {
        perror("Main: Could not fork spooler process");
        return 1;
    }
    if (spooler_pid == 0) {
        return spooler();
    }
    printf("Main: Started spooler with PID %d\n", spooler_pid);

    for (int printer_id = 0; printer_id < PRINTER_COUNT; printer_id++) {
        printf("Main: Starting printer %d (%d out of %d)\n", printer_id, printer_id + 1, PRINTER_COUNT);

        const pid_t printer_pid = fork();
        if (printer_pid == -1) {
            perror("Main: Could not fork printer process");
            return 1;
        }
        if (printer_pid == 0) {
            return printer(printer_id);
        }

        printf(
            "Main: Started printer %d (%d out of %d) with PID %d\n",
            printer_id,
            printer_id + 1,
            PRINTER_COUNT,
            printer_pid);
    }

    for (int application_id = 0; application_id < APPLICATION_COUNT; application_id++) {
        const int delay = rand_range(0, 4);
        printf(
            "Main: Waiting %d minutes before starting application %d (%d out of %d)\n",
            delay,
            application_id,
            application_id + 1,
            APPLICATION_COUNT);
        if (sleep(delay * MINUTE) != 0) {
            printf("Main: Could not sleep\n");
            break;
        }

        const pid_t application_pid = fork();
        if (application_pid == -1) {
            perror("Main: Could not fork application process");
            return 1;
        }
        if (application_pid == 0) {
            return application(application_id);
        }

        printf(
            "Main: Started application %d (%d out of %d) with PID %d\n",
            application_id,
            application_id + 1,
            APPLICATION_COUNT,
            application_pid);
    }

    for (int i = 0; i < TOTAL_CHILD_PROCESS_COUNT; i++) {
        int status;
        pid_t pid;

        // Retry if wait was interrupted by signal
        while ((pid = wait(&status)) == -1 && errno == EINTR) {}

        if (pid == -1) {
            if (errno == ECHILD) {
                break;
            }

            perror("Main: Could not wait for child process to exit");
        }

        if (WIFEXITED(status)) {
            printf(
                "Main: Child process %d exited with status %d (%d out of %d)\n",
                pid,
                WEXITSTATUS(status),
                i + 1,
                TOTAL_CHILD_PROCESS_COUNT);
        } else {
            printf(
                "Main: Child process %d exited with signal %d (%d out of %d)\n",
                pid,
                WTERMSIG(status),
                i + 1,
                TOTAL_CHILD_PROCESS_COUNT);
        }
    }

    return 0;
}
