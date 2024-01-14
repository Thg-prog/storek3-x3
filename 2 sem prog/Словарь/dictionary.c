#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "dictionary.h"

KeyValue* makeKeyValue(char* key, void* value, int type, size_t size) {
    KeyValue* kv = (KeyValue*)malloc(sizeof(KeyValue));
    kv->key = (char*)malloc(sizeof(char)*(strlen(key)+1));
    memcpy(kv->key, key, sizeof(char)*(strlen(key)+1));
    kv->type = type;
    kv->size = size;
    kv->value = malloc(size);
    memcpy(kv->value, value, size);
    return kv;
}

void destroyKeyValue(KeyValue* kv) {
    free(kv->value);
    free(kv->key);
    kv->size = 0;
    free(kv);
}

void copyValue(KeyValue* kvFrom, KeyValue* kvTo) {
    kvTo->type = kvFrom->type;
    kvTo->size = kvFrom->size;
    free(kvTo->value);
    kvTo->value = malloc(kvTo->size);
    memcpy(kvTo->value, kvFrom->value, kvTo->size);
}

Dictionary* makeDictionary(void) {
    Dictionary* dictionary = (Dictionary*)malloc(sizeof(Dictionary));
    dictionary->elements = (KeyValue**)malloc(sizeof(KeyValue*));
    dictionary->size = 0;
    return dictionary;
}

void destroyDictionary(Dictionary* dictionary) {
    for (int i = 0; i < dictionary->size; i++) {
        destroyKeyValue(dictionary->elements[i]);
    }
    free(dictionary->elements);
    dictionary->size = 0;
    free(dictionary);
}

int getIndexOfElement(Dictionary* dictionary, char* key) {
    for (int i = 0; i < dictionary->size; i++) {
        if (strcmp(dictionary->elements[i]->key, key) == 0)
            return i;
    }
    return -1;
}

void addElement(Dictionary* dictionary, KeyValue* kv) {
    int index = getIndexOfElement(dictionary, kv->key);
    if (index != -1) {
        free(dictionary->elements[index]->value);
        dictionary->elements[index]->value = malloc(kv->size);
        memcpy(dictionary->elements[index]->value, kv->value, kv->size);
        dictionary->elements[index]->type = kv->type;
        dictionary->elements[index]->size = kv->size;
    } else {
        dictionary->size++;
        dictionary->elements = realloc(dictionary->elements, sizeof(KeyValue)*dictionary->size);
        dictionary->elements[dictionary->size-1] = kv;
    }
}

KeyValue* findElement(Dictionary* dictionary, char* key) {
    for (int i = 0; i < dictionary->size; i++) {
        if (strcmp(key, dictionary->elements[i]->key) == 0) {
            return dictionary->elements[i];
        }
    }
    return NULL;
}


void removeElement(Dictionary* dictionary, char* key) {
    KeyValue* kv = findElement(dictionary, key);
    int index = getIndexOfElement(dictionary, key);
    for (int i = index+1; i < dictionary->size; i++) {
        dictionary->elements[i-1] = dictionary->elements[i];
    }
    destroyKeyValue(kv);
    dictionary->size--;
    dictionary->elements = realloc(dictionary->elements, sizeof(KeyValue)*dictionary->size);
}
