#ifndef DICTIONARY_H_INCLUDED
#define DICTIONARY_H_INCLUDED

typedef struct KeyValue {
    char* key;
    void* value;
    int type;
    size_t size;
} KeyValue;

typedef struct Dictionary {
    KeyValue** elements;
    size_t size;
} Dictionary;

KeyValue* makeKeyValue(char* key, void* value, int type, size_t size);

void destroyKeyValue(KeyValue* kv);

void copyValue(KeyValue* kvFrom, KeyValue* kvTo);

Dictionary* makeDictionary(void);

void destroyDictionary(Dictionary* dictionary);

void addElement(Dictionary* dictionary, KeyValue* kv);

KeyValue* findElement(Dictionary* dictionary, char* key);

void removeElement(Dictionary* dictionary, char* key);

int getIndexOfElement(Dictionary* dictionary, char* key);

#endif // DICTIONARY_H_INCLUDED
