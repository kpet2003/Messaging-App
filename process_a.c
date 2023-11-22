#include "ipc_functions.h"

int main(void) {

    Memory read_memory = memory_init("b_writes");
    Memory write_memory = memory_init("a_writes");

    receive_message(read_memory);
    send_message(write_memory);


    return 0;
}
