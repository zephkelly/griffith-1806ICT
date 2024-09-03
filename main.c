#include <stdio.h>
#include <stdlib.h>

#include "tsp_file_reader.h"
#include "solver_factory.h"

void solve_tsp(TSPData* problem, int time_limit, SolverType solver_type);

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

    printf("Problem Name: %s\n", problem.name);
    printf("Comment: %s\n", problem.comment);
    printf("Type: %s\n", problem.type);
    printf("Dimensions: %d\n", problem.dimension);
    printf("Read Nodes: %d\n", problem.read_nodes);
    printf("Edge Weight Type: %s\n", problem.edge_weight_type);

    solve_tsp(&problem, time_limit, NEAREST_NEIGHBOUR);
    solve_tsp(&problem, time_limit, GREEDY_THREE_OPT);

    return 0;
}

void solve_tsp(TSPData* problem, int time_limit, SolverType solver_type)
{
    Solver* solver = create_solver(solver_type);
}