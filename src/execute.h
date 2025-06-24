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
#include "warp.h"
#include "peek.h"
#include "pastevents.h"
#include "system_commands.h"
#include "proclore.h"
#include "seek.h"
#include "redirect.h"
#include "activities.h"
#include "ping.h"
#include "neonate.h"
#include "fg_bg.h"
#include "pipe.h"
#include "iman.h"
char*substr(char*str,int start,int len);
int execute_function(struct commands command1, int curr_indx);
int execute_multi_commands(char *input);
void execute_command(char**args, bool use_pipe, bool background);

extern char* Multiple_Commands[1024];
#endif