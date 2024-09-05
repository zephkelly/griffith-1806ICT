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

void solve(Solver *self, TSPData *problem, int time_limit, Tour *tour)
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

    tour->tour_by_city_id[n-1] = -1;
    tour->tour_distance += calculate_euclidean_distance(&problem->cities[tour->tour_by_city_id[n-1]], &problem->cities[tour->tour_by_city_id[0]]);
    tour->cities_visited = n;
}

typedef struct {
    int delta;
    int best_case;
} BestMove;


BestMove calculate_3opt_best_move(TSPData *problem, int *path, int i, int j, int k)
{
    int max_delta = 0;
    int best_case = 0;
    BestMove best_move = {max_delta, best_case};

    return best_move;
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
                    BestMove best_move = calculate_3opt_best_move(problem, path, i, j, k);

                    if (best_move.best_case != 0)
                    {
                        apply_3opt_move(path, best_move.best_case, i, j, k, n);
                        *total_distance -= best_move.delta;

                        printf("Total Distance: %d\n", *total_distance);
                        improvements = 1;
                    }
                }
            }
        }
    }
}