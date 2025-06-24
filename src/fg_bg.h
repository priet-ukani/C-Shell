#ifndef FG_BG_H
#define FG_BG_H

#include <stdio.h>

#include <dirent.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "extra_functions.h"
#include "bg.h"
void fg(char*command);
void bg(char*command);

#endif