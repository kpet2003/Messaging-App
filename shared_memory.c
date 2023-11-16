#include "shared_memory.h"


// allocate shared memory block
char* memory_init(const char* name, int size ) {
    int memory = shm_open(name,O_CREAT | O_RDWR,0666);
    ftruncate(memory,size);

    char* memory_block = (char*)mmap(0,size,PROT_READ| PROT_WRITE,MAP_SHARED,memory,0);

    return memory_block;
}

char* memory_open(const char* name,int size) {
    int mem = shm_open(name,O_RDONLY,0666);

    char* string = (char*)mmap(0,size,PROT_READ| PROT_WRITE,MAP_SHARED,mem,0);

    return string;
} 

void memory_free(const char* name) {
    shm_unlink(name);
}