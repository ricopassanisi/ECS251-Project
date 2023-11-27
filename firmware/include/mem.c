#include <stdlib.h>

extern char _heap_base[];
extern char _stack[];

char *_sbrk(int incr) {
  static char *heap_end;
  char *prev_heap_end;
 
  if (heap_end == 0) {
    heap_end = (char *)&_heap_base;
  }
  prev_heap_end = heap_end;
  if (heap_end + incr > _stack) {
    write (1, "Heap and stack collision\n", 25);
    abort ();
  }

  heap_end += incr;
  return prev_heap_end;
}