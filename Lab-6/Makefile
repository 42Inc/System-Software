CC := gcc
OBJ_PATH := ./obj
SRC_PATH := ./src
BIN_PATH = ./bin
CFLAGS = -g3 -O0 -Wall

all: DIRECTORY prog

prog: $(OBJ_PATH)/main.o
	$(CC) $(OBJ_PATH)/main.o -o $(BIN_PATH)/prog $(CFLAGS)

$(OBJ_PATH)/main.o: $(SRC_PATH)/main.c
	$(CC) -c $(SRC_PATH)/main.c -o $(OBJ_PATH)/main.o $(CFLAGS)


DIRECTORY: $(OBJ_PATH) $(BIN_PATH)

$(OBJ_PATH):
	$(if ifeq test -d "$(OBJ_PATH)" 0, @mkdir -p $(OBJ_PATH))

$(BIN_PATH):
	$(if ifeq test -d "$(BIN_PATH)" 0, @mkdir -p $(BIN_PATH))
