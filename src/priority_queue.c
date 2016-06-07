#include "priority_queue.h"
#include "utils.h"

static inline void swap(block_t* a, block_t* b) {
  void* temp = a->data;
  a->data = b->data;
  b->data = temp;
}

static inline unsigned heapifymin(priority_queue_t* self, unsigned idxa, unsigned idxb, unsigned idxc) {
  unsigned idxtemp = (self->compare(self->buffer[idxa].data, self->buffer[idxb].data) < 0) ? idxa : idxb;
  return (self->compare(self->buffer[idxtemp].data, self->buffer[idxc].data) < 0) ? idxtemp : idxc;
}

static void heapifyup(priority_queue_t* self) {
  ASSERT(self);
  ASSERT(self->lastIdx > 0);

  unsigned idx = self->lastIdx;

  while (idx != 1 && self->compare(self->buffer[idx].data, self->buffer[idx / 2].data) > 0) {
    swap(&self->buffer[idx], &self->buffer[idx / 2]);
    idx = idx / 2;
  }
}

static void heapifydown(priority_queue_t* self) {
  unsigned idx = 1;
  unsigned swap_idx;
  while ((swap_idx = heapifymin(self, idx, min(idx * 2, self->lastIdx), min(idx * 2 + 1, self->lastIdx))) != idx) {
    swap(&self->buffer[idx], &self->buffer[swap_idx]);
    idx = swap_idx;
  }
}

unsigned priority_queue_size(const priority_queue_t* self) {
  return self->lastIdx;
}

const void* priority_queue_peek(const priority_queue_t* self) {
  ASSERT(self->lastIdx > 0);
  return self->buffer[1].data;
}

void priority_queue_init(priority_queue_t* self, pq_compare_fn compare, block_t* buffer, size_t length) {
  ASSERT(self);
  ASSERT(compare);
  ASSERT(buffer);

  self->buffer       = buffer;
  self->lastIdx      = 0;
  self->compare      = compare;
  self->bufferLength = length;
}

void* priority_queue_insert(priority_queue_t* self, void* item) {
  ASSERT(self);
  ASSERT(item);

  if (self->lastIdx + 1 == self->bufferLength) {
    return NULL;
  }
  self->buffer[++self->lastIdx].data = item;
  heapifyup(self);
  return item;
}

void* priority_queue_remove(priority_queue_t* self) {
  ASSERT(self->lastIdx > 0);

  void* removed = self->buffer[1].data;
  swap(&self->buffer[1], &self->buffer[self->lastIdx]);
  self->lastIdx--;
  heapifydown(self);
  
  return removed;
}
