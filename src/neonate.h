#ifndef NEONATE_H
#define NEONATE_H

#include <stdio.h>
#include <termios.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include "extra_functions.h"

void disableRawMode();
void enableRawMode();
void neonate(char*command);

#endif