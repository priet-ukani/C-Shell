#ifndef PEEK_H
#define PEEK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/utsname.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <dirent.h>


#define COLOR_DIRECTORY BLUE  
#define COLOR_EXECUTABLE GREEN 
#define COLOR_FILES WHITE
#define COLOR_RESET RESET

int compare(const void*a, const void*b);
void peek_peek(char *command);


#endif