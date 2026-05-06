#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

#include "../sem_helpers.c"

static constexpr int SEM_NOTIFY_CHILD = 0;
static constexpr int SEM_NOTIFY_PARENT = 1;

int child_process(const int sem_handle) {
    printf("Child:  Waiting for notification from parent\n");
    semset_wait(sem_handle, SEM_NOTIFY_CHILD);
    printf("Child:  Notification from parent received\n");

    printf("Child:  Press enter to continue\n");
    getchar();

    printf("Child:  Notifying parent\n");
    semset_signal(sem_handle, SEM_NOTIFY_PARENT);

    printf("Child:  Exiting\n");
    return 0;
}

int main(void) {
    const int sem_handle = semset_create(IPC_PRIVATE, 2);
    if (sem_handle == -1) {
        perror("Could not create semaphore");
        return 1;
    }
    if (semset_set_all(sem_handle, (unsigned short[]){ 0, 0 }) == -1) {
        perror("Could not initialize semaphore");
        return 1;
    }

    const pid_t child_pid = fork();
    if (child_pid == -1) {
        perror("Could not fork process");
        return 1;
    }

    if (child_pid == 0) {
        return child_process(sem_handle);
    }

    printf("Parent: Press enter to continue\n");
    getchar();

    printf("Parent: Notifying child\n");
    semset_signal(sem_handle, SEM_NOTIFY_CHILD);

    printf("Parent: Waiting for notification from child\n");
    semset_wait(sem_handle, SEM_NOTIFY_PARENT);
    printf("Parent: Notification from child received\n");

    printf("Parent: Waiting for child to exit\n");
    wait(nullptr);

    printf("Parent: Exiting\n");
    sem_delete(sem_handle);
    return 0;
}
