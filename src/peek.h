#ifndef PEEK_H
#define PEEK_H

#include "colours.h"
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdbool.h>
#include "time.h"
#include "extra_functions.h"
#include "grp.h"
#include "main.h"




// void ls(ArgList *args);
void print_ls(char *path, bool l, bool a);
#define COLOR_DIRECTORY BLUE  
#define COLOR_EXECUTABLE GREEN 
#define COLOR_FILES WHITE
#define COLOR_RESET RESET

void file_details(char *path, char*filename);

int compare(const void*a, const void*b);
int peek_peek(char *Command_words_list);


#endif