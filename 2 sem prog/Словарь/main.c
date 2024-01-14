#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dictionary.h"

void printKeys(Dictionary* dictionary) {
    if (dictionary->size == 0) printf("There are no keys!\n");
    for (int i = 0; i < dictionary->size; i++) {
        printf("%s\n", dictionary->elements[i]->key);
    }
}

void printElement(Dictionary* dictionary, char* key) {
    KeyValue* kv = findElement(dictionary, key);
    if (kv->type == 1) {
        printf("%d\n", *(int*)kv->value);
    } else if (kv->type == 2) {
        printf("%s\n", (char*)kv->value);
    } else if (kv->type == 3) {
        printf("%f\n", *(double*)kv->value);
    }
}

void toAddElement(Dictionary* dictionary) {
    printf("Enter the length of the key: ");
    int n;
    scanf("%d", &n);
    printf("Enter the key: ");
    char* key = (char*)malloc(sizeof(char) * (n+1));
    scanf("%s", key);
    printf("Enter type (1-integer number; 2-string; 3-real number;): ");
    int t;
    scanf("%d", &t);
    KeyValue* kv;
    if (t == 1) {
        printf("Enter the value: ");
        int value;
        scanf("%d", &value);
        kv = makeKeyValue(key, &value, t, sizeof(int));
    } else if (t == 2) {
        int len;
        printf("Enter the length of the string: ");
        scanf("%d", &len);
        printf("Enter the value: ");
        char* value = (char*)malloc(sizeof(char) * (len+1));
        scanf("%s", value);
        kv = makeKeyValue(key, value, t, sizeof(char)*(len+1));
    } else if (t == 3) {
        printf("Enter the value: ");
        double value;
        scanf("%lf", &value);
        kv = makeKeyValue(key, &value, t, sizeof(double));
    }
    free(key);
    addElement(dictionary, kv);
}

void toDeleteElement(Dictionary* dictionary) {
    printf("Enter the length of the key: ");
    int len;
    scanf("%d", &len);
    char* key = (char*)malloc(sizeof(char) * (len+1));
    printf("Enter the key: ");
    scanf("%s", key);
    removeElement(dictionary, key);
    free(key);
}

void toPrintElement(Dictionary* dictionary) {
    printf("Enter the length of the key: ");
    int len;
    scanf("%d", &len);
    char* key = (char*)malloc(sizeof(char) * (len+1));
    printf("Enter the key: ");
    scanf("%s", key);
    printElement(dictionary, key);
    free(key);
}

void toCopyElement(Dictionary* dictionary) {
    printf("Enter the length of the key: ");
    int len;
    scanf("%d", &len);
    char* keyFrom = (char*)malloc(sizeof(char) * (len+1));
    printf("Enter the key from: ");
    scanf("%s", keyFrom);
    printf("Enter the length of the key: ");
    int len1;
    scanf("%d", &len1);
    char* keyTo = (char*)malloc(sizeof(char) * (len1+1));
    printf("Enter the key to: ");
    scanf("%s", keyTo);
    KeyValue* kvFrom = findElement(dictionary, keyFrom);
    KeyValue* kvTo = findElement(dictionary, keyTo);
    copyValue(kvFrom, kvTo);
    free(keyFrom);
    free(keyFrom);
}

int main(void)
{
    Dictionary* dictionary = makeDictionary();
    printf("0 to exit; 1 to add element; 2 to print keys; 3 to delete element; 4 to print element; 5 to copy element\n");
    while(1) {
        printf("Enter number: ");
        int type;
        scanf("%d", &type);
        if(type == 1) {
            toAddElement(dictionary);
        } else if (type == 0) {
            destroyDictionary(dictionary);
            break;
        } else if (type == 2) {
            printKeys(dictionary);
        } else if (type == 3) {
            toDeleteElement(dictionary);
        } else if (type == 4) {
            toPrintElement(dictionary);
        } else if (type == 5) {
            toCopyElement(dictionary);
        }
    }
    return 0;
}
