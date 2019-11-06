#ifndef _READTABLE
#define _READTABLE

#include <stdio.h>
#include "expandable_array.h"

extern const int MAX_LINE_LENGTH;

int read_table(ExpandableArray *ea, char *filename);

#endif

