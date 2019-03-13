#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include "memory.h"

int main(int argc, char **argv) {
  int blocks_count = argc > 1 ? atoi(argv[1]) : 1000;
  int block_size = argc > 2 ? atoi(argv[2]) : 120;
  void *ptr = malloc(blocks_count * block_size);
  if (ptr == NULL) {
    fprintf(stderr, "%sFatal error%s: Malloc (%d:%d)\n", RED, RESET, blocks_count, block_size);
    return EXIT_FAILURE;
  }

  fprintf(stderr, "/*----------------------------*/\n");
  fprintf(stdout, "In main : ptr = %p\n", ptr);
  fprintf(stderr, "/*----------------------------*/\n");
  fprintf(stderr, "Malloc stats: \n");
  malloc_stats();
  fprintf(stderr, "/*----------------------------*/\n");
  free(ptr);
  fprintf(stderr, "/*----------------------------*/\n");
  fprintf(stdout, "Address main : %p\n", main);
  fprintf(stderr, "/*----------------------------*/\n");
  return EXIT_SUCCESS;
}
