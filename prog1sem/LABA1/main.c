#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

int main(int argc, char* argv[]) {
    if(argc == 1){
        printf("Gde argumenty? Naznachenie programmy i kak ispolzovat'.");
    } else if(argc == 2){
        if(strcmp(argv[1], "-h") == 0 || strcmp("--help", argv[1]) == 0){
            printf("Pomosh. (-c(--calc)) [-i(--int)] [-x(--hex); \n-t(--table)\n  ");
        } else if(strcmp(argv[1], "-t") == 0 || strcmp("--table", argv[1]) == 0){
            printf("bool %llu \n"
                   "char %llu \n"
                   "int %llu \n"
                   "double %llu \n"
                   "float %llu \n"
                   "long %llu", sizeof(bool), sizeof(char), sizeof(int), sizeof(double), sizeof(float), sizeof(long));
        } else if(strcmp(argv[1], "-c") == 0 || strcmp("--calc", argv[1]) == 0){
            printf("Primer dai.");
        } else{ printf("Error, check help.");}
    } else if(argc == 5){
        if(strcmp((argv[1]), "-c") == 0 || strcmp((argv[1]), "--calc") == 0){
            double num1 = atof(argv[2]);
            double num2 = atof(argv[4]);
            char oper = *argv[3];
            switch (oper) {
                case '+':
                    printf("%f",num1 + num2);
                    break;
                case '-':
                    printf("%f", num1 - num2);
                    break;
                case '#':
                    printf("%f", num1*num2);
                    break;
                case '/':
                    printf("%f", num1 / num2);
                    break;
                default:
                    printf("Emae, chto ty vvel?");
            }
        } else{ printf("Error, check help.");}
    } else if(argc == 6 && (strcmp(argv[1], "-c") == 0 || strcmp("--calc", argv[1]) == 0)){
        if (strcmp("-i", argv[2]) == 0 || strcmp("--int", argv[2]) == 0){
            int num1 = atoi(argv[3]);
            int num2 = atoi(argv[5]);
            char oper = *argv[4];
            switch (oper) {
                case '+':
                    printf("%i",num1 + num2);
                    break;
                case '-':
                    printf("%i", num1 - num2);
                    break;
                case '#':
                    printf("%i", num1*num2);
                    break;
                case '/':
                    printf("%i", num1 / num2);
                    break;
                default:
                    printf("Emae, chto ty vvel?");
            }
        } else if(strcmp("-x", argv[2]) == 0 || strcmp("--hex", argv[2]) == 0){
            int num1 = atof(argv[3]);
            int num2 = atof(argv[5]);
            char oper = *argv[4];
            switch (oper) {
                case '+':
                    printf("%x", num1 + num2);
                    break;
                case '-':
                    printf("%x", num1 - num2);
                    break;
                case '#':
                    printf("%x", num1 * num2);
                    break;
                case '/':
                    printf("%x", num1 / num2);
                    break;
                default:
                    printf("Emae, chto ty vvel?");
            }
        } else{ printf("Error, check help.");}
    } else if(argc == 7 && (strcmp("-c", argv[1]) == 0 || strcmp("--calc", argv[1]) == 0)){
        if (((strcmp("-x", argv[2]) == 0 || strcmp("--hex", argv[3]) == 0) || ((strcmp("--hex", argv[2]) == 0 || strcmp("-x", argv[3]) == 0) && (strcmp("-i", argv[2]) == 0 ||
                strcmp("-i", argv[3]) == 0 ||strcmp("--int", argv[3]) == 0) || strcmp("--int", argv[2]) == 0))){
            int num1 = atoi(argv[4]);
            int num2 = atoi(argv[6]);
            char oper = *argv[5];
            switch (oper) {
                case '+':
                    printf("%x", num1 + num2);
                    break;
                case '-':
                    printf("%x", num1 - num2);
                    break;
                case '#':
                    printf("%x", num1 * num2);
                    break;
                case '/':
                    printf("%x", num1 / num2);
                    break;
                default:
                    printf("Emae, chto ty vvel?");
            }
        } else{ printf("Error, check help.");}
    } else{ printf("Error, check help.");}
}


