#include "nearest_neighbour.h"
#include <stdlib.h>
#include <stdio.h>

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
}