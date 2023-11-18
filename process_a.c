#include "shared_memory.h"
#include "ipc_functions.h"
#include <string.h>
#include <pthread.h>

int main(int argc, char** argv) {

    char* write_memory = memory_get("a_writes",4096);
    char* read_memory = memory_get("b_writes",4096);

    write_message(write_memory);
    read_message(read_memory);


    

    return 0;
}