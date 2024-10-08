#ifndef GREEDY_3OPT_H
#define GREEDY_3OPT_H

#include "../tsp_solver.h"

typedef struct Greedy3OptSolver {
    Solver base;
} Greedy3OptSolver;

Solver* create_greedy_3opt_solver();

void solve_greedy_3opt(Solver *self, TSPData *problem, int time_limit, Tour *calculated_tour);

#endif