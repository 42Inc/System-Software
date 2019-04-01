#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
void generate_binary(char** argv);
void generate_text(char** argv);
void helper() {
  printf ("Usage:\n");
  printf ("\tprog bin <out-file-name> [size]\n");
  printf ("\tprog txt <out-file-name> [size]\n");
}

int main(int argc, char** argv) {
  if (argc < 3) {
    helper();
    return 1;
  }
  srand(time(NULL));
  if (!strcmp(argv[1], "bin")) {
    generate_binary(argv);
  } else if (!strcmp(argv[1], "txt")) {
    generate_text(argv);
  } else {
    helper();
    return 1;
  }

  return 0;
}

void generate_binary(char** argv) {
  size_t size = 100;
  size_t i = 0;
  unsigned char byte = 0;
  int fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0666);
  if (argv[3] != NULL) {
    size = atoi(argv[3]);
    printf("Size set in %lu\n", size);
  }
  fd = fd == -1 ? 1 : fd;
  for (i = 0; i < size; ++i) {
    byte = rand() % 256;
    write(fd, &byte, 1);
  }
  close(fd);
}

void generate_text(char** argv) {
  size_t size = 100;
  size_t i = 0;
  unsigned char byte = 0;
  unsigned char _register = 0;
  int fd = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, 0666);
  if (argv[3] != NULL) {
    size = atoi(argv[3]);
    printf("Size set in %lu\n", size);
  }
  fd = fd == -1 ? 1 : fd;
  for (i = 0; i < size; ++i) {
    _register = rand() % 3;
    byte = _register == 0 ? (rand() % ('Z' - 'A') + 'A') : (_register == 1 ? (rand() % ('z' - 'a') + 'a') : (rand() % ('9' - '0') + '0'));
    write(fd, &byte, 1);
  }
  close(fd);
}
