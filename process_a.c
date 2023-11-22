#include "ipc_functions.h"

int main(void) {

    Memory read_memory = memory_init("b_writes");
    Memory write_memory = memory_init("a_writes");

    pthread_t writer;
    pthread_t reader;

   
    pthread_create(&reader,NULL,receive_message,read_memory);
    pthread_create(&writer,NULL,send_message,write_memory);

    pthread_join(reader,NULL);
    pthread_join(writer,NULL);



    return 0;
}
