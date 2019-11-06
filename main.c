#include <stdio.h>
#include "read_table.h"
#include "tsp.h"

// clang -g main.c read_table.c tsp.c expandable_array.c -lm

int main(int argc, char *argv[])
{
	// Read parameters
	if (argc == 1 || argc > 3) {
		printf("Usage: ./minitsp filename [rounds]\n");
		exit(1);
	}
	char *filename = argv[1];
	int shortcut_rounds = 20; // default number of rounds
	if (argc == 3) {
		shortcut_rounds = atoi(argv[2]);
	}
	if (shortcut_rounds < 1) {
		fprintf(stderr, "Warning: skipping shortcut finding.\n");
		shortcut_rounds = 0;
	}

	// Read file into array
	ExpandableArray ea;
	init_array(&ea);
	int cols = read_table(&ea, filename);

	// Create a Coordinates format object
	Coordinates c;
	c.cols = cols;
	c.rows = (ea.size + 0.0) / cols;
	c.mat = ea.contents;

	// Do greedy algorithm and check for shortcuts
	int *result = NULL;
	greedy(&result, &c);
	for (int i = 0; i < shortcut_rounds; ++i) {
		check_shortcuts(&result, &c);
	}

	// Show solution
	int num_pts = c.rows;
	for (int i = 0; i < num_pts; ++i) {
		printf("%d\n", result[i]);
	}

	// Clean up
	free(result);
	free_array(&ea);

	return 0;
}

