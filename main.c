#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
  time_t t;
  int n;

  srand((unsigned)time(&t));
  n = rand();

  printf("Hello, world %d times!\n", n);

  return 0;
}