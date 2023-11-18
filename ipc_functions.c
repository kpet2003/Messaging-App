# include "ipc_functions.h"
#include <string.h>


static char* get_message() {
    char* message = malloc(4096*sizeof(char));

    fgets(message,4096,stdin);

    return message;

}



void* write_message(char* memory) {

    char* message = get_message();
    sprintf(memory,"%s",message);
    memory+=strlen(message);
    free(message);
    return NULL;

}

void* read_message(char* memory) {
    printf("%s",memory);
    return NULL;
}
