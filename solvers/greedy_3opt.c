#include "greedy_3opt.h"
#include <stdlib.h>
#include <stdio.h>

#include "greedy_3opt.h"
#include "../tsp_structures.h"

// https://www.geeksforgeeks.org/travelling-salesman-problem-greedy-approach/

Solver* create_greedy_3opt_solver()
{
    Greedy3OptSolver* solver = malloc(sizeof(Greedy3OptSolver));
    printf("Greedy 3-Opt Solver Created\n");
    solver->base.solve = solve_greedy_3opt;
    return (Solver*) solver;
}

void solve_greedy_3opt(Solver *self, TSPData *problem, int time_limit, Tour *calculated_tour)
{
    Greedy3OptSolver *solver = (Greedy3OptSolver*) self;
    // printf("Greedy 3-Opt Solver\n");
}