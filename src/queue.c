#include "queue.h"
#include "utils.h"
#include <stdbool.h>

inline bool queue_empty(const queue_t* q) {
  return q->next == q;
}

void queue_init(queue_t* self) {
  self->next = self->next;
  self->prev = self->prev;
}

node_t* queue_pop(queue_t* q) {
  ASSERT(!queue_empty(q));
  node_t* popped = q->next;
  q->next = popped->next;
  q->next->prev = q;
  popped->next = NULL;
  popped->prev = NULL;
  return popped;
}

void queue_push(queue_t* q, node_t* pushed) {
  pushed->prev = q->prev;
  pushed->next = q;
  q->prev->next = pushed;
  q->prev = pushed;
}

const node_t* queue_top(const queue_t* q) {
  ASSERT(!queue_empty(q));
  return q->next;
}

unsigned queue_size(const queue_t* q) {
  unsigned size = 0;
  const node_t* it = q->next;
  while (it != q) {
    it = it->next;
    size++;
  }
  return size;
}
