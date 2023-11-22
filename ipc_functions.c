# include "ipc_functions.h"

static void print_message(char* memory) {
    printf("Received message: %s",memory);
}

static char* get_message(void) {
    printf("Write message: ");
    char* message = malloc(15*sizeof(char));
    fgets(message,sizeof(message),stdin);
    return message;
}

static void write_message(char* memory) {
    char* message = get_message();
    memcpy(memory,message,BUFFER_SIZE);
    free(message);
}


void* send_message(void* shared_memory) {
    Memory memory = (Memory)shared_memory;
    write_message(memory->buffer);     
    return NULL;
}

void* receive_message(void* shared_memory) {
    Memory memory = (Memory)shared_memory;
    print_message(memory->buffer);
    return NULL;
}






