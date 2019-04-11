CC = gcc
LD = LD_PRELOAD
QUIET = @
CFLAGS = -g3 -O0 -Wall -rdynamic -ldl -fPIC
OFLAGS = -c -Wall

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
LIB_DIR = $(PWD)/mylib.so
DIRS = $(BIN_DIR) $(OBJ_DIR)
INCLUDES = -I $(SRC_DIR)

.PHONY: all run bins objs clean
all: bins
run:
	$(LD)=$(LIB_DIR) $(BIN_DIR)/cmpl

bins: $(DIRS) objs
	$(CC) $(SRC_DIR)/main.c -o $(BIN_DIR)/cmpl $(LIB) $(CFLAGS)
	$(LD)=$(LIB_DIR)


$(DIRS):
		mkdir $(OBJ_DIR)
		mkdir $(BIN_DIR)

objs:
	$(CC) $(OFLAGS) $(SRC_DIR)/main.c -o $(OBJ_DIR)/main.o $(INCLUDES)

clean:
	$(QUIET)rm -rfv $(DIRS)
