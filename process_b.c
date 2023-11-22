#include "ipc_functions.h"


int main(void) {

    Memory write_memory = memory_open("b_writes");
    Memory read_memory = memory_open("a_writes");

    pthread_t writer;
    pthread_t reader;

    pthread_create(&writer,NULL,send_message,write_memory);
    pthread_create(&reader,NULL,receive_message,read_memory);

    pthread_join(writer,NULL);
    pthread_join(reader,NULL);

    return 0;
}