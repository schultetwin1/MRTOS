#include "queue.h"
#include "utils.h"

inline bool queue_empty(const queue_t* q) {
  return queue->next == queue;
}

queue_t* queue_init(queue_t* self) {
  self->next = self->next;
  self->prev = self->prev;
  return self;
}

node_t* queue_pop(queue_t* q) {
  assert(!queue_empty(q));
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
  assert(!queue_empty(q));
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

void queue_add(queue_t* queue, node_t* item, node_cmp_fn_t cmp) {
  node_t* it;
  node_t* it_prev;

  // Empty case
  if (queue_size(queue) == 0) {
    queue->head = item;
    item->next = 0;
    return;
  }

  // Insert at front
  if (cmp(item, queue->head) < 0) {
    item->next = queue->head;
    queue->head = item;
    return;
  }

  // Insert anywhere else
  it = queue->head->next;
  it_prev = queue->head;
  while (it && cmp(item, it) < 0) {
    it = it->next;
  }
  it_prev->next = item;
  item->next = it;
  return;
}
