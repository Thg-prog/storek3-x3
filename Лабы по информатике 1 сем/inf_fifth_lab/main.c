#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double* makeArray(int n);
double* sort(int n, double* ar);

double* makeRandomArray(int length) {
    double* ar = (double*)malloc(sizeof(double) * length);
    double min = -100;
    double max = 100;
    for (int i = 0; i < length; i++) {
        ar[i] = (double)(rand()) / RAND_MAX * (max - min) + min;
    }
    return ar;
}

double compare(const double* first, const double* second) {
    return *first - *second;
}

double getTimeSort(int length, double* randomAr) {
    clock_t start, finish;
    start = clock();
    randomAr = sort(length, randomAr);
    finish = clock();
    double time = (finish - start) / CLOCKS_PER_SEC;
    return time;
}

double getTimeQSort(int length, double* randomAr) {
    clock_t start, finish;
    start = clock();
    qsort(randomAr, length, sizeof(double*), (double(*) (const void *, const void *))compare);
    finish = clock();
    double time = (finish - start) / CLOCKS_PER_SEC;
    return time;
}

double* sort(int n, double* ar) {
    for (int i = 0; i < n - 1; i++) {
        double min = ar[i];
        int imin = i;
        for (int j = i + 1; j < n; j++) {
            if (ar[j] < min) {
                min = ar[j];
                imin = j;
            }
        }
        ar[imin] = ar[i];
        ar[i] = min;
    }
    return ar;
}

double* makeArray(int n) {
    double* ar = (double*)malloc(sizeof(double) * n);
    for (int i = 0; i < n; i++) {
        printf("ar[%d]: ", i);
        scanf("%lf", &ar[i]);
    }
    return ar;
}

void printArray(int n, double* ar) {
    for (int i = 0; i < n; i++)
        printf("%.3f ", ar[i]);
}

int main()
{
    int n;
    do {
        printf("Enter n: ");
        scanf("%d", &n);
    } while(n < 1);
    double* ar = makeArray(n);
    ar = sort(n, ar);
    printf("Sorted array: ");
    printArray(n, ar);
    free(ar);
    int length = 100000;
    double* randomAr = makeRandomArray(length);
    double time1 = getTimeSort(length, randomAr);
    double time2 = getTimeQSort(length, randomAr);
    if (time1 > time2) {
        printf("\nThe qsort function is faster: %f", time1 - time2);
    } else {
        printf("\nThe qsort function is slower: %f", time2 - time1);
    }
    free(randomAr);
    return 0;
}
