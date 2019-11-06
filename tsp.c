#include "tsp.h"

// Squared distance between points i and j
double sq_distance(Coordinates *coords, int i, int j)
{
	double d = 0;
	int dim = coords->cols;
	int i_start = i * dim, j_start = j * dim;
	for (int k = 0; k < dim; ++k) {
		d += pow(coords->mat[i_start + k] - coords->mat[j_start + k], 2);
	}
	return d;
}

// Returns the distance of a travelling salesman problem solution
// result is pointer to integer array containing indices of the points in the path in order
double round_trip_distance(int **result, Coordinates *coords)
{
	double d = 0;
	int num_pts = coords->rows;
	for (int i = 0; i < num_pts; ++i) {
		d += sqrt(sq_distance(coords, 
			(*result)[i], (*result)[(i+1) % num_pts]));
	}
	return d;
}

// Swaps elements at position i and j of result variable
void swap(int **result, int i, int j)
{
	int tmp = (*result)[i];
	(*result)[i] = (*result)[j];
	(*result)[j] = tmp;
}

// Reverses the part of result from [i, j). Assumes i < j.
void reverse(int **result, int i, int j)
{
	int low = i, high = j-1;
	while (low < high) {
		swap(result, low, high);
		low++;
		high--;
	}
}

// Does greedy algorithm for the travelling salesman problem and saves result
void greedy(int **result, Coordinates *coords)
{
	// Initialize the variable which will contain the results
	int num_pts = coords->rows;
	*result = calloc(num_pts, sizeof(int));
	for (int i = 0; i < num_pts; ++i) {
		(*result)[i] = i;
	}
	// Start with first vertex and search nearest neighbours
	for (int v1 = 0; v1 < num_pts; ++v1) {
		// Find closest vertex to result[v1]
		int where_found = 0;
		double closest_dist = DBL_MAX;
		for (int v2 = v1 + 1; v2 < num_pts; ++v2) {
			// The vertex that's currently in next position
			int v2_ind = (*result)[v2 % num_pts];
			double dist = sq_distance(coords, (*result)[v1], v2_ind);
			if (dist < closest_dist) {
				closest_dist = dist;
				where_found = v2;
			}
		}
		// Swap next vertex for the closest one
		swap(result, v1 + 1, where_found);
	}
}

// See which paths can be reversed to give shorter distance and then reverses them
// Assumes the result variable is already initialized
void check_shortcuts(int **result, Coordinates *coords)
{
	int num_pts = coords->rows;
	for (int i = 0; i < num_pts; ++i) {
		int v_i1 = (*result)[i-1 % num_pts];
		int v_i = (*result)[i];

		// Distance from vertex at result[i-1] to result[i]
		double dist_before_i = sq_distance(coords, v_i1, v_i);

		for (int j = i+1; j < num_pts; ++j) {
			int v_j1 = (*result)[j-1];
			int v_j = (*result)[j % num_pts];

			// Distance from vertex at result[j-1] to result[j]
			double dist_before_j = sq_distance(coords, v_j1, v_j);

			// Distance before we reverse [i, j)
			double original_dist = dist_before_i + dist_before_j;
			// Distance after we reverse [i, j)
			double new_dist =
				sq_distance(coords, v_i1, v_j1) +
				sq_distance(coords, v_i, v_j);

			// If new distance is shorter then we reverse
			if (new_dist < original_dist) {
				reverse(result, i, j);
			}
		}
	}
}

