#ifndef TSP_STRUCTURES_H
#define TSP_STRUCTURES_H

typedef struct {
    int id;
    double x;
    double y;
} City;

typedef struct {
    char name[50];
    char comment[255];
    char type[20];
    int dimension;
    char edge_weight_type[20];
    City cities[1000];
    int read_nodes;
} TSPInformation;

typedef struct {
    char name[50];
    int tour_length;
    int tour_by_city_id[];
} Tour;

#endif