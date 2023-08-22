#ifndef SEEK_H
#define SEEK_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include "main.h"
#include "extra_functions.h"


void searchFile(char *path, char *name, bool searchFiles, bool searchDirs);
int seek_seek(char*command);

#endif