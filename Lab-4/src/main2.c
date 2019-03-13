#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include "memory.h"
static int heap_size =  0;
static int block_size = 0;

int main(int argc, char **argv) {
  heap_size = argc > 1 ? atoi(argv[1]) : 1000;
  block_size = argc > 2 ? atoi(argv[2]) : 120;
  return EXIT_SUCCESS;
}
