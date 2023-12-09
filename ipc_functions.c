# include "ipc_functions.h"

// initialise stats struct //
Stats stats_init(void) {
    Stats st = malloc(sizeof(struct process_stats));
    st->received_messages = 0;
    st->sent_messages = 0;
    st->total_segments_received = 0;
    st->total_segments_sent = 0;
    st->total_time_waited = 0;
    return st;
}
// initialise thread data
Data data_init(Memory m) {
    Data data = malloc(sizeof(struct thread_data));
    data->shared_memory = m;
    data->stats = stats_init();
    return data;
}

// calculate time difference in seconds
double time_diff(struct timeval *start, struct timeval *end) {
    return (double)(end->tv_sec - start->tv_sec) + 
           (double)(end->tv_usec - start->tv_usec) / 1000000.0;
}



// print received message
static void print_message(char* memory) {
   fputs(memory,stdout);
   return;
}

// get the message from user
static char* get_message(void) {
    char* message = malloc(MAX_SIZE*sizeof(char));
    fgets(message,MAX_SIZE*sizeof(char),stdin);
    return message;
}

static void clear_string(char* string) {
    string[0] = '\0';
}

static void write_message(Data data) {
    char* message = get_message();
    data->stats->sent_messages++;
    
    // get the time that we got the message from user
    gettimeofday(&data->shared_memory->start, NULL);

    // we clear the old message segments
    for(int i=0; i<data->shared_memory->total_segments; i++) {
        clear_string(data->message_segments[i]);
    }
    // we calculate the segments of the new message
    data->shared_memory->total_segments = ((strlen(message)+14)/15);
    data->stats->total_segments_sent+=data->shared_memory->total_segments;

    // we store the message to the thread data
    memcpy(data->message_to_send,message,strlen(message)+1);

    // we break the message in segments of BUFFER size and store them  
    for(int i=0; i<data->shared_memory->total_segments; i++) {
        memcpy(data->message_segments[i],data->message_to_send+BUFFER_SIZE*i  ,BUFFER_SIZE);
    }
    free(message);
}


// we send the correct segment to the shared memory buffer
static void send_to_buffer(Data data) {
    int index = data->shared_memory->segments_sent;
    memcpy(data->shared_memory->buffer,data->message_segments[index],BUFFER_SIZE);
}

// we retreive the message from the buffer
static void get_from_buffer(Data data) {
    // if we haven't received any segments, clear the old message so that we don't have overwrites
    if(!data->shared_memory->segments_sent) {
        clear_string(data->message_to_receive);
    }
    // append each segment in the message to receive segment
    strcat(data->message_to_receive,data->shared_memory->buffer);
    if(!data->shared_memory->segments_sent) {
        // get the time that we got the first message segment and add it to the total time that we waited for the first segment
        gettimeofday(&data->shared_memory->end, NULL);
        data->stats->total_time_waited+=time_diff(&data->shared_memory->start,&data->shared_memory->end);
    }
    data->shared_memory->segments_sent++;
}


void* send_message(void* data) {
    Data my_data = (Data)data;
    while(true) {
        // we wait for the other process to finish reading the message
        sem_wait(&my_data->shared_memory->reader_sem);

        // if we haven't sent any segments,get new message from user
        if(!my_data->shared_memory->segments_sent) {
            clear_string(my_data->message_to_send);
            write_message(my_data);
        }
        // send a segment
        send_to_buffer(my_data);
        sem_post(&my_data->shared_memory->writer_sem);

        // if the user enters END_MESSAGE the communication ends
        if(!strncmp(END_MESSAGE,my_data->message_to_send,5)) {
            break;
        }
    }
    return my_data;
}

void* receive_message(void* data) {
    Data my_data = (Data)data;

    while(true) {
        // we wait for the other process to finish writing the message
        sem_wait(&my_data->shared_memory->writer_sem);

        get_from_buffer(my_data);

        // if we received all the segments, print the message and update the statistics
        if(my_data->shared_memory->segments_sent==my_data->shared_memory->total_segments) {
            print_message(my_data->message_to_receive);
            my_data->stats->received_messages++;
            my_data->stats->total_segments_received+=my_data->shared_memory->total_segments;      
            my_data->shared_memory->segments_sent = 0;
        }
       
        sem_post(&my_data->shared_memory->reader_sem);
        // if the user enters END_MESSAGE the communication ends
        if(!strncmp(END_MESSAGE,my_data->shared_memory->buffer,5)) {
            break;
        }
 
    }
    return my_data;
}

// free all the data
void destroy_data(Data data) {
    free(data->stats);
    free(data);
}