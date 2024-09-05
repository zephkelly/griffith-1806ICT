#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#include "nearest_neighbour.h"
#include "../tsp_utils.h"
#include "../tsp_structures.h"

Solver* create_nearest_neighbour_solver()
{
    NearestNeighbourSolver* solver = malloc(sizeof(NearestNeighbourSolver));
    solver->base.solve = solve_nearest_neighbour;
    return (Solver*) solver;
}

int check_time_and_progress(clock_t start_time, clock_t *last_update_time, int time_limit, int cities_visited, double total_tour_distance)
{
    clock_t current_time = clock();
    double elapsed_time = (double)(current_time - start_time) / CLOCKS_PER_SEC;
    
    if ((double)(current_time - *last_update_time) / CLOCKS_PER_SEC >= 5.0)
    {
        printf("    Progress update: %d cities visited, current tour distance: %.2f\n", cities_visited, total_tour_distance);
        *last_update_time = current_time;
    }
    
    return elapsed_time >= time_limit;
}

void solve_nearest_neighbour(Solver *self, TSPData *problem, int time_limit, Tour *calculated_tour)
{
    NearestNeighbourSolver *solver = (NearestNeighbourSolver*) self;

    int n = problem->dimension;
    int *tour_by_city_id = (int*)malloc((n + 1) * sizeof(int));
    int cities_visited = 0;
    double total_tour_distance = 0.0;
    calculated_tour->early_stop = 0;
    
    clock_t start_time = clock();
    clock_t last_update_time = start_time;

    if (tour_by_city_id == NULL)
    {
        printf("Memory allocation failed\n");
        free(tour_by_city_id);
    }

    int current_city = 0;
    tour_by_city_id[cities_visited++] = current_city;

    for (int i = 1; i < n; i++) 
    {
        if (check_time_and_progress(start_time, &last_update_time, time_limit, cities_visited, total_tour_distance))
        {
            printf("Time limit reached. Stopping early.\n\n");
            calculated_tour->early_stop = 1;
            break;
        }

        int next_city = -1;
        double min_squared_distance = INFINITY;

        for (int j = 0; j < n; j++)
        {
            if (j != current_city && !is_in_tour(tour_by_city_id, cities_visited, j))
            {
                double distance = calculate_squared_distance(&problem->cities[current_city], &problem->cities[j]);
                if (distance < min_squared_distance)
                {
                    min_squared_distance = distance;
                    next_city = j;
                }
            }
        }

        if (next_city == -1)
        {
            fprintf(stderr, "Error: No nearest city found\n");
            break;
        }

        tour_by_city_id[cities_visited++] = next_city;
        total_tour_distance += calculate_euclidean_distance(&problem->cities[tour_by_city_id[cities_visited-2]], &problem->cities[next_city]);
        current_city = next_city;
    }

    if (cities_visited == n)
    {
        total_tour_distance += calculate_euclidean_distance(&problem->cities[current_city], &problem->cities[tour_by_city_id[0]]);
    }

    tour_by_city_id[cities_visited++] = -1;
    clock_t end_time = clock();
    double solution_elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    calculated_tour->problem_name = problem->name;
    calculated_tour->elapsed_time = solution_elapsed_time;
    calculated_tour->tour_distance = total_tour_distance;
    calculated_tour->cities_visited = cities_visited;
    calculated_tour->tour_by_city_id = tour_by_city_id;

    if (calculated_tour->tour_by_city_id == NULL) {
        printf("Memory allocation failed for tour_by_city_id\n");
        free(tour_by_city_id);
        return;
    }
}

int is_in_tour(int *tour_by_city_id, int cities_visited, int city)
{
    for (int i = 0; i < cities_visited; i++)
    {
        if (tour_by_city_id[i] == city) return 1;
    }

    return 0;
}