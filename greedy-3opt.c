#include "greedy-3opt.h"
#include <stdlib.h>

typedef struct Greedy3OptSolver {
    Solver base;
} Greedy3OptSolver;

Solver* create_greedy_3opt_solver() {
    Greedy3OptSolver* solver = malloc(sizeof(Greedy3OptSolver));
    // solver->base.solve = solve_greedy_3opt;
    // solver->base.free = free_greedy_3opt;
    return (Solver*) solver;
}