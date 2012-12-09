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

int main(int argc, char ** argv) {
  /* create a vector with an initial size of 1 */
  struct Vector * vector = vector_new(1);
  struct Order * order;

  /* append an order to the end of the array */
  order = order_new("foo", 1);
  vector_push(vector, order);

  /* get the 0'th element in the vector */
  order = vector_get(vector, 0);
  printf("%s costs $%i\n", order->title, order->cost);

  /* set the 0'th element in the vector to `order`, returns the element replaced */
  order->cost = 5;
  vector_set(vector, 0, order);

  /* get the last element and remove it */
  order = vector_pop(vector);
  printf("%s costs $%i\n", order->title, order->cost);

  /* free all of the data in the vector */
  while ( (order = vector_pop(vector)) ) {
    free(order);
  }

  /* free the vector storage and the vector pointer */
  vector_destroy(vector);
  return 0;
}

