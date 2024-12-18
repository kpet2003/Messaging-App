#include "ipc_functions.h"

int main(void) {

    // initialise the shared memory segments
    Memory read_memory = memory_init("b_writes");
    Memory write_memory = memory_init("a_writes");


    // declare threads
    pthread_t writer;
    pthread_t reader;


    // allocate thread data
    Data write_data = data_init(write_memory);
    Data read_data = data_init(read_memory);
    
    // create and call thread functions
    pthread_create(&writer,NULL,send_message,write_data);
    pthread_create(&reader,NULL,receive_message,read_data);
    
    // return from thread functions
    pthread_join(writer,(void**)&write_data);
    pthread_join(reader,(void**)&read_data);

    
    // print statistics
    printf("Process_a sent %d messages\n",write_data->stats->sent_messages);
    printf("Process_a sent %d message segments\n",write_data->stats->total_segments_sent);
    printf("Process_a sent %lf message segments average\n", (double)write_data->stats->total_segments_sent / (double)write_data->stats->sent_messages);
    printf("Process_a received %d messages\n",read_data->stats->received_messages);
    printf("Process_a received %d message segments\n",read_data->stats->total_segments_received);
    printf("Process_a received %lf message segments average\n",(double)read_data->stats->total_segments_received / (double)read_data->stats->received_messages);
    printf("Process_a waited %lf seconds for the first segment average\n ",(double)read_data->stats->total_time_waited/(double)read_data->stats->received_messages);


    // free all memory and destroy the threads
    memory_free("a_writes");
    destroy_data(write_data);
    destroy_data(read_data);
    

    return 0;
}
