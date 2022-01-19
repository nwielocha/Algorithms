#include <iostream>
#include <fstream>
#include <ostream>
#include <string>
#define N 10

void heapify(std::string A[], int n, int i);
void swap(std::string* a, std::string* b);
void buildHeap(std::string A[], int n); 
void heapSort(std::string A[], int n);

int main() {

    std::string A[N];
    std::string linia;
    int i = 0;

    std::ifstream myfile("plik.txt");

    if (myfile.is_open()) {
        while (getline(myfile, linia)) {
            A[i] = linia;
            std::cout << A[i] << std::endl;
            i++;
        }

        myfile.close();
    }
    else std::cout << "Error!\n";

    heapSort(A, N);

    std::cout << A[0] << A[1] << A[2] << A[3] << A[4] << 
        A[5] << A[6] << A[7] << A[8] << A[9] << std::endl;

    return 0;
}

void swap(std::string* a, std::string* b) {
    std::string t = *a;
    *a = *b;
    *b = t;
}

void heapify(std::string A[], int n, int i) {
    int l = 2 * i;
    int r = 2 * i + 1;
    int largest;

    if (l <= n && A[l] > A[i])
        largest = l;
    else largest = i;

    if (r <= n && A[r] > A[largest]) 
        largest = r;

    if (largest != i) {
        swap(A[i], A[largest]);
        heapify(A, n, largest);
    }
}

void buildHeap(std::string A[], int n) {
    for (int i = n / 2; i >= 0; i--)
        heapify(A, n, i);
}

void heapSort(std::string A[], int n) {
    buildHeap(A, n);
    int t = n;
    for (int i = t; i >= 1; i--) {
        swap(A[0], A[n]);
        n = n - 1;
        heapify(A, t, 1);
    }
}
