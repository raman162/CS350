// CS 350, Spring 2014
//
// ptr1.c: Declare, set, and inspect a pointer.
//
// Illinois Institute of Technology, (c) 2013, James Sasaki

#include <stdio.h>
int main() {
  int x = 17;
  printf("Value and address of x:\n");
  printf("x : %d\n", x);
  printf("&x: %p\n", &x);

  int *p;
  p = &x;
  printf("\nValue of p, value of *p, address of p:\n");
  printf("p : %p\n", p);
  printf("*p: %d\n", *p);
  printf("&p: %p\n", &p);

  x = 23;
  printf("\nAfter x = 23:\n");
  printf("x : %d\n", x);
  printf("*p: %d\n", *p);
}
