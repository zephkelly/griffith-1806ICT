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

    printf("File: %s.tsp\n", problem.name);
    read_tsp_file(filename, &problem);

    printf("Solving with Nearest Neighbour:\n");
    solve_tsp(&problem, time_limit, NEAREST_NEIGHBOUR);

    free_tsp_data(&problem);
    return 0;
}

void solve_tsp(TSPData* problem, int time_limit, SolverType solver_type)
{
    Solver* solver = create_solver(solver_type);
    Tour calculated_tour = {0};
    solver->solve(solver, problem, time_limit, &calculated_tour);

    output_results(&calculated_tour);

    free(calculated_tour.tour_by_city_id);
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

    printf("Problem Name: %s.tsp\n", tour->problem_name);
    printf("Time Taken: %f seconds\n", tour->elapsed_time);
    printf("Tour Distance: %f\n", tour->tour_distance);
    printf("Cities visited:\n");

    for (int i = 2; i < tour->cities_visited; i++)
    {
        printf(" %d\n", tour->tour_by_city_id[i]);
    }

    if (tour->early_stop)
    {
        printf("*Tour terminated early\n");
    }
}