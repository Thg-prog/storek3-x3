#include <stdio.h>
#include <stdlib.h>


double* input(int n) {
    double* ar = (double*)malloc(sizeof(double) * n);
    for (int i = 0; i < n; i++) {
        printf("ar[%d] = ", i);
        scanf("%lf", &ar[i]);
    }
    return ar;
}


int getIMin(int n, double* ar) {
    double min = 0;
    int imin = 0;
    int i = 0;
    while (i < n && min == 0) {
        if (ar[i] > 0) {
            min = ar[i];
            imin = i;
        }
        i++;
    }
    if (min == 0) return -1;
    int firstI = imin;
    for (int i = firstI; i < n; i++) {
        if (ar[i] > 0 && ar[i] < min) {
            min = ar[i];
            imin = i;
        }
    }
    return imin;
}


int getIMax(int n, double* ar) {
    double max = 0;
    int imax = 0;
    int i = 0;
    while (i < n && max == 0) {
        if (ar[i] < 0) {
            max = ar[i];
            imax = i;
        }
        i++;
    }
    if (max == 0) return -1;
    int firstI = imax;
    for (int i = firstI; i < n; i++) {
        if (ar[i] < 0 && ar[i] > max) {
            max = ar[i];
            imax = i;
        }
    }
    return imax;
}


double* change(int imin, int imax, double* ar) {
    if (imin != -1 && imax != -1) {
        double tmp = ar[imin];
        ar[imin] = ar[imax];
        ar[imax] = tmp;
    }
    return ar;
}


void output(int n, double* ar) {
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
    double* ar = input(n);
    int imin = getIMin(n, ar);
    int imax = getIMax(n, ar);
    ar = change(imin, imax, ar);
    output(n, ar);
    free(ar);
    return 0;
}
