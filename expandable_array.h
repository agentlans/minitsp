#ifndef _EXPANDABLEARRAY
#define _EXPANDABLEARRAY

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ExpandableArray
{
	int size;
	int capacity;
	double *contents;
} ExpandableArray;

void init_array(ExpandableArray *arr);
void free_array(ExpandableArray *arr);
void push_back(ExpandableArray *arr, double x);
int read_numbers_into(ExpandableArray *ea, char *str);

#endif

