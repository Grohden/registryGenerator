typedef struct TypeRegistry {
    int test;
    char * str;
} Registry;

Registry *initRegistry();

void generateEntries(int howMany);
