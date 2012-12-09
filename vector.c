#include <stdlib.h>
#include <stdio.h>
#include "vector.h"

struct Vector * vector_new(int size, void (*free_element)(void*)) {
  struct Vector * vector = malloc(sizeof(struct Vector));

  vector->length = size;
  vector->population = 0;
  vector->free_element = free_element;
  vector->storage = calloc(size, sizeof(void *));

  return vector;
}

void vector_destroy(struct Vector * vector) {
  int i = 0;
  for (; i < vector->length; i++) {
    vector->free_element(vector->storage[i]);
  }
  free(vector->storage);
  free(vector);
}

int vector_push(struct Vector * vector, void * elem) {
  vector->storage[vector->population++] = elem;
  vector_resize(vector);
  return 0;
}

void * vector_pop(struct Vector * vector) {
  void * elem = vector->storage[--vector->population];
  vector_resize(vector);
  return elem;
}

void vector_resize(struct Vector * vector) {
  void * new_storage;
  int new_length;

  if (vector->population == vector->length) {
    new_length = vector->length * 2;
    new_storage = realloc(vector->storage, sizeof(void *) * vector->length * 2);
  } else if ((float)vector->population/(float)vector->length < 0.25) {
    new_length = vector->length / 2;
    new_storage = realloc(vector->storage, sizeof(void *) * vector->length / 2);
  } else {
    return;
  }

  if (new_storage == NULL) {
    vector_destroy(vector);
    fprintf(stderr, "could not allocate more memory for vector. Sorry\n");
    exit (1);
  }

  vector->storage = new_storage;
  vector->length = new_length;
}
