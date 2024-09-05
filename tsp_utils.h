#ifndef TSP_UTILS_H
#define TSP_UTILS_H

#include "tsp_structures.h"

int calculate_squared_distance(const City *city1, const City *city2);
int calculate_euclidean_distance(const City *city1, const City *city2);

#endif