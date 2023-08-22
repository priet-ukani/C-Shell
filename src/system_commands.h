#ifndef SYSTEM_COMMANDS_H
#define SYSTEM_COMMANDS_H

#include "colours.h"
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdbool.h>
#include "grp.h"
#include "time.h"
#include "extra_functions.h"
#include "main.h"

void Insert_Process(char* command_bro, int pid);

typedef struct BackgroundJobs
{
    int pid;
    char Job_name[1024];
}BackgroundJobs;

extern BackgroundJobs Store_BackgroundJobs[1024];
void other_system_commands(char* command_bro, int Is_Background);

extern int number_of_background_jobs;
extern int begin, endtime;

#endif