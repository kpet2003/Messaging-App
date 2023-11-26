# include "ipc_functions.h"


Stats stats_init(void) {
    Stats st = malloc(sizeof(struct process_stats));
    st->received_messages = 0;
    st->sent_messages = 0;
    st->total_segments = 0;
    st->average_time = 0;
    st->average_segments = 0;
    return st;
}

Data data_init(Memory m) {
    Data data = malloc(sizeof(struct thread_data));
    data->shared_memory = m;
    data->stats = stats_init();
    return data;
}

static void print_message(char* memory) {
   fputs(memory,stdout);
   return;
}

static char* get_message(void) {
    char* message = malloc(15*sizeof(char));
    fgets(message,15*sizeof(char),stdin);
    return message;
}

static void write_message(char* memory) {
    char* message = get_message();
    memcpy(memory,message,BUFFER_SIZE);
    free(message);
}


void* send_message(void* data) {
    Data my_data = (Data)data;
    Memory memory = my_data->shared_memory;
    while(true) {
        write_message(memory->buffer);
        my_data->stats->sent_messages++;
        sem_post(&memory->writer_sem);
        if(!strncmp(END_MESSAGE,memory->buffer,5)) {
            my_data->shared_memory = memory;
            break;
        }
    }
    return my_data;
}

void* receive_message(void* data) {
    Data my_data = (Data)data;
    Memory memory = my_data->shared_memory;
    while(true) {
        
        sem_wait(&memory->writer_sem);
        print_message(memory->buffer);
        my_data->stats->received_messages++;
        if(!strncmp(END_MESSAGE,memory->buffer,5)) {
            my_data->shared_memory = memory;
            break;
        }
 
    }
    return my_data;
}

Stats calculate_stats(Stats s) {
    return s;
}



