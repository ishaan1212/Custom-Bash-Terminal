#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdbool.h>

#define MAX_ARGS 5
#define MAX_COMMAND_LENGTH 100
#define MAX_PIPE_COMMANDS 7
#define MAX_FILES_CONCATENATION 6


void execute_command(char *args[], int argc) {
    printf("Executing command: ");
    for (int i = 0; i < argc; i++) {
        printf("%s ", args[i]);
    }
    printf("\n");

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork failed");
    } else if (pid == 0) {
        // Child process
        if (execvp(args[0], args) == -1) {
            perror("execvp failed");
            exit(EXIT_FAILURE);
        }
    } else {
        // Parent process
        int status;
        waitpid(pid, &status, 0);
    }
}

bool validate_args(char *args[], int argc) {
    if (argc < 1 || argc > MAX_ARGS) {
        printf("Number of arguments should be between 1 and %d.\n", MAX_ARGS);
        return false;
    }
    return true;
}



void parse_command(char *command) {
    char *args[MAX_ARGS + 1]; // Additional one for NULL
    int argc = 0;

    char *token = strtok(command, " \t\n");
    while (token != NULL) {
        args[argc++] = token;
        token = strtok(NULL, " \t\n");
    }
    args[argc] = NULL;

    if (!validate_args(args, argc)) {
        return;
    }

    if (strcmp(args[0], "newt") == 0) {
        // Open a new shell24 in a new terminal
        pid_t pid = fork();
        if (pid < 0) {
            perror("fork failed");
        } else if (pid == 0) {
            // Child process
            pid_t grandchild_pid = fork();
            if (grandchild_pid < 0) {
                perror("fork failed");
                exit(EXIT_FAILURE);
            } else if (grandchild_pid == 0) {
                // Grandchild process
                if (execlp("xterm", "xterm", "-e", "./shell24", NULL) == -1) {
                    perror("execlp failed");
                    exit(EXIT_FAILURE);
                }
            }
            exit(EXIT_SUCCESS); // Child process exits
        } else {
            // Parent process continues without waiting for the child
        }
    } else if (strstr(command, "#") != NULL) {
        // Handle file concatenation
        char *token = strtok(command, "#");
        FILE *file;
        while (token != NULL && argc < MAX_ARGS) {
            file = fopen(token, "r");
            if (file == NULL) {
                perror("fopen");
                return;
            }
            int c;
            while ((c = fgetc(file)) != EOF) {
                putchar(c); // Output character by character
            }
            fclose(file);
            token = strtok(NULL, "#");
        }
    }  else {
        execute_command(args, argc);
    }
}


int main() {
    char command[MAX_COMMAND_LENGTH];

    while (1) {
        printf("shell24$ ");
        fflush(stdout);

        if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL) {
            perror("fgets failed");
            exit(EXIT_FAILURE);
        }

        parse_command(command);
    }

    return 0;
}
