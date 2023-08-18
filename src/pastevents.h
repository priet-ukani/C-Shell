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

#include "colours.h"
#include "extra_functions.h"

void pastevents(char *args[], int num_args);

#endif