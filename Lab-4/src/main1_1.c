#include "memory.h"
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  int blocks_count = argc > 1 ? atoi(argv[1]) : 1000;
  int block_size = argc > 2 ? atoi(argv[2]) : 120;
  int i = 0;
  fprintf(stderr, "/*----------------------------*/\n");
  fprintf(stderr, "Malloc stats: \n");
  malloc_stats();
  fprintf(stderr, "/*----------------------------*/\n");
  void **ptr = (void*)malloc(blocks_count*sizeof(void*));
  if (ptr == NULL) {
    fprintf(stderr, "%sFatal error%s: Malloc (%d)\n", RED, RESET,
            blocks_count);
    return EXIT_FAILURE;
  }
  for (i = 0; i < blocks_count; ++i) {
    ptr[i] = malloc(block_size);
    if (ptr[i] == NULL) {
      fprintf(stderr, "%sFatal error%s: Malloc (%d)\n", RED, RESET,
              block_size);
      return EXIT_FAILURE;
    }
  }
  fprintf(stderr, "/*----------------------------*/\n");
  fprintf(stdout, "In main : ptr = %p\n", ptr);
  fprintf(stderr, "/*----------------------------*/\n");
  fprintf(stderr, "Malloc stats: \n");
  malloc_stats();
  fprintf(stderr, "/*----------------------------*/\n");
  fprintf(stderr, "/*----------------------------*/\n");
  fprintf(stdout, "Address main : %p\n", main);
  fprintf(stderr, "/*----------------------------*/\n");

  for (i = 0; i < blocks_count; ++i) {
    free(ptr[i]);
  }
    free(ptr);
  return EXIT_SUCCESS;
}
