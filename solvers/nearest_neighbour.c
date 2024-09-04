#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "nearest_neighbour.h"
#include "../tsp_utils.h"
#include "../tsp_structures.h"

// https://sindhukumari.medium.com/traveling-salesman-problem-9deb6853ac6

Solver* create_nearest_neighbour_solver()
{
    NearestNeighbourSolver* solver = malloc(sizeof(NearestNeighbourSolver));
    solver->base.solve = solve_nearest_neighbour;
    return (Solver*) solver;
}

void solve_nearest_neighbour(Solver *self, TSPData *problem, int time_limit)
{
    NearestNeighbourSolver *solver = (NearestNeighbourSolver*) self;

    int n = problem->dimension;
    int *tour_by_city_index = (int*)malloc((n + 1) * sizeof(int));
    int *visited_cities = (int*)malloc(n * sizeof(int));
    NearestCityInfo *nearest_cities = (NearestCityInfo*)malloc(n * sizeof(NearestCityInfo));
    double total_tour_length = 0.0;
    time_t start_time = time(NULL);


    if (!tour_by_city_index || !visited_cities || !nearest_cities)
    {
        printf("Memory allocation failed\n");
    }
}