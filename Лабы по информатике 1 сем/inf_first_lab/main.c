#include <stdio.h>
#include <stdlib.h>


int getSumOfDigits(int number) {
    if (number < 0) number *= -1;
    int sum = 0;
    while(number != 0) {
        sum += number % 10;
        number /= 10;
    }
    return sum;
}

int main()
{
    printf("Enter number: ");
    int number;
    scanf("%d", &number);
    int sum = getSumOfDigits(number);
    printf("Sum of digits: %d", sum);
    return 0;
}
