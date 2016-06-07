#include "queue.h"
#include "pool.h"
#include "utils.h"

void pool_init(pool_t* self, byte_t* buffer, size_t length) {
  ASSERT(self);
  ASSERT(buffer);

  self->buffer       = buffer;
  self->bufferLength = length;
  queue_init(&self->freelist);
}

unsigned pool_set_block_size(pool_t* self, size_t block_size) {
  ASSERT(self);
  ASSERT(self->bufferLength);

  unsigned num_blocks = 0;
  byte_t* buffer_it = self->buffer;
  byte_t* buffer_end = self->buffer + self->bufferLength;

  while (buffer_it < buffer_end) {
    queue_push(&self->freelist, (node_t*)(buffer_it));
    buffer_it = buffer_it + block_size;
    num_blocks++;
  }
  return num_blocks;
}

node_t* pool_alloc(pool_t* self) {
  ASSERT(self);

  node_t* block = queue_pop(&self->freelist);
  return block;
}

void pool_free(pool_t* self, node_t* block) {
  ASSERT(self);
  ASSERT(block);

  queue_push(&self->freelist, block);
}
