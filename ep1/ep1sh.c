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

int build_child_call (char * command, char ** argv) {
    int i;
    int argc = 1;
    char ls = 0;

    for (i = 0; command[i]; ls = command[i++]) {
        if (ls == ' ' && command[i] != ls) {
            argc++;
        }
    }

    argv = (char **) malloc(sizeof(char **) * argc);

    argc = 0;
    ls = 0;
    for (i = 0; command[i]; ls = command[i++]) {
        if (command[i] == ' ') {
            command[i] = 0;
        } else if (ls == 0) {
            argv[argc++] = command+i;
        }
    }
    return argc;
}

int main (int argc, char * argv[]) {
    char ** c_argv = NULL;
    char * c_arge[] = { NULL };
    char * command;
    char prompt[PROMPT_SIZE];
    pid_t pid;
    int call_status;
    int i;

    while (1) {
        build_prompt_string(prompt);
        command = readline(prompt);

        if ((pid = fork()) == 0) {
            call_status = build_child_call(command, c_argv);
            for (i = 0; i < call_status; i++)
                printf("%s\n", c_argv[i]);
            execve(command, c_argv, c_arge);
        } else {
            call_status = 42;
            waitpid(pid, &call_status, 0);
        }
        free(c_argv);
    }

    return 0;
}
