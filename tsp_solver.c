#include <stdio.h>
#include <stdlib.h>
#include "tsp_file_reader.h"

int main(int argc, char* argv[]) 
{
    if (argc != 3) 
    {
        printf("Usage: %s <input file> <time limit>\n", argv[0]);
        return 1;
    }

    const char* filename = argv[1];
    int time_limit = atoi(argv[2]);

    TSPProblem problem;
    read_tsp_file(filename, &problem);

    printf("Problem Name: %s\n", problem.name);
    printf("Comment: %s\n", problem.comment);
    printf("Type: %s\n", problem.type);
    printf("Dimensions: %d\n", problem.dimension);
    printf("Read Nodes: %d\n", problem.read_nodes);
    printf("Edge Weight Type: %s\n", problem.edge_weight_type);

    printf("\nFirst 10 cities:\n");
    int cities_to_print = (problem.read_nodes < 10) ? problem.read_nodes : 10;
    for (int i = 0; i < cities_to_print; i++)
    {
        printf("City %d: ID = %d, X = %.2f, Y = %.2f\n", 
               i+1, problem.cities[i].id, problem.cities[i].x, problem.cities[i].y);
    }

    return 0;
}