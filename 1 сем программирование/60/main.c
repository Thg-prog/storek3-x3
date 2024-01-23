#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

int main()
{
    int n;
    printf("Enter n: ");
    scanf("%d", &n);
    int* ar = (int*)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        printf("Enter ar[%d]: ", i);
        scanf("%d", &ar[i]);
    }
    int d = ar[1] - ar[0];
    int index = 0;
    int* counts = (int*)malloc(sizeof(int) * index);
    int count = 2;
    for (int i = 1; i < n-1; i++) {
        if (ar[i+1] - ar[i] == d) {
            count++;
        } else {
            d = ar[i+1] - ar[i];
            counts = (int*)realloc(counts, sizeof(int) * (index + 1));
            counts[index] = count;
            index++;
            count = 2;
        }
    }
    counts = (int*)realloc(counts, sizeof(int) * (index + 1));
    counts[index] = count;
    int max = counts[0];
    for (int i = 1; i < index+1; i++) {
        if (counts[i] > max)
            max = counts[i];
    }
    printf("Max count: %d", max);
    free(ar);
    free(counts);
    return 0;
}
