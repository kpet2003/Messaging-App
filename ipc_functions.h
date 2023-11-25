#include "shared_memory.h"

struct process_stats {
    int sent_messages;
    int received_messages;
    int total_segments;
    double average_segments;
    double average_time;
};

typedef struct process_stats* Stats;

struct thread_data {
    Memory shared_memory;
    bool communication_ended;
    char message[4096];
    Stats stats;
};

typedef struct thread_data* Data;

Data data_init(Memory mem);
Stats stats_init(void);
void* send_message(void* shared_memory);
void* receive_message(void* shared_memory);

