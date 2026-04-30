// ReSharper disable CppDFAEndlessLoop
#include <stdio.h>
#include <unistd.h>

int main(void) {
    if (fork() == -1) {
        perror("fork failed");
        return 1;
    }

    printf("pid: %d, ppid: %d\n", getpid(), getppid());

    while (true);
}
