#include 'Ordenação.h'

//Extração de número da string do id
int extractNumber(const char* str);


int partition(char* arr[], int low, int high);

//quicksort principal
void quickSort(char* arr[], int low, int high);

//impressão de array usada para teste
void printArray(char* arr[], int size);
