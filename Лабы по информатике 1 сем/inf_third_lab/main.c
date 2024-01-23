#include <stdio.h>
#include <stdlib.h>


double* makeArray(int n) {
    double* ar = (double*)malloc(sizeof(double) * n);
    for (int i = 0; i < n; i++) {
        printf("ar[%d]: ", i);
        scanf("%lf", &ar[i]);
    }
    return ar;
}


int getIndex(int n, double* ar, double x) {
    for (int i = 0; i < n; i++) {
        if (ar[i] == x) {
            return i;
        }
    }
    return -1;
}


int main()
{
    int n;
    do {
        printf("Enter n: ");
        scanf("%d", &n);
    } while (n < 1);
    double* ar = makeArray(n);
    double x;
    printf("Enter x: ");
    scanf("%lf", &x);
    int index = getIndex(n, ar, x);
    printf("%d", index);
    free(ar);
    return 0;
}
