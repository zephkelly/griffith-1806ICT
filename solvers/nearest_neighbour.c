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

Tour solve_nearest_neighbour(Solver *self, TSPData *problem, int time_limit)
{
    NearestNeighbourSolver *solver = (NearestNeighbourSolver*) self;

    int n = problem->dimension;
    int *tour_by_city_index = (int*)malloc((n + 1) * sizeof(int));
    int cities_toured = 0;
    double total_tour_distance = 0.0;
    
    time_t start_time = time(NULL);
    time_t solution_time_limit = start_time + time_limit;

    if (tour_by_city_index == NULL)
    {
        printf("Memory allocation failed\n");
        free(tour_by_city_index);
    }

    int current_city = 0;
    tour_by_city_index[cities_toured++] = current_city;

    // Sort the nearest cities by distance
    for (int iter = 1; iter < n && time(NULL) < solution_time_limit; iter++) 
    {
        int next_city = -1;
        double min_squared_distance = INFINITY;

        // Find the overall nearest unvisited city
        for (int i = 0; i < n; i++)
        {
            if (i != current_city && !is_in_tour(tour_by_city_index, cities_toured, i))
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

        tour_by_city_index[cities_toured++] = next_city;
        total_tour_distance += calculate_euclidean_distance(&problem->cities[tour_by_city_index[cities_toured-2]], &problem->cities[next_city]);
        current_city = next_city;
    }

    if (cities_toured == n)
    {
        total_tour_distance += calculate_euclidean_distance(&problem->cities[current_city], &problem->cities[tour_by_city_index[0]]);
        tour_by_city_index[cities_toured++] = -1;
    }

    time_t end_time = time(NULL);
    time_t elapsed_time = end_time - start_time;

    Tour calculated_tour = {
        .problem_name = problem->name,
        .solver_name = "Nearest Neighbour",
        .time_taken = elapsed_time,
        .tour_distance = total_tour_distance,
        .tour_by_city_id = (int*)malloc(cities_toured * sizeof(int))
    };

    printf("Problem Name: %s.tsp\n", calculated_tour.problem_name);
    printf("Solver Used: %s\n", calculated_tour.solver_name);
    printf("Time Taken: %ld\n", calculated_tour.time_taken);
    printf("Tour Distance: %f\n", calculated_tour.tour_distance);
    printf("Cities visited:\n");

    for (int i = 0; i < cities_toured; i++)
    {
        calculated_tour.tour_by_city_id[i] = problem->cities[tour_by_city_index[i]].id;
        printf(" %d\n", calculated_tour.tour_by_city_id[i]);
    }

    free(tour_by_city_index);
    return calculated_tour;
}

int is_in_tour(int *tour_by_city_index, int cities_toured, int city)
{
    for (int i = 0; i < cities_toured; i++)
    {
        if (tour_by_city_index[i] == city) return 1;
    }

    return 0;
}