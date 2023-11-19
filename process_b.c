#include "shared_memory.h"
#include "ipc_functions.h"
#include <string.h>
#include <pthread.h>
#include <semaphore.h>


int main(void) {

    char* read_memory = memory_get("a_writes",4096);
    char* write_memory = memory_get("b_writes",4096);

    sem_t* writer_sem = sem_open(WRITER_SEMAPHORE_FOR_A,0);
    sem_t* reader_sem = sem_open(READER_SEMAPHORE_FOR_A,1);

    while(1) {
        sem_wait(writer_sem);
        read_message(read_memory);
        sem_post(reader_sem);
    }

    write_message(write_memory);

    memory_free(read_memory);
    memory_free(write_memory);

    sem_close(writer_sem);
    sem_close(reader_sem);


    return 0;
}