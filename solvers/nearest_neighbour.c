#include "nearest_neighbour.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "../tsp_utils.h"

// https://sindhukumari.medium.com/traveling-salesman-problem-9deb6853ac6

Solver* create_nearest_neighbour_solver()
{
    NearestNeighbourSolver* solver = malloc(sizeof(NearestNeighbourSolver));
    // solver->base.solve = solve_nearest_neighbour;
    // solver->base.free = free_nearest_neighbour;
    solver->base.find_distances = find_distances_nearest_neighbour;
    return (Solver*) solver;
}


void find_distances_nearest_neighbour(Solver *self, TSPData *problem)
{
    NearestNeighbourSolver *solver = (NearestNeighbourSolver*) self;
    printf("Finding distances for Nearest Neighbour Solver\n");

    printf("NN: Calculating distances for %d cities\n", problem->dimension);
    clock_t start = clock();

    for (int i = 0; i < problem->dimension; i++)
    {
        for (int j = 0; j < problem->dimension; j++)
        {
            if (i == j)
            {
                continue;
            }

            const City city1 = problem->cities[i];
            const City city2 = problem->cities[j];

            double distance = calculate_distance(&city1, &city2);
        }
    }

    clock_t end = clock();
    double time_taken = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("NN: Time taken to calculate distances: %f\n", time_taken);

    printf("NN: Calculating squared distances\n");
    start = clock();

    for (int i = 0; i < problem->dimension; i++)
    {
        for (int j = 0; j < problem->dimension; j++)
        {
            if (i == j)
            {
                continue;
            }

            City city1 = problem->cities[i];
            City city2 = problem->cities[j];

            double distance = calculate_squared_distance(&city1, &city2);
        }
    }

    end = clock();

    time_taken = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("NN: Time taken to calculate squared distances: %f\n", time_taken);
}