CC = gcc
OBJ_PATH = obj
SRC_PATH = src
BIN_PATH = bin
CFLAGS = -g3 -O0 -Wall

all: DIRECTORY cmpl

cmpl: $(OBJ_PATH)/main.o
	$(CC) $(OBJ_PATH)/main.o -o $(BIN_PATH)/cmpl $(CFLAGS)

$(OBJ_PATH)/main.o: $(SRC_PATH)/main.c
	$(CC) -c $(SRC_PATH)/main.c -o $(OBJ_PATH)/main.o $(CFLAGS)


DIRECTORY: $(OBJ_PATH) $(BIN_PATH)

$(OBJ_PATH):
	$(if ifeq test -d "$(OBJ_PATH)" 0, @mkdir -p $(OBJ_PATH))

$(BIN_PATH):
	$(if ifeq test -d "$(BIN_PATH)" 0, @mkdir -p $(BIN_PATH))

clean:
	rm -rf $(OBJ_PATH)
	rm -rf $(BIN_PATH)
	rm -f *key
	rm -f *.dgst
	rm -f *.pem
	rm -f *.pub
	rm -f *.enc
	rm -f *.dec
	rm -f *.bin
	rm -f *.dat
