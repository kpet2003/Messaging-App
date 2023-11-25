#include "ipc_functions.h"

int main(void) {

    Memory read_memory = memory_init("b_writes");
    Memory write_memory = memory_init("a_writes");

    pthread_t writer;
    pthread_t reader;

    Data write_data = data_init(write_memory);
    Data read_data = data_init(read_memory);
   
    pthread_create(&reader,NULL,receive_message,read_data);
    pthread_create(&writer,NULL,send_message,write_data);

    pthread_join(reader,NULL);
    pthread_join(writer,NULL);

    memory_free("b_writes");
    memory_free("a_writes");

    return 0;
}
