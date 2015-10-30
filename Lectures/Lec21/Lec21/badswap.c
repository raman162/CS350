// CS 350, Spring 2014
//
// badswap.c: Buggy call-by-reference
//
// Illinois Institute of Technology, (c) 2013, James Sasaki

// Changes to arguments passed by value aren't
// reflected in caller's variables.

#include <stdio.h>
void badswap(int v1, int v2) {
  printf("Swapping values at %p and %p\n", &v1, &v2);
  int temp = v1;
  v1 = v2;
  v2 = temp;
}

main() {
  int x = 2, y = 3;
  printf("x and y are at %p and %p\n", &x, &y);
  printf("Before swap, x: %d, y: %d\n", x, y);
  badswap(x, y);  // Doesn't change x and y
  printf("After swap, x: %d, y: %d\n", x, y);
}
