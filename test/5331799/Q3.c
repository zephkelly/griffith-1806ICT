#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_WORD 30

// Your global data structure for storing words

char **words = {NULL};

int word_count = 0;

int compare(const void *a, const void *b) {
  return strcmp(*(char **)a, *(char **)b);
}

void load_file(char *fname) { // Load from file into words
  FILE *fp = fopen(fname, "r");
  if (fp == NULL) {
    printf("Error opening file\n");
    exit(1);
  }

  char buffer[MAX_WORD];

  while (fgets(buffer, sizeof(buffer), fp)) {
    word_count++;
  }

  rewind(fp);

  words = malloc(word_count * sizeof(char *));
  for (int i = 0; i < word_count; i++) {
    words[i] = malloc(MAX_WORD * sizeof(char));
    fgets(words[i], MAX_WORD, fp);

    words[i][strcpn(words[i], "\n")] = 0;
  }

  qsort(words, word_count, sizeof(char *), compare);

  fclose(fp);
}

bool search(char *word) {
  if (bsearch(&word, words, word_count, sizeof(char *), compare)) {
    return true;
  }

  return false;
} // Check to see if word is in words

bool find_close(char *word) {
  
} // Generate close possibilities and call search()

int main(int argc, char *argv[]) {
  load_file(argv[1]);
  if (search(argv[2])) {
    if (!find_close(argv[2])) {
      printf("There are no words close to %s\n", argv[2]);
    }
  }
  else {
    printf("%s is not in the dictionary\n", argv[2]);
  }

  for (int i = 0; i < word_count; i++) {
    free(words[i]);
  }
  free(words);

  return 0;
}