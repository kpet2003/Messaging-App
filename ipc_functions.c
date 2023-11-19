# include "ipc_functions.h"
#include <string.h>


static char* get_message() {
    char* message = malloc(4096*sizeof(char));
    fgets(message,4096,stdin);
    return message;
}

Stats stats_init(void) {
    Stats st = malloc(sizeof(Stats)); 
    st->sent_messages = 0;
    st->received_messages = 0;
    st->average_segments_per_message = 0;
    st->average_time = 0;
    st->segments_per_message = 0;

    return st;
}

Arguements create_arguements(char* mem, sem_t* write_sem, sem_t* read_sem) {
    Arguements arg = malloc(sizeof(Arguements));

    arg->memory = mem;
    arg->writer_sem = write_sem;
    arg->reader_sem = read_sem;

    arg->done = false;

    arg->process = stats_init();

    return arg;

}

void* send_message(void* args) {

    Arguements my_args = (Arguements)args;
    while(true) {
        sem_wait(my_args->reader_sem);
        write_message(my_args->memory);
        sem_post(my_args->writer_sem);
    }
}


void* write_message(char* memory) {

    char* message = get_message();
    sprintf(memory,"%s",message);
    fflush(stdin); 
    memory+=strlen(message);
    free(message);
    return NULL;

}

void* receive_message(void* args) {
    Arguements my_args = (Arguements)args;
    while(true) {
        sem_wait(my_args->writer_sem);
        read_message(my_args->memory);
        sem_post(my_args->reader_sem);
    }
}


void* read_message(char* memory) {
    printf("%s",memory);
    return NULL;
}
