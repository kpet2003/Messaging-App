#include "shared_memory.h"
#include <string.h>

int main(void) {

    char* write_memory = memory_open("write",30);

    printf("%s",write_memory);

    memory_free("write");

    return 0;
}