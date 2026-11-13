#include "builtins.h"

#include <dirent.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define DEBUG_NAME(name) (printf("------------------------------RUNNING %s------------------------------\n", name))

#define READONLY ("r")
#define MAX_BUFF_SIZE 256

typedef enum {
        SUCCESS,
        FAILURE
} builtins_status_e;

static builtins_status_e bltn_cat(int argc, char* args[])
{
        DEBUG_NAME("CAT");

        if (argc < 2) {
                fprintf(stderr, "cat: Invalid args.\n");
                return FAILURE;
        }

        for (int i = 1; i < argc; ++i) {
                FILE* fptr = fopen(args[i], READONLY);

                if (!fptr) {
                        perror("bltn fopen");
                        return FAILURE;
                }

                for (char buff[MAX_BUFF_SIZE]; fgets(buff, sizeof buff, fptr);) {
                        printf("%s", buff);
                }

                fclose(fptr);
        }

        return SUCCESS;
}

static builtins_status_e bltn_cd(int argc, char* args[])
{
        DEBUG_NAME("CD");
        if (argc != 2) {
                fprintf(stderr, "cd: Invalid args.\n");
                return FAILURE;
        }

        if (chdir(args[1]) < 0) {
                perror("chdir");
                return FAILURE;
        }

        return SUCCESS;
}

static builtins_status_e bltn_ls(int argc, char* args[])
{
        DEBUG_NAME("LS");
        if (argc != 1) {
                fprintf(stderr, "ls: Invalid args.\n");
                return FAILURE;
        }

        DIR* dirp = opendir(".");

        if (!dirp) {
                perror("builtins opendir");
                return FAILURE;
        }

        struct dirent* entry = NULL;
        while ((entry = readdir(dirp))) {
                if (*entry->d_name != '.')
                        printf("%s\n", entry->d_name);
        }

        closedir(dirp);
        return SUCCESS;
}

int bltn_run(int argc, char* args[])
{
        if (strncmp("ls", *args, 2) == 0) {
                bltn_ls(argc, args);
                return 1;
        }

        if (strncmp("cd", *args, 2) == 0) {
                bltn_cd(argc, args);
                return 1;
        }

        if (strncmp("cat", *args, 3) == 0) {
                bltn_cat(argc, args);
                return 1;
        }

        return 0;
}
