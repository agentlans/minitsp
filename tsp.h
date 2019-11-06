#ifndef _TSP
#define _TSP

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

// Struct that holds coordinates for travelling salesman problem
typedef struct Coordinates
{
	int rows;
	int cols;
	double *mat;
} Coordinates;

double sq_distance(Coordinates *coords, int i, int j);
double round_trip_distance(int **result, Coordinates *coords);
void swap(int **result, int i, int j);
void reverse(int **result, int i, int j);
void greedy(int **result, Coordinates *coords);
void check_shortcuts(int **result, Coordinates *coords);

#endif

