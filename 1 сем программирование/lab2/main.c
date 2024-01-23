#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


int getWordsCount(char** ar, int length);
void printCountFrequency(char** ar, int n, char* flag);


int getWordsCount(char** ar, int length) {
	int globalCount = 1;
	for (int i = 0; i < length; i++) {
		int localCount = 0;
		for (int j = 0; j < 255; j++) {
			if (isspace(ar[i][j]) && !isspace(ar[i][j+1])) {
				localCount++;
			}
		}
		globalCount += localCount;
	}
	return globalCount;

}


void printCountFrequency(char** ar, int n, char* flag) {
    int symbolsCount;
    char* symbols;
    if (strcmp(flag, "-en") == 0) {
        symbolsCount = 52;
        symbols = (char*)malloc(sizeof(char) * symbolsCount);
        for (int i = 0; i < symbolsCount / 2; i++) {
            symbols[i] = i + 65;
        }
        for (int i = symbolsCount / 2; i < symbolsCount; i++) {
            symbols[i] = i + 71;
        }
    } else if (strcmp(flag, "-all") == 0) {
        symbolsCount = 256;
        symbols = (char*)malloc(sizeof(char) * symbolsCount);
        for (int i = 0; i < symbolsCount; i++) {
            symbols[i] = i;
        }
    } else if (strcmp(flag, "-ir") == 0) {
        symbolsCount = 26;
        symbols = (char*)malloc(sizeof(char) * symbolsCount);
        for (int i = 0; i < symbolsCount; i++) {
            symbols[i] = i + 97;
        }
    }
	int* allSymbolsCount = (int*)malloc(sizeof(int) * symbolsCount);
	int allSymbolsCountInText = 0;
	for (int x = 0; x < symbolsCount; x++) {
		int count = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < 256; j++) {
				if ((strcmp(flag, "-ir") != 0 && ar[i][j] == symbols[x]) \
        || (strcmp(flag, "-ir") == 0 && tolower(ar[i][j]) == symbols[x])) {
					count++;
					allSymbolsCountInText++;
				}
			}
		}
		allSymbolsCount[x] = count;
	}
	printf("\n   Count | Frequency\n");
	for (int i = 0; i < symbolsCount; i++) {
        double frequency = (double)allSymbolsCount[i] / (double)allSymbolsCountInText;
        printf("%c|   %d   |    %.4f\n", symbols[i], allSymbolsCount[i], frequency);
    }
	free(allSymbolsCount);
	free(symbols);
}


int main(int argc, char* argv[]) {
    if (argc >= 2) {
        FILE* file = fopen(argv[1], "r");
        char** ar = (char**)malloc(sizeof(char*));
        int n = 0;
        while (!feof(file)) {
            ar[n] = (char*)malloc(sizeof(char) * 256);
            fgets(ar[n], 256, file);
            n++;
            ar = (char**)realloc(ar, sizeof(char*) * (n + 1));
        }
        fclose(file);

        if (argc == 3 && strcmp(argv[2], "-w") == 0) {
            int wordsCount = getWordsCount(ar, n);
            printf("Number of words in the file: %d", wordsCount);
        } else if (argc == 3 && strcmp(argv[2], "-en") == 0) {
            printCountFrequency(ar, n, "-en");
        } else if (argc == 3 && strcmp(argv[2], "-all") == 0) {
            printCountFrequency(ar, n, "-all");
        } else if (argc == 3 && strcmp(argv[2], "-ir") == 0) {
            printCountFrequency(ar, n, "-ir");
        }

        for (int i = 0; i < n; i++) {
            free(ar[i]);
        }
        free(ar);
    }
	return 0;
}
