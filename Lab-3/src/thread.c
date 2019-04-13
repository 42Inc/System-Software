#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int i = 0;

void* increment()
{
  int j;
  for (j = 0; j < 100000; ++j) ++i;

  return NULL;
}

int main(int argc, char const *argv[])
{
  pthread_t tid = -1;
  pthread_attr_t attr;
  int j;

  pthread_attr_init(&attr);
  pthread_create(&tid, &attr, increment, NULL);

  for (j = 0; j < 100000; ++j) ++i;

  if (tid != -1) pthread_join(tid, NULL);
  printf("i = %d (expected: 200000)\n", i);

  return EXIT_SUCCESS;
}
