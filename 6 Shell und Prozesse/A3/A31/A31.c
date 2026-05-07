#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

#include "../sem_helpers.c"

#define SEM_NOTIFY_CHILD 0
#define SEM_NOTIFY_PARENT 1

int child_process(const int sem_handle) {
    printf("Child:  Waiting for notification from parent\n");
    if (semset_wait(sem_handle, SEM_NOTIFY_CHILD) == -1) {
        perror("Child:  Could not wait for notification from parent");
        return 1;
    }
    printf("Child:  Notification from parent received\n");

    printf("Child:  Press enter to continue\n");
    getchar();

    printf("Child:  Notifying parent\n");
    if (semset_signal(sem_handle, SEM_NOTIFY_PARENT) == -1) {
        perror("Child:  Could not notify parent");
        return 1;
    }

    printf("Child:  Exiting\n");
    return 0;
}

int main(void) {
    const int sem_handle = semset_create(IPC_PRIVATE, 2);
    if (sem_handle == -1) {
        perror("Parent: Could not create semaphore");
        return 1;
    }
    if (semset_set_all(sem_handle, (unsigned short[]){0, 0}) == -1) {
        perror("Parent: Could not initialize semaphore");
        return 1;
    }

    const pid_t child_pid = fork();
    if (child_pid == -1) {
        perror("Parent: Could not fork process");
        return 1;
    }
    if (child_pid == 0) {
        return child_process(sem_handle);
    }

    printf("Parent: Press enter to continue\n");
    getchar();

    printf("Parent: Notifying child\n");
    if (semset_signal(sem_handle, SEM_NOTIFY_CHILD) == -1) {
        perror("Parent: Could not notify child");
        return 1;
    }

    printf("Parent: Waiting for notification from child\n");
    if (semset_wait(sem_handle, SEM_NOTIFY_PARENT) == -1) {
        perror("Parent: Could not wait for notification from child");
        return 1;
    }
    printf("Parent: Notification from child received\n");

    printf("Parent: Waiting for child to exit\n");
    if (wait(NULL) == -1) {
        perror("Parent: Could not wait for child to exit");
        return 1;
    }

    printf("Parent: Exiting\n");
    if (sem_delete(sem_handle) == -1) {
        perror("Parent: Could not delete semaphore");
        return 1;
    }
    return 0;
}
