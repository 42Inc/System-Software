#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include "memory.h"
static int heap_size =  0;
static int block_size = 0;

static void swap(int* a, int* b)
{
  int tmp = 0;
  tmp = *a;
  *a = *b;
  *b = tmp;
}
int main(int argc, char **argv) {
  heap_size = argc > 1 ? atoi(argv[1]) : 1000;
  block_size = argc > 2 ? atoi(argv[2]) : 120;
  int i = 0;
  int j = 0;
  void* ptr1;
  void* ptr2;
  void* ptr3;
  void* ptr4;
  void* ptr5;
  void* ptr6;
  void* ptr7;
  void* ptr8;
  void* ptr9;
  void* ptr10;
  char* ptr11;
  int* ptr12;

  ptr1 = malloc(15);
  ptr2 = malloc(87);
  free(ptr1);
  ptr3 = malloc(43);
  free(ptr2);
  ptr4 = malloc(100);
  ptr5 = malloc(10000);

  ptr11 = (char*)calloc(sizeof(char), 10);
  fprintf(stdout, "Calloc\n");
  fprintf(stderr, "/*----------------------------*/\n");
  for (i = 0; i < 10; ++i)
    printf("%d ", ptr11[i]);
  printf("\n");
  fprintf(stderr, "/*----------------------------*/\n");
  fprintf(stdout, "Malloc\n");
  ptr12 = (int*)malloc(sizeof(int) * 16);
  for (i = 0; i < 16; ++i){
    ptr12[i] = rand()%100;
    printf("%d ", ptr12[i]);
  }
  printf("\n");
  fprintf(stderr, "/*----------------------------*/\n");
  fprintf(stdout, "Sort\n");
  for (i = 0; i < 16; ++i) {
    for (j = 0; j < 16; ++j) {
      if (ptr12[i] < ptr12[j]) {
        swap(&ptr12[i], &ptr12[j]);
      }
    }
  }
  for (i = 0; i < 16; ++i){
    printf("%d ", ptr12[i]);
  }
  printf("\n");
  return EXIT_SUCCESS;
}
