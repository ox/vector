# Vector

Vector is a tiny library that implements a growing and shrinking array in C. It's fairly small and concise, and it offers just a handful of functions.

## EXAMPLE

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

## DOCUMENTATION

### struct Vector * vector_new(size, void (\*free_func)(void\*))

Create a new `Vector` which will start out with space for `size` pointers.

### void vector_destroy(\* vector)

Calls the `free_func` passed into `vector_new()` on every element in the vector. Then the vector `free`'s the pointer `vector`.

### int vector_push(\* vector, void \* element)

Appends the pointer to `element` at the end of the array. If the population of the array reached max capacity, it will allocate more memory. If it cannot acquire any more memory, the program quits.

### int vector_pop(\* vector)

Pop's off the last element added to `vector`.
