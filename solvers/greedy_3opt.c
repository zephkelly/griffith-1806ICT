#include "greedy_3opt.h"
#include <stdlib.h>
#include <stdio.h>

#include "greedy_3opt.h"
#include "../tsp_structures.h"
#include "../tsp_utils.h"

// https://www.geeksforgeeks.org/travelling-salesman-problem-greedy-approach/

int generate_random_tour_with_distance(TSPData *problem, Tour *tour);
void solve_greedy_3opt(Solver *self, TSPData *problem, int time_limit, Tour *tour);
void improve_tour_3opt(TSPData *problem, int *path, int *total_distance, int time_limit);

void reverse(int *path, int i, int j);
void apply_3opt_move(int *path, int i, int j, int k, int n);
int calculate_2opt_distance_delta(TSPData *problem, int *path, int i, int j, int k);

Solver* create_greedy_3opt_solver()
{
    Greedy3OptSolver* solver = malloc(sizeof(Greedy3OptSolver));
    solver->base.solve = solve_greedy_3opt;
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

    for (int i = 0; i < n + 1; i++)
    {
        printf("tour_by_city_id[%d]: %d\n", i, tour->tour_by_city_id[i]);
    }

    total_distance += calculate_euclidean_distance(&problem->cities[tour->tour_by_city_id[n-1]], &problem->cities[tour->tour_by_city_id[0]]);
    return total_distance;
}

void solve_greedy_3opt(Solver *self, TSPData *problem, int time_limit, Tour *tour)
{
    Greedy3OptSolver *solver = (Greedy3OptSolver*) self;
    int n = problem->dimension + 1;

    int initial_distance = generate_random_tour_with_distance(problem, tour);

    printf("Initial Distance: %d\n", initial_distance);

    improve_tour_3opt(problem, tour->tour_by_city_id, &initial_distance, time_limit);

    tour->tour_distance = 0.0;

    for (int i = 0; i < n - 1; i++)
    {
        tour->tour_distance += calculate_euclidean_distance(&problem->cities[tour->tour_by_city_id[i]], &problem->cities[tour->tour_by_city_id[(i+1)%n]]);
    }

    tour->tour_distance += calculate_euclidean_distance(&problem->cities[tour->tour_by_city_id[n-1]], &problem->cities[tour->tour_by_city_id[0]]);
    tour->tour_by_city_id[n-1] = -1;
    tour->cities_visited = n - 1;
}

void improve_tour_3opt(TSPData *problem, int *path, int *total_distance, int time_limit)
{
    int n = problem->dimension;
    time_t start_time = time(NULL);
    int improvements = 1;
    
    while (improvements && (time(NULL) - start_time < time_limit))
    {
        improvements = 0;

        for (int i = 0; i < n - 2; i++)
        {
            for (int j = i + 1; j < n - 1; j++)
            {
                for (int k = j + 1; k < n; k++)
                {
                    int best_delta = calculate_2opt_distance_delta(problem, path, i, j, k);

                    if (best_delta > 0)
                    {
                        apply_3opt_move(path, i, j, k, n);
                        *total_distance -= best_delta;
                        improvements = 1;
                    }
                }
            }
        }
    }
}

int calculate_2opt_distance_delta(TSPData *problem, int *path, int i, int j, int k)
{
    int a = path[i];
    int b = path[(i + 1) % problem->dimension];

    int c = path[j];
    int d = path[(j + 1) % problem->dimension];

    int e = path[k];
    int f = path[(k + 1) % problem->dimension];

    int d0 = calculate_euclidean_distance(&problem->cities[a], &problem->cities[b]) +
            calculate_euclidean_distance(&problem->cities[c], &problem->cities[d]) +
            calculate_euclidean_distance(&problem->cities[e], &problem->cities[f]);

    int d1 = calculate_euclidean_distance(&problem->cities[a], &problem->cities[c]) +
            calculate_euclidean_distance(&problem->cities[b], &problem->cities[e]) +
            calculate_euclidean_distance(&problem->cities[d], &problem->cities[f]);

    return d0 - d1;
}

void apply_3opt_move(int *path, int i, int j, int k, int n)
{
    reverse(path, i+1, j);
    reverse(path, j+1, k);
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