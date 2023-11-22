#include "ipc_functions.h"


int main(void) {

    Memory read_memory = memory_open("a_writes");
    receive_message(read_memory);
    return 0;
}