#include "solver_factory.h"
#include "solvers/greedy_2opt.h"
#include "solvers/nearest_neighbour.h"

Solver* create_solver(SolverType type) 
{
    switch (type) 
    {
        case NEAREST_NEIGHBOUR:
            return create_nearest_neighbour_solver();
        case GREEDY_THREE_OPT:
            return create_greedy_2opt_solver();
        default:
            return create_greedy_2opt_solver();
    }
}