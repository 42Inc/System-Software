#include "memory.h"
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FREE 0
#define BUSY 1
#define MIN 1998
#define MAX 1998

static int heap_use = 1;
static size_t debug = 1;

static size_t realloc_use = 0;
static size_t calloc_use = 0;
static size_t malloc_use = 0;
static size_t free_use = 0;

static const size_t HEAP_SIZE = 10000000;
static size_t _heap_size = 0;
static int heap_blocks_managment = 0;
static size_t heap_minimum = MIN;
static size_t heap_maximum = MAX;

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
void __initialize_my_malloc(void);
void __initialize_my_calloc(void);
void __initialize_my_free(void);
void __initialize_my_realloc(void);

typedef struct memory_chunk {
  size_t size;
  int status;
  void *address;
  struct memory_chunk *next;
  struct memory_chunk *prev;
} chunk_t;

static void *heap = NULL;
static chunk_t *mem_chunk = NULL;

void _print_heap() {
  chunk_t *cursor = mem_chunk;
  size_t iterator = 0;
  size_t __heap_size = 0;
  while (cursor != NULL) {
    if (debug) {
      fprintf(stderr,
              "%sHeap[%lu]%s - %p:%lu\t| %sStatus%s : %d | %sp%s|%sc%s|%sn%s = "
              "%s%p%s|%s%p%s|%s%p%s\n",
              YELLOW, iterator++, RESET, cursor->address, cursor->size, YELLOW,
              RESET, cursor->status, RED, RESET, BLUE, RESET, GREEN, RESET, RED,
              cursor->prev, RESET, BLUE, cursor, RESET, GREEN, cursor->next,
              RESET);
    }
    if (cursor->status == BUSY)
      __heap_size = __heap_size + cursor->size;
    cursor = cursor->next;
  }
  fprintf(stderr, "%sHeap size%s : %s%luB%s\n", YELLOW, RESET, GREEN,
          __heap_size, RESET);
  if (debug) {
    fprintf(stderr,
            "%sHeap address range%s : %s%p%s:%s%p%s|%s%luB%s|[%lu:%lu]\n",
            YELLOW, RESET, GREEN, heap, RESET, RED, heap + _heap_size, RESET,
            CYAN, _heap_size, RESET, heap_minimum, heap_maximum);
  }
}
void _check_heap() {
  chunk_t *cursor = mem_chunk;
  chunk_t *tmpcursor = NULL;
  int iterator = 0;
  while (cursor != NULL) {
    if (cursor->next != NULL) {
      if (cursor->status == FREE && cursor->next->status == FREE) {
        tmpcursor = cursor->next;
        cursor->next = tmpcursor->next;
        cursor->size = cursor->size + tmpcursor->size;
        real_free(tmpcursor);
      }
    }
    cursor = cursor->next;
  }
}

void _heap_init() {
  heap = __libc_malloc(HEAP_SIZE);
  mem_chunk = (chunk_t *)__libc_malloc(sizeof(chunk_t));
  char *_local_size = getenv("ENV_MEMHOOK_HEAP_SIZE");
  char *_local_use_heap = getenv("ENV_MEMHOOK_USE_HEAP");
  char *_local_heap_blocks_managment =
      getenv("ENV_MEMHOOK_USE_HEAP_BLOCKS_MANAGMENT");
  char *_local_heap_maximum = getenv("ENV_MEMHOOK_BLOCK_HEAP_MAXIMUM");
  char *_local_heap_minimum = getenv("ENV_MEMHOOK_BLOCK_HEAP_MINIMUM");
  char *_local_heap_debug = getenv("ENV_MEMHOOK_DEBUG");
  if (_local_use_heap == NULL || strlen(_local_use_heap) < 1) {
    heap_use = 0;
  } else {
    if (!strcmp("true", _local_use_heap)) {
      heap_use = 1;
    } else {
      heap_use = 0;
    }
  }
  if (heap_use) {
    if (_local_heap_blocks_managment == NULL ||
        strlen(_local_heap_blocks_managment) < 1) {
      heap_blocks_managment = 0;
    } else {
      if (!strcmp("true", _local_heap_blocks_managment)) {
        heap_blocks_managment = 1;
      } else {
        heap_blocks_managment = 0;
      }
    }
    if (_local_heap_debug == NULL || strlen(_local_heap_debug) < 1) {
      debug = 0;
    } else {
      if (!strcmp("true", _local_heap_debug)) {
        debug = 1;
      } else {
        debug = 0;
      }
    }
    if (_local_size == NULL || strlen(_local_size) < 1) {
      _heap_size = HEAP_SIZE;
    } else {
      _heap_size = atol(_local_size);
      if (_heap_size == 0) {
        _heap_size = HEAP_SIZE;
      }
    }
    if (heap_blocks_managment) {
      if (_local_heap_maximum == NULL || strlen(_local_heap_maximum) < 1) {
        heap_maximum = MAX;
      } else {
        heap_maximum = atol(_local_heap_maximum);
        if (heap_maximum == 0) {
          heap_maximum = HEAP_SIZE;
        }
      }
      if (_local_heap_minimum == NULL || strlen(_local_heap_minimum) < 1) {
        heap_minimum = MIN;
      } else {
        heap_minimum = atol(_local_heap_minimum);
        if (heap_minimum == 0) {
          heap_minimum = HEAP_SIZE;
        }
      }
      if (heap_minimum > heap_maximum) {
        size_t tmp = heap_maximum;
        heap_maximum = heap_minimum;
        heap_minimum = tmp;
      }
    }
  }

  if (mem_chunk == NULL) {
    fprintf(stderr, "%sFatal error%s: Init heap\n", RED, RESET);
    abort();
  }
  mem_chunk->size = _heap_size;
  mem_chunk->address = heap;
  mem_chunk->next = NULL;
  mem_chunk->prev = NULL;
  mem_chunk->status = FREE;
  fprintf(stderr, "%sInit heap complete%s\n", GREEN, RESET);
  fprintf(stderr, "%sHeap address range%s : %s%p%s:%s%p%s|%s%luB%s|[%lu:%lu]\n",
          YELLOW, RESET, GREEN, heap, RESET, RED, heap + _heap_size, RESET,
          CYAN, _heap_size, RESET, heap_minimum, heap_maximum);
  _print_heap();
}

void *malloc(size_t size) {
  void *ptr = NULL;
  chunk_t *cursor = NULL;
  chunk_t *new_heap_node = NULL;
  if (real_malloc == NULL) {
    __initialize_my_malloc();
  }
  if (heap_blocks_managment) {
    if (size > heap_maximum || size < heap_minimum) {
      fprintf(stderr, "%sFatal error%s: Wrong malloc size %lu [%lu, %lu]\n",
              RED, RESET, size, heap_minimum, heap_maximum);
      return NULL;
    }
  }
  if (!heap_use) {
    ptr = real_malloc(size);
  } else {
    cursor = mem_chunk;
    while (cursor != NULL) {
      if (cursor->status == FREE && cursor->size >= size) {
        new_heap_node = (chunk_t *)real_malloc(sizeof(chunk_t));
        new_heap_node->size = cursor->size - size;
        new_heap_node->address = cursor->address + size;
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
    _print_heap();
  }
  fprintf(stderr, "%sMalloc hook[%lu]%s - %p:%lu\t| %sCaller%s : %p\n", YELLOW,
          malloc_use++, RESET, ptr, size, YELLOW, RESET,
          __builtin_return_address(0));
  return ptr;
}

void *realloc(void *ptr, size_t size) {
  void *new_ptr = NULL;
  if (real_realloc == NULL) {
    __initialize_my_realloc();
  }
  if (!heap_use) {
    new_ptr = real_realloc(ptr, size);
  } else {
    new_ptr = malloc(size);
    if (new_ptr != NULL && ptr != NULL) {
      memcpy(new_ptr, ptr, size);
      free(ptr);
    }
  }
  fprintf(stderr, "%sRealloc hook[%lu]%s - %p -> %p:%lu\t| %sCaller%s : %p\n",
          YELLOW, realloc_use++, RESET, ptr, new_ptr, size, YELLOW, RESET,
          __builtin_return_address(0));
  return new_ptr;
}

void *calloc(size_t blocks_count, size_t block_size) {
  void *ptr = NULL;
  if (real_calloc == NULL) {
    __initialize_my_calloc();
  }

  if (!heap_use) {
    ptr = real_calloc(blocks_count, block_size);
  } else {
    ptr = malloc(blocks_count * block_size);
    memset(ptr, 0, blocks_count * block_size);
    //    print_heap();
  }
  fprintf(stderr, "%sCalloc hook[%lu]%s - %p:%lu x %lu\t| %sCaller%s : %p\n",
          YELLOW, calloc_use++, RESET, ptr, blocks_count, block_size, YELLOW,
          RESET, __builtin_return_address(0));
  return ptr;
}

void free(void *ptr) {

  chunk_t *cursor = NULL;
  int _change = 0;
  size_t _size = 0;
  if (real_free == NULL) {
    __initialize_my_free();
  }

  if (!heap_use) {
    real_free(ptr);
  } else {
    cursor = mem_chunk;
    while (cursor != NULL) {
      if (ptr == cursor->address) {
        cursor->status = FREE;
        _size = cursor->size;
        _change = 1;
        break;
      }
      cursor = cursor->next;
    }
    _check_heap();
    _print_heap();
    if (!_change) {
      fprintf(stderr, "%sFree hook%s - %p\t| %sDouble free!%s\n", YELLOW, RESET,
              ptr, RED, RESET);
    }
  }
  fprintf(stderr, "%sFree hook[%lu]%s - %p:%lu\t| %sCaller%s : %p\n", YELLOW,
          free_use++, RESET, ptr, _size, YELLOW, RESET,
          __builtin_return_address(0));
}

void __initialize_my_free(void) {
  fprintf(stderr, "/*----------------------------*/\n");
  fprintf(stderr, "%sStart Init free hook%s\n", CYAN, RESET);
  if (heap == NULL)
    _heap_init();
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

void __initialize_my_realloc(void) {
  fprintf(stderr, "/*----------------------------*/\n");
  fprintf(stderr, "%sStart Init realloc hook%s\n", CYAN, RESET);
  if (heap == NULL)
    _heap_init();
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

void __initialize_my_malloc(void) {
  fprintf(stderr, "/*----------------------------*/\n");
  fprintf(stderr, "%sStart Init malloc hook%s\n", CYAN, RESET);
  if (heap == NULL)
    _heap_init();
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

void __initialize_my_calloc(void) {
  fprintf(stderr, "/*----------------------------*/\n");
  fprintf(stderr, "%sStart Init calloc hook%s\n", CYAN, RESET);
  if (heap == NULL)
    _heap_init();
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
