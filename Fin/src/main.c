#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

int main(int argc, char const *argv[]) {
  void *ptr;
  ptr = dlopen("mylib.so", RTLD_LAZY | RTLD_GLOBAL);

  int (*f1) (void);
  int (*f2) (int);

  f1 = dlsym(ptr, "getVal");
  f2 = dlsym(ptr, "getFlag");

  printf("%s\n", dlsym(ptr, "targetVariable"));
  printf("0x%x\n", f2(f1()));

  return EXIT_SUCCESS;
}
