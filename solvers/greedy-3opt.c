#include "greedy-3opt.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct Greedy3OptSolver {
    Solver base;
} Greedy3OptSolver;

// https://www.geeksforgeeks.org/travelling-salesman-problem-greedy-approach/

Solver* create_greedy_3opt_solver() {
    Greedy3OptSolver* solver = malloc(sizeof(Greedy3OptSolver));
    printf("Greedy 3-Opt Solver Created\n");
    // solver->base.solve = solve_greedy_3opt;
    // solver->base.free = free_greedy_3opt;
    return (Solver*) solver;
}