#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

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
    int tour_length = 0;
    NearestCityInfo *nearest_cities = (NearestCityInfo*)malloc(n * sizeof(NearestCityInfo));
    double total_tour_length = 0.0;
    
    time_t start_time = time(NULL);
    time_t solution_time_limit = start_time + time_limit;

    if (tour_by_city_index == NULL || nearest_cities == NULL)
    {
        printf("Memory allocation failed\n");
        free(tour_by_city_index);
        free(nearest_cities);
    }

    int current_city = 0;
    tour_by_city_index[tour_length++] = current_city;

    for (int i = 0; i < n; i++)
    {
        if (i != current_city)
        {
            nearest_cities[i].city_index = current_city;
            nearest_cities[i].squared_distance = calculate_squared_distance(&problem->cities[current_city], &problem->cities[i]);
        }
        else
        {
            nearest_cities[i].city_index = -1;
            nearest_cities[i].squared_distance = INFINITY;
        }
    }
}