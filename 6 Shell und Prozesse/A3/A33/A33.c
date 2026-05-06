#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../sem_helpers.c"
#include "../shm_helpers.c"

static constexpr int MINUTE = 60;
static constexpr int APPLICATION_COUNT = 5;
static constexpr size_t QUEUE_SIZE = 5;
static constexpr int PRINTER_COUNT = 2;
static constexpr int TOTAL_CHILD_PROCESS_COUNT = APPLICATION_COUNT + PRINTER_COUNT + 1;

static constexpr int PENDING_JOBS_SHM_KEY = 424242424;
static constexpr int PRINTING_JOBS_SHM_KEY = 434343434;
static constexpr int PENDING_JOBS_MUTEX_SEM_KEY = 444444444;
static constexpr int PENDING_JOBS_FREE_SEM_KEY = 454545454;
static constexpr int PENDING_JOBS_WAITING_SEM_KEY = 464646464;
static constexpr int PRINTER_MUTEX_SEM_KEY = 474747474;

static volatile bool should_terminate = false;

void loop_signal_handler(const int signal) {
    printf("Child process %d: Received signal %d\n", getpid(), signal);
    should_terminate = true;
}

void main_signal_handler(const int signal) {
    printf("Main: Received signal %d", signal);

    if (kill(0, SIGTERM) == -1) { // This sends SIGTERM to all child processes
        perror("Main: Could not terminate child processes");
    }
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
    int printer_mutex = -1;
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

    pending_jobs_shm_handle = shm_create(PENDING_JOBS_SHM_KEY, sizeof(struct Queue));
    if (pending_jobs_shm_handle == -1) {
        perror("Spooler: Could not create shared memory");
        exit_code = 1;
        goto exit;
    }
    pending_jobs = shm_attach(pending_jobs_shm_handle);
    if ((intptr_t) pending_jobs == -1) {
        perror("Spooler: Could not attach shared memory");
        exit_code = 1;
        pending_jobs = nullptr;
        goto exit;
    }
    queue_init(pending_jobs);

    printing_jobs_shm_handle = shm_create(PRINTING_JOBS_SHM_KEY, sizeof(struct PrintJob[PRINTER_COUNT]));
    if (printing_jobs_shm_handle == -1) {
        perror("Spooler: Could not create shared memory");
        exit_code = 1;
        goto exit;
    }
    printing_jobs = shm_attach(printing_jobs_shm_handle);
    if ((intptr_t) printing_jobs == -1) {
        perror("Spooler: Could not attach shared memory");
        exit_code = 1;
        printing_jobs = nullptr;
        goto exit;
    }

    pending_jobs_mutex = sem_create(PENDING_JOBS_MUTEX_SEM_KEY);
    if (pending_jobs_mutex == -1) {
        perror("Spooler: Could not create semaphore");
        exit_code = 1;
        goto exit;
    }
    if (sem_set(pending_jobs_mutex, 1) == -1) {
        perror("Spooler: Could not initialize semaphore");
        exit_code = 1;
        goto exit;
    }

    pending_jobs_free = sem_create(PENDING_JOBS_FREE_SEM_KEY);
    if (pending_jobs_free == -1) {
        perror("Spooler: Could not create semaphore");
        exit_code = 1;
        goto exit;
    }
    if (sem_set(pending_jobs_free, QUEUE_SIZE) == -1) {
        perror("Spooler: Could not initialize semaphore");
        exit_code = 1;
        goto exit;
    }

    pending_jobs_waiting = sem_create(PENDING_JOBS_WAITING_SEM_KEY);
    if (pending_jobs_waiting == -1) {
        perror("Spooler: Could not create semaphore");
        exit_code = 1;
        goto exit;
    }
    if (sem_set(pending_jobs_waiting, 0) == -1) {
        perror("Spooler: Could not initialize semaphore");
        exit_code = 1;
        goto exit;
    }

    printer_mutex = semset_create(PRINTER_MUTEX_SEM_KEY, PRINTER_COUNT);
    if (printer_mutex == -1) {
        perror("Spooler: Could not create semaphore");
        exit_code = 1;
        goto exit;
    }
    if (semset_set_all(printer_mutex, (unsigned short[]){0, 0}) == -1) {
        perror("Spooler: Could not initialize semaphore");
        exit_code = 1;
        goto exit;
    }

    printf("Spooler: Initialized\n");

    // Main loop
    while (!should_terminate) {
        printf("Spooler: Waiting for pending print jobs\n");
        sem_wait(pending_jobs_waiting);

        printf("Spooler: Waiting for printer %d to be available\n", current_printer_id);
        semset_wait(printer_mutex, current_printer_id);

        printf("Spooler: Waiting for access to pending jobs queue\n");
        sem_wait(pending_jobs_mutex);
        struct PrintJob current_job;
        queue_get(pending_jobs, &current_job);
        printing_jobs[current_printer_id] = current_job;
        sem_signal(pending_jobs_mutex);
        printf("Spooler: Wrote print job to printer %d (data: %d, pages: %d)\n", current_printer_id, current_job.data, current_job.pageCount);

        printf("Spooler: Signaling free space in pending job queue\n");
        sem_signal(pending_jobs_free);
        printf("Spooler: Signaling new print job to printer %d\n", current_printer_id);
        semset_signal(printer_mutex, current_printer_id);

        current_printer_id = (current_printer_id + 1) % PRINTER_COUNT;
    }

    // Cleanup
exit:
    printf("Spooler: Cleaning up resources\n");

    if (killpg(getppid(), SIGTERM) == -1) {
        perror("Spooler: Could not terminate sibling processes");
    }

    if (pending_jobs != nullptr && shm_detach(pending_jobs) == -1) {
        perror("Spooler: Could not detach shared memory");
    }
    if (pending_jobs_shm_handle != -1 && shm_delete(pending_jobs_shm_handle) == -1) {
        perror("Spooler: Could not delete shared memory");
    }

    if (printing_jobs != nullptr && shm_detach(printing_jobs) == -1) {
        perror("Spooler: Could not detach shared memory");
    }
    if (printing_jobs_shm_handle != -1 && shm_delete(printing_jobs_shm_handle) == -1) {
        perror("Spooler: Could not delete shared memory");
    }

    if (pending_jobs_mutex != -1 && sem_delete(pending_jobs_mutex) == -1) {
        perror("Spooler: Could not delete semaphore");
    }

    if (pending_jobs_free != -1 && sem_delete(pending_jobs_free) == -1) {
        perror("Spooler: Could not delete semaphore");
    }

    if (pending_jobs_waiting != -1 && sem_delete(pending_jobs_waiting) == -1) {
        perror("Spooler: Could not delete semaphore");
    }

    if (printer_mutex != -1 && sem_delete(printer_mutex) == -1) {
        perror("Spooler: Could not delete semaphore");
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
        snprintf(perror_msg, sizeof(perror_msg), "Printer %d: Could not get shared memory", printer_id);
        perror(perror_msg);
        exit_code = 1;
        goto exit;
    }
    printing_jobs = shm_attach(printing_jobs_shm_handle);
    if ((intptr_t) printing_jobs == -1) {
        char perror_msg[128];
        snprintf(perror_msg, sizeof(perror_msg), "Printer %d: Could not attach shared memory", printer_id);
        perror(perror_msg);
        exit_code = 1;
        printing_jobs = nullptr;
        goto exit;
    }

    const int printer_mutex = sem_get_handle(PRINTER_MUTEX_SEM_KEY);
    if (printer_mutex == -1) {
        char perror_msg[128];
        snprintf(perror_msg, sizeof(perror_msg), "Printer %d: Could not get semaphore", printer_id);
        perror(perror_msg);
        exit_code = 1;
        goto exit;
    }

    printf("Printer %d: Initialized\n", printer_id);

    // Main loop
    while (!should_terminate) {
        printf("Printer %d: Waiting for job\n", printer_id);
        semset_wait(printer_mutex, printer_id);
        const struct PrintJob print_job = printing_jobs[printer_id];

        // Printing: 1 Minute / page
        for (int page = 0; page < print_job.pageCount; page++) {
            printf("Printer %d: Printing page %d (data: %d)\n", printer_id, page, print_job.data);
            sleep(1 * MINUTE);
        }

        printf("Printer %d: Finished printing\n", printer_id);
        semset_signal(printer_mutex, printer_id);
    }

    // Cleanup
exit:
    printf("Printer %d: Cleaning up resources\n", printer_id);

    if (printing_jobs != nullptr && shm_detach(printing_jobs) == -1) {
        char perror_msg[128];
        snprintf(perror_msg, sizeof(perror_msg), "Printer %d: Could not detach shared memory", printer_id);
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

    const int pending_jobs_shm_handle = shm_get_handle(PENDING_JOBS_SHM_KEY);
    if (pending_jobs_shm_handle == -1) {
        char perror_msg[128];
        snprintf(perror_msg, sizeof(perror_msg), "print() for application %d: Could not create shared memory", pid);
        perror(perror_msg);
        exit_code = -1;
        goto exit;
    }
    pending_jobs = shm_attach(pending_jobs_shm_handle);
    if ((intptr_t) pending_jobs == -1) {
        char perror_msg[128];
        snprintf(perror_msg, sizeof(perror_msg), "print() for application %d: Could not attach shared memory", pid);
        perror(perror_msg);
        exit_code = -1;
        pending_jobs = nullptr;
        goto exit;
    }

    const int pending_jobs_mutex = sem_create(PENDING_JOBS_MUTEX_SEM_KEY);
    if (pending_jobs_mutex == -1) {
        char perror_msg[128];
        snprintf(perror_msg, sizeof(perror_msg), "print() for application %d: Could not create semaphore", pid);
        perror(perror_msg);
        exit_code = -1;
        goto exit;
    }

    const int pending_jobs_free = sem_create(PENDING_JOBS_FREE_SEM_KEY);
    if (pending_jobs_free == -1) {
        char perror_msg[128];
        snprintf(perror_msg, sizeof(perror_msg), "print() for application %d: Could not create semaphore", pid);
        perror(perror_msg);
        exit_code = -1;
        goto exit;
    }

    const int pending_jobs_waiting = sem_create(PENDING_JOBS_WAITING_SEM_KEY);
    if (pending_jobs_waiting == -1) {
        char perror_msg[128];
        snprintf(perror_msg, sizeof(perror_msg), "print() for application %d: Could not create semaphore", pid);
        perror(perror_msg);
        exit_code = -1;
        goto exit;
    }

    printf("print() for application %d: Initialized\n", pid);

    // Main function
    printf("print() for application %d: Waiting for space in pending jobs queue\n", pid);
    sem_wait(pending_jobs_free);

    printf("print() for application %d: Waiting for access to pending jobs queue\n", pid);
    sem_wait(pending_jobs_mutex);
    queue_put(pending_jobs, print_job);
    sem_signal(pending_jobs_mutex);
    printf("print() for application %d: Wrote print job to queue\n", pid);

    printf("print() for application %d: Signaling waiting print job to spooler\n", pid);
    sem_signal(pending_jobs_waiting);

    // Cleanup
exit:
    printf("print() for application %d: Cleaning up resources\n", pid);

    if (pending_jobs != nullptr && shm_detach(pending_jobs) == -1) {
        char perror_msg[128];
        snprintf(perror_msg, sizeof(perror_msg), "print() for application %d: Could not detach shared memory", pid);
        perror(perror_msg);
    }

    printf("print() for application %d: Returning with %s\n", pid, exit_code == 0 ? "success" : "failure");
    return exit_code;
}

int application() {
    const pid_t pid = getpid();
    printf("Application %d: Started\n", pid);

    struct PrintJob print_job;
    print_job.pageCount = rand_range(2, 6);
    print_job.data = rand();

    printf("Application %d: Printing job with %d pages and data of %d\n", pid, print_job.pageCount, print_job.data);

    if (print(print_job) == -1) {
        printf("Application %d: Error while printing\n", pid);
        printf("Application %d: Exiting with code 1\n", pid);
        return 1;
    }

    printf("Application %d: Finished printing\n", pid);
    printf("Application %d: Exiting with code 0\n", pid);
    return 0;
}

int main(void) {
    sranddev(); // Initializes the random number generator with a random seed

    printf("Main: Starting spooler\n");
    const pid_t spooler_pid = fork();
    if (spooler_pid == -1) {
        perror("Main: Could not fork spooler process");
        return -1;
    }
    if (spooler_pid == 0) {
        return spooler();
    }
    printf("Main: Started spooler with PID %d\n", spooler_pid);

    for (int printer_id = 0; printer_id < PRINTER_COUNT; printer_id++) {
        const pid_t printer_pid = fork();
        if (printer_pid == -1) {
            perror("Main: Could not fork printer process");
            return -1;
        }
        if (printer_pid == 0) {
            return printer(printer_id);
        }

        printf("Main: Started printer %d out of %d with PID %d\n", printer_id, PRINTER_COUNT, spooler_pid);
    }

    for (int application_id = 0; application_id < APPLICATION_COUNT; application_id++) {
        const int delay = rand_range(0, 4);
        printf("Main: Waiting %d minutes before starting application %d\n", delay, application_id);
        sleep(delay * MINUTE);

        const pid_t application_pid = fork();
        if (application_pid == -1) {
            perror("Main: Could not fork application process");
            return -1;
        }
        if (application_pid == 0) {
            return application();
        }

        printf("Main: Started application %d out of %d with PID %d\n", application_id, APPLICATION_COUNT, spooler_pid);
    }

    for (int i = 0; i < TOTAL_CHILD_PROCESS_COUNT; i++) {
        int status;
        const pid_t pid = wait(&status);
        if (pid == -1) {
            perror("Main: Could not wait for child process to exit");
        }

        printf("Main: Child process %d exited with status %d\n", pid, status);
    }

    return 0;
}
