#include <stdio.h>
#include <stdlib.h>


double* createArray(int n) {
    double* ar = (double*)malloc(sizeof(double) * n);
    for (int i = 0; i < n; i++) {
        printf("Enter ar[%d]: ", i);
        scanf("%lf", &ar[i]);
    }
    return ar;
}


int getIMax(int n, double* ar) {
    double max = ar[0];
    int imax = 0;
    for (int i = 1; i < n; i++) {
        if (ar[i] > max) {
            max = ar[i];
            imax = i;
        }
    }
    return imax;
}

int getIMin(int n, double* ar) {
    double min = ar[0];
    int imin = 0;
    for (int i = 1; i < n; i++) {
        if (ar[i] < min) {
            min = ar[i];
            imin = i;
        }
    }
    return imin;
}


double* change(double* ar, int imax, int imin) {
    if (imax == imin) {
        double tmp = ar[imax];
        ar[imax] = ar[imin];
        ar[imin] = tmp;
    }
    return ar;
}


void printArray(int n, double* ar) {
    for (int i = 0; i < n; i++) {
        printf("%f ", ar[i]);
    }
}

int main()
{
    int n;
    do {
        printf("Enter n: ");
        scanf("%d", &n);
    } while (n < 1);
    double* ar = createArray(n);
    int imax = getIMax(n, ar);
    int imin = getIMin(n, ar);
    ar = change(ar, imax, imin);
    printArray(n, ar);
    free(ar);
    return 0;
}
