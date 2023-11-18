#include "shared_memory.h"
#include "ipc_functions.h"
#include <string.h>
#include <pthread.h>
#include <semaphore.h>




int main(int argc, char** argv) {

    char* write_memory = memory_get("a_writes",4096);
    char* read_memory = memory_get("b_writes",4096);


    // we remove them, in case they already exist
    sem_unlink(WRITER_SEMAPHORE_FOR_A);
    sem_unlink(READER_SEMAPHORE_FOR_A);

    sem_t* writer_sem = sem_open(WRITER_SEMAPHORE_FOR_A,O_CREAT,0660,1);
    sem_t* reader_sem = sem_open(READER_SEMAPHORE_FOR_A,O_CREAT,0660,0);

    if(writer_sem==SEM_FAILED) {
        perror("Failed to create writer semaphore");
        exit(1);
    }

    if(reader_sem==SEM_FAILED) {
        perror("Failed to create reader semaphore");
        exit(1);
    }


    while(1) {
        sem_wait(reader_sem);
        write_message(write_memory);
        sem_post(writer_sem);
    }

  
    read_message(read_memory);

    sem_close(reader_sem);
    sem_close(writer_sem);

    sem_unlink(WRITER_SEMAPHORE_FOR_A);
    sem_unlink(READER_SEMAPHORE_FOR_A);


    return 0;
}