#ifndef IMPORTS_H
  #define IMPORTS_H
  #include "../../imports.h"
#endif

// Reparte o vetor separando os elementos maiores que o vetor e os menores que o vetor
int partition(ResumedTitle *arr, int low, int high);

// Realiza a ordenação dos dados utilizando o algoritmo Quick Sort
void quickSort(ResumedTitle *arr, int low, int high);

// Troca o conteúdo de duas variáveis
void swap(ResumedTitle* a, ResumedTitle* b);

// Entrypoint do teste de Quick Sort
int initializeQuickSort();