#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int extractNumber(const char* str) {
    return atoi(str + 1); // Converte os caracteres após 's' para número inteiro
}

void swap(char* arr[], int i, int j) {
    char* temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

int partition(char* arr[], int low, int high) {
    int pivot = extractNumber(arr[high]); // Escolhe o número do elemento pivô
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (extractNumber(arr[j]) < pivot) {
            i++;
            swap(arr, i, j);
        }
    }
    swap(arr, i + 1, high);
    return i + 1;
}

void quickSort(char* arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void printArray(char* arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%s ", arr[i]);
    }
    printf("\n");
}

/*int main() {
    // Array de strings no formato "s(numero)"
    char* strings[] = {"s23", "s5", "s8", "s15", "s2"};
    int n = sizeof(strings) / sizeof(strings[0]);

    printf("Array original:\n");
    printArray(strings, n);

    // Ordenando o array com QuickSort
    quickSort(strings, 0, n - 1);

    printf("\nArray ordenado:\n");
    printArray(strings, n);

    return 0;
}*/
