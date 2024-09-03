#include "nearest_neighbour.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct NearestNeighbourSolver {
    Solver base;
} NearestNeighbourSolver;

// https://sindhukumari.medium.com/traveling-salesman-problem-9deb6853ac6

Solver* create_nearest_neighbour_solver() {
    NearestNeighbourSolver* solver = malloc(sizeof(NearestNeighbourSolver));
    printf("Nearest Neighbour Solver Created\n");
    // solver->base.solve = solve_nearest_neighbour;
    // solver->base.free = free_nearest_neighbour;
    return (Solver*) solver;
}