#include "input.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GROWTH_FACTOR 2

static bool try_realloc_line(char* line, size_t* cap, size_t pos)
{
        if (pos >= *cap) {
                size_t temp_cap = *cap == 0 ? 2 : *cap * GROWTH_FACTOR;
                char* temp = (char*)realloc(line, temp_cap);

                if (!temp) {
                        perror("input realloc");
                        return NULL;
                }

                line = temp;
                *cap = temp_cap;
        }

        return true;
}

char* inp_read_line()
{
        size_t cap = 64;
        char* line = (char*)malloc(sizeof(cap));

        if (!line) {
                perror("input malloc");
                return NULL;
        }

        size_t pos = 0;

        for (int c = 0; (c = getchar()) != '\n' && c != EOF;) {
                if (!try_realloc_line(line, &cap, pos)) {
                        return false;
                }

                line[pos++] = c;
        }

        line[pos] = '\0';
        return line;
}

static bool try_realloc_tokens(char** tokens, size_t* cap, size_t pos)
{
        if (pos >= *cap) {
                size_t temp_cap = *cap == 0 ? 2 : *cap * GROWTH_FACTOR;
                char** temp = (char**)realloc(tokens, temp_cap * sizeof(char*));

                if (!temp) {
                        perror("input realloc");
                        return NULL;
                }

                tokens = temp;
                *cap = temp_cap;
        }

        return true;
}

bool inp_split_args(userargs_t* uargs, char* line)
{
        size_t cap = 12;
        char** tokens = (char**)malloc(cap * sizeof(char*));

        if (!tokens) {
                perror("input malloc");
                return false;
        }

        char* token = strtok(line, " ");
        size_t pos = 0;

        for (; token; ++pos) {
                if (!try_realloc_tokens(tokens, &cap, pos)) {
                        return false;
                }

                tokens[pos] = token;
                token = strtok(NULL, " ");
        }

        uargs->args = tokens;
        uargs->size = pos;

        return true;
}

void inp_cleanup(char* line, userargs_t* uargs)
{
        free(line);
        free(uargs->args);
        uargs->size = 0;
}
