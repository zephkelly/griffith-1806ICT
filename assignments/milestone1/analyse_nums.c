#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int *arr, n, range, numOps;
static size_t totalAllocated = 0;

int cmp(const void *a, const void *b) { return (*(int *)a - *(int *)b); }

void* myMalloc(size_t size) {
  totalAllocated += size;
  return malloc(size);
}

double calculateTime(clock_t start, clock_t end) {
  return ((double) (end - start)) / CLOCKS_PER_SEC;
}

void init_array(int size, int r1, int r2) {
  numOps = (size * 0.1) * 7;
  n = 1.1 * size;
  arr = (int *)myMalloc(n * sizeof(int));
  range = r2 - r1 + 1;

  for (int i = 0; i < n; i++) {
    arr[i] = r1 + rand() % (range);
  }

  qsort(arr, n, sizeof(int), cmp);

  for (int i = 9; i < n; i += 10) {
    if (arr[i-1] != arr[i+1]) {
      arr[i] = -1;
    }
  }
}

int binary_search(int target, int high, int low) {
  while (low <= high) {
    int mid = low + (high - low) / 2;

    if (arr[mid] == target) {
      while (mid > 0 && arr[mid-1] == target) mid--;
      return mid;
    }

    if (arr[mid] == -1) {
      int left = mid - 1;
      int right = mid + 1;

      while (left >= 0 && arr[left] == -1) left--;
      while (right < n && arr[right] == -1) right++;

      if (left >= 0 && arr[left] == target) return left;
      if (right < n && arr[right] == target) return right;

      if (left >= 0 && arr[left] > target) {
        high = left - 1;
      } else if (right < n && arr[right] < target) {
        low = right + 1;
      } else {
        low = right;
        high = left;
      }
    } else if (arr[mid] < target) {
      low = mid + 1;
    } else {
      high = mid - 1;
    }
  }

  return -low - 1;
}

int find(int v) {
  int index = binary_search(v, n-1, 0);

  if (index < 0) {
    return 0;
  } else {
    int count = 1;
    int rightIndex = index + 1;

    while (rightIndex < n && arr[rightIndex] == v) {
      count++;
      rightIndex++;
    }

    return count;
  }
}

int min() {
  int index = 0;
  while (arr[index] == -1) index++;
  return index;
}

int max() {
  int index = n - 1;
  while (arr[index] == -1) index--;
  return index;
}

int pred(int v) {
  int index = binary_search(v, n-1, 0);

  if (index < 0) return -1;
  while (index > 0 && (arr[index] == -1 || arr[index] == v)) index--;
  return index;
}

int succ(int v) {
  int index = binary_search(v, n-1, 0);
  if (index < 0) return -1;
  while (index < n && (arr[index] == -1 || arr[index] == v)) index++;
  return index;
}

int delete(int v) {
  int index = binary_search(v, n -1, 0);

  if (index < 0) {
    return 0;
  } else {
    arr[index] = -1;
    return 1;
  }
}

int add(int v) {
  int index = binary_search(v, n-1, 0);

  if (index < 0) {
      index = -index - 1;
  }

  if (arr[index] == -1) {
    arr[index] = v;
    return 1;
  }
  else if (index - 1 >= 0 && arr[index - 1] == -1) {
    arr[index - 1] = v;
    return 1;
  }
  else if (index + 1 < n && arr[index + 1] == -1) {
    arr[index + 1] = v;
    return 1;
  }

  int gapIndex = index;
  while (gapIndex < n && arr[gapIndex] != -1) {
    gapIndex++;
  }

  if (gapIndex == n) return 0;

  for (int i = gapIndex; i > index; i--) {
    arr[i] = arr[i - 1];
  }
  arr[index] = v;

  return 1;
}

void drive(int size, int r1, int r2) {
  double findCount = 0, minCount = 0, maxCount = 0, predCount = 0, succCount = 0, deleteCount = 0, addCount = 0;
  double timeTakenFind = 0, timeTakenMin = 0, timeTakenMax = 0, timeTakenPred = 0, timeTakenSucc = 0, timeTakenDelete = 0, timeTakenAdd = 0;
  clock_t start, end;

  srand(time(NULL));
  init_array(size, r1, r2);

  printf("n = %d, r1 = %d, r2 = %d, Memory used = %zu Mbytes\n", size, r1, r2, totalAllocated/1024/1024);
  printf("          Op counts        Total time        Avg. Time\n");

  while (numOps > 0) {
    int op = rand() % 7;
    int randNum = r1 + rand() % (range);
    
    start = clock();
        switch (op) {
      case 0:
        find(randNum);
        findCount++;
        end = clock();
        timeTakenFind += calculateTime(start, end);
        break;
      case 1:
        min();
        minCount++;
        end = clock();
        timeTakenMin += calculateTime(start, end);
        break;
      case 2:
        max();
        maxCount++;
        end = clock();
        timeTakenMax += calculateTime(start, end);
        break;
      case 3:
        pred(randNum);
        predCount++;
        end = clock();
        timeTakenPred += calculateTime(start, end);
        break;
      case 4:
        succ(randNum);
        succCount++;
        end = clock();
        timeTakenSucc += calculateTime(start, end);
        break;
      case 5:
        delete(randNum);
        deleteCount++;
        end = clock();
        timeTakenDelete += calculateTime(start, end);
        break;
      case 6:
        add(randNum);
        addCount++;
        end = clock();
        timeTakenAdd += calculateTime(start, end);
        break;
    }
    numOps--;
  }

  printf("find:     %d          %f          %0.7e\n", (int)findCount, timeTakenFind, timeTakenFind / findCount);
  printf("add:      %d          %f          %0.7e\n", (int)addCount, timeTakenAdd, timeTakenAdd / addCount);
  printf("delete:   %d          %f          %0.7e\n", (int)deleteCount, timeTakenDelete, timeTakenDelete / deleteCount);
  printf("succ:     %d          %f          %0.7e\n", (int)succCount, timeTakenSucc, timeTakenSucc / succCount);
  printf("pred:     %d          %f          %0.7e\n", (int)predCount, timeTakenPred, timeTakenPred / predCount);
  printf("min:      %d          %f          %0.7e\n", (int)minCount, timeTakenMin, timeTakenMin / minCount);
  printf("max:      %d          %f          %0.7e\n", (int)maxCount, timeTakenMax, timeTakenMax / maxCount);
}

void printArray() {
  printf("Numbers: ");
  for (int i = 0; i < n; i++) {
    if (arr[i] != -1) printf("%d ", arr[i]);
  }
  printf(":min = %d :max = %d\n", arr[min()], arr[max()]);
}

void test(int size) {
  n = abs((float)size * 1.1);
  arr = (int *)myMalloc(n * sizeof(int));

  int testValues[] = {10, 10, 24, 31, 41, 50, 50, 59, 73, 74, 74};
  for (int i = 0; i < n; i++) arr[i] = testValues[i];


  printArray();

  for (int i = 0; i < n; i++) {
    int v = testValues[i];
    if (v == -1) continue;
    if (testValues[i-1] == v) continue;
     
    printf("find %d %d : ", v, find(v)); printf("delete %d %d : ", v, delete(v)); printf("find %d %d : ", v, find(v)); printf("delete %d %d : ", v, delete(v)); printf("add %d %d : ", v, add(v)); printf("find %d %d : ", v, find(v)); printf("succ %d %d : ", v, arr[succ(v)]); printf("pred %d %d\n", v, arr[pred(v)]);
  }

  printArray();
  printf("add 10 %d : ", add(10)); printf("find 10 %d\n", find(10)); printf("add 50 %d : ", add(50)); printf("find 50 %d\n", find(50)); printf("add 74 %d : ", add(74)); printf("find 74 %d\n", find(74));
  printArray();
}

int main(int argc, char *argv[]) {
  int size = atoi(argv[1]);
  int r1 = atoi(argv[2]);
  int r2 = atoi(argv[3]);

  if (r1 <= 0 || r2 <= r1) {
    printf("Error: r1 and r2 must be positive and r2 > r1\n");
    return 1;
  }

  if (size < 0) {
    test(size);
  } else {
    drive(size, r1, r2);
  }

  free(arr);
  arr = NULL;

  return 0;
}