#ifndef DISPLAY_USER_PROMPT_H
#define DISPLAY_USER_PROMPT_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "main.h"
#include "extra_functions.h"
#include "colours.h"
#include "execute.h"
#include "pastevents.h"
#include "execute.h"

extern int print_bg_output_flag;
extern char *print_bg_output;
extern char* previous_prompt_username;
extern char* previous_prompt_system_name;
extern char* previous_prompt_cwd;
void format_directory(char *cwd, char *parent_directory);
void display_user_prompt_function(char *parent_directory);
#endif
