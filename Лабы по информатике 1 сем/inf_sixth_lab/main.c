#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>


double* makeRandomArray(int length) {
    double* ar = (double*)malloc(sizeof(double) * length);
    double min = -100;
    double max = 100;
    for (int i = 0; i < length; i++) {
        ar[i] = (double)(rand()) / RAND_MAX * (max - min) + min;
    }
    return ar;
}


int compare(const void* first, const void* second) {
    const double *f, *s;
    f = (const double*)first;
    s = (const double*)second;
    if (*f > *s)
        return 1;
    else if (*f < *s)
        return -1;
    return 0;
}


double getTimeSort(void) {
    int length = 100000;
    double* randomAr = makeRandomArray(length);
    clock_t start, finish;
    start = clock();
    sort(length, randomAr);
    finish = clock();
    double time = (finish - start) / CLOCKS_PER_SEC;
    free(randomAr);
    return time;
}


double getTimeQSort(void) {
    int length = 100000;
    double* randomAr = makeRandomArray(length);
    clock_t start, finish;
    start = clock();
    qsort(randomAr, length, sizeof(double*), compare);
    finish = clock();
    double time = (finish - start) / CLOCKS_PER_SEC;
    free(randomAr);
    return time;
}


void sort(int n, double* ar) {
    int i = 0;
    bool flag = true;
    if (n != 1) {
        while (flag) {
            flag = false;
            for (int j = 0; j < n-i-1; j++) {
                if (ar[j] > ar[j+1]) {
                    double tmp = ar[j];
                    ar[j] = ar[j+1];
                    ar[j+1] = tmp;
                    flag = true;
                }
            }
            i++;
        }
    }
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
    sort(n, ar);
    printf("Sorted array: ");
    printArray(n, ar);
    free(ar);
    double time1 = getTimeSort();
    double time2 = getTimeQSort();
    if (time1 > time2) {
        printf("\nThe qsort function is faster: %f", time1 - time2);
    } else {
        printf("\nThe qsort function is slower: %f", time2 - time1);
    }
    return 0;
}
