CC = gcc
OC = objcopy
S = strip -g
QUIET = @

CFLAGS = -O0 -Wall
OFLAGS = -c -Wall
EFLAGS = -ansi -pedantic -ggdb3

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
DIRS = $(BIN_DIR) $(OBJ_DIR)
BIN_FILE = cmpl_
BIN_FILE_PATH = $(BIN_DIR)/$(BIN_FILE)
SRC_FILE = $(SRC_DIR)/prog.c

.PHONY: all one two three four clean
all: $(DIRS) one two three four

$(DIRS):
	mkdir $(DIRS)

one:
	$(CC) $(CFLAGS) $(SRC_FILE) -o $(BIN_FILE_PATH)1_1 -g1
	$(CC) $(CFLAGS) $(SRC_FILE) -o $(BIN_FILE_PATH)1_2 -g2
	$(CC) $(CFLAGS) $(SRC_FILE) -o $(BIN_FILE_PATH)1_3 -g3


two:
	$(CC) $(CFLAGS) $(SRC_FILE) -o $(BIN_FILE_PATH)2_1 $(EFLAGS)
	$(OC) --only-keep-debug $(BIN_FILE_PATH)2_1 $(BIN_FILE_PATH)2_1.debug
	$(OC) --add-gnu-debuglink=$(BIN_FILE_PATH)2_1.debug $(BIN_FILE_PATH)2_1
	$(S) $(BIN_FILE_PATH)2_1

three:
	$(CC) $(CFLAGS) $(SRC_FILE) -o $(BIN_FILE_PATH)3_1 $(EFLAGS)
	$(S) $(BIN_FILE_PATH)3_1

four:
	$(CC) $(CFLAGS) $(SRC_DIR)/thread.c -o $(BIN_FILE_PATH)4_1 -pthread $(EFLAGS)
	$(OC) --only-keep-debug $(BIN_FILE_PATH)4_1 $(BIN_FILE_PATH)4_1.debug
	$(OC) --add-gnu-debuglink=$(BIN_FILE_PATH)4_1.debug $(BIN_FILE_PATH)4_1
	$(S) $(BIN_FILE_PATH)4_1
	gcc ./src/thread2.c -g -D_REENTERANT -o ./bin/cmpl_4_2  -lpthread

clean:
	$(QUIET)rm -rvf $(DIRS)
