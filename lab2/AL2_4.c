#include <stdio.h>
#include <stdlib.h>
#define N 10

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(int numbersFromFile[], int n, int  i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && numbersFromFile[l] > numbersFromFile[largest])
        largest = l;

    if (r < n && numbersFromFile[r] > numbersFromFile[largest])
        largest = r;

    if (largest != i) {
        swap(&numbersFromFile[i], &numbersFromFile[largest]);

        heapify(numbersFromFile, n, largest);
    }
}

void buildHeap(int numbersFromFile[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(numbersFromFile, n, i);
}

void heapSort(int numbersFromFile[], int n) {
    buildHeap(numbersFromFile, n);

    for (int i = n - 1; i > 0; i--) {
        swap(&numbersFromFile[0], &numbersFromFile[i]);

        heapify(numbersFromFile, i, 0);
    }
}

void printNumbersFromFile(int numbersFromFile[], int n) {
    for (int i = 0; i < n; ++i)
        printf("%d ", numbersFromFile[i]);
    printf("\n");
}

int main() {

    int numbersFromFile[N];
    FILE *fptr;

    if ((fptr = fopen("plik.txt", "r")) == NULL) {
        printf("Error! opening file");

        exit(1);
    }
    
    for (int i = 0; i < N; i++) {
        fscanf(fptr, "%1d", &numbersFromFile[i]);
    }

    for (int i = 0; i < N; i++) {
        printf("%d ", numbersFromFile[i]);
    }

    printf("\n");

    fclose(fptr);

    int n = sizeof(numbersFromFile) / sizeof(numbersFromFile[0]);

    heapSort(numbersFromFile, n);

    printf("Posortowana tablica:\n");
    printNumbersFromFile(numbersFromFile, n);

    return 0;

}
