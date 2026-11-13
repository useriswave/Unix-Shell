#include "shell.h"
#include "input/input.h"
#include "shell/builtins/builtins.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

static bool exec_from_path(int argc, char* args[])
{
        pid_t pid = fork();

        switch (pid) {
        case -1:
                perror("shell fork");
                return false;
        case 0:
                execvp(*args, args);
                break;
        default:
                wait(NULL);
        }

        return true;
}

void sh_start()
{
        while (true) {
                printf("$ ");
                char* line = inp_read_line();

                userargs_t uargs = {0};
                inp_split_args(&uargs, line);

                if (strncmp("q", line, 2) == 0) {
                        inp_cleanup(line, &uargs);
                        return;
                }

                if (!bltn_run(uargs.size, uargs.args)) {
                        exec_from_path(uargs.size, uargs.args);
                }

                inp_cleanup(line, &uargs);
        }
}
