#include "shared_memory.h"

#define WRITER_SEMAPHORE_FOR_A "/writer_sem"
#define READER_SEMAPHORE_FOR_A "/reader_sem"


void* write_message(char* memory);

void* read_message(char* memory);