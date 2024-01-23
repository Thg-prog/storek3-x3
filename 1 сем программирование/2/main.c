#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int getNewNumber(int n) {
    int* ar = (int*)malloc(sizeof(int));
    int len = 0;
    while (n != 0) {
        ar = (int*)realloc(ar, sizeof(int) * (len + 1));
        ar[len] = n % 2;
        n /= 2;
        len++;
    }
    int index = 0;
    while (index < len && ar[index] != 1) {
        index++;
    }
    int number = 0;
    for (int i = index; i >= 0; i--) {
        number += pow(2, i) * ar[i];
    }
    return number;
    free(ar);
}


int main()
{
    printf("Enter a, b: ");
    int a;
    int b;
    scanf("%d %d", &a, &b);
    int sum = 0;
    for (int i = a; i <= b; i++) {
        sum += getNewNumber(i);
    }
    printf("%d", sum);
    return 0;
}
