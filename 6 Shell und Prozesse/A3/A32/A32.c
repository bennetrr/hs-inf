#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../shm_helpers.c"

static constexpr int PENDING_JOBS_SHM_KEY = 424242424;

int child_process(const int shared_memory_handle, const int iterations) {
    const int* shared_memory = shm_attach(shared_memory_handle);

    for (int i = 0; i < iterations; ++i) {
        printf("Leser    %d: %d\n", i, *shared_memory);
    }

    return 0;
}

int main(const int argc, const char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: <ITERATIONS> <SEED>");
        return 1;
    }

    const int iterations = atoi(argv[1]);
    const int seed = atoi(argv[2]);
    srand(seed);

    const int shared_memory_handle = shm_create(PENDING_JOBS_SHM_KEY, sizeof(int));
    if (shared_memory_handle == -1) {
        perror("Could not create shared memory");
        return 1;
    }

    const pid_t child_pid = fork();
    if (child_pid == -1) {
        perror("Could not fork process");
        shm_delete(shared_memory_handle);
        return 1;
    }
    if (child_pid == 0) {
        return child_process(shared_memory_handle, iterations);
    }

    int* shared_memory = shm_attach(shared_memory_handle);

    for (int i = 0; i < iterations; ++i) {
        *shared_memory = rand();
        printf("Schreiber %d: %d\n", i, *shared_memory);
    }

    shm_delete(shared_memory_handle);
    return 0;
}
