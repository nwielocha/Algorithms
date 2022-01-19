#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct nazwiskaASCII {
    int popularnosc;
    char *nazwisko;
};

void countingSort(struct nazwiskaASCII*, struct nazwiskaASCII*, int);

int main() {

    char ch;
    int linesCount = 0;
    FILE *fptr;

    if ((fptr = fopen("nazwiskaASCII.txt", "r")) == NULL) {
        printf("Error! opening file");
        exit(1);
    }

    // zliczanie lini w pliku
    while((ch = fgetc(fptr)) != EOF) 
        if (ch == '\n')
            linesCount += 1;

    fclose(fptr);

    struct nazwiskaASCII nazwiskaASCII[linesCount];

    if ((fptr = fopen("nazwiskaASCII.txt", "r")) == NULL) {
        printf("Error! opening file");
        exit(1);
    }

    for (int i = 0; i < linesCount; i++) 
        fscanf(fptr, "%d %s\n", &nazwiskaASCII[i].popularnosc, nazwiskaASCII[i].nazwisko);

    for (int i = 0; i < linesCount; i++) 
        printf("%s\n", nazwiskaASCII[i].nazwisko);

    fclose(fptr);


    return 0;

}
/*
void countingSort(struct nazwiskaASCII* A, struct nazwiskaASCII* B, int k) {
    struct nazwiskaASCII C[k];

    for (int i = 0; i < k; i++) 
        C[i].nazwisko = 0; 

    int lengthA = sizeof(A->nazwisko) / sizeof(A[0].nazwisko);
    for (int j = 1; j < lengthA; j++) {
        C[A[j].nazwisko].nazwisko += 1;
    } 
    
}

*/
