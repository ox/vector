#ifndef _VECTOR_H
#define _VECTOR_H

struct Vector {
  int length;
  int population;
  void ** storage;
};

struct Vector * vector_new(int size);
void vector_destroy(struct Vector * vector);

void * vector_get(struct Vector * vector, int index);
void * vector_set(struct Vector * vector, int index, void * elem);
void   vector_push(struct Vector * vector, void * elem);
void * vector_pop(struct Vector * vector);

void vector_resize(struct Vector * vector);

#endif
