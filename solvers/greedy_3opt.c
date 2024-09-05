#include "greedy_3opt.h"
#include <stdlib.h>
#include <stdio.h>

#include "greedy_3opt.h"
#include "../tsp_structures.h"

// https://www.geeksforgeeks.org/travelling-salesman-problem-greedy-approach/

void generate_random_tour(int *tour, int n);

Solver* create_greedy_3opt_solver()
{
    Greedy3OptSolver* solver = malloc(sizeof(Greedy3OptSolver));
    solver->base.solve = solve_greedy_3opt;
    return (Solver*) solver;
}


void solve_greedy_3opt(Solver *self, TSPData *problem, int time_limit, Tour *calculated_tour)
{
    Greedy3OptSolver *solver = (Greedy3OptSolver*) self;

    clock_t start_time = clock();

    calculated_tour->tour_by_city_id = (int*)malloc((problem->dimension + 1) * sizeof(int));
    generate_random_tour(calculated_tour->tour_by_city_id, problem->dimension);

    for (int i = 0; i < problem->dimension; i++)
    {
        printf("%d ", calculated_tour->tour_by_city_id[i] + 1);
    }
}

void generate_random_tour(int *tour, int n)
{
    for (int i = 0; i < n; i++)
    {
        tour[i] = i;
    }
    for (int i = n - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        int temp = tour[i];
        tour[i] = tour[j];
        tour[j] = temp;
    }
}