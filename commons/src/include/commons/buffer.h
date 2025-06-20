#pragma once

#include <stddef.h>
#include <stdlib.h>

typedef struct {
  void *buffer;
  size_t data_size;
  size_t capacity;
  size_t head;
  size_t tail;
  size_t count;
} circular_buffer_t;

static inline int circular_buffer_init(circular_buffer_t *cb, size_t data_size, size_t capacity) {
  cb->buffer = malloc(data_size * capacity);
  if (!cb->buffer) {
    return 0; // Memory allocation failed
  }
  cb->data_size = data_size;
  cb->capacity = capacity;
  cb->head = 0;
  cb->tail = 0;
  cb->count = 0;
  return 1; // Success
}