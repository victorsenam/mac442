#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>

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
    char running = 1;

    while (running) {
        build_prompt_string(prompt);
        command = readline(prompt);
        add_history(command);

        c_argv = (char **) malloc(sizeof(char *) * count_arguments(command));
        build_call(command, c_argv);

        if (strcmp(c_argv[0], "exit") == 0) {
            running = 0;
        } else if ((pid = fork()) == 0) {
            call_status = execve(c_argv[0], c_argv, c_arge);
        }

        if (running) {
            waitpid(pid, &call_status, 0);
        }

        free(c_argv);
        free(command);
    }

    return 0;
}
