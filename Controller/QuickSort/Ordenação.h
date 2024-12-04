#ifndef IMPORTS_H
#define IMPORTS_H
#include "../../imports.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//Extração de número da string do id
int extractNumber(const char* str);

//troca duas strings em um array
void swap(char* arr[], int i, int j);

//faz a partição e define o pivô para o quicksort
int partition(char* arr[], int low, int high);

//quicksort principal
void quickSort(char* arr[], int low, int high);

//impressão de array usada para teste
void printArray(char* arr[], int size);
