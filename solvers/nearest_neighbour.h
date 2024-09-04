#ifndef NEAREST_NEIGHBOUR_H
#define NEAREST_NEIGHBOUR_H

#include "../tsp_solver.h"

typedef struct NearestNeighbourSolver {
    Solver base;
} NearestNeighbourSolver;

Solver* create_nearest_neighbour_solver();

void find_distances_nearest_neighbour(Solver *self, TSPData *problem);

#endif