#include "read_table.h"

const int MAX_LINE_LENGTH = 256;

// Reads the number contents of filename into an already-initialized ExpandableArray.
// Returns the number of entries per line.
int read_table(ExpandableArray *ea, char *filename)
{
	// Open file containing coordinates
	FILE *ptr;
	ptr = fopen(filename, "r");
	if (ptr == NULL) {
		fprintf(stderr, "Can't open file.\n");
		free_array(ea);
		exit(1);
	}
	int cols = -1;
	// Read each line
	char str[MAX_LINE_LENGTH];
	while (fgets(str, MAX_LINE_LENGTH, ptr) != NULL) {
		int num_read = read_numbers_into(ea, str);
		if (num_read == 0) {
			fprintf(stderr, 
				"Warning: Blank or unparseable line ignored.\n");
		}
		if (num_read != 0 && cols == -1) {
			cols = num_read;
		}
		if (num_read != cols && num_read != 0) {
			fprintf(stderr, "Irregular line in file.\n");
			free_array(ea);
			exit(1);
		}
		//printf("%d\n", num_read);
	}
	if (ferror(ptr)) {
		fprintf(stderr, "Error reading file.\n");
		free_array(ea);
		exit(1);
	}
	// Clean up
	fclose(ptr);
	// Return number of columns in file
	return cols;
}

