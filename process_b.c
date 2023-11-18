#include "shared_memory.h"
#include "ipc_functions.h"
#include <string.h>
#include <pthread.h>

int main(void) {

    char* read_memory = memory_get("a_writes",4096);
    char* write_memory = memory_get("b_writes",4096);

    read_message(read_memory);
    write_message(write_memory);

    memory_free(read_memory);

    return 0;
}