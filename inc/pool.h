#ifndef __MRTOS_POOL__
#define __MRTOS_POOL__
#include "utils.h"
#include "queue.h"
#include <stdlib.h>

/*
 * USAGE: Any data you want in a pool must be in a struct with a node_t as the
 *        first element.
 */
typedef struct pool pool_t;
struct pool {
  byte_t* buffer;
  size_t  bufferLength;
  queue_t freelist;
};

#define POOL_LENGTH(BLOCK_SIZE, NUM_BLOCKS) (BLOCK_SIZE * NUM_BLOCKS)

void     pool_init(pool_t* self, byte_t* buffer, size_t length);
unsigned pool_set_block_size(pool_t* self, size_t block_size);
node_t*  pool_alloc(pool_t* self);
void     pool_free(pool_t* self, node_t* data);
#endif
