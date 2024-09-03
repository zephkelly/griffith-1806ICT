#include "nearest_neighbour.h"
#include <stdlib.h>

typedef struct NearestNeighbourSolver {
    Solver base;
} NearestNeighbourSolver;

Solver* create_nearest_neighbour_solver() {
    NearestNeighbourSolver* solver = malloc(sizeof(NearestNeighbourSolver));
    // solver->base.solve = solve_nearest_neighbour;
    // solver->base.free = free_nearest_neighbour;
    return (Solver*) solver;
}