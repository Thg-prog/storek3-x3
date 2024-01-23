#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n;
    printf("Enter n: ");
    scanf("%d", &n);
    int k = 0;
    for (int i = n+1; i < 2*n; i++) {
        int count = 0;
        for (int j = 2; j < i; j++) {
            if (i % j == 0)
                count += 1;
        }
        if (count == 0)
            k += 1;
    }
    printf("%d", k);
    return 0;
}
