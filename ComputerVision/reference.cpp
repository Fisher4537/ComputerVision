#include <stdio.h>

void swapnum_reference(int &i, int &j) {
  printf("swapnum.&a = %p\n", &i);
  int temp = i;
  i = j;
  j = temp;
}

void swapnum(int i, int j) {
  printf("swapnum.&a = %p\n", &i);
  int temp = i;
  i = j;
  j = temp;
}

void swapnum_pointer_a(int *i, int *j) {
  printf("swapnum.&a = %p\n", i);
  int* temp = i;
  i = j;
  j = temp;
}

void swapnum_pointer_v(int *i, int *j) {
  printf("swapnum.&a = %p\n", i);
  int temp = *i;
  *i = *j;
  *j = temp;
}

int main(void) {

  // pass argument by value
  int a = 10;
  int b = 20;
  printf("start &a = %p\n", &a);
  swapnum(a, b);
  printf("A is %d and B is %d (value)\nend   &a = %p\n\n", a, b, &a);

  // pass argument by reference 
  a = 10;
  b = 20;
  printf("start &a = %p\n", &a);
  swapnum_reference(a, b);
  printf("A is %d and B is %d (reference)\nend   &a = %p\n\n", a, b, &a);

  // pass argument by address modify address
  a = 10;
  b = 20;
  printf("start &a = %p\n", &a);
  swapnum_pointer_a(&a, &b);
  printf("A is %d and B is %d (address - modify address)\nend   &a = %p\n\n", a, b, &a);

  // pass argument by address modify value
  a = 10;
  b = 20;
  printf("start &a = %p\n", &a);
  swapnum_pointer_v(&a, &b);
  printf("A is %d and B is %d (address - modify value)\nend   &a = %p\n\n", a, b, &a);
  return 0;
}