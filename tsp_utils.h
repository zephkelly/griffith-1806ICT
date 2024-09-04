#ifndef TSP_UTILS_H
#define TSP_UTILS_H

#include "tsp_structures.h"

// #include <math.h>

int calculate_squared_distance(const City *city1, const City *city2);
double calculate_distance(const City *city1, const City *city2);

#endif