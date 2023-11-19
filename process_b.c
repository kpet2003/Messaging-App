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


    Arguements for_reader_thread = create_arguements(read_memory,writer_sem,reader_sem);

    pthread_t reader_thread;

    pthread_create(&reader_thread,NULL,receive_message,for_reader_thread);
    pthread_join(reader_thread,NULL);


    Arguements for_writer_thread = create_arguements(write_memory,reader_sem,writer_sem);

    pthread_t writer_thread;
    pthread_create(&writer_thread,NULL,send_message,for_writer_thread);
    pthread_join(writer_thread,NULL);


    memory_free(read_memory);
    memory_free(write_memory);

    sem_close(writer_sem);
    sem_close(reader_sem);


    return 0;
}