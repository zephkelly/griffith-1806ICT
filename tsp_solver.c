#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) 
{
    if (argc != 3) 
    {
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        return 1;
    }

    const char* filename = argv[1];
    int time_limit = atoi(argv[2]);
}