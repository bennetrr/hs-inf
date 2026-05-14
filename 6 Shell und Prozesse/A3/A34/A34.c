#include <errno.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../sem_helpers.c"
#include "../shm_helpers.c"

#define PRODUCER_COUNT 3
#define MAX_CHAR_COUNT 7
#define MAX_LINE_COUNT 3
#define TOTAL_CHILD_PROCESS_COUNT (PRODUCER_COUNT * 2 + 1)

static const char *INPUT_SOURCES[] = {NULL, "testfiles/1.txt", "testfiles/2.txt"};

static bool should_terminate = false;

void consumer_signal_handler(const int signal) {
    printf("Consumer: Received signal %d\n", signal);
    should_terminate = true;
}

void main_signal_handler(const int signal) {
    printf("Main: Received signal %d\n", signal);
}

// Escape non-printable characters in the string. sizeof(dst) must be len * 4 + 1
void debug_string(char* dst, const char *src, const size_t len) {
    int w = 0;
    for (size_t r = 0; r < len; r++) {
        if (src[r] >= ' ' && src[r] <= '~') {
            dst[w++] = src[r];
        } else if (src[r] == '\0') {
            dst[w++] = '\\';
            dst[w++] = '0';
        } else if (src[r] == '\n') {
            dst[w++] = '\\';
            dst[w++] = 'n';
        } else {
            snprintf(&dst[w], 5 * sizeof(char), "\\x%02X", src[r]);
            w += 4;
        }
    }

    dst[w] = '\0';
}

int producer(
    const int instance_id,
    const char input_path[],  // For reading from a file, specify the path here. For interactive mode, pass NULL
    const int char_buffer_shm_handle,
    const int char_buffer_mutex,
    const int char_buffer_empty,
    const int char_buffer_full) {
    // Initialization
    printf("Producer %d: Started with PID %d\n", instance_id, getpid());
    printf("Producer %d: Initializing\n", instance_id);

    int exit_code = 0;
    char *input_string = NULL;
    size_t input_string_length = 0;
    char *char_buffer = NULL;

    char_buffer = shm_attach(char_buffer_shm_handle);
    if ((intptr_t) char_buffer == -1) {
        char perror_msg[128];
        snprintf(perror_msg, sizeof(perror_msg), "Producer %d: Could not attach char buffer sharded memory", instance_id);
        perror(perror_msg);
        char_buffer = NULL;
        exit_code = 1;
        goto exit;
    }

    printf("Producer %d: Initialized\n", instance_id);

    // Main loop
    if (input_path) {
        FILE *input_file = fopen(input_path, "r");
        if (!input_file) {
            char perror_msg[128];
            snprintf(
                perror_msg,
                sizeof(perror_msg),
                "Producer %d: Could not open input file '%s'",
                instance_id,
                input_path);
            perror(perror_msg);
            exit_code = 2;
            goto exit;
        }

        if (fseek(input_file, 0, SEEK_END) == -1) {
            char perror_msg[128];
            snprintf(perror_msg, sizeof(perror_msg), "Producer %d: Could not seek through input file", instance_id);
            perror(perror_msg);
            exit_code = 2;
            goto error;
        }
        const long len = ftell(input_file);
        if (len == -1L) {
            char perror_msg[128];
            snprintf(perror_msg, sizeof(perror_msg), "Producer %d: Could not get input file length", instance_id);
            perror(perror_msg);
            exit_code = 2;
            goto error;
        }
        input_string_length = len;

        rewind(input_file);

        input_string = malloc(input_string_length * sizeof(char));
        if (!input_string) {
            char perror_msg[128];
            snprintf(
                perror_msg,
                sizeof(perror_msg),
                "Producer %d: Could not allocate memory for input string",
                instance_id);
            perror(perror_msg);
            exit_code = 2;
            goto error;
        }

        const size_t read_length = fread(input_string, sizeof(char), input_string_length, input_file);
        if (read_length < input_string_length) {
            if (feof(input_file)) {
                input_string_length = read_length;
            } else {
                char perror_msg[128];
                snprintf(
                    perror_msg,
                    sizeof(perror_msg),
                    "Producer %d: Could not read from input file",
                    instance_id);
                perror(perror_msg);
                exit_code = 2;
                goto error;
            }
        }

error:
        if (fclose(input_file) == EOF) {
            char perror_msg[128];
            snprintf(
                perror_msg,
                sizeof(perror_msg),
                "Producer %d: Could not close input file",
                instance_id);
            perror(perror_msg);
        }
        if (exit_code != 0) {
            goto exit;
        }
    } else {
        printf("Producer %d: Interactive mode - please enter a string to process:\n", instance_id);

        size_t buffer_size = 0;
        const ssize_t length = getline(&input_string, &buffer_size, stdin);
        if (length == -1) {
            if (feof(stdin)) {
                input_string = malloc(sizeof(char));
                if (!input_string) {
                    char perror_msg[128];
                    snprintf(
                        perror_msg,
                        sizeof(perror_msg),
                        "Producer %d: Could not allocate memory for input string",
                        instance_id);
                    perror(perror_msg);
                    exit_code = 2;
                    goto exit;
                }

                input_string[0] = '\0';
            } else {
                char perror_msg[128];
                snprintf(
                    perror_msg,
                    sizeof(perror_msg),
                    "Producer %d: Could not read from stdin",
                    instance_id);
                perror(perror_msg);
                exit_code = 2;
                goto exit;
            }
        }
        input_string[strcspn(input_string, "\n")] = '\0';
        input_string_length = strlen(input_string);
    }

    char *debug_input_string = malloc(input_string_length * 4 + 1);
    if (debug_input_string) {
        debug_string(debug_input_string, input_string, input_string_length);
        printf(
            "Producer %d: Read input '%s' (%lu chars long)\n",
            instance_id,
            debug_input_string,
            input_string_length);
    } else {
        char perror_msg[128];
        snprintf(
            perror_msg,
            sizeof(perror_msg),
            "Producer %d: Could not allocate memory for debug print",
            instance_id);
        perror(perror_msg);
    }
    free(debug_input_string);

    for (size_t i = 0; i <= input_string_length; i += MAX_CHAR_COUNT) {
        char next_chars[MAX_CHAR_COUNT + 1];

        // Take the next 7 chars from the input string. If there are not enough chars left, the rest is filled with \0
        if (i < input_string_length) {
            strlcpy(next_chars, input_string + i, sizeof(next_chars));

            char debug_read_chars[MAX_CHAR_COUNT * 4 + 1];
            debug_string(debug_read_chars, next_chars, MAX_CHAR_COUNT);
            printf(
                "Producer %d: Read characters '%s' (%lu to %lu) from input\n",
                instance_id,
                debug_read_chars,
                i,
                i + MAX_CHAR_COUNT < input_string_length ? i + MAX_CHAR_COUNT - 1 : input_string_length - 1);

            for (size_t j = 0; j < MAX_CHAR_COUNT; j++) {
                // Replace all \0 with EOT, so the reader knows that the end of transmission is reached
                if (next_chars[j] == '\0') {
                    next_chars[j] = 0x04;
                }

                // Replace all \n with \0 which is the required line seperator for this program
                if (next_chars[j] == '\n') {
                    next_chars[j] = '\0';
                }
            }
        } else {
            printf("Producer %d: Creating extra end of transmission message\n", instance_id);
            memset(next_chars, 0x04, MAX_CHAR_COUNT + 1);
        }

        char debug_encoded_chars[MAX_CHAR_COUNT * 4 + 1];
        debug_string(debug_encoded_chars, next_chars, MAX_CHAR_COUNT);
        printf("Producer %d: Sending next char batch '%s'\n", instance_id, debug_encoded_chars);

        printf("Producer %d: Waiting for char buffer to be empty\n", instance_id);
        if (sem_wait(char_buffer_empty) == -1) {
            char perror_msg[128];
            snprintf(
                perror_msg,
                sizeof(perror_msg),
                "Producer %d: Could not wait for char buffer to be empty",
                instance_id);
            perror(perror_msg);
            exit_code = 2;
            goto exit;
        }

        printf("Producer %d: Waiting for access to char buffer\n", instance_id);
        if (sem_wait(char_buffer_mutex) == -1) {
            char perror_msg[128];
            snprintf(
                perror_msg,
                sizeof(perror_msg),
                "Producer %d: Could not wait for access to char buffer",
                instance_id);
            perror(perror_msg);
            exit_code = 2;
            goto exit;
        }
        memcpy(char_buffer, next_chars, MAX_CHAR_COUNT * sizeof(char));
        if (sem_signal(char_buffer_mutex) == -1) {
            char perror_msg[128];
            snprintf(
                perror_msg,
                sizeof(perror_msg),
                "Producer %d: Could not release access for char buffer",
                instance_id);
            perror(perror_msg);
            exit_code = 2;
            goto exit;
        }
        printf("Producer %d: Wrote next char batch to char buffer\n", instance_id);

        printf("Producer %d: Signaling new char batch to buffered reader\n", instance_id);
        if (sem_signal(char_buffer_full) == -1) {
            char perror_msg[128];
            snprintf(
                perror_msg,
                sizeof(perror_msg),
                "Producer %d: Could not signal new char batch to buffered reader",
                instance_id);
            perror(perror_msg);
            exit_code = 2;
            goto exit;
        }
    }

    // Cleanup
exit:
    printf("Producer %d: Cleaning up resources\n", instance_id);

    free(input_string);

    if (char_buffer != NULL && shm_detach(char_buffer) == -1) {
        char perror_msg[128];
        snprintf(
            perror_msg,
            sizeof(perror_msg),
            "Producer %d: Could not detach char buffer sharded memory",
            instance_id);
        perror(perror_msg);
    }

    printf("Producer %d: Exiting with code %d (PID was %d)\n", instance_id, exit_code, getpid());
    return exit_code;
}

int buffered_reader(
    const int instance_id,
    const int char_buffer_shm_handle,
    const int lines_buffer_shm_handle,
    const int char_buffer_mutex,
    const int char_buffer_empty,
    const int char_buffer_full,
    const int lines_buffer_mutex,
    const int lines_buffer_empty,
    const int lines_buffer_full) {
    // Initialization
    printf("Buffered reader %d: Started with PID %d\n", instance_id, getpid());
    printf("Buffered reader %d: Initializing\n", instance_id);

    int exit_code = 0;
    char *char_buffer = NULL;
    int *lines_buffer = NULL;
    char *line_buffer = NULL;
    size_t line_length = 0;

    char_buffer = shm_attach(char_buffer_shm_handle);
    if ((intptr_t) char_buffer == -1) {
        char perror_msg[128];
        snprintf(perror_msg, sizeof(perror_msg), "Buffered reader %d: Could not attach char buffer sharded memory", instance_id);
        perror(perror_msg);
        char_buffer = NULL;
        exit_code = 1;
        goto exit;
    }

    lines_buffer = shm_attach(lines_buffer_shm_handle);
    if ((intptr_t) lines_buffer == -1) {
        char perror_msg[128];
        snprintf(perror_msg, sizeof(perror_msg), "Buffered reader %d: Could not attach lines buffer sharded memory", instance_id);
        perror(perror_msg);
        lines_buffer = NULL;
        exit_code = 1;
        goto exit;
    }

    printf("Buffered reader %d: Initialized\n", instance_id);

    // Main loop
    bool eot_reached = false;

    while (!eot_reached) {
        char next_chars[MAX_CHAR_COUNT];

        printf("Buffered reader %d: Waiting for new char batch\n", instance_id);
        if (sem_wait(char_buffer_full) == -1) {
            char perror_msg[128];
            snprintf(
                perror_msg,
                sizeof(perror_msg),
                "Buffered reader %d: Could not wait for new char buffer to be full",
                instance_id);
            perror(perror_msg);
            exit_code = 2;
            goto exit;
        }

        printf("Buffered reader %d: Waiting for access to char buffer\n", instance_id);
        if (sem_wait(char_buffer_mutex) == -1) {
            char perror_msg[128];
            snprintf(
                perror_msg,
                sizeof(perror_msg),
                "Buffered reader %d: Could not wait for access to char buffer",
                instance_id);
            perror(perror_msg);
            exit_code = 2;
            goto exit;
        }
        memcpy(next_chars, char_buffer, MAX_CHAR_COUNT * sizeof(char));
        if (sem_signal(char_buffer_mutex) == -1) {
            char perror_msg[128];
            snprintf(
                perror_msg,
                sizeof(perror_msg),
                "Buffered reader %d: Could not release access for char buffer",
                instance_id);
            perror(perror_msg);
            exit_code = 2;
            goto exit;
        }
        printf("Buffered reader %d: Read next char batch from char buffer\n", instance_id);

        printf("Buffered reader %d: Signaling empty char buffer to producer\n", instance_id);
        if (sem_signal(char_buffer_empty) == -1) {
            char perror_msg[128];
            snprintf(
                perror_msg,
                sizeof(perror_msg),
                "Buffered reader %d: Could not signal empty char buffer to producer",
                instance_id);
            perror(perror_msg);
            exit_code = 2;
            goto exit;
        }

        char debug_received_chars[MAX_CHAR_COUNT * 4 + 1];
        debug_string(debug_received_chars, next_chars, MAX_CHAR_COUNT);
        printf("Buffered reader %d: Received next char batch '%s'\n", instance_id, debug_received_chars);

        for (size_t i = 0, s = 0, l = 1; i < MAX_CHAR_COUNT; i++, l++) {
            if (next_chars[i] == '\0' || next_chars[i] == 0x04 || i == MAX_CHAR_COUNT - 1) {
                if (next_chars[i] == '\0' || next_chars[i] == 0x04) {
                    l--; // Don't copy the \0 or 0x04 character

                    printf(
                        "Buffered reader %d: Encountered %s at position %lu (current segment started at %lu and is %lu chars long)\n",
                        instance_id,
                        next_chars[i] == '\0' ? "line break" : "end of transmission",
                        i,
                        s,
                        l);
                } else {
                    printf("Buffered reader %d: End of buffer reached without line break\n", instance_id);
                }

                const size_t old_line_length = line_length;
                line_length += l;
                char *old_line_buffer = line_buffer;
                line_buffer = malloc((line_length + 1) * sizeof(char));
                if (!line_buffer) {
                    free(old_line_buffer);

                    char perror_msg[128];
                    snprintf(
                        perror_msg,
                        sizeof(perror_msg),
                        "Buffered reader %d: Could not allocate memory for line buffer",
                        instance_id);
                    perror(perror_msg);
                    exit_code = 2;
                    goto exit;
                }

                if (old_line_buffer != NULL) {
                    strlcpy(line_buffer, old_line_buffer, line_length + 1);
                }
                strlcpy(line_buffer + old_line_length, next_chars + s, l + 1);

                free(old_line_buffer);
                old_line_buffer = NULL;
                s = i + 1;
                l = 0;

                char debug_line[line_length * 4 + 1];
                debug_string(debug_line, line_buffer, line_length);
                printf("Buffered reader %d: Line is '%s' (%lu chars long)\n", instance_id, debug_line, line_length);
            }

            if ((next_chars[i] == '\0' || next_chars[i] == 0x04) && line_buffer) {
                char debug_line[line_length * 4 + 1];
                debug_string(debug_line, line_buffer, line_length);
                printf("Buffered reader %d: Sending line '%s' (%lu chars long)\n", instance_id, debug_line, line_length);

                printf("Buffered reader %d: Waiting for empty slot in lines buffer\n", instance_id);
                if (sem_wait(lines_buffer_empty) == -1) {
                    char perror_msg[128];
                    snprintf(
                        perror_msg,
                        sizeof(perror_msg),
                        "Buffered reader %d: Could not wait for empty slot in lines buffer",
                        instance_id);
                    perror(perror_msg);
                    exit_code = 2;
                    goto exit;
                }

                const int line_buffer_shm_handle = shm_create(IPC_PRIVATE, (line_length + 1) * sizeof(char));
                if (line_buffer_shm_handle == -1) {
                    char perror_msg[128];
                    snprintf(
                        perror_msg,
                        sizeof(perror_msg),
                        "Buffered reader %d: Could not create line buffer shared memory",
                        instance_id);
                    perror(perror_msg);
                    exit_code = 2;
                    goto exit;
                }
                char *line_buffer_shm = shm_attach(line_buffer_shm_handle);
                if ((intptr_t) line_buffer_shm == -1) {
                    char perror_msg[128];
                    snprintf(
                        perror_msg,
                        sizeof(perror_msg),
                        "Buffered reader %d: Could not attach line buffer shared memory",
                        instance_id);
                    perror(perror_msg);

                    if (shm_delete(line_buffer_shm_handle) == -1) {
                        char perror_msg_2[128];
                        snprintf(
                            perror_msg_2,
                            sizeof(perror_msg_2),
                            "Buffered reader %d: Could not delete line buffer shared memory",
                            instance_id);
                        perror(perror_msg_2);
                    }

                    exit_code = 2;
                    goto exit;
                }

                strlcpy(line_buffer_shm, line_buffer, line_length + 1);

                if (shm_detach(line_buffer_shm) == -1) {
                    char perror_msg[128];
                    snprintf(
                        perror_msg,
                        sizeof(perror_msg),
                        "Buffered reader %d: Could not detach line buffer sharded memory",
                        instance_id);
                    perror(perror_msg);
                }

                printf("Buffered reader %d: Waiting for access to lines buffer\n", instance_id);
                if (sem_wait(lines_buffer_mutex) == -1) {
                    char perror_msg[128];
                    snprintf(
                        perror_msg,
                        sizeof(perror_msg),
                        "Buffered reader %d: Could not wait for access to lines buffer",
                        instance_id);
                    perror(perror_msg);
                    exit_code = 2;
                    goto exit;
                }
                for (int j = 0; j < MAX_LINE_COUNT; ++j) {
                    if (lines_buffer[j] == -1) {
                        lines_buffer[j] = line_buffer_shm_handle;
                        break;
                    }
                }
                if (sem_signal(lines_buffer_mutex) == -1) {
                    char perror_msg[128];
                    snprintf(
                        perror_msg,
                        sizeof(perror_msg),
                        "Buffered reader %d: Could not release access for lines buffer",
                        instance_id);
                    perror(perror_msg);
                    exit_code = 2;
                    goto exit;
                }
                printf(
                    "Buffered reader %d: Wrote next line with SHM handle %d to lines buffer\n",
                    instance_id,
                    line_buffer_shm_handle);

                printf("Buffered reader %d: Signaling new line in lines buffer to consumer\n", instance_id);
                if (sem_signal(lines_buffer_full) == -1) {
                    char perror_msg[128];
                    snprintf(
                        perror_msg,
                        sizeof(perror_msg),
                        "Buffered reader %d: Could not signal new line in lines buffer to consumer",
                        instance_id);
                    perror(perror_msg);
                    exit_code = 2;
                    goto exit;
                }

                free(line_buffer);
                line_buffer = NULL;
                line_length = 0;
            }

            if (next_chars[i] == 0x04) {
                printf("Buffered reader %d: End of transmission encountered, exiting\n", instance_id);
                eot_reached = true;
                break;
            }
        }
    }

    // Cleanup
exit:
    printf("Buffered reader %d: Cleaning up resources\n", instance_id);

    if (char_buffer != NULL && shm_detach(char_buffer) == -1) {
        char perror_msg[128];
        snprintf(
            perror_msg,
            sizeof(perror_msg),
            "Buffered reader %d: Could not detach char buffer sharded memory",
            instance_id);
        perror(perror_msg);
    }

    if (lines_buffer != NULL && shm_detach(lines_buffer) == -1) {
        char perror_msg[128];
        snprintf(
            perror_msg,
            sizeof(perror_msg),
            "Buffered reader %d: Could not detach lines buffer sharded memory",
            instance_id);
        perror(perror_msg);
    }

    if (line_buffer != NULL) {
        free(line_buffer);
    }

    printf("Buffered reader %d: Exiting with code %d (PID was %d)\n", instance_id, exit_code, getpid());
    return exit_code;
}

int consumer(
    const int lines_buffer_shm_handle,
    const int lines_buffer_mutex,
    const int lines_buffer_empty,
    const int lines_buffer_full) {
    // Initialization
    printf("Consumer: Started with PID %d\n", getpid());
    printf("Consumer: Initializing\n");

    int exit_code = 0;
    int *lines_buffer = NULL;

    struct sigaction sa;
    sa.sa_handler = consumer_signal_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("Consumer: Could not install SIGINT handler");
        exit_code = 1;
        goto exit;
    }
    if (sigaction(SIGTERM, &sa, NULL) == -1) {
        perror("Consumer: Could not install SIGTERM handler");
        exit_code = 1;
        goto exit;
    }

    lines_buffer = shm_attach(lines_buffer_shm_handle);
    if ((intptr_t) lines_buffer == -1) {
        char perror_msg[128];
        snprintf(perror_msg, sizeof(perror_msg), "Consumer: Could not attach lines buffer sharded memory");
        perror(perror_msg);
        lines_buffer = NULL;
        exit_code = 1;
        goto exit;
    }

    printf("Consumer: Initialized\n");

    // Main loop
    while (!should_terminate) {
        printf("Consumer: Waiting for new line\n");
        if (sem_wait(lines_buffer_full) == -1) {
            if (errno == EINTR && should_terminate) {
                break;
            }

            perror("Consumer: Could not wait for new line");
            exit_code = 2;
            goto exit;
        }

        printf("Consumer: Waiting for access to lines buffer\n");
        if (sem_wait(lines_buffer_mutex) == -1) {
            if (errno == EINTR && should_terminate) {
                break;
            }

            perror("Consumer: Could not wait for access to lines buffer");
            exit_code = 2;
            goto exit;
        }

        int line_buffer_shm_handle = -1;
        for (int j = 0; j < MAX_LINE_COUNT; ++j) {
            if (lines_buffer[j] != -1) {
                line_buffer_shm_handle = lines_buffer[j];
                lines_buffer[j] = -1;
                break;
            }
        }

        if (sem_signal(lines_buffer_mutex) == -1) {
            perror("Consumer: Could not release access for lines buffer");
            exit_code = 2;
            goto exit;
        }
        printf("Consumer: Read SHM handle %d for next line from lines buffer\n", line_buffer_shm_handle);

        printf("Consumer: Signaling empty slot in lines buffer to buffered reader\n");
        if (sem_signal(lines_buffer_empty) == -1) {
            perror("Consumer: Could not signal empty slot in lines buffer to buffered reader");
            exit_code = 2;
            goto exit;
        }

        const char *line_buffer_shm = shm_attach(line_buffer_shm_handle);
        if ((intptr_t) line_buffer_shm == -1) {
            perror("Consumer: Could not attach line buffer");

            if (shm_delete(line_buffer_shm_handle) == -1) {
                perror("Consumer: Could not delete line buffer");
            }
            continue;
        }

        const size_t line_length = strlen(line_buffer_shm);
        char line_buffer[line_length + 1];
        strlcpy(line_buffer, line_buffer_shm, sizeof(line_buffer));

        if (shm_detach(line_buffer_shm) == -1) {
            perror("Consumer: Could not detach line buffer");
        }
        if (shm_delete(line_buffer_shm_handle) == -1) {
            perror("Consumer: Could not delete line buffer");
        }

        char debug_line[line_length * 4 + 1];
        debug_string(debug_line, line_buffer, line_length);
        printf("Consumer: Received line '%s' (%lu chars long)\n", debug_line, line_length);
    }

    // Cleanup
exit:
    printf("Consumer: Cleaning up resources\n");

    if (lines_buffer != NULL && shm_detach(lines_buffer) == -1) {
        perror("Consumer: Could not detach lines buffer sharded memory");
    }

    printf("Consumer: Exiting with code %d (PID was %d)\n", exit_code, getpid());
    return exit_code;
}

int main(void) {
    printf("Main: Started with PID %d\n", getpid());
    printf("Main: Initializing global resources\n");

    int exit_code = 0;
    size_t shm_handle_count = 0;
    int shm_handles[PRODUCER_COUNT + 1];
    size_t sem_handle_count = 0;
    int sem_handles[3 * PRODUCER_COUNT + 3];

    struct sigaction sa;
    sa.sa_handler = main_signal_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("Main: Could not install SIGINT handler");
        return 1;
    }
    if (sigaction(SIGTERM, &sa, NULL) == -1) {
        perror("Main: Could not install SIGTERM handler");
        return 1;
    }

    const int lines_buffer_shm_handle = shm_create(IPC_PRIVATE, MAX_LINE_COUNT * sizeof(int));
    if (lines_buffer_shm_handle == -1) {
        perror("Main: Could not create lines buffer shared memory");
        exit_code = 1;
        goto exit;
    }
    shm_handles[shm_handle_count++] = lines_buffer_shm_handle;
    int *lines_buffer = shm_attach(lines_buffer_shm_handle);
    if ((intptr_t) lines_buffer == -1) {
        perror("Main: Could not attach lines buffer shared memory");
        exit_code = 1;
        goto exit;
    }
    for (int i = 0; i < MAX_LINE_COUNT; i++) {
        lines_buffer[i] = -1;
    }
    if (shm_detach(lines_buffer) == -1) {
        perror("Main: Could not detach lines buffer shared memory");
    }

    const int lines_buffer_mutex = sem_create(IPC_PRIVATE);
    if (lines_buffer_mutex == -1) {
        perror("Main: Could not create lines buffer mutex semaphore");
        exit_code = 1;
        goto exit;
    }
    sem_handles[sem_handle_count++] = lines_buffer_mutex;
    if (sem_set(lines_buffer_mutex, 1) == -1) {
        perror("Main: Could not initialize lines buffer mutex semaphore");
        exit_code = 1;
        goto exit;
    }

    const int lines_buffer_empty = sem_create(IPC_PRIVATE);
    if (lines_buffer_empty == -1) {
        perror("Main: Could not create lines buffer empty semaphore");
        exit_code = 1;
        goto exit;
    }
    sem_handles[sem_handle_count++] = lines_buffer_empty;
    if (sem_set(lines_buffer_empty, MAX_LINE_COUNT) == -1) {
        perror("Main: Could not initialize lines buffer empty semaphore");
        exit_code = 1;
        goto exit;
    }

    const int lines_buffer_full = sem_create(IPC_PRIVATE);
    if (lines_buffer_full == -1) {
        perror("Main: Could not create lines buffer full semaphore");
        exit_code = 1;
        goto exit;
    }
    sem_handles[sem_handle_count++] = lines_buffer_full;
    if (sem_set(lines_buffer_full, 0) == -1) {
        perror("Main: Could not initialize lines buffer full semaphore");
        exit_code = 1;
        goto exit;
    }

    printf("Main: Starting consumer\n");

    const pid_t consumer_pid = fork();
    if (consumer_pid == -1) {
        perror("Main: Could not fork consumer process");
        exit_code = 1;
        goto exit;
    }
    if (consumer_pid == 0) {
        return consumer(
            lines_buffer_shm_handle,
            lines_buffer_mutex,
            lines_buffer_empty,
            lines_buffer_full);
    }

    printf("Main: Started consumer with PID %d\n", consumer_pid);

    for (int instance_id = 0; instance_id < PRODUCER_COUNT; instance_id++) {
        printf(
            "Main: Initializing resources for producer / buffered reader pair %d (%d out of %d)\n",
            instance_id,
            instance_id + 1,
            PRODUCER_COUNT);

        const int char_buffer_shm_handle = shm_create(IPC_PRIVATE, MAX_CHAR_COUNT * sizeof(char));
        if (char_buffer_shm_handle == -1) {
            perror("Main: Could not create char buffer shared memory");
            exit_code = 1;
            goto exit;
        }
        shm_handles[shm_handle_count++] = char_buffer_shm_handle;

        const int char_buffer_mutex = sem_create(IPC_PRIVATE);
        if (char_buffer_mutex == -1) {
            perror("Main: Could not create char buffer mutex semaphore");
            exit_code = 1;
            goto exit;
        }
        sem_handles[sem_handle_count++] = char_buffer_mutex;
        if (sem_set(char_buffer_mutex, 1) == -1) {
            perror("Main: Could not initialize char buffer mutex semaphore");
            exit_code = 1;
            goto exit;
        }

        const int char_buffer_empty = sem_create(IPC_PRIVATE);
        if (char_buffer_empty == -1) {
            perror("Main: Could not create char buffer empty semaphore");
            exit_code = 1;
            goto exit;
        }
        sem_handles[sem_handle_count++] = char_buffer_empty;
        if (sem_set(char_buffer_empty, 1) == -1) {
            perror("Main: Could not initialize char buffer empty semaphore");
            exit_code = 1;
            goto exit;
        }

        const int char_buffer_full = sem_create(IPC_PRIVATE);
        if (char_buffer_full == -1) {
            perror("Main: Could not create char buffer full semaphore");
            exit_code = 1;
            goto exit;
        }
        sem_handles[sem_handle_count++] = char_buffer_full;
        if (sem_set(char_buffer_full, 0) == -1) {
            perror("Main: Could not initialize char buffer full semaphore");
            exit_code = 1;
            goto exit;
        }

        printf("Main: Starting buffered reader %d (%d out of %d)\n", instance_id, instance_id + 1, PRODUCER_COUNT);

        const pid_t buffered_reader_pid = fork();
        if (buffered_reader_pid == -1) {
            perror("Main: Could not fork buffered reader process");
            exit_code = 1;
            goto exit;
        }
        if (buffered_reader_pid == 0) {
            return buffered_reader(
                instance_id,
                char_buffer_shm_handle,
                lines_buffer_shm_handle,
                char_buffer_mutex,
                char_buffer_empty,
                char_buffer_full,
                lines_buffer_mutex,
                lines_buffer_empty,
                lines_buffer_full);
        }

        printf(
            "Main: Started buffered reader %d (%d out of %d) with PID %d\n",
            instance_id,
            instance_id + 1,
            PRODUCER_COUNT,
            buffered_reader_pid);

        printf("Main: Starting producer %d (%d out of %d)\n", instance_id, instance_id + 1, PRODUCER_COUNT);

        const pid_t producer_pid = fork();
        if (producer_pid == -1) {
            perror("Main: Could not fork producer process");
            exit_code = 1;
            goto exit;
        }
        if (producer_pid == 0) {
            return producer(
                instance_id,
                INPUT_SOURCES[instance_id],
                char_buffer_shm_handle,
                char_buffer_mutex,
                char_buffer_empty,
                char_buffer_full);
        }

        printf(
            "Main: Started producer %d (%d out of %d) with PID %d\n",
            instance_id,
            instance_id + 1,
            PRODUCER_COUNT,
            producer_pid);
    }

    for (int i = 0; i < TOTAL_CHILD_PROCESS_COUNT; i++) {
        int status;
        pid_t pid;

        // Retry if wait was interrupted by signal
        while ((pid = wait(&status)) == -1 && errno == EINTR) {}

        if (pid == -1) {
            if (errno == ECHILD) {
                break;
            }

            perror("Main: Could not wait for child process to exit");
        }

        if (WIFEXITED(status)) {
            printf(
                "Main: Child process %d exited with status %d (%d out of %d)\n",
                pid,
                WEXITSTATUS(status),
                i + 1,
                TOTAL_CHILD_PROCESS_COUNT);
        } else {
            printf(
                "Main: Child process %d exited with signal %d (%d out of %d)\n",
                pid,
                WTERMSIG(status),
                i + 1,
                TOTAL_CHILD_PROCESS_COUNT);
        }
    }

exit:
    printf("Main: Cleaning up resources\n");
    for (size_t i = 0; i < shm_handle_count; ++i) {
        if (shm_delete(shm_handles[i]) == -1) {
            perror("Main: Could not delete shared memory");
        }
    }

    for (size_t i = 0; i < sem_handle_count; ++i) {
        if (sem_delete(sem_handles[i]) == -1) {
            perror("Main: Could not delete semaphore");
        }
    }

    printf("Main: Exiting with code %d (PID was %d)\n", exit_code, getpid());
    return exit_code;
}
