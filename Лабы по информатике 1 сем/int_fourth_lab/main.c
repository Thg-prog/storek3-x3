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
    int left = 0;
    int right = n - 1;
    int i;
    while (left <= right) {
        i = (left + right) / 2;
        if (ar[i] > x) {
            right = i - 1;
        } else if (ar[i] < x) {
            left = i + 1;
        } else {
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
    if (index == -1)
        printf("This number is not in the array");
    else
        printf("This number is index %d", index);
    free(ar);
    return 0;
}
