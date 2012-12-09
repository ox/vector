#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vector.h"

struct Order {
  char * title;
  int cost;
};

struct Order * order_new(char * title, int cost) {
  struct Order * order = malloc(sizeof(struct Order));

  order->title = title;
  order->cost = cost;

  return order;
}

void order_free(void * a) {
  struct Order * order = (struct Order *)a;
  free(order);
}

int main(int argc, char ** argv) {
  struct Vector * vector = vector_new(1, order_free);
  struct Order * order;

  order = order_new("foo", 1);
  vector_push(vector, order);

  order = vector_pop(vector);
  printf("%s costs $%i\n", order->title, order->cost);

  vector_destroy(vector);
  return 0;
}
