// CS 350, Spring 2014
//
// swap.c: Emulate call-by-reference using pointers
//
// Illinois Institute of Technology, (c) 2013, James Sasaki

#include <stdio.h>
void swap(int *v1, int *v2) {
  printf("Swapping values at %p and %p\n", v1, v2);
  int temp = *v1;
  *v1 = *v2;
  *v2 = temp;
}

main() {
  int x = 2, y = 3;
  printf("x and y are at %p and %p\n", &x, &y);
  printf("Before swap, x: %d, y: %d\n", x, y);
  swap(&x, &y);  // Now x == 3, y == 2
  printf("After swap, x: %d, y: %d\n", x, y);
}