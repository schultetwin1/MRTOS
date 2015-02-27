#include "queue.h"

void queue_add(node_t** queue_ptr, node_t* item, int (*cmp)(node_t*, node_t*)) {
  node_t* it;
  node_t* it_prev;

  // Empty case
  if (!*queue_ptr) {
    *queue_ptr = item;
    item->next = 0;
    return;
  }

  // Insert at front
  if (cmp(item, *queue_ptr) < 0) {
    item->next = *queue_ptr;
    *queue_ptr = item;
    return;
  }

  // Insert anywhere else
  it = (*queue_ptr)->next;
  it_prev = *queue_ptr;
  while (it && cmp(item, it) < 0) {
    it = it->next;
  }
  it_prev->next = item;
  item->next = it;
  return;
}

void queue_remove_item(node_t* item) {

}

node_t* queue_pop(node_t** queue_ptr) {
  node_t* popped = *queue_ptr;
  *queue_ptr = (*queue_ptr)->next;
  return popped;
}

unsigned queue_size(const node_t* queue) {
  unsigned size = 0;
  while (queue) {
    size++;
    queue = queue->next;
  }
  return size;
}
