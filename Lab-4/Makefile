CC = gcc
QUIET = @
CFLAGS = -g3 -O0 -Wall
OFLAGS = -c -Wall
LIB = -lm

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
DIRS = $(BIN_DIR) $(OBJ_DIR)
INCLUDES = -I $(SRC_DIR)
MS_OBJ = $(OBJ_DIR)/malloc_stats.o
HEAP_OBJ = $(OBJ_DIR)/heap.o

.PHONY: all bins objs clean
all: bins

bins: $(DIRS) objs
	$(CC) $(MS_OBJ) $(CFLAGS) -o $(BIN_DIR)/ms_cmpl $(LIB)
	$(CC) $(HEAP_OBJ) $(CFLAGS) -o $(BIN_DIR)/heap_cmpl $(LIB)

$(DIRS):
		mkdir $(OBJ_DIR)
		mkdir $(BIN_DIR)

objs:
	$(CC) $(OFLAGS) $(SRC_DIR)/malloc_stats.c -o $(MS_OBJ) $(INCLUDES)
	$(CC) $(OFLAGS) $(SRC_DIR)/heap.c -o $(HEAP_OBJ) $(INCLUDES)

clean:
	$(QUIET)rm -rfv $(BIN_DIR)/
	$(QUIET)rm -rfv $(OBJ_DIR)/
