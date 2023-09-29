typedef struct {
    char* key;
    void* value;
    int type;
    size_t size;
} keyvalue_t;

typedef struct {
    int i; // количество кейвалуе
    size_t size;
    keyvalue_t* list;
} dictionary_t;

keyvalue_t* keyvalue_find( dictionary_t A, char* key );
void keyvalue_copy( keyvalue_t* key_0, keyvalue_t* key_1 );
keyvalue_t* keyvalue_create( size_t size, char* key, void* val, int type );
void keyvalue_remove( keyvalue_t* key );
int keyvalue_compare( keyvalue_t* key_0, keyvalue_t* key_1 );

dictionary_t* dictionary_init();
void dictionary_print( dictionary_t* A );
void dictionary_remove( dictionary_t* A );
void dictionary_add( dictionary_t* A, keyvalue_t* new_key );