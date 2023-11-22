#include "ipc_functions.h"

int main(void) {

    Memory write_memory = memory_init("a_writes");

    send_message(write_memory);



    return 0;
}
