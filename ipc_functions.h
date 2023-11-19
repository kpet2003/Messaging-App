#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <semaphore.h>

#define WRITER_SEMAPHORE_FOR_A "/writer_sem"
#define READER_SEMAPHORE_FOR_A "/reader_sem"

struct process_stats {
    int sent_messages;
    int received_messages;

    int average_segments_per_message;
    int segments_per_message;

    int average_time;

};

typedef struct process_stats* Stats;

struct function_arguments {
    char* memory;
    sem_t* writer_sem;
    sem_t* reader_sem;
    bool done;

    Stats process;

};

typedef struct function_arguments* Arguements;

Stats stats_init(void);

Arguements create_arguements(char* mem, sem_t* write_sem, sem_t* read_sem);

void* send_message(void* args);

void* write_message(char* memory);

void* receive_message(void* args);

void* read_message(char* memory);