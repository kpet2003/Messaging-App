#include "shared_memory.h" 

int main(int argc, char** argv) {

    char* write_memory = memory_init("write",30);

    sprintf(write_memory,"%s","Hello world");

    return 0;
}