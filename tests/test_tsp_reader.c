#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "./../tsp_file_reader.h"

#define MAX_PATH 1024

int test_tsp_file(const char* filename)
{
    TSPProblem problem = {0};
    read_tsp_file(filename, &problem);


    if (problem.name[0] && problem.type[0] && problem.dimension > 0 && problem.edge_weight_type[0] && problem.read_nodes > 0)
    {
        printf("Read %s successfully!\n", filename);
        return 1;
    }
    else
    {
        printf("Failed to read %s completely. Missing data:\n", filename);
        if (!problem.name[0]) printf("- Name\n");
        if (!problem.type[0]) printf("- Type\n");
        if (problem.dimension <= 0) printf("- Dimension\n");
        if (!problem.edge_weight_type[0]) printf("- Edge Weight Type\n");
        if (problem.read_nodes <= 0) printf("- Nodes\n");

        return 0;
    }
}

int main()
{
    DIR *dir;
    struct dirent *ent;
    char path[MAX_PATH];
    int tests_run = 0, tests_passed = 0;

    dir = opendir("./../problems");
    if (dir == NULL)
    {
        printf("Could not open directory");
        return 1;
    }

    while ((ent = readdir(dir)) != NULL)
    {
        if (strlen(ent->d_name) > 4 && strcmp(ent->d_name + strlen(ent->d_name) - 4, ".tsp") == 0)
        {
            snprintf(path, sizeof(path), "./../problems/%s", ent->d_name);
            
            tests_run++;
            tests_passed += test_tsp_file(path);
        }
    }

    closedir(dir);

    printf("\nTest Summary:\n");
    printf("Total tests run: %d\n", tests_run);
    printf("Tests passed: %d\n", tests_passed);
    printf("Tests failed: %d\n", tests_run - tests_passed);

    return 0;
}