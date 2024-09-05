#include "greedy_3opt.h"
#include <stdlib.h>
#include <stdio.h>

#include "../tsp_structures.h"
#include "../tsp_utils.h"

// https://www.geeksforgeeks.org/travelling-salesman-problem-greedy-approach/

int generate_random_tour_with_distance(TSPData *problem, Tour *tour);
void solve(Solver *self, TSPData *problem, int time_limit, Tour *tour);
void improve_tour_3opt(TSPData *problem, int *path, int *total_distance, int time_limit);

void reverse(int *path, int i, int j);

typedef struct {
    int delta;
    int best_case;
} DeltaMove;


Solver* create_greedy_3opt_solver()
{
    Greedy3OptSolver* solver = malloc(sizeof(Greedy3OptSolver));
    solver->base.solve = solve;
    return (Solver*) solver;
}

int generate_random_tour_with_distance(TSPData *problem, Tour *tour)
{
    srand(time(NULL));

    int n = problem->dimension;
    int total_distance = 0.0;

    if (tour->tour_by_city_id != NULL)
    {
        free(tour->tour_by_city_id);
    }

    tour->tour_by_city_id = (int*)malloc((problem->dimension + 1) * sizeof(int));

    if (tour->tour_by_city_id == NULL)
    {
        printf("Failed to allocate memory for tour.\n");
        return -1.0;
    }
 
    for (int i = 0; i < n; i++)
    {
        tour->tour_by_city_id[i] = i;
    }

    for (int i = n - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        int temp = tour->tour_by_city_id[i];
        tour->tour_by_city_id[i] = tour->tour_by_city_id[j];
        tour->tour_by_city_id[j] = temp;

        if (i > 1)
        {
            total_distance += calculate_euclidean_distance(&problem->cities[tour->tour_by_city_id[i]], &problem->cities[tour->tour_by_city_id[i-1]]);
        }
    }

    total_distance += calculate_euclidean_distance(&problem->cities[tour->tour_by_city_id[n-1]], &problem->cities[tour->tour_by_city_id[0]]);
    return total_distance;
}

DeltaMove calculate_3opt_best_move(void *dist, int a, int b, int c, int d, int e, int f, int dimensions)
{
    int (*matrix)[dimensions] = dist;

	int deleted_edges = matrix[a][b] + matrix[c][d] + matrix[e][f];

	int delta_options[8];

	delta_options[0] = 0; // No move
	delta_options[1] = matrix[a][e] + matrix[b][f] - matrix[a][b] - matrix[e][f];
	delta_options[2] = matrix[c][e] + matrix[d][f] - matrix[c][d] - matrix[e][f];
	delta_options[3] = matrix[a][c] + matrix[b][d] - matrix[a][b] - matrix[c][d];
	delta_options[4] = matrix[a][c] + matrix[b][e] + matrix[d][f] - deleted_edges;
	delta_options[5] = matrix[a][e] + matrix[d][b] + matrix[c][f] - deleted_edges;
	delta_options[6] = matrix[a][d] + matrix[e][c] + matrix[b][f] - deleted_edges;
	delta_options[7] = matrix[a][d] + matrix[e][b] + matrix[c][f] - deleted_edges;

	int best_delta = 0;
	int best_move = 0;
	int i;

	for (i = 1; i < 8; i++)
    {
		if (delta_options[i] < 0 && delta_options[i] < best_delta)
        {
			best_move = i;
			best_delta = delta_options[i];
		}
	}

    DeltaMove best_delta_move = {best_delta, best_move};

    return best_delta_move;
}

void solve(Solver *self, TSPData *problem, int time_limit, Tour *tour)
{
    Greedy3OptSolver *solver = (Greedy3OptSolver*) self;
    int n = problem->dimension + 1;

    int initial_distance = generate_random_tour_with_distance(problem, tour);

    printf("Initial Distance: %d\n", initial_distance);

    int (*distance_matrix)[n] = malloc(sizeof(int[n][n]));

    for (int i = 0; i < n; i++)
    {
		for (int j = 0; j < n; j++)
        {
            const City *city1 = &problem->cities[tour->tour_by_city_id[i]];
            const City *city2 = &problem->cities[tour->tour_by_city_id[j]];

            distance_matrix[i][j] = calculate_euclidean_distance(city1, city2);
		}
	}

    // City indexes
    int i, j, k, a, b, c, d, e, f, improving = 1;

    int best_move = 0;

    while (improving)
    {
        improving = 0;
        int improved_this_iteration = 0;

        int case_1, case_2, case_3 = 0; // Edges

        for (case_1 = 0; case_1 < n; case_1++)
        {
            i = case_1;
            a = tour->tour_by_city_id[i]; // Index i
            b = tour->tour_by_city_id[(i+1) % n]; // Index i+1

            for (case_2 = 1; case_2 < n - 2; case_2++)
            {
                j = (i + case_2) % n;
                c = tour->tour_by_city_id[j];
                d = tour->tour_by_city_id[(j+1) % n];

                for (case_3 = case_2 + 1; case_3 < n; case_3++)
                {
                    k = (i + case_3) % n;
                    e = tour->tour_by_city_id[k];
                    f = tour->tour_by_city_id[(k+1) % n];

                    DeltaMove best_move = calculate_3opt_best_move(distance_matrix, a, b, c, d, e, f, n);
                    printf("Best Move: %d\n", best_move.delta);
                }
            }
        }
    }

    // improve_tour_3opt(problem, tour->tour_by_city_id, &initial_distance, time_limit);

    // tour->tour_distance = 0.0;

    // for (int i = 0; i < n - 1; i++)
    // {
    //     tour->tour_distance += calculate_euclidean_distance(&problem->cities[tour->tour_by_city_id[i]], &problem->cities[tour->tour_by_city_id[(i+1)%n]]);
    // }

    // tour->tour_by_city_id[n-1] = -1;
    // tour->tour_distance += calculate_euclidean_distance(&problem->cities[tour->tour_by_city_id[n-1]], &problem->cities[tour->tour_by_city_id[0]]);
    // tour->cities_visited = n;
}

void reverse(int *path, int start, int end)
{
    while (start < end) {
        int temp = path[start];
        path[start] = path[end];
        path[end] = temp;
        start++;
        end--;
    }
}

void apply_3opt_move(int *path, int best_move, int i, int j, int k, int n)
{

}