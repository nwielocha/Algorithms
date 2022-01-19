#include <stdio.h>
#include <stdlib.h>

struct dane {
    int popularnosc;
    char nazwisko[30];
};

void radixSort(int [], int);
void print(int [], int);

int main() {

    FILE *fptr;
    int A[] = { 170, 45, 75, 90, 802, 24, 2, 66 };
    int n = sizeof(A) / sizeof(A[0]);
    int m = 0, c; // Rozmiar tablicy B

    if ((fptr = fopen("nazwiskaASCII.txt", "r")) == NULL) {
        printf("Error! opening file");
        exit(1);
    }

    // Zliczanie linii w pliku
    while ((c = fgetc(fptr)) != EOF)
        if (c == '\n')
            ++m;

    fclose(fptr);

    struct dane dane[m];

    if ((fptr = fopen("nazwiskaASCII.txt", "r")) == NULL) {
        printf("Error! opening file");
        exit(1);
    }

    for (int i = 0; i < m; i++)
        fscanf(fptr, "%d %s\n", &dane[i].popularnosc, dane[i].nazwisko);

    fclose(fptr);

    for (int i = 0; i < m; i++)
        printf("%s\n", dane[i].nazwisko);

    int tmp[m][30];
    for (int i = 0; i < m; i++) 
        for (int j = 0; j < 30; j++)
            sscanf(&dane[i].nazwisko[j], "%d", &tmp[i][j]);

    for (int i = 0; i < m; i++)
        for (int j = 0; j < 30; j++)
            printf("%d\n", tmp[i][j]);


    radixSort(A, n);
    print(A, n);

    return 0;
}
//////////////////////////////////////////////////////////////////////////////
int getMax(int A[], int n) {

    int x = A[0];
    for (int i = 1; i < n; i++) 
        if (A[i] > x)
            x = A[i];
    return x;
}
//////////////////////////////////////////////////////////////////////////////
void countingSort(int A[], int n, int p) {

    int output[n];
    int i, count[10] = {0};

    for (i = 0; i < n; i++) 
        count[(A[i] / p) % 10]++;

    for (i = 1; i < 10; i++)
        count[i] += count[i -1];

    for (i = n - 1; i >= 0; i--) {
        output[count[(A[i] / p) % 10] - 1] = A[i];
        count[(A[i] / p) % 10]--;
    }

    for (i = 0; i < n; i++)
        A[i] = output[i];
}
//////////////////////////////////////////////////////////////////////////////
void radixSort(int A[], int n) {

    int m = getMax(A, n);

    for (int p = 1; m / p > 0; p *= 10) 
        countingSort(A, n, p);
}
//////////////////////////////////////////////////////////////////////////////
void print(int A[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", A[i]);
}
//////////////////////////////////////////////////////////////////////////////



