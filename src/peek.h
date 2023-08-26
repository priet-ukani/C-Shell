#ifndef PEEK_H
#define PEEK_H

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <unistd.h> // Include for X_OK constant

// ANSI escape codes for text color
#define COLOR_RESET   "\x1B[0m"
#define COLOR_GREEN   "\x1B[32m"
#define COLOR_BLUE    "\x1B[34m"

// void ls(ArgList *args);
void print_ls(char *path, bool l, bool a);
#define COLOR_DIRECTORY BLUE  
#define COLOR_EXECUTABLE GREEN 
#define COLOR_FILES WHITE

char *get_permissions(mode_t mode);
void file_details(char *path, char*filename);

int compare(const void*a, const void*b);
int peek_peek(char *Command_words_list);


#endif