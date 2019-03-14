#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include "memory.h"
static int heap_size =  0;
static int block_size = 0;

int main(int argc, char **argv) {
  heap_size = argc > 1 ? atoi(argv[1]) : 1000;
  block_size = argc > 2 ? atoi(argv[2]) : 120;
  void* ptr1 = malloc(15);
  void* ptr2 = malloc(87);
  free(ptr1);
  void* ptr3 = malloc(23);
  free(ptr2);
  void* ptr4 = malloc(100);
  void* ptr5 = malloc(1000);
  return EXIT_SUCCESS;
}
