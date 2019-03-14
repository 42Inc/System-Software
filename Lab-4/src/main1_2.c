#include "memory.h"
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  int iterator_max = argc > 1 ? atoi(argv[1]) : 2;
  int block_size = argc > 2 ? atoi(argv[2]) : 1024;
  int i = 0;
  for (i = 1; i <= iterator_max; ++i) {
    fprintf(stderr, "/*----------------------------*/\n");
    fprintf(stderr, "Malloc\n");
    void *ptr = malloc(i * block_size);
    if (ptr == NULL) {
      fprintf(stderr, "%sFatal error%s: Malloc (%d:%d)\n", RED, RESET, i,
              block_size);
      return EXIT_FAILURE;
    }

    fprintf(stderr, "/*----------------------------*/\n");
    fprintf(stdout, "In main : ptr = %p; iterator = %d\n", ptr, i);
    fprintf(stderr, "/*----------------------------*/\n");
    fprintf(stderr, "Malloc stats: \n");
    malloc_stats();
    fprintf(stderr, "/*----------------------------*/\n");
    free(ptr);
  }
  fprintf(stderr, "/*----------------------------*/\n");
  fprintf(stdout, "Address main : %p\n", main);
  fprintf(stderr, "/*----------------------------*/\n");
  return EXIT_SUCCESS;
}
