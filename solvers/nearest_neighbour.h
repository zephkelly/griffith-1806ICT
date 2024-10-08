#ifndef NEAREST_NEIGHBOUR_H
#define NEAREST_NEIGHBOUR_H

#include "../tsp_solver.h"
#include "../tsp_structures.h"

typedef struct NearestNeighbourSolver {
    Solver base;
} NearestNeighbourSolver;

Solver* create_nearest_neighbour_solver();

void solve_nearest_neighbour(Solver *self, TSPData *problem, int time_limit, Tour *calculated_tour);

int is_in_tour(int *tour, int tour_length, int city);

#endif