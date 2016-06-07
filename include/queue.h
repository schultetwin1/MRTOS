#ifndef __MRTOS_QUEUE__
#define __MRTOS_QUEUE__

/**
 * In order to use this queue, define your own struct where the first member is a node_t
 */

typedef struct node node_t;
struct node {
  node_t* next;
  node_t* prev;
};

typedef node_t queue_t;

void          queue_init(queue_t* q);
node_t*       queue_pop(queue_t* q);
void          queue_push(queue_t* q, node_t* pushed);
const node_t* queue_top(const queue_t* q);
unsigned      queue_size(const queue_t* q);

#endif
