#ifndef DISPLAY_USER_PROMPT_H
#define DISPLAY_USER_PROMPT_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include <sys/types.h>
#include <sys/wait.h>

void format_directory(char *cwd, char *parent_directory);
void display_user_prompt_function(char *parent_directory);
#endif
