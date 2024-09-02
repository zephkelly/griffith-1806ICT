#ifndef TSP_FILE_READER_H
#define TSP_FILE_READER_H

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
} TSPProblem;

void read_tsp_file(const char* filename, TSPProblem* tsp);

#endif