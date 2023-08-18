#ifndef EXTRA_FUNCTIONS_H
#define EXTRA_FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct commands{
    char *command;
    bool print_pid_and_background;
};

char* remove_extra_spaces_and_tabs(char * input_str);

struct commands *split_commands(char *input_str);

#endif