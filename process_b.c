#include "ipc_functions.h"


int main(void) {

    Memory write_memory = memory_open("b_writes");
    Memory read_memory = memory_open("a_writes");

    send_message(write_memory);
    receive_message(read_memory);

    return 0;
}