#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/mman.h>
#include <pthread.h>
#include <string.h>
#include <semaphore.h>
#include <stdbool.h>
#include <sys/time.h>


#define BUFFER_SIZE 15

struct memory {
    char buffer[BUFFER_SIZE];   // message buffer
    sem_t writer_sem;
    sem_t reader_sem;
    int segments_sent;
    int total_segments;
    // structs for gettimeofday
    struct timeval start;
    struct timeval end;
};

typedef struct memory* Memory;

Memory memory_init(const char* name );

Memory memory_open(const char* name);

void memory_free(const char* name);