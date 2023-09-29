#include <stdio.h>
#include <string.h>
#include <ctype.h>

int wordcount(char* argv)
{
    FILE *file;
    int words;
    file = fopen(argv, "r");
    words = 0;
    fseek(file, 0, SEEK_END);
    int size = ftell(file);
    fseek(file, 0, SEEK_SET);
    if(size == 0){
        return 0;
    }
    int islastspace = 1;
    char symbol;
    while(1){
        symbol = getc(file);
        if(symbol == EOF){
            break;
        }
        if(!isspace(symbol) && islastspace == 1){
            words++;
            islastspace = 0;
        } else if(isspace(symbol)){
            islastspace = 1;
        }
    }

    return words;
}
void asciiTable(char* argv)
{
    FILE *file;
    int c, all = 0;
    int ArrayOfASCIICount[256];
    for(int i = 0; i<=255; i++){
        ArrayOfASCIICount[i] = 0;
    }
    file = fopen(argv, "r");
    while(1){
        c = fgetc(file);
        if(feof(file)){
            break;
        }
        all++;
        ArrayOfASCIICount[c]++;
    }
    fclose(file);
    int out = 0;
    while(out <= 255){
        printf("%c : %d\n", out, ArrayOfASCIICount[out]);
        out++;
    }
    printf("All symbols: %d", all);


}
void latinaSymbols(char* argv)
{
    FILE *file;
    int c, all = 0;
    int ArrayOfASCIICountA[26];
    int ArrayOfASCIICounta[26];
    for(int i = 0; i<=25; i++){
        ArrayOfASCIICountA[i] = 0;
        ArrayOfASCIICounta[i] = 0;
    }
    file = fopen(argv, "r");
    while(1){
        c = fgetc(file);
        if(feof(file)){
            break;
        }
        if(c >= 'A' && c <= 'Z'){
            all++;
            ArrayOfASCIICountA[c - 'A']++;
        } else if(c >= 'a' && c <= 'z'){
            all++;
            ArrayOfASCIICounta[c-'a']++;
        }
    }
    for(int i = 0; i <= 25; i++){
        printf("%c : %d\n", i + 65, ArrayOfASCIICountA[i]);
    }
    for(int i = 0; i <= 25; i++){
        printf("%c : %d\n", i + 97, ArrayOfASCIICounta[i]);
    }
    printf("All symbols: %d", all);
}
void latinaNoRegSymbols(char* argv){
    FILE *file;
    int c, all = 0;
    int ArrayOfASCIICount[26];
    for(int i = 0; i<=25; i++){
        ArrayOfASCIICount[i] = 0;
    }
    file = fopen(argv, "r");
    while(1){
        c = fgetc(file);
        if(feof(file)){
            break;
        }
        if(c >= 'A' && c <= 'Z'){
            all++;
            ArrayOfASCIICount[c - 65]++;
        } else if(c >= 'a' && c <= 'z'){
            all++;
            ArrayOfASCIICount[c-97]++;
        }
    }
    for(int i = 0; i <= 25; i++){
        printf("%c : %d\n", i + 65, ArrayOfASCIICount[i]);
    }

}
int main(int argc, char* argv[])
{
    char *help = " LABA2 (path to file) [-w(--word)] [[--en] --ir] [--all]";
    if(argc == 1){
       printf("Not correct request.\n %s", help);
    } else if(argc == 2){
        asciiTable(argv[1]);
    } else if(argc == 3){
        if(strcmp("--all", argv[2]) == 0){
            asciiTable(argv[1]);
        } else if(strcmp("-w", argv[2]) == 0 || strcmp("--word", argv[2]) == 0){
            printf("%i", wordcount(argv[1]));
        } else if(strcmp("--en", argv[2]) == 0){
            latinaSymbols(argv[1]);
        }
    } else if(argc == 4){
        if((strcmp("--ir", argv[3]) == 0 && strcmp("--en", argv[2]) == 0) || (strcmp("--ir", argv[2]) == 0 && strcmp("--en", argv[3]) == 0)){
            latinaNoRegSymbols(argv[1]);
        }
    }
}