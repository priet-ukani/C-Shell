#ifndef EXTRA_FUNCTIONS_H
#define EXTRA_FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "system_commands.h"
struct commands{
    char *command;
    bool print_pid_and_background;
};


int mini(int a, int b);
char** separate_by_delimeter(char*str, char* delimeter);
char *replace_home(char *path);

char* remove_extra_spaces_and_tabs(char * input_str);
struct commands *split_commands(char *input_str);

#endif