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


#define COLOR_DIRECTORY BLUE  // Blue
#define COLOR_EXECUTABLE "\x1B[32m" // Green
#define COLOR_FILES WHITE

int compare(const void*a, const void*b);
void peek_peek(char *command);


#endif