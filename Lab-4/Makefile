CC = gcc
QUIET = @
CFLAGS = -g3 -O0 -Wall
OFLAGS = -c -Wall

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
DIRS = $(BIN_DIR) $(OBJ_DIR)
INCLUDES = -I $(SRC_DIR)
MS_OBJ = $(OBJ_DIR)/malloc_stats.o

.PHONY: all bins objs clean
all: bins


bins: $(DIRS) lib objs
	$(CC) $(MS_OBJ) $(CFLAGS) -o $(BIN_DIR)/ms_cmpl $(LIB)
	$(CC)  $(SRC_DIR)/main1_1.c -o $(BIN_DIR)/main1_1 $(LIB) $(CFLAGS) -ldl -fPIC
	$(CC)  $(SRC_DIR)/main1_2.c -o $(BIN_DIR)/main1_2 $(LIB) $(CFLAGS) -ldl -fPIC
	$(CC)  $(SRC_DIR)/main2.c -o $(BIN_DIR)/main2 $(LIB) $(CFLAGS) -ldl -fPIC

lib:
	gcc -shared -fPIC -ldl -lpthread $(SRC_DIR)/memory.c -o $(BIN_DIR)/libmemory.so

manualrun:
	LD_PRELOAD=$(PWD)/$(BIN_DIR)/libmemory.so ENV_MEMHOOK_HEAP_SIZE=$(size) ENV_MEMHOOK_USE_HEAP=$(heap) ENV_MEMHOOK_USE_HEAP_BLOCKS_MANAGMENT=$(blocks) ENV_MEMHOOK_BLOCK_HEAP_MAXIMUM=$(max) ENV_MEMHOOK_BLOCK_HEAP_MINIMUM=$(min) ENV_MEMHOOK_DEBUG=$(debug) $(target)

trace:
	LD_PRELOAD=$(PWD)/$(BIN_DIR)/libmemory.so strace $(target)

debug:
	gdb -c core --args $(target)

run:
	LD_PRELOAD=$(PWD)/$(BIN_DIR)/libmemory.so $(BIN_DIR)/main1_1
	LD_PRELOAD=$(PWD)/$(BIN_DIR)/libmemory.so $(BIN_DIR)/main1_2

$(DIRS):
		mkdir $(OBJ_DIR)
		mkdir $(BIN_DIR)

objs:
	$(CC) $(OFLAGS) $(SRC_DIR)/malloc_stats.c -o $(MS_OBJ) $(INCLUDES)

clean:
	$(QUIET)rm -rfv $(BIN_DIR)/
	$(QUIET)rm -rfv $(OBJ_DIR)/
