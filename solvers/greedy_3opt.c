#include "greedy_3opt.h"
#include <stdlib.h>
#include <stdio.h>

#include "greedy_3opt.h"
#include "../tsp_structures.h"
#include "../tsp_utils.h"

// https://www.geeksforgeeks.org/travelling-salesman-problem-greedy-approach/

int generate_random_tour_with_distance(TSPData *problem, Tour *tour);

Solver* create_greedy_3opt_solver()
{
    Greedy3OptSolver* solver = malloc(sizeof(Greedy3OptSolver));
    printf("Greedy 3-Opt Solver Created\n");
    solver->base.solve = solve_greedy_3opt;
    return (Solver*) solver;
}

int generate_random_tour_with_distance(TSPData *problem, Tour *tour)
{
    srand(time(NULL));

    int n = problem->dimension;
    int total_distance = 0.0;
    tour->tour_by_city_id = (int*)malloc((problem->dimension + 1) * sizeof(int));

    if (tour->tour_by_city_id != NULL)
    {
        free(tour->tour_by_city_id);
    }

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

void solve_greedy_3opt(Solver *self, TSPData *problem, int time_limit, Tour *tour)
{
    Greedy3OptSolver *solver = (Greedy3OptSolver*) self;
    int n = problem->dimension;

    tour->tour_by_city_id = (int*)malloc((problem->dimension + 1) * sizeof(int));

    int initial_distance = generate_random_tour_with_distance(problem, tour);

    printf("Initial Distance: %d\n", initial_distance);

}

