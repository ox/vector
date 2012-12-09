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

## DOCUMENTATION

The `struct Vector` is defined as follows:

    struct Vector {
      int length; /* the number of elements that can be held until resize */
      int population; /* the number of elements held */
      void ** storage; /* the storage container for the elements */
    };

### struct Vector * vector\_new(size)

Create a new `Vector` which will start out with space for `size` pointers.

### void vector\_destroy(\* vector)

Free's the storage area of `vector` and it's pointer. You are responsible for `free`'ing all of the memory your objects allocated. If you do not, there will be a memory leak.

### void * vector\_get(\* vector, int index)

Retrieve the element at index `index` inside of `vector`. Returns a pointer to the element (vector only stores pointers), or NULL otherwise.

### void * vector\_set(\* vector, int index, void \* elem)

Sets the `index`'th element in `vector` to be `elem`. Returns the element that it replaced.

### void vector\_push(\* vector, void \* element)

Appends the pointer to `element` at the end of the array. If the population of the array reached max capacity, it will allocate more memory. If it cannot acquire any more memory, the program quits. Increments `vector->population`.

### void * vector_pop(\* vector)

Pop's off the last element added to `vector`, decrements `vector->population`.
