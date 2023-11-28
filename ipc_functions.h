#include "shared_memory.h"
#define MAX_SIZE 4096
#define END_MESSAGE "#BYE#"

struct process_stats {
    int sent_messages;
    int received_messages;
    int total_segments_sent;
    int total_segments_received;
    double average_time;
};

typedef struct process_stats* Stats;

struct thread_data {
    Memory shared_memory;
    char message_to_send[MAX_SIZE];
    char message_to_receive[MAX_SIZE];
    char message_segments[MAX_SIZE/BUFFER_SIZE][BUFFER_SIZE+1];
    Stats stats;
};

typedef struct thread_data* Data;

Data data_init(Memory mem);
Stats stats_init(void);
void* send_message(void* shared_memory);
void* receive_message(void* shared_memory);
void  destroy_stats(Stats s);
void  destroy_data(Data d);
