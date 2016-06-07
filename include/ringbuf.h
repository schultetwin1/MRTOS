#pragma once

typedef struct ringbuf ringbuf_t;

struct ringbuf{
  void*  buffer;
  size_t blockSize;
  size_t bufferSize;
};

void  ringbuf_init(ringbuf_t* self, void* buffer, size_t bufferSize, size_t blocksize);
void* ringbuf_insert(ringbuf_t* self, void* item);
void* ringbuf_delete(ringbuf_t* self);
