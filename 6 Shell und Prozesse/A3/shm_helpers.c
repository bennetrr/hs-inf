#include <sys/shm.h>

// Creates a shared memory and returns the handle, or -1 if the creation failed
int shm_create(const key_t key, const size_t size) {
    return shmget(key, size, 0666 | IPC_CREAT | IPC_EXCL);
}

// Returns the handle of the shared memory, or -1 if the shared memory does not exist
int shm_get_handle(const key_t key) {
    return shmget(key, 0, 0666);
}

// Deletes the shared memory and returns 0 on success or -1 on error
int shm_delete(const int handle) {
    return shmctl(handle, IPC_RMID, NULL);
}

// Attach the shared memory to the process and return the pointer, or -1 on error
void *shm_attach(const int handle) {
    return shmat(handle, NULL, 0);
}

// Detach the shared memory to the process and return 0 on success or -1 on error
int shm_detach(const void *pointer) {
    return shmdt(pointer);
}
