#include 'Ordenação.h'

//Extração de número da string do id
int extractNumber(const char* str);

//troca duas strings em um array
swap(char* arr[], int i, int j);

//faz a partição e define o pivô para o quicksort
int partition(char* arr[], int low, int high);

//quicksort principal
quickSort(char* arr[], int low, int high);

//impressão de array usada para teste
printArray(char* arr[], int size);
