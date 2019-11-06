#include "expandable_array.h"

// Initializes an expandable array
void init_array(ExpandableArray *arr)
{
	arr->size = 0;
	arr->capacity = 100;
	arr->contents = calloc(100, sizeof(double));
	if (arr->contents == NULL) {
		fprintf(stderr, "Can't allocate memory for expandable array.");
		exit(1);
	}
}

// Frees memory allocated to an expandable array
void free_array(ExpandableArray *arr)
{
	free(arr->contents);
}

// Pushes x to the end of ExpandableArray
void push_back(ExpandableArray *arr, double x)
{
	int start_ind = arr->size;
	// Expand array to hold new element
	if (start_ind >= arr->capacity) {
		arr->capacity *= 2;
		arr->contents = realloc(arr->contents, sizeof(double)*arr->capacity);
		if (arr->contents == NULL) {
			fprintf(stderr, "Can't reallocate memory.");
			exit(1);
		}
	}
	arr->contents[start_ind] = x;
	arr->size++;
}

// Reads the numbers in str into array and returns number of elements read.
int read_numbers_into(ExpandableArray *ea, char *str)
{
	// Keep track of where we are in string
	char *ptr = str;
	char *endptr = NULL;
	int num_read = 0;
	while (1) {
		// Try to read value
		double val = strtod(ptr, &endptr);
		if (ptr == endptr) {
			break;
		} else {
			// Put the number read into the array
			push_back(ea, val);
		}
		ptr = endptr;
		num_read++;
	}
	return num_read;
}

