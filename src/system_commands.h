#ifndef SYSTEM_COMMANDS_H
#define SYSTEM_COMMANDS_H

#include "colours.h"
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdbool.h>
#include "grp.h"
#include "time.h"
#include "main.h"
#include "extra_functions.h"
#include "display_user_prompt.h"
#include <signal.h>

void set_signal_handlers();
void child_signal();

// #define MAX_BACKGROUND_JOBS 1024
// struct BackgroundJobs
// {
//     int pid;
//     char p_name[1024];
// };
// struct BackgroundJobs BJobs[MAX_BACKGROUND_JOBS];
// int num_of_bg_jobs;

void add_process(char** name,int pid);

void other_commands(char*cmmd, int is_bg);

void kill_all_exit();

#endif