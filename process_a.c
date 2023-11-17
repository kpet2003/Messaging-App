#include "shared_memory.h"
#include <string.h>

int main(int argc, char** argv) {

    char* write_memory = memory_get("a_writes",30);

    sprintf(write_memory,"%s","Hello from a\n");

    char* read_memory = memory_get("b_writes",30);

    write_memory+=strlen("Hello from a\n");

    read_memory = memory_get("b_writes",30);
    printf("%s",read_memory);
    return 0;
}