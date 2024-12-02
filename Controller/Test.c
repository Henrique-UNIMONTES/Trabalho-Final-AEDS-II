#include "Test.h"

time_t showTime() {
  time_t rawtime;
  struct tm *timeinfo;

  time(&rawtime);
  timeinfo = localtime(&rawtime);

  printf("%s", ctime(&rawtime));

  return rawtime;
}

void getShuffledIndexes(int *indexes, int size) {
  for (int i = size - 1; i >= 0; i--) {
    int j = rand() % (i + 1);
    int aux = indexes[i];
    indexes[i] = indexes[j];
    indexes[j] = aux;
  }
}

void configIndexes() {
  indexes = (int *) malloc(titles_size * sizeof(int));

  for (int i = 0; i < titles_size; i++) {
    indexes[i] = i;
  }

  getShuffledIndexes(indexes, titles_size);
}

void loadData() {
  titles_data = (ResumedTitle *) malloc(sizeof(ResumedTitle) * titles_size);

  for (int i = 0; i < titles_size; i++) {
    Title t;
    deserializeModel(&t, indexes[i]);

    int length = stringLength(t.id);

    titles_data[i].id = (char *) malloc(sizeof(char) * length + 1);
    stringToCharArray(t.id, titles_data[i].id);

    length = stringLength(t.data_added);

    titles_data[i].date = (char *) malloc(sizeof(char) * length + 1);
    stringToCharArray(t.data_added, titles_data[i].date);

    titles_data[i].index = indexes[i];
    
    clearModel(&t);
    
    if ((i + 1) % 500 == 0) {
      printf("Titles [%d] - [%d] loaded\n", i + 1 - 500, i + 1);
    }
  }

  tests_loaded = TRUE;
  printf("\n");
}

void initializeTests(int test) {
  if (!tests_loaded) {
    printf("\nThe data isn't loaded yet\n");
    printf("Shuffling the data...\n");
    configIndexes();
    printf("Start loading the data...\n\n");
    loadData();
  }

  if (test == 1) {
    printf("Test not implemented yet\n\n");
  }

  else if (test == 2) {
    printf("Binary Search Tree test initializing...\n\n");
    initializeAbb();
  }

  else {
    printf("Test not implemented yet");
    exit(1);
  }
}