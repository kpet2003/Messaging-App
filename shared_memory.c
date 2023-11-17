#include "shared_memory.h"


// allocate shared memory block
char* memory_get(const char* name, int size ) {
    int memory = shm_open(name,O_CREAT | O_RDWR,0666);
    ftruncate(memory,size);

    char* memory_block = (char*)mmap(0,size,PROT_READ| PROT_WRITE,MAP_SHARED,memory,0);

    return memory_block;
}

void memory_free(const char* name) {
   shm_unlink(name);
}