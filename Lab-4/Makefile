CC = gcc
CFLAGS = -g3 -O0 -Wall
LIB = -lm
INCLUDES = -I src/
ms_obj = ./obj/malloc_stats.o
heap_obj = ./obj/heap.o

all: bins

bins: dirs objs
	$(CC) $(ms_obj) $(CFLAGS) -o ./bin/ms_cmpl $(LIB)
	$(CC) $(heap_obj) $(CFLAGS) -o ./bin/heap_cmpl $(LIB)

dirs:
	mkdir obj
	mkdir bin

objs: ./src/malloc_stats.c ./src/heap.c
	$(CC) -c ./src/malloc_stats.c -Wall -o $(ms_obj) $(INCLUDES)
	$(CC) -c ./src/heap.c -Wall -o $(heap_obj) $(INCLUDES)

.PHONY: clean exec
clean:
	rm -r -f bin/
	rm -r -f obj/

exec:
	make ; ./bin/cmpl
