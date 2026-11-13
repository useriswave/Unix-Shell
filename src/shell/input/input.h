#ifndef INPUT_H
#define INPUT_H

#include <stdbool.h>
#include <stddef.h>

typedef struct {
        char** args;
        size_t size;
} userargs_t;

char* inp_read_line();
bool inp_split_args(userargs_t* uargs, char* line);
void inp_cleanup(char* line, userargs_t* uargs);

#endif
