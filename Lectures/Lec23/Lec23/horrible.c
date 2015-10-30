// CS 350, Spring 2014
//
// horrible.c: b[i] and i[b] are equivalent
//
// Illinois Institute of Technology, (c) 2014, James Sasaki

#include <stdio.h>
int main() {
  int b[5];
  2[b] = 17;

  printf("&b[2] = %p\n", &b[2]);
  printf("b+2   = %p\n", b+2);
  printf("2+b   = %p\n", 2+b);
  printf("&2[b] = %p\n", &2[b]);
  printf("\n");

  printf("b[2]  = %d\n", b[2]);
  printf("2[b]  = %d\n", 2[b]);
}

/* Output

&b[2] = 0x7fff5354ba90
b+2   = 0x7fff5354ba90
2+b   = 0x7fff5354ba90
&2[b] = 0x7fff5354ba90

b[2]  = 17
2[b]  = 17
*/
