#include "memory.h"
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  int iterator_max = argc > 1 ? atoi(argv[1]) : 2;
  int block_size = argc > 2 ? atoi(argv[2]) : 1024;
  int i = 0;
  malloc_stats();

  void **ptr = (void*)malloc(iterator_max*sizeof(void*));
  for (i = 1; i <= iterator_max; ++i) {
    fprintf(stderr, "/*----------------------------*/\n");
    fprintf(stderr, "Malloc\n");
    ptr[i - 1] = malloc(i * block_size);
    if (ptr == NULL) {
      fprintf(stderr, "%sFatal error%s: Malloc (%d:%d)\n", RED, RESET, i,
              block_size);
      return EXIT_FAILURE;
    }

    fprintf(stderr, "/*----------------------------*/\n");
    fprintf(stdout, "In main : ptr = %p; iterator = %d\n", ptr, i);
    fprintf(stderr, "/*----------------------------*/\n");
    fprintf(stderr, "Malloc stats: \n");
    fprintf(stderr, "/*----------------------------*/\n");
  }
  malloc_stats();
  for (i = 1; i <= iterator_max; ++i) {
    free(ptr[i - 1]);
  }
  free(ptr);
  fprintf(stderr, "/*----------------------------*/\n");
  fprintf(stdout, "Address main : %p\n", main);
  fprintf(stderr, "/*----------------------------*/\n");
  return EXIT_SUCCESS;
}
