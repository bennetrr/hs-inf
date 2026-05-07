#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../shm_helpers.c"

#define SHARED_MEMORY_KEY 0x18AF4BE6

int child_process(const int shared_memory_handle, const int iterations) {
    const int *shared_memory = shm_attach(shared_memory_handle);
    if ((intptr_t) shared_memory == -1) {
        perror("Reader: Could not attach shared memory");
    }

    for (int i = 0; i < iterations; ++i) {
        printf("Reader %d: %d\n", i, *shared_memory);
    }

    if (shm_detach(shared_memory) == -1) {
        perror("Reader: Could not detach shared memory");
        return 1;
    }

    return 0;
}

int main(const int argc, const char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: <ITERATIONS> <SEED>\n");
        return 1;
    }

    const int iterations = atoi(argv[1]);
    const int seed = atoi(argv[2]);
    srand(seed);

    const int shared_memory_handle = shm_create(SHARED_MEMORY_KEY, sizeof(int));
    if (shared_memory_handle == -1) {
        perror("Writer: Could not create shared memory");
        return 1;
    }

    const pid_t child_pid = fork();
    if (child_pid == -1) {
        perror("Writer: Could not fork process");
        if (shm_delete(shared_memory_handle) == -1) {
            perror("Writer: Could not delete shared memory");
        }
        return 1;
    }
    if (child_pid == 0) {
        return child_process(shared_memory_handle, iterations);
    }

    int *shared_memory = shm_attach(shared_memory_handle);
    if ((intptr_t) shared_memory == -1) {
        perror("Writer: Could not attach shared memory");
        if (shm_delete(shared_memory_handle) == -1) {
            perror("Writer: Could not delete shared memory");
        }
        return 1;
    }

    for (int i = 0; i < iterations; ++i) {
        *shared_memory = rand();
        printf("Writer %d: %d\n", i, *shared_memory);
    }

    if (shm_detach(shared_memory) == -1) {
        perror("Could not detach shared memory");
    }
    if (shm_delete(shared_memory_handle) == -1) {
        perror("Could not delete shared memory");
        return 1;
    }
    return 0;
}
