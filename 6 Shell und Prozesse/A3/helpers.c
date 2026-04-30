#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/types.h>

// Creates n semaphores and returns the handle, or -1 if the creation failed
int sem_create(const int n) {
    return semget(IPC_PRIVATE, n, 0666 | IPC_CREAT);
}

// Deletes all semaphores associated with the handle and returns 0 on success and -1 on failure
int sem_delete(const int handle) {
    return semctl(handle, 0, IPC_RMID);
}

// Waits for the specified semaphore. Returns 0 on success and -1 on failure
int sem_wait(const int handle, const int n) {
    struct sembuf opts;
    opts.sem_num = n;
    opts.sem_op = -1;
    opts.sem_flg = 0;

    return semop(handle, &opts, 1);
}

// Signals the specified semaphore. Returns 0 on success and -1 on failure
int sem_signal(const int handle, const int n) {
    struct sembuf opts;
    opts.sem_num = n;
    opts.sem_op = 1;
    opts.sem_flg = 0;

    return semop(handle, &opts, 1);
}

// Create a shared memory and returns the handle, or -1 if the creation failed
int shm_create(const key_t key, const int size) {
    return shmget(key, size, 0666 | IPC_CREAT);
}

// Attach the shared memory to the process and return the pointer, or -1 on error
void *shm_attach(const int handle) {
    return shmat(handle, nullptr, 0);
}
