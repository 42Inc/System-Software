CC = gcc
CFLAGS = -g3 -O0 -Wall
LIB = -lm
INCLUDES = -I src/
DIRS = ./obj ./bin
MS_OBJ = ./obj/malloc_stats.o
HEAP_OBJ = ./obj/heap.o

all: bins

bins: $(DIRS) objs
	$(CC) $(MS_OBJ) $(CFLAGS) -o ./bin/ms_cmpl $(LIB)
	$(CC) $(HEAP_OBJ) $(CFLAGS) -o ./bin/heap_cmpl $(LIB)

$(DIRS):
	mkdir obj
	mkdir bin

objs: ./src/malloc_stats.c ./src/heap.c
	$(CC) -c ./src/malloc_stats.c -Wall -o $(MS_OBJ) $(INCLUDES)
	$(CC) -c ./src/heap.c -Wall -o $(HEAP_OBJ) $(INCLUDES)

.PHONY: clean exec
clean:
	rm -r -f bin/
	rm -r -f obj/

exec:
	make ; ./bin/cmpl
