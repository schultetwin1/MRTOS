#include "queue.h"
#include "utils.h"

struct queue {
  node_t* head;
};

queue_t* queue_init() {
  queue_t* self = malloc(sizeof(queue_t));
  self->head = NULL;
  return self;
}

node_t* queue_pop(queue_t* queue) {
  node_t* popped = queue->head;
  queue->head = queue->head->next;
  return popped;
}

const node_t* queue_top(const queue_t* queue) {
  return queue->head;
}

unsigned queue_size(const queue_t* queue) {
  const node_t* it = queue->head;
  while (it) {
    it++;
  }
  return it - queue->head;
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

void queue_remove_item(queue_t* queue, node_t* item) {

}
