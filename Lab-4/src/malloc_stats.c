#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

int main(int argc, char const *argv[])
{
  char * str;
  int * array;
  str = (char *) malloc (15);
  array = (int *) calloc (sizeof(int), 10);
  if (str == NULL) {
    printf ("Error!\n");
    exit(EXIT_FAILURE);
  }
  strcpy (str, "System Software");
  array[4] = strlen(str);
  printf ("String [%s] has %d symbols\n", str, array[4]);
  free (str);
  free (array);
  return EXIT_SUCCESS;
}
