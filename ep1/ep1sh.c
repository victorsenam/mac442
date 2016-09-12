#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

#define PROMPT_SIZE (1<<10)

void build_prompt_string (char * prompt) {
    int prompt_siz;
    int i;

    prompt[0] = '(';
    getcwd(prompt+1, PROMPT_SIZE-4);
    prompt_siz = strlen(prompt);
    for (i = 0; i < 4; i++)
        prompt[prompt_siz+i] = "): "[i];
}

int count_arguments (char * command) {
    int i;
    int argc = 0;

    for (i = 0; command[i]; i++)
        if (command[i] != ' ' && (i == 0 || command[i-1] == ' '))
            argc++;
    return argc + 1;
}

void build_call (char * command, char ** argv) {
    int argc = 0;
    int i;
    for (i = 0; command[i]; i++) {
        if (command[i] == ' ') {
            command[i] = 0;
        } else if (i == 0 || command[i-1] == 0) {
            argv[argc++] = command+i;
        }
    }
    argv[argc] = NULL;
}

int main (int argc, char * argv[]) {
    char ** c_argv = NULL;
    char * c_arge[] = { NULL };
    char * command;
    char prompt[PROMPT_SIZE];
    pid_t pid;
    int call_status;
    mode_t chmod_mode;
    char running = 1;

    while (running) {
        build_prompt_string(prompt);
        command = readline(prompt);
        if (command == NULL) {
            command = (char *) malloc(sizeof(char) * 5);
            strcpy(command, "exit");
        } else {
            add_history(command);
        }

        c_argv = (char **) malloc(sizeof(char *) * count_arguments(command));
        build_call(command, c_argv);
        call_status = 0;

        if (strcmp(c_argv[0], "exit") == 0) {
            running = 0;
        } else if (strcmp(c_argv[0], "chmod") == 0) {
            chmod_mode = strtol(c_argv[1], 0, 8);
            if (chmod(c_argv[2], chmod_mode))
                fprintf(stderr, "chmod failed: %s\n", strerror(errno));
        } else if (strcmp(c_argv[0], "id") == 0 && strcmp(c_argv[1], "-u") == 0) {
            printf("%d\n", getuid());
        } else if (access(c_argv[0], F_OK)) {
            fprintf(stderr, "ep1sh: %s is not accessible\n", c_argv[0]);
        } else if (access(c_argv[0], X_OK)) {
            fprintf(stderr, "ep1sh: %s is not executable\n", c_argv[0]);            
        } else if ((pid = fork()) == 0) {
            execve(c_argv[0], c_argv, c_arge);
            call_status = -1;
            return -1;
        } else if (running) {
            if (call_status == -1) {
                fprintf(stderr, "ep1sh: failed to execute %s\n", c_argv[0]);
            } else {
                waitpid(pid, &call_status, 0);
                if (WIFEXITED(call_status)) {
                    if (WEXITSTATUS(call_status))
                        fprintf(stderr, strerror(errno));
                } else {
                    fprintf(stderr, "child process was not terminated normally\n");
                }
            }
        }

        free(c_argv);
        free(command);
    }

    return 0;
}
