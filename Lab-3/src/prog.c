#include <stdio.h>
#include <string.h>
int fill_array(char *str, char ch) {
  int i;
  for (i = 0; i < 21; i++)
    str[i] = ch;
  return (0);
}
int main(int argc, char **argv) {
  char str1[10], str2[10];
  fill_array(str2, 'A');
  fill_array(str1, 'B');

  printf("Массив символов [%s], len = %lu\n", str1, strlen(str1));
  printf("Массив символов [%s], len = %lu\n", str2, strlen(str2));
  return (0);
}
