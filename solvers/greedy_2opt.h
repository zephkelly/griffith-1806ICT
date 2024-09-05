#ifndef GREEDY_3OPT_H
#define GREEDY_3OPT_H

#include "../tsp_solver.h"

typedef struct Greedy2OptSolver {
    Solver base;
} Greedy2OptSolver;

Solver* create_greedy_2opt_solver();

void solve_greedy_2opt(Solver *self, TSPData *problem, int time_limit, Tour *calculated_tour);

#endif