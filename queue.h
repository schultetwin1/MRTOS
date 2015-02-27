#ifndef __MRTOS_QUEUE__
#define __MRTOS_QUEUE__

/**
 * In order to use this queue, define your own struct where the first member is a node_t
 */

typedef struct node node_t;

struct node {
  node_t* next;
};

static inline node_t* queue_init();
static inline int     queue_empty(const node_t* queue);
node_t*        queue_pop(node_t** queue_ptr);
static inline  const node_t* queue_top(const node_t* queue);
unsigned       queue_size(const node_t* queue);

void           queue_add(node_t** queue_ptr, node_t* item, int (*cmp)(node_t*, node_t*));
void           queue_remove_item(node_t* item);
void           queue_search_item(node_t* item);

node_t* queue_init() {
  return 0;
}

int queue_empty(const node_t* queue) {
  return !queue;
}

const node_t* queue_top(const node_t* queue) {
  return queue;
}

#endif
