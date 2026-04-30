// ReSharper disable CppDFAEndlessLoop
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(const int argc, const char *argv[]) {
    if (argc != 5) {
        fprintf(stderr, "This program requires 4 arguments\n");
        return 1;
    }

    printf("parent process: pid %d, arg %s\n", getpid(), argv[1]);

    // fork() returns -1 on error, 0 for the child process, and the PID of the child process to the parent process
    const pid_t pid1 = fork();
    if (pid1 == -1) {
        // perror() appends the textual representation of errno to the message
        perror("fork failed");
        return 1;
    }
    if (pid1 == 0) {
        printf("child process 1: pid %d, arg %s\n", getpid(), argv[2]);
        while (true);
    }

    const pid_t pid2 = fork();
    if (pid2 == -1) {
        perror("fork failed");
        return 1;
    }
    if (pid2 == 0) {
        printf("child process 2: pid %d, arg %s\n", getpid(), argv[3]);
        while (true);
    }

    const pid_t pid3 = fork();
    if (pid3 == -1) {
        perror("fork failed");
        return 1;
    }
    if (pid3 == 0) {
        sleep(1);
        printf("child process 3: pid %d, arg %s\n", getpid(), argv[4]);
        return 2;
    }

    sleep(2);

    kill(pid1, SIGTERM);
    kill(pid2, SIGKILL);
    kill(pid3, SIGKILL);
    
    int status1 = 0;
    const pid_t wait_pid1 = wait(&status1);
    printf("child process with PID %d exited with %d\n", wait_pid1, status1);
    
    int status2 = 0;
    const pid_t wait_pid2 = wait(&status2);
    printf("child process with PID %d exited with %d\n", wait_pid2, status2);
    
    int status3 = 0;
    const pid_t wait_pid3 = wait(&status3);
    printf("child process with PID %d exited with %d\n", wait_pid3, status3);

    // Expected outputs:
    // child process 1: 15, because killed with SIGTERM (15)
    // child process 2: 9, because killed with SIGKILL (9)
    // child process 3: 512, because normal exit with code 2, and normal exit codes are shifted left by 8 bits
    return 0;
}
