#ifndef _VECTOR_H
#define _VECTOR_H

struct Vector {
  int length;
  int population;
  void (*free_element)(void*);
  void ** storage;
};

struct Vector * vector_new(int size, void (*free_element)(void*));
void vector_destroy(struct Vector * vector);

int vector_push(struct Vector * vector, void * elem);
void * vector_pop(struct Vector * vector);

void vector_resize(struct Vector * vector);

#endif
