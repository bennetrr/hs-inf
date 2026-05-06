#include <sys/sem.h>

// Creates a semaphore set with n semaphores and returns the handle, or -1 if the creation failed
int semset_create(const int key, const int n) {
    return semget(key, n, 0666 | IPC_CREAT);
}

// Sets the value of the semaphore associated with the handle and index. Returns 0 on success and -1 on failure
int semset_set(const int handle, const int n, const int value) {
    union semun opts;
    opts.val = value;
    return semctl(handle, n, SETVAL, opts);
}

// Sets the values of all n semaphores associated with the handle. Returns 0 on success and -1 on failure
int semset_set_all(const int handle, unsigned short values[]) {
    union semun opts;
    opts.array = values;
    return semctl(handle, 0, SETALL, opts);
}

// Waits for the specified semaphore. Returns 0 on success and -1 on failure
int semset_wait(const int handle, const int n) {
    struct sembuf opts;
    opts.sem_num = n;
    opts.sem_op = -1;
    opts.sem_flg = 0;

    return semop(handle, &opts, 1);
}

// Signals the specified semaphore. Returns 0 on success and -1 on failure
int semset_signal(const int handle, const int n) {
    struct sembuf opts;
    opts.sem_num = n;
    opts.sem_op = 1;
    opts.sem_flg = 0;

    return semop(handle, &opts, 1);
}

// Creates one semaphore and returns the handle, or -1 if the creation failed
int sem_create(const int key) {
    return semset_create(key, 1);
}

// Returns the handle of the semaphore or semaphore set, or -1 if the semaphore does not exist
int sem_get_handle(const int key) {
    return semget(key, 0, 0666);
}

// Deletes all semaphores associated with the handle and returns 0 on success and -1 on failure
int sem_delete(const int handle) {
    return semctl(handle, 0, IPC_RMID);
}

// Sets the value of the semaphore associated with the handle. Returns 0 on success and -1 on failure
int sem_set(const int handle, const int value) {
    return semset_set(handle, 0, value);
}

// Waits for the specified semaphore. Returns 0 on success and -1 on failure
int sem_wait(const int handle) {
    return semset_wait(handle, 0);
}

// Signals the specified semaphore. Returns 0 on success and -1 on failure
int sem_signal(const int handle) {
    return semset_signal(handle, 0);
}
