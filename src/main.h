#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "display_user_prompt.h"
#include "extra_functions.h"
#include "colours.h"
#include "execute.h"
#include "bg.h"
#include "pastevents.h"


extern char **past_events;
extern char *parent_directory;
extern char* file_open_path;
extern char *input;
extern char* shell_open_path;
    
extern int begin, endtime;

#endif