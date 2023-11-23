# include "ipc_functions.h"

static void print_message(char* memory) {
    printf("%s",memory);
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


void* send_message(void* shared_memory) {
    Memory memory = (Memory)shared_memory;
    while(true) {
        write_message(memory->buffer);
        sem_post(&memory->writer_sem);
    }
    return NULL;
}

void* receive_message(void* shared_memory) {
    Memory memory = (Memory)shared_memory;
   
    while(true) {
        sem_wait(&memory->writer_sem);
        print_message(memory->buffer);
        sem_post(&memory->reader_sem);
    }
    return NULL;
}






