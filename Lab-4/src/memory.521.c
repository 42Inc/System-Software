#include "memory.521.h"
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>

static void *(*real_malloc)(size_t) = NULL;
static void *(*real_calloc)(size_t, size_t) = NULL;
static void *(*real_realloc)(void *, size_t) = NULL;
static void (*real_free)(void *) = NULL;
extern void *__libc_malloc(size_t);
extern void *__libc_calloc(size_t, size_t);
extern void *__libc_realloc(void *, size_t);
extern void __libc_free(void *);
void _initialize_my_malloc(void);
void _initialize_my_calloc(void);
void _initialize_my_free(void);
void _initialize_my_realloc(void);

void *malloc(size_t size) {
  if (real_malloc == NULL) {
    _initialize_my_malloc();
  }

  void *ptr = NULL;
  ptr = real_malloc(size);
  fprintf(stderr, "%sMalloc hook%s - %p:%lu\t| %sCaller%s : %p\n", YELLOW, RESET,
          ptr, size, YELLOW, RESET, __builtin_return_address(0));
  return ptr;
}

void *realloc(void *ptr, size_t size) {
  if (real_realloc == NULL) {
    _initialize_my_realloc();
  }

  void *new_ptr = NULL;
  new_ptr = real_realloc(ptr, size);
  fprintf(stderr, "%sRealloc hook%s - %p -> %p:%lu\t| %sCaller%s : %p\n", YELLOW, RESET, ptr,
          new_ptr, size, YELLOW, RESET, __builtin_return_address(0));
  return new_ptr;
}

void *calloc(size_t blocks_count, size_t block_size) {
  if (real_calloc == NULL) {
    _initialize_my_calloc();
  }

  void *ptr = NULL;
  ptr = real_calloc(blocks_count, block_size);
  fprintf(stderr, "%sCalloc hook%s - %p:%lu x %lu\t| %sCaller%s : %p\n", YELLOW, RESET, ptr,
          blocks_count, block_size, YELLOW, RESET, __builtin_return_address(0));
  return ptr;
}

void free(void *ptr) {
  if (real_free == NULL) {
    _initialize_my_free();
  }

  if (ptr == NULL) {
    fprintf(stderr, "%sFatal error%s: Double free or ptr is NULL\n", RED, RESET);
    abort();
  }

  fprintf(stderr, "%sFree hook%s - %p\t| %sCaller%s : %p\n", YELLOW, RESET, ptr, YELLOW, RESET, __builtin_return_address(0));
  real_free(ptr);
}

void _initialize_my_free(void) {
  fprintf(stderr, "/*----------------------------*/\n");
  fprintf(stderr, "%sStart Init free hook%s\n", CYAN, RESET);
  if (real_free != NULL)
    return;
  real_free = __libc_free;
  if (real_free == NULL) {
    fprintf(stderr, "%sFatal error%s: Init free hook\n", RED, RESET);
    abort();
  }
  fprintf(stderr, "%sInit free hook complete%s\n", GREEN, RESET);
  fprintf(stderr, "Real free addr : %p\n", real_free);
  fprintf(stderr, "My free addr   : %p\n", free);
  fprintf(stderr, "/*----------------------------*/\n");
}

void _initialize_my_realloc(void) {
  fprintf(stderr, "/*----------------------------*/\n");
  fprintf(stderr, "%sStart Init realloc hook%s\n", CYAN, RESET);
  if (real_realloc != NULL)
    return;
  real_realloc = __libc_realloc;
  if (real_realloc == NULL) {
    fprintf(stderr, "%sFatal error%s: Init realloc hook\n", RED, RESET);
    abort();
  }
  fprintf(stderr, "%sInit realloc hook complete%s\n", GREEN, RESET);
  fprintf(stderr, "Real realloc addr : %p\n", real_realloc);
  fprintf(stderr, "My realloc addr   : %p\n", realloc);
  fprintf(stderr, "/*----------------------------*/\n");
}

void _initialize_my_malloc(void) {
  fprintf(stderr, "/*----------------------------*/\n");
  fprintf(stderr, "%sStart Init malloc hook%s\n", CYAN, RESET);
  if (real_malloc != NULL)
    return;
  real_malloc = __libc_malloc;
  if (real_malloc == NULL) {
    fprintf(stderr, "%sFatal error%s: Init malloc hook\n", RED, RESET);
    abort();
  }
  fprintf(stderr, "%sInit malloc hook complete%s\n", GREEN, RESET);
  fprintf(stderr, "Real malloc addr : %p\n", real_malloc);
  fprintf(stderr, "My malloc addr   : %p\n", malloc);
  fprintf(stderr, "/*----------------------------*/\n");
}

void _initialize_my_calloc(void) {
  fprintf(stderr, "/*----------------------------*/\n");
  fprintf(stderr, "%sStart Init calloc hook%s\n", CYAN, RESET);
  if (real_calloc != NULL)
    return;
  real_calloc = __libc_calloc;
  if (real_calloc == NULL) {
    fprintf(stderr, "%sFatal error%s: Init caloc hook\n", RED, RESET);
    abort();
  }
  fprintf(stderr, "%sInit calloc hook complete%s\n", GREEN, RESET);
  fprintf(stderr, "Real calloc addr : %p\n", real_calloc);
  fprintf(stderr, "My calloc addr   : %p\n", calloc);
  fprintf(stderr, "/*----------------------------*/\n");
}
