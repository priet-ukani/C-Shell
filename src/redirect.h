#ifndef REDIRECT_H
#define REDIRECT_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include "extra_functions.h"
#include "main.h"
#include "execute.h"


void modify_command(int curr_indx);
void Redirect(char* command, int curr_indx);


#endif