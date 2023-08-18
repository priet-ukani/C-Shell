#ifndef PEEK_H
#define PEEK_H

#include "colours.h"
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define COLOR_DIRECTORY BLUE  
#define COLOR_EXECUTABLE GREEN 
#define COLOR_FILES WHITE
#define COLOR_RESET RESET

int compare(const void*a, const void*b);
int peek_peek(char *command);


#endif