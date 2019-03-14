#include "memory.h"
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MYHEAP 1
#define DEBUG 1
#define HEAP_SIZE 1000
#define FREE 0
#define BUSY 1

static void *(*real_malloc)(size_t) = NULL;
static void *(*real_calloc)(size_t, size_t) = NULL;
static void *(*real_realloc)(void *, size_t) = NULL;
static void (*real_free)(void *) = NULL;
extern void *__libc_malloc(size_t);
extern void *__libc_calloc(size_t, size_t);
extern void *__libc_realloc(void *, size_t);
extern void __libc_free(void *);
void *malloc(size_t);
void *calloc(size_t, size_t);
void *realloc(void *, size_t);
void free(void *);
void _initialize_my_malloc(void);
void _initialize_my_calloc(void);
void _initialize_my_free(void);
void _initialize_my_realloc(void);

typedef struct memory_chunk {
  size_t size;
  int status;
  void* address;
  struct memory_chunk* next;
  struct memory_chunk* prev;
} chunk_t;

static void* heap = NULL;
static chunk_t* mem_chunk = NULL;

void print_heap() {
  #if DEBUG
  chunk_t *cursor = mem_chunk;
  int iterator = 0;
  while (cursor != NULL) {
    fprintf(stderr, "%sHeap[%d]%s - %p:%lu\t| %sStatus%s : %d\n", YELLOW, iterator++, RESET,
            cursor->address, cursor->size, YELLOW, RESET, cursor->status);
    cursor = cursor->next;
  }
  #endif
}
void check_heap() {
  #if DEBUG
  chunk_t *cursor = mem_chunk;
  chunk_t *tmpcursor = NULL;
  int iterator = 0;
  while (cursor != NULL) {
    if (cursor->next != NULL) {
      if (cursor->status == FREE && cursor->next->status == FREE) {
        tmpcursor = cursor->next;
        cursor->next = tmpcursor ->next;
        cursor->size = cursor->size + tmpcursor->size;
        real_free(tmpcursor);
      }
    }
    cursor = cursor->next;
  }
  #endif
}

void heap_init() {
  heap = __libc_malloc(HEAP_SIZE);
  mem_chunk = (chunk_t*)__libc_malloc(sizeof(chunk_t));
  mem_chunk->size = HEAP_SIZE;
  mem_chunk->address = heap;
  mem_chunk->next = NULL;
  mem_chunk->prev = NULL;
  mem_chunk->status = FREE;
  fprintf(stderr, "%sInit heap complete%s\n", GREEN, RESET);
  fprintf(stderr, "%sHeap addr%s : %p\n", YELLOW, RESET, heap);
  print_heap(
  );
}

void *malloc(size_t size) {
  void *ptr = NULL;
  chunk_t *cursor = NULL;
  chunk_t *new_heap_node = NULL;
  if (real_malloc == NULL) {
    _initialize_my_malloc();
  }
  #if !MYHEAP
  ptr = real_malloc(size);
  #else
  cursor = mem_chunk;
  while (cursor != NULL) {
    if (cursor->status == FREE && cursor->size >= size) {
      new_heap_node = (chunk_t*)real_malloc(sizeof(chunk_t));
      new_heap_node->size = cursor->size - size;
      new_heap_node->address = heap + size;
      new_heap_node->next = cursor->next;
      new_heap_node->prev = cursor;
      new_heap_node->status = FREE;

      cursor->size = size;
      cursor->next = new_heap_node;
      cursor->status = BUSY;
      ptr = cursor->address;
      break;
    }
    cursor = cursor->next;
  }
  #endif
  print_heap();
  fprintf(stderr, "%sMalloc hook%s - %p:%lu\t| %sCaller%s : %p\n", YELLOW, RESET,
          ptr, size, YELLOW, RESET, __builtin_return_address(0));
  return ptr;
}

void *realloc(void *ptr, size_t size) {
  void *new_ptr = NULL;
  if (real_realloc == NULL) {
    _initialize_my_realloc();
  }
  #if !MYHEAP
  new_ptr = real_realloc(ptr, size);
  #else
  new_ptr = malloc(size);
  free(ptr);
  #endif
  fprintf(stderr, "%sRealloc hook%s - %p -> %p:%lu\t| %sCaller%s : %p\n", YELLOW, RESET, ptr,
          new_ptr, size, YELLOW, RESET, __builtin_return_address(0));
  return new_ptr;
}

void *calloc(size_t blocks_count, size_t block_size) {
  void *ptr = NULL;
  if (real_calloc == NULL) {
    _initialize_my_calloc();
  }

  #if !MYHEAP
  ptr = real_calloc(blocks_count, block_size);
  #else
  ptr = malloc(blocks_count * block_size);
  memset(ptr, 0, blocks_count * block_size);
  #endif
  fprintf(stderr, "%sCalloc hook%s - %p:%lu x %lu\t| %sCaller%s : %p\n", YELLOW, RESET, ptr,
          blocks_count, block_size, YELLOW, RESET, __builtin_return_address(0));
  return ptr;
}

void free(void *ptr) {
  chunk_t *cursor = NULL;
  int _change = 0;
  if (real_free == NULL) {
    _initialize_my_free();
  }

  #if !MYHEAP
  real_free(ptr);
  #else
  cursor = mem_chunk;
  while (cursor != NULL) {
    if (ptr == cursor->address) {
      if (cursor->prev != NULL && cursor->prev->status == FREE) {
        cursor->prev->next = cursor->next;
        cursor->prev->size = cursor->prev->size + cursor->size;
        cursor->next->prev = cursor->prev;
        real_free(cursor);
        _change = 1;
        break;
      } else if (cursor->next != NULL && cursor->next->status == FREE) {
        cursor->prev->next = cursor->next;
        cursor->next->prev = cursor->prev;
        cursor->next->size = cursor->next->size + cursor->size;
        real_free(cursor);
        _change = 1;
        break;
      } else {
        cursor->status = FREE;
        _change = 1;
        break;
      }
    }
    cursor = cursor->next;
  }
  #endif
  check_heap();
  print_heap();
  fprintf(stderr, "%sFree hook%s - %p\t| %sCaller%s : %p\n", YELLOW, RESET, ptr, YELLOW, RESET, __builtin_return_address(0));
  if (_change) {
    fprintf(stderr, "%sFree hook%s - %p\t| %sDouble free!%s\n", YELLOW, RESET, ptr, RED, RESET);
  }
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
  if (heap == NULL)
    heap_init();
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
  if (heap == NULL)
    heap_init();
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
  if (heap == NULL)
    heap_init();
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
