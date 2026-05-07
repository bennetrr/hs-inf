#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

ssize_t get_input(char **buffer) {
    size_t len = 0;
    const ssize_t res = getline(buffer, &len, stdin);
    (*buffer)[strcspn(*buffer, "\n")] = '\0';
    return res;
}

bool str_starts_with(const char *str, const char *prefix) {
    return strncmp(str, prefix, strlen(prefix)) == 0;
}

size_t str_count_char(const char *str, const char c) {
    if (str == NULL) {
        return 0;
    }

    size_t count = 0;
    for (size_t i = 0; str[i] != '\0'; i++) {
        if (str[i] == c) {
            ++count;
        }
    }

    return count;
}

bool str_is_empty_or_whitespace(const char *str) {
    return str == NULL || str[0] == '\0' || strspn(str, " \t\n") == strlen(str);
}

// Splits the commandline input
size_t split_cmdline(char **argv, const size_t estimated_argc, char *cmdline) {
    char *token = strtok(cmdline, " ");
    size_t argc = 0;

    while (token != NULL) {
        // This should not happen, but just in case
        if (argc >= estimated_argc - 1) {
            break;
        }

        argv[argc++] = token;
        token = strtok(NULL, " ");
    }

    argv[argc] = NULL;
    return argc;
}

bool execute_builtin(char **argv, const size_t argc) {
    if (strcmp(argv[0], "cd") == 0) {
        if (argc < 2) {
            fprintf(stderr, "cd: Missing argument\n");
            return true;
        }

        if (chdir(argv[1]) != 0) {
            perror("Could not change directory");
        }

        return true;
    }

    return false;
}

// Returns whether the executable was found and puts a complete path in executable_path
bool get_absolute_path_of_executable(char *executable_path, const char *argv0) {
    // Simply copy the executable path:
    // - Absolute path (/)
    // - Relative path (./)
    // - Relative upwards path (../)
    if (str_starts_with(argv0, "/") || str_starts_with(argv0, "./") || str_starts_with(argv0, "../")) {
        if (access(argv0, X_OK) != 0) {
            return false;
        }

        strlcpy(executable_path, argv0, PATH_MAX); // strlcpy prevents buffer overflows
        return true;
    }

    // Replace tilde:
    // - Path starting with home directory (~/)
    if (str_starts_with(argv0, "~/")) {
        const char *home = getenv("HOME");
        if (home == NULL) {
            fprintf(stderr, "HOME environment variable not set\n");
            return false;
        }

        char candidate_path[PATH_MAX];
        snprintf(candidate_path, PATH_MAX, "%s/%s", home, argv0 + 2); // Skip the tilde and the slash

        if (access(candidate_path, X_OK) == 0) {
            strlcpy(executable_path, candidate_path, PATH_MAX);
            return true;
        }

        return false;
    }

    // For all other commands: Search in PATH
    const char *path_ro = getenv("PATH");
    if (path_ro == NULL) {
        fprintf(stderr, "PATH environment variable not set\n");
        return false;
    }

    char path[strlen(path_ro) + 1]; // strlen does not include the NUL character
    // From the manpage: The application should not modify the string pointed to by getenv()
    strlcpy(path, path_ro, sizeof(path));

    char *token = strtok(path, ":");
    while (token != NULL) {
        char candidate_path[PATH_MAX];
        snprintf(candidate_path, PATH_MAX, "%s/%s", token, argv0);

        if (access(candidate_path, X_OK) == 0) {
            strlcpy(executable_path, candidate_path, PATH_MAX);
            return true;
        }

        token = strtok(NULL, ":");
    }

    return false;
}

// Executes the specified program and returns its status code
int execute_command(const char *executable_path, char *argv[]) {
    const pid_t child_pid = fork();
    if (child_pid == -1) {
        perror("Could not execute command");
        return -1;
    }

    if (child_pid == 0) {
        if (execv(executable_path, argv) == -1) {
            perror("Could not execute command");
            exit(1);
        }
        return -1;
    }

    int status = 0;
    if (waitpid(child_pid, &status, 0) == -1) {
        perror("Could not wait for command");
        return -1;
    }
    return status;
}

// Returns -1 if another prompt should follow, or any other positive integer if the program should exit with that code
int process_cmdline(char *cmdline) {
    if (str_is_empty_or_whitespace(cmdline)) {
        return -1;
    }

    const size_t estimated_argc = str_count_char(cmdline, ' ') + 2; // argv always needs a NULL terminator as last item
    char *argv[estimated_argc];
    const size_t argc = split_cmdline(argv, estimated_argc, cmdline);

    if (strcmp(argv[0], "exit") == 0 || strcmp(argv[0], "schluss") == 0) {
        return 0; // exit remains here because otherwise execute_builtin would need to return whether to exit the shell
    }

    if (execute_builtin(argv, argc)) {
        return -1;
    }

    char executable_path[PATH_MAX];
    if (!get_absolute_path_of_executable(executable_path, argv[0])) {
        fprintf(stderr, "Command not found: %s\n", argv[0]);
        return -1;
    }

    const int status = execute_command(executable_path, argv);
    if (status > 0) {
        if (WIFEXITED(status)) {
            fprintf(stderr, "\033[31mE %d\033[0m   ", WEXITSTATUS(status));
        } else {
            fprintf(stderr, "\033[41mS %d\033[0m   ", WTERMSIG(status));
        }
    }

    return -1;
}

int main(void) {
    while (true) {
        // PATH_MAX is the maximum number of chars a path can have
        char cwd[PATH_MAX]; // This way cwd does not need to be freed manually (thanks Nico!)
        if (getcwd(cwd, PATH_MAX) == NULL) {
            perror("Could not get current working directory");
            return 1;
        }

        // Fancy color codes: https://stackoverflow.com/a/33206814
        fprintf(stderr, "\033[94m%s\033[0m \033[32m> \033[0m", cwd);

        char *cmdline = NULL;
        if (get_input(&cmdline) == -1) {
            free(cmdline);

            // Handles EOF / CTRL+D
            if (feof(stdin)) {
                fprintf(stderr, "\n");
                return 0;
            }

            perror("Error reading input");
            continue;
        }

        const int exit_code = process_cmdline(cmdline);
        free(cmdline);

        if (exit_code != -1) {
            return exit_code;
        }
    }
}
