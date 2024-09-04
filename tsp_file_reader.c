#include "tsp_file_reader.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 1000

char *trim_whitespace(char *str)
{
    char *end;

    while(isspace((unsigned char)*str)) str++;

    if(*str == 0)
        return str;

    end = str + strlen(str) - 1;
    while(end > str && isspace((unsigned char)*end)) end--;

    end[1] = '\0';

    return str;
}

void read_tsp_file(const char* filename, TSPData* problem)
{
    FILE* input_file = fopen(filename, "r");

    if (input_file == NULL)
    {
        printf("Error opening file: %s\n", filename);
        exit(1);
    }

    char line[MAX_LINE_LENGTH];
    bool reading_nodes = false;
    int node_count = 0;

    while (fgets(line, sizeof(line), input_file))
    {
        char* formatted_line = trim_whitespace(line);

        if (strncmp(line, "EOF", 3) == 0)
        {
            break;
        }

        char* colon_char = strchr(formatted_line, ':');

        if (colon_char)
        {
            *colon_char = '\0';
            char* key = trim_whitespace(formatted_line);
            char* value = trim_whitespace(colon_char + 1);

            if (strncmp(key, "NAME", 4) == 0)
            {
                sscanf(value, "%49s", problem->name);
            }
            else if (strncmp(key, "COMMENT", 7) == 0)
            {
                strncpy(problem->comment, value, sizeof(problem->comment) - 1);
                problem->comment[sizeof(problem->comment) - 1] = '\0';
            }
            else if (strncmp(key, "TYPE", 4) == 0)
            {
                sscanf(value, "%19s", problem->type);
            }
            else if (strncmp(key, "DIMENSION", 9) == 0)
            {
                sscanf(value, "%d", &problem->dimension);
            }
            else if (strncmp(key, "EDGE_WEIGHT_TYPE", 16) == 0)
            {
                sscanf(value, "%19s", problem->edge_weight_type);
            }
        }
        else if (strncmp(line, "NODE_COORD_SECTION", 18) == 0)
        {
            reading_nodes = true;
        }
        else if (reading_nodes && node_count < problem->dimension)
        {
            City* city = &problem->cities[node_count];
            sscanf(formatted_line, "%d %lf %lf", &city->id, &city->x, &city->y);
            node_count++;
        }
    }

    problem->read_nodes = node_count;
    fclose(input_file);
}