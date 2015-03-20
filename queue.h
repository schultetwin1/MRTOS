#ifndef __MRTOS_QUEUE__
#define __MRTOS_QUEUE__

/**
 * In order to use this queue, define your own struct where the first member is a node_t
 */

typedef struct node node_t;
struct node {
  node_t* next;
};

typedef int (*node_cmp_fn_t)(node_t*, node_t*);
typedef struct queue queue_t;

queue_t*      queue_init();
node_t*       queue_pop(queue_t* queue);
const node_t* queue_top(const queue_t* queue);
unsigned      queue_size(const queue_t* queue);

void     queue_add(queue_t* queue, node_t* item, node_cmp_fn_t cmp);
void     queue_remove_item(queue_t* queue, node_t* item);

#endif
