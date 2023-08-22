#ifndef EXECUTE_H
#define EXECUTE_H
#include <stdio.h>

#include <dirent.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "colours.h"
#include "extra_functions.h"

char*substr(char*str,int start,int len);
int execute_function(struct commands command1);
int execute_multi_commands(char *input);

#endif