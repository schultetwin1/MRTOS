#include "queue.h"

void queue_add(node_t* queue, node_t* item, int (*cmp)(node_t*, node_t*)) {
  node_t* it;
  node_t* it_prev;

  // Empty case
  if (!queue) {
    queue = item;
    item->next = 0;
    return;
  }

  // Insert at front
  if (cmp(item, queue) < 0) {
    item->next = queue;
    queue = item;
    return;
  }

  // Insert anywhere else
  it = queue->next;
  it_prev = queue;
  while (it && cmp(item, it) < 0) {
    it = it->next;
  }
  it_prev->next = item;
  item->next = it;
  return;
}

void queue_remove_item(node_t* item) {

}

node_t* queue_pop(node_t* queue) {
  node_t* popped = queue;
  queue = queue->next;
  return popped;
}

unsigned queue_size(node_t* queue) {
  unsigned size = 0;
  while (queue) {
    size++;
    queue = queue->next;
  }
  return size;
}
