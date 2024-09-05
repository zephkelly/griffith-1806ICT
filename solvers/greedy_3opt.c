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

double get_distance(GreedyData *data, int i, int j)
{
    if (data->matrix != NULL)
    {
        return data->matrix[i][j];
    }
    else
    {
        return calculate_euclidean_distance(&data->problem->cities[i], &data->problem->cities[j]);
    }
}

void reverse_segment(int *tour, int i, int j)
{
    while (i < j)
    {
        int temp = tour[i];
        tour[i] = tour[j];
        tour[j] = temp;
        i++;
        j--;
    }
}

double calculate_best_delta_distance(GreedyData *data, int *tour, int i, int j, int k)
{
    int n = data->problem->dimension;

    double d0 = get_distance(data, tour[i-1], tour[i]) + get_distance(data, tour[j-1], tour[j]) + get_distance(data, tour[k-1], tour[k % n]);
    double d1 = get_distance(data, tour[i-1], tour[j-1]) + get_distance(data, tour[i], tour[j]) + get_distance(data, tour[k-1], tour[k % n]);
    double d2 = get_distance(data, tour[i-1], tour[i]) + get_distance(data, tour[j-1], tour[k-1]) + get_distance(data, tour[j], tour[k % n]);
    double d3 = get_distance(data, tour[i-1], tour[k-1]) + get_distance(data, tour[j], tour[i]) + get_distance(data, tour[j-1], tour[k % n]);
    double d4 = get_distance(data, tour[i-1], tour[j-1]) + get_distance(data, tour[k-1], tour[i]) + get_distance(data, tour[j], tour[k % n]);
    double d5 = get_distance(data, tour[i-1], tour[j]) + get_distance(data, tour[k-1], tour[i]) + get_distance(data, tour[j-1], tour[k % n]);
    double d6 = get_distance(data, tour[i-1], tour[k-1]) + get_distance(data, tour[j], tour[j-1]) + get_distance(data, tour[i], tour[k % n]);
    
    double deltas[7] = {
        0.0,
        d0 - d1,
        d0 - d2,
        d0 - d3,
        d0 - d4,
        d0 - d5,
        d0 - d6,
    };

    double best_delta = 0.0;
    int best_move = 0;
    for (int m = 1; m < 7; m++)
    {
        if (deltas[m] < best_delta)
        {
            best_delta = deltas[m];
            best_move = m;
        }
    }

    if (best_delta < 0.0)
    {
        switch (best_move)
        {
            case 1:
                reverse_segment(tour, i, j-1);
                break;
            case 2:
                reverse_segment(tour, j, k-1);
                break;
            case 3:
                reverse_segment(tour, i, k-1);
                break;
            case 4:
                reverse_segment(tour, i, j-1);
                reverse_segment(tour, j, k-1);
                break;
            case 5:
                reverse_segment(tour, i, k-1);
                reverse_segment(tour, i, j-1);
                break;
            case 6:
                reverse_segment(tour, i, k-1);
                reverse_segment(tour, j, k-1);
                break;
        }
    }

    return best_delta;
}

void solve_greedy_3opt(Solver *self, TSPData *problem, int time_limit, Tour *calculated_tour)
{
    Greedy3OptSolver *solver = (Greedy3OptSolver*) self;

    clock_t start_time = clock();

    GreedyData* data = should_create_distance_matrix(problem);
    double current_distance = generate_random_tour_with_distance(problem, calculated_tour);
    const int n = problem->dimension;

    int iterations = 0;

    while (1)
    {
        clock_t current_time = clock();
        double elapsed_time = (double)(current_time - start_time) / CLOCKS_PER_SEC;

        if (elapsed_time >= time_limit)
        {
            printf("Time limit reached. Terminating early.\n\n");
            break;
        }

        if (iterations >= 1)
        {
            printf("Iteration %d, current distance: %f\n", iterations, current_distance);
            break;
        }

        int improved = 0;

        for (int i = 0; i < n - 2; i++)
        {
            for (int j = i + 1; j < n - 1; j++)
            {
                for (int k = j + 1; k < n; k++)
                {
                    double delta_distance = calculate_best_delta_distance(data, calculated_tour->tour_by_city_id, i, j, k);
                    printf("Delta distance: %f\n", delta_distance);
                }
            }
        }

        iterations++;
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