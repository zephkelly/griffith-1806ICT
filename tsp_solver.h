#ifndef TSP_SOLVER_H
#define TSP_SOLVER_H

#include "tsp_structures.h"

typedef struct Solver Solver;

struct Solver {
    Tour (*solve)(Solver *self, TSPInformation *problem, int time_limit);
    void (*free)(Solver *self);
};

#endif