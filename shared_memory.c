#include "shared_memory.h"


// allocate shared memory block
Memory memory_init(const char* name) {
    shm_unlink(name);
    int fd = shm_open(name,O_CREAT | O_EXCL | O_RDWR ,0600);

    
    if(fd == -1) {
        perror("shm_open");
        exit(1);
    }
    int error_code = ftruncate(fd,sizeof(struct memory));

    if(error_code == -1) {
        perror("ftruncate");
        exit(1);
    }

    Memory memory_block = (Memory)mmap(NULL,sizeof(*memory_block),PROT_READ| PROT_WRITE,MAP_SHARED,fd,0);

    if(memory_block == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }

    error_code = sem_init(&memory_block->writer_sem,1,0);
    if(error_code == -1) {
        perror("writer semaphore");
        exit(1);
    }

    error_code = sem_init(&memory_block->reader_sem,1,1);
    if(error_code == -1) {
        perror("writer semaphore");
        exit(1);
    }

    error_code = pthread_mutex_init(&memory_block->mutex,NULL);
    if(error_code == -1) {
        perror("mutex");
        exit(1);
    }


    memory_block->message_sent = false;
    memory_block->segments_sent = 0;
    
    return memory_block;
}

Memory memory_open(const char* name) {
    int fd = shm_open(name,O_RDWR,0);

    if(fd==-1) {
        perror("shm_open");
        exit(1);
    }

    Memory memory_block = (Memory)mmap(NULL,sizeof(*memory_block),PROT_READ| PROT_WRITE,MAP_SHARED,fd,0);

    if(memory_block == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }

    return memory_block;
}


void memory_free(const char* name) {
    Memory mem = memory_open(name);
    shm_unlink(name);
    sem_close(&mem->writer_sem);
    sem_close(&mem->reader_sem);
    munmap(mem,sizeof(*mem));
}