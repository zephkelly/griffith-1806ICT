#include "tsp_file_reader.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_LINE_LENGTH 1000

void read_tsp_file(const char* filename, TSPProblem* problem)
{
    FILE* input_file = fopen(filename, "r");

    if (input_file == NULL)
    {
        printf("Error opening file: %s\n", filename);
        exit(1);
    }

    char line[MAX_LINE_LENGTH];
    bool reading_nodes = false;
    int current_node = 0;

    while (fgets(line, sizeof(line), input_file))
    {
        if (strncmp(line, "EOF", 3) == 0)
        {
            break;
        }

        if (strncmp(line, "NAME :", 6) == 0)
        {
            sscanf(line, "NAME : %s", problem->name);
        }
        else if (strncmp(line, "COMMENT :", 9) == 0)
        {
            sscanf(line, "COMMENT : %s", problem->comment);
        }
        else if (strncmp(line, "TYPE :", 6) == 0)
        {
            sscanf(line, "TYPE : %s", problem->type);
        }
        else if (strncmp(line, "DIMENSION:", 10) == 0)
        {
            sscanf(line, "DIMENSION: %d", &problem->dimension);
        }
        else if (strncmp(line, "EDGE_WEIGHT_TYPE :", 17) == 0)
        {
            sscanf(line, "EDGE_WEIGHT_TYPE : %s", problem->edge_weight_type);
        }
        else if (strncmp(line, "NODE_COORD_SECTION", 18) == 0)
        {
            reading_nodes = true;
        }
        else if (reading_nodes && current_node < problem->dimension)
        {
            current_node++;
        }
    }

    problem->read_nodes = current_node;
    fclose(input_file);
}