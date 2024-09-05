#include <stdio.h>
#include <stdlib.h>

#include "tsp_file_reader.h"
#include "solver_factory.h"

void solve_tsp(TSPData* problem, int time_limit, SolverType solver_type);
void free_tsp_data(TSPData* problem);
void output_results(const Tour* tour);

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

    printf("Solving with Nearest Neighbour:\n");
    solve_tsp(&problem, time_limit, NEAREST_NEIGHBOUR);

    printf("Solving with Greedy 3-Opt:\n");
    solve_tsp(&problem, time_limit, GREEDY_THREE_OPT);

    free_tsp_data(&problem);
    return 0;
}

void solve_tsp(TSPData* problem, int time_limit, SolverType solver_type)
{
    Tour tour = {0};
    
    Solver* solver = create_solver(solver_type);
    solver->solve(solver, problem, time_limit, &tour);

    output_results(&tour);

    free(tour.tour_by_city_id);
}

void free_tsp_data(TSPData* problem)
{
    if (problem->cities != NULL)
    {
        free(problem->cities);
        problem->cities = NULL;
    }
}

void output_results(const Tour* tour)
{
    if (tour == NULL)
    {
        printf("Error: Null tour pointer\n");
        return;
    }

    printf("%s.tsp\n", tour->problem_name);
    printf("Shortest found tour length: %f\n", tour->tour_distance);
    printf("Tour:\n");

    for (int i = 0; i < tour->cities_visited; i++)
    {
        printf("%d\n", tour->tour_by_city_id[i] + 1);
    }

    printf("-1\n\n");

    if (tour->early_stop)
    {
        printf("*Tour terminated early\n");
    }
}