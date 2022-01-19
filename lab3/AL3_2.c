#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 100000

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int numbersFromFile[], int n, int p, int r) {
    int x = numbersFromFile[r];
    int i = p - 1;

    for (int j = p; j <= r; j++) 
        if (numbersFromFile[j] <= x) {
            i++;
            swap(&numbersFromFile[i], &numbersFromFile[j]);
        }
    

    if (i < r)
        return i;
    else return i - 1;
}

void quickSort(int numbersFromFile[], int n, int p, int r) {
    int q;
    if (p < r) {
        q = partition(numbersFromFile, n, p, r);
        quickSort(numbersFromFile, N, p, q);
        quickSort(numbersFromFile, N, q + 1, r);
    }
}

int main() {

    time_t t;
    FILE *fptr, *fptr1, *fptr2;

    fptr = fopen("plik.txt", "w");
    if (fptr == NULL) {
        printf("Error!");
        exit(1);
    }

    srand((unsigned) time(&t));

    for (int i = 0; i < N; i++) 
        fprintf(fptr, "%d\n", rand() % (N + 1)); 

    fclose(fptr);

    int numbersFromFile[N];

    if ((fptr = fopen("plik.txt", "r")) == NULL) {
        printf("Error! opening file");
        exit(1);
    }
    
    for (int i = 0; i < N; i++) 
        fscanf(fptr, "%6d", &numbersFromFile[i]);

    fclose(fptr);

    clock_t begin = clock();
    quickSort(numbersFromFile, N, 0, N-1);
    clock_t end = clock();
    double timeSpent = (double)(end - begin) / CLOCKS_PER_SEC;

    printf("Czas wykonywania programu dla %d elementow: %f\n", N, timeSpent);

    fptr1 = fopen("plik1.txt", "w");
    if (fptr1 == NULL) {
        printf("Error!");
        exit(1);
    }
    
    for (int i = 0; i < N; i++) 
        fprintf(fptr1, "%d\n", numbersFromFile[i]); 

    fclose(fptr1);

    return 0;

}
