#ifndef PASTEVENTS_H
#define PASTEVENTS_H

#include <stdio.h>

#include <dirent.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "execute.h"
#include "colours.h"
#include "extra_functions.h"

void pastevents_function(char *command);
void write_to_file(int success, char*given_input);

#endif