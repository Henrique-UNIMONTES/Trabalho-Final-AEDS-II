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
  quick_sort_vector = (ResumedTitle *) malloc(sizeof(ResumedTitle) * titles_size);

  for (int i = 0; i < titles_size; i++) {
    Title t;
    deserializeModel(&t, indexes[i]);

    int length = stringLength(t.id);

    titles_data[i].id = (char *) malloc(sizeof(char) * length + 1);
    stringToCharArray(t.id, titles_data[i].id);

    quick_sort_vector[i].id = (char *) malloc(sizeof(char) * length + 1);
    stringToCharArray(t.id, quick_sort_vector[i].id);

    length = stringLength(t.title);

    titles_data[i].title = (char *) malloc(sizeof(char) * length + 1);
    stringToCharArray(t.title, titles_data[i].title);

    quick_sort_vector[i].title = (char *) malloc(sizeof(char) * length + 1);
    stringToCharArray(t.title, quick_sort_vector[i].title);

    for (int j = 0; j < strlen(quick_sort_vector[i].title); j++) {
      quick_sort_vector[i].title[j] = tolower(quick_sort_vector[i].title[j]);
    }

    titles_data[i].index = indexes[i];
    quick_sort_vector[i].index = indexes[i];
    
    clearModel(&t);
    
    if ((i + 1) % 500 == 0) {
      printf("Titles [%d] - [%d] loaded\n", i + 1 - 500, i + 1);
    }
  }

  tests_loaded = TRUE;
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
    printf("Quick sort test initializing...\n\n");
    int repeat = 0;

    do {
      repeat = initializeQuickSort();
    } while(repeat);
  }

  else if (test == 2) {
    printf("\nBinary Search Tree test initializing...\n\n");
    int repeat;
    do {
      repeat = initializeAbb();
    } while (repeat);
  }

  else {
    printf("Test not implemented");
    exit(1);
  }
}