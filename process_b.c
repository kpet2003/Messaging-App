#include "shared_memory.h"
#include <string.h>

int main(void) {

    char* read_memory = memory_get("a_writes",30);

    printf("%s",read_memory);

    char* write_memory = memory_get("b_writes",30);

    sprintf(write_memory,"%s","Hello from b\n");

    memory_free(read_memory);

    return 0;
}