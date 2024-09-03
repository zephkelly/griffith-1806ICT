#ifndef TSP_SOLVER_H
#define TSP_SOLVER_H

#include "tsp_structures.h"

typedef struct Solver Solver;

struct Solver {
    Tour (*solve)(Solver *self, TSPData *problem, int time_limit);
    void (*free)(Solver *self);
};

typedef enum {
    GREEDY_THREE_OPT,
} SolverType;

#endif