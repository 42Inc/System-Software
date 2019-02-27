CC := gcc
BIN_FILE := prog
BIN_FILE_PATH := ./bin/$(BIN_FILE)
SRC_FILE := ./src/$(BIN_FILE).c

all: one two three

one: $(SRC_FILE)
	$(CC) -c $(SRC_FILE) -o $(BIN_FILE_PATH)1_1 -g1 -O0
	$(CC) -c $(SRC_FILE) -o $(BIN_FILE_PATH)1_2 -g2 -O0
	$(CC) -c $(SRC_FILE) -o $(BIN_FILE_PATH)1_3 -g3 -O0
two:
	$(CC) -c $(SRC_FILE) -o $(BIN_FILE_PATH)2_1 -Wall -ansi -pedantic -ggdb3 -O0
	objcopy --only-keep-debug $(BIN_FILE_PATH)2_1 $(BIN_FILE_PATH)2_1.debug
	objcopy --add-gnu-debuglink=$(BIN_FILE_PATH)2_1.debug $(BIN_FILE_PATH)2_1
	strip -g $(BIN_FILE_PATH)2_1
three:
	$(CC) -c $(SRC_FILE) -o $(BIN_FILE_PATH)3_1 -Wall -ansi -pedantic -ggdb3 -O0
	strip -g $(BIN_FILE_PATH)3_1

clean:
	rm -f ./obj/*.o
	rm -f /bin/*
