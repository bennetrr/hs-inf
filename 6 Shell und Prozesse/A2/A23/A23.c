#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int signal_count = 0;

static void signal_handler(const int signum) {
    printf("Received signal %d\n", signum);
    signal_count++;

    if (signal_count == 3) {
        printf("Goodbye\n");
        exit(5);
    }
}

int main(void) {
    struct sigaction sa;
    sa.sa_handler = signal_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    if (sigaction(SIGTERM, &sa, nullptr) == -1) {
        perror("sigaction failed");
        return 1;
    }

    if (sigaction(SIGINT, &sa, nullptr) == -1) {
        perror("sigaction failed");
        return 1;
    }

    printf("Started with PID %d\n", getpid());
    printf("When receiving SIGTERM or SIGINT 3 times, this program exits with code 5\n");

    while (true);
}
