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

  unsigned block_num;
  unsigned num_blocks = self->bufferLength / (block_size);

  for (block_num = 0; block_num < num_blocks; block_num++) {
    queue_push(&self->freelist, (node_t*)(self->buffer + (block_num * block_size)));
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
