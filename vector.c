#include <stdlib.h>
#include <stdio.h>
#include "vector.h"

struct Vector * vector_new(int size) {
  struct Vector * vector = malloc(sizeof(struct Vector));

  vector->length = size;
  vector->population = 0;
  vector->storage = calloc(size, sizeof(void *));

  return vector;
}

void vector_destroy(struct Vector * vector) {
  free(vector->storage);
  free(vector);
}

void * vector_get(struct Vector * vector, int index) {
  if (index >= vector->population || index < 0) {
    return NULL;
  }

  return vector->storage[index];
}

void * vector_set(struct Vector * vector, int index, void * elem) {
  void * old_elem = NULL;
  if (index < vector->population && index >= 0) {
    old_elem = vector->storage[index];
    vector->storage[index] = elem;
  }

  return old_elem;
}

void vector_push(struct Vector * vector, void * elem) {
  vector->storage[vector->population++] = elem;
  vector_resize(vector);
}

void * vector_pop(struct Vector * vector) {
  if (vector->population == 0) {
    return NULL;
  }

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

  /* not sure if this is morally correct. On one hand, the system has no more
     memory to give. On the other, such a trivial error should not bring down
     the program. Comments? */
  if (new_storage == NULL) {
    vector_destroy(vector);
    fprintf(stderr, "could not allocate more memory for vector. Sorry\n");
    exit (1);
  }

  vector->storage = new_storage;
  vector->length = new_length;
}
