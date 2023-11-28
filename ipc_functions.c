# include "ipc_functions.h"


Stats stats_init(void) {
    Stats st = malloc(sizeof(struct process_stats));
    st->received_messages = 0;
    st->sent_messages = 0;
    st->total_segments_received = 0;
    st->total_segments_sent = 0;
    st->average_time = 0;
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
    char* message = malloc(MAX_SIZE*sizeof(char));
    fgets(message,MAX_SIZE*sizeof(char),stdin);
    return message;
}

static void write_message(Data data) {
    char* message = get_message();
    data->stats->sent_messages++;
    data->shared_memory->total_segments = ((strlen(message)+14)/15);
    data->stats->total_segments_sent+=data->shared_memory->total_segments;
    memcpy(data->message_to_send,message,strlen(message)+1);
    

    
    for(int i=0; i<data->shared_memory->total_segments; i++) {
        memcpy(data->message_segments[i],data->message_to_send+BUFFER_SIZE*i  ,BUFFER_SIZE);
    }
    
    free(message);
}

static void send_to_buffer(Data data) {
    int index = data->shared_memory->segments_sent;
    memcpy(data->shared_memory->buffer,data->message_segments[index],BUFFER_SIZE);
}

static void get_from_buffer(Data data) {
    int index = data->shared_memory->segments_sent*BUFFER_SIZE;
    memcpy(data->message_to_receive+index,data->shared_memory->buffer,BUFFER_SIZE);
    data->shared_memory->segments_sent++;

    if(data->shared_memory->segments_sent==data->shared_memory->total_segments) {
        data->shared_memory->message_sent = true;
    }
}



void* send_message(void* data) {
    Data my_data = (Data)data;
    while(true) {
        if(my_data->shared_memory->segments_sent==0) {
            write_message(my_data);
        }
        send_to_buffer(my_data);
        sem_post(&my_data->shared_memory->writer_sem);
        if(!strncmp(END_MESSAGE,my_data->message_to_send,5)) {
            break;
        }
    }
    return my_data;
}

void* receive_message(void* data) {
    Data my_data = (Data)data;

    while(true) {
        sem_wait(&my_data->shared_memory->writer_sem);
        get_from_buffer(my_data);
        if(my_data->shared_memory->message_sent) {
            print_message(my_data->message_to_receive);      
            my_data->stats->received_messages++;
            my_data->shared_memory->segments_sent = 0;
            my_data->shared_memory->message_sent = false;
        }

        
        if(!strncmp(END_MESSAGE,my_data->shared_memory->buffer,5)) {
            break;
        }
 
    }
    return my_data;
}

void destroy_stats(Stats s) {
    free(s);
}

void destroy_data(Data data) {
    destroy_stats(data->stats);
    free(data);
}