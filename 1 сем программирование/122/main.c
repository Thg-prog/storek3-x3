#include <stdio.h>
#include <stdlib.h>

int main()
{
    // int a, b;
    // scanf("%d %d", &a, &b);
    FILE* file = fopen("in.txt", "r");
    char** ar = (char**)malloc(sizeof(char*));
    int len = 0;
    while (!feof(file)) {
        ar[len] = (char*)malloc(sizeof(char) * 256);
        fgets(ar[len], 256, file);
        len++;
        ar = (char**)realloc(ar, sizeof(char*) * (len + 1));
    }
    fclose(file);
    int a = atoi(ar[0]), b = atoi(ar[1]);

    int n;
    if (a < b) {
        n = a;
    } else {
        n = b;
    }
    int* arFirst = (int*)malloc(sizeof(int));
    int* arSecond = (int*)malloc(sizeof(int));
    int countFirst = 0;
    int countSecond = 0;
    for (int i = 2; i <= n; i++) {
        if (a % i == 0) {
            arFirst[countFirst] = i;
            countFirst++;
            arFirst = (int*)realloc(arFirst, sizeof(int) * (countFirst + 1));
        }
        if (b % i == 0) {
            arSecond[countSecond] = i;
            countSecond++;
            arSecond = (int*)realloc(arSecond, sizeof(int) * (countSecond + 1));
        }
    }
    int k = 1;
    int flag = 0;
    for (int i = countFirst - 1; i >= 0; i--) {
        for (int j = countSecond - 1; j >= 0; j--) {
            if (arFirst[i] == arSecond[j]) {
                k = arFirst[i];
                flag = 1;
                break;
            }
        }
        if (flag)
            break;
    }
    int c = a / k;
    int d = b / k;
    FILE* answerFile = fopen("out.txt", "w");
    char answer[4];
    answer[0] = c + '0';
    answer[1] = ' ';
    answer[2] = d + '0';
    fputs(answer, answerFile);
    fclose(answerFile);
    // printf("%d %d", c, d);
    free(ar);
    free(arFirst);
    free(arSecond);
    return 0;
}
