typedef struct TypeHashTable {
    int size;
    void **elements;
} HashTable;

void createCachedHashTable(size_t size);

void destroyHashTable(HashTable *table);

unsigned long hash(const char *string);

void* getFromHashTable(char *string);

void putIntoHashTable(char *string, void *structPointer);
