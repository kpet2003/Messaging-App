#include "shared_memory.h"
#include <string.h>

int main(int argc, char** argv) {

    char* write_memory = memory_init("write",30);

    sprintf(write_memory,"%s","Hello world");

    write_memory+=strlen("Hello world");

    memory_free("write");

    return 0;
}