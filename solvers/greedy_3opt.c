#include "greedy_3opt.h"
#include <stdlib.h>
#include <stdio.h>

#include "greedy_3opt.h"
#include "../tsp_structures.h"
#include "../tsp_utils.h"

// https://www.geeksforgeeks.org/travelling-salesman-problem-greedy-approach/

#define MAX_PROBLEM_SIZE 20000

typedef struct {
    double **matrix;
    TSPData *problem;
} GreedyData;

double generate_random_tour_with_distance(TSPData *problem, Tour *tour);

Solver* create_greedy_3opt_solver()
{
    Greedy3OptSolver* solver = malloc(sizeof(Greedy3OptSolver));
    solver->base.solve = solve_greedy_3opt;
    return (Solver*) solver;
}

GreedyData* should_create_distance_matrix(TSPData *problem)
{
    GreedyData *data = malloc(sizeof(GreedyData));
    data->problem = problem;
    
    if (problem->dimension <= MAX_PROBLEM_SIZE)
    {
        printf("Creating distance matrix\n");
        int n = problem->dimension;
        data->matrix = malloc(n * sizeof(double*));

        for (int i = 0; i < n; i++)
        {
            data->matrix[i] = malloc(n * sizeof(double));

            for (int j = 0; j < n; j++)
            {
                data->matrix[i][j] = calculate_euclidean_distance(&problem->cities[i], &problem->cities[j]);
            }
        }
    }
    else
    {
        data->matrix = NULL;
    }

    printf("Distance matrix created\n");
    
    return data;
}

void solve_greedy_3opt(Solver *self, TSPData *problem, int time_limit, Tour *calculated_tour)
{
    Greedy3OptSolver *solver = (Greedy3OptSolver*) self;

    clock_t start_time = clock();

    GreedyData* data = should_create_distance_matrix(problem);
    double current_distance = generate_random_tour_with_distance(problem, calculated_tour);
    const int n = problem->dimension;

    while (1)
    {
        clock_t current_time = clock();
        double elapsed_time = (double)(current_time - start_time) / CLOCKS_PER_SEC;

        if (elapsed_time >= time_limit)
        {
            printf("Time limit reached. Terminating early.\n\n");
            break;
        }

        int improved = 0;

        for (int i = 1; n - 2; i++)
        {
            for (int j = i + 1; n - 1; j++)
            {
                for (int k = j + 1; n; k++)
                {
                    // Calculate the delta distances of i, j, k

                    //Calculate the distance first or grab from the matrix

                   
                }
            }
        }
    }
}

double generate_random_tour_with_distance(TSPData *problem, Tour *tour)
{
    srand(time(NULL));

    int n = problem->dimension;
    double total_distance = 0.0;
    tour->tour_by_city_id = (int*)malloc((problem->dimension + 1) * sizeof(int));

    if (tour->tour_by_city_id != NULL)
    {
        free(tour->tour_by_city_id);
    }

    if (tour->tour_by_city_id == NULL)
    {
        printf("Failed to allocate memory for tour.\n");
        return -1.0;
    }
 
    for (int i = 0; i < n; i++)
    {
        tour->tour_by_city_id[i] = i;
    }
    for (int i = n - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        int temp = tour->tour_by_city_id[i];
        tour->tour_by_city_id[i] = tour->tour_by_city_id[j];
        tour->tour_by_city_id[j] = temp;

        if (i > 1)
        {
            total_distance += calculate_euclidean_distance(&problem->cities[tour->tour_by_city_id[i]], &problem->cities[tour->tour_by_city_id[i-1]]);
        }
    }

    total_distance += calculate_euclidean_distance(&problem->cities[tour->tour_by_city_id[n-1]], &problem->cities[tour->tour_by_city_id[0]]);
    return total_distance;
}