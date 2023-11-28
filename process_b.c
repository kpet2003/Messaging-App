#include "ipc_functions.h"


int main(void) {

    Memory write_memory = memory_open("b_writes");
    Memory read_memory = memory_open("a_writes");

    pthread_t writer;
    pthread_t reader;

    Data write_data = data_init(write_memory);
    Data read_data = data_init(read_memory);

    pthread_create(&writer,NULL,send_message,write_data);
    pthread_create(&reader,NULL,receive_message,read_data);

    pthread_join(writer,(void**)&write_data);
    pthread_join(reader,(void**)&read_data);

    printf("Process_b sent %d messages\n",write_data->stats->sent_messages);
    printf("Process_b received %d messages\n",read_data->stats->received_messages);
    printf("Process_b sent %d message segments\n",write_data->stats->total_segments_sent);
    printf("Process_b received %d message segments\n",read_data->stats->total_segments_received);
    printf("Process_b sent %lf message segments average\n",(double)write_data->stats->total_segments_sent / (double)write_data->stats->sent_messages);
    printf("Process_b received %lf message segments average\n",(double)read_data->stats->total_segments_received / (double)read_data->stats->received_messages);

    memory_free("b_writes");
    
    
    destroy_data(write_data);
    destroy_data(read_data);

    return 1;
}