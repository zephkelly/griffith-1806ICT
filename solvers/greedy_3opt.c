#include "greedy_3opt.h"
#include <stdlib.h>
#include <stdio.h>

// https://www.geeksforgeeks.org/travelling-salesman-problem-greedy-approach/

Solver* create_greedy_3opt_solver()
{
    Greedy3OptSolver* solver = malloc(sizeof(Greedy3OptSolver));
    printf("Greedy 3-Opt Solver Created\n");
    // solver->base.solve = solve_greedy_3opt;
    // solver->base.free = free_greedy_3opt;
    solver->base.find_distances = find_distances_greedy_3opt;
    return (Solver*) solver;
}

void find_distances_greedy_3opt(Solver *self, TSPData *problem)
{
    Greedy3OptSolver *solver = (Greedy3OptSolver*) self;
    printf("Finding distances for Greedy 3-Opt Solver\n");
}