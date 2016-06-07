#ifndef __MRTOS_PRIORITY_QUEUE__
#define __MRTOS_PRIORITY_QUEUE__

#include <stdlib.h> //size_t

typedef int (*pq_compare_fn)(void* a, void* b);

typedef struct block block_t;
struct block {
  void* data;
};

typedef struct priority_queue priority_queue_t;
struct priority_queue {
  pq_compare_fn compare;
  block_t* buffer;
  size_t  bufferLength;
  unsigned lastIdx;
};

#define PRIORITY_QUEUE_LENGTH(NUM_BLOCKS) (sizeof(block_t) * NUM_BLOCKS)

void        priority_queue_init(priority_queue_t* self, pq_compare_fn compare, block_t* buffer, size_t length);
unsigned    priority_queue_size(const priority_queue_t* self);
const void* priority_queue_peek(const priority_queue_t* self);
void*       priority_queue_insert(priority_queue_t* self, void* item);
void*       priority_queue_remove(priority_queue_t* self);

#endif
