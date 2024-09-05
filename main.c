#include <stdio.h>
#include <stdlib.h>

#include "tsp_file_reader.h"
#include "solver_factory.h"

void solve_tsp(TSPData* problem, int time_limit, SolverType solver_type);
void free_tsp_data(TSPData* problem);

int main(int argc, char* argv[]) 
{
    if (argc != 3) 
    {
        printf("Usage: %s <input file> <time limit>\n", argv[0]);
        return 1;
    }

    const char* filename = argv[1];
    int time_limit = atoi(argv[2]);

    TSPData problem;

    read_tsp_file(filename, &problem);

    printf("Evan Kelly's TSP Solver\n");
    printf("Problem Name: %s.tsp\n", problem.name);

    printf("Solving with Nearest Neighbour\n");
    solve_tsp(&problem, time_limit, NEAREST_NEIGHBOUR);
    solve_tsp(&problem, time_limit, GREEDY_THREE_OPT);

    free_tsp_data(&problem);
    return 0;
}

void solve_tsp(TSPData* problem, int time_limit, SolverType solver_type)
{
    Solver* solver = create_solver(solver_type);
    solver->solve(solver, problem, time_limit);
}

void free_tsp_data(TSPData* problem)
{
    if (problem->cities != NULL) {
        free(problem->cities);
        problem->cities = NULL;
    }
}