#include "tsp_utils.h"
#include <math.h>

int calculate_squared_distance(const City *city1, const City *city2)
{
    double dx = city1->x - city2->x;
    double dy = city1->y - city2->y;
    return dx*dx + dy*dy;
}

int calculate_euclidean_distance(const City *city1, const City *city2)
{
    double dx = city1->x - city2->x;
    double dy = city1->y - city2->y;
    double distance = sqrt(dx*dx + dy*dy);

    distance = round(distance);
    return (int) distance;
}