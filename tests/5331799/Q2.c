#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// Your global variables and data structures go here

#define MAX_RANDOM_RANGE 10000

int compare(const void *a, const void *b) {
  return *(int *)a - *(int *)b;
}

int gen_rand() {
  return (RAND_MAX == 0x7fffffff ? rand() : rand() << 16 | rand() << 1 | rand() & 1) % MAX_RANDOM_RANGE;
}

void create(int *input, int n) {
  for (int i = 0; i < n; i++) {
    input[i] = gen_rand();
  }
}

void compress(int *input, int n) {
  if (n == 0) {
    return;
  }

  qsort(input, n, sizeof(int), compare);

  //remove duplicates
  int uniqueElements = 1;
  for (int i = 1; i < n; i++) {
    if (input[i] != input[i - 1]) {
      input[uniqueElements] = input[i];
      uniqueElements++;
    }
  }

  float percentReduction = (float)(n - uniqueElements) / n * 100;
  printf("Reduced from %d to %d, a reduction of %.2f%%\n", n, uniqueElements, percentReduction);
}

int main(int argc, char *argv[])
{
  //seed the number generator
  srand(time(NULL));

  int n = atoi(argv[1]);
  int *input = (int *)malloc(n * sizeof(int));

  create(input, n);
  compress(input, n);

  free(input);
  return 0;
}