#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(const int argc, char *argv[]) {
    const pid_t child_pid = fork();
    if (child_pid == -1) {
        perror("fork failed");
        return 1;
    }

    if (child_pid == 0) {
        execv("./A24-child-a.out", argv);
        perror("execv failed");
        return 1;
    }

    int child_status = 0;
    if (waitpid(child_pid, &child_status, 0) == -1) {
        perror("wait failed");
    }

    if (WIFEXITED(child_status)) {
        printf("child process %d exited with %d\n", child_pid, WEXITSTATUS(child_status));
    } else {
        printf("child process %d terminated with signal %d\n", child_pid, WTERMSIG(child_status));
    }

    return 0;
}
