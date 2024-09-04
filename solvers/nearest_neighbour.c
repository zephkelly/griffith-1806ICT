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
    double total_tour_length = 0.0;
    
    time_t start_time = time(NULL);
    time_t solution_time_limit = start_time + time_limit;

    if (tour_by_city_index == NULL)
    {
        printf("Memory allocation failed\n");
        free(tour_by_city_index);
    }

    int current_city = 0;
    tour_by_city_index[tour_length++] = current_city;

    // Sort the nearest cities by distance
    for (int iter = 1; iter < n && time(NULL) < solution_time_limit; iter++) 
    {
        int next_city = -1;
        double min_squared_distance = INFINITY;

        // Find the overall nearest unvisited city
        for (int i = 0; i < n; i++)
        {
            if (i != current_city && !is_in_tour(tour_by_city_index, tour_length, i))
            {
                double distance = calculate_squared_distance(&problem->cities[current_city], &problem->cities[i]);
                if (distance < min_squared_distance)
                {
                    min_squared_distance = distance;
                    next_city = i;
                }
            }
        }

        if (next_city == -1)
        {
            fprintf(stderr, "Error: No nearest city found\n");
            break;
        }

        tour_by_city_index[tour_length++] = next_city;
        total_tour_length += calculate_euclidean_distance(&problem->cities[tour_by_city_index[tour_length-2]], &problem->cities[next_city]);
        current_city = next_city;
    }

    if (tour_length == n)
    {
        total_tour_length += calculate_euclidean_distance(&problem->cities[current_city], &problem->cities[tour_by_city_index[0]]);
        tour_by_city_index[tour_length++] = tour_by_city_index[0];
    }

    printf("Total Tour Length: %f\n", total_tour_length);
    printf("Tour Length: %d\n", tour_length);
}

int is_in_tour(int *tour_by_city_index, int tour_length, int city)
{
    for (int i = 0; i < tour_length; i++)
    {
        if (tour_by_city_index[i] == city) return 1;
    }

    return 0;
}