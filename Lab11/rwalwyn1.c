#include <stdio.h>

int main(void){
  typedef struct {int a, b;} Pair;
  Pair x[2];
  Pair *p;
  int *q, *r;
  x[0].a =10;
  x[0].b =20;
  x[1].a =30;
  x[1].b =40;
  p= &x[0];
  q=&x[0].b;
  r=&x[1].a;
  printf("%d\n",  r == x[1].&a );
}
//a. evaluates as true 
//b. causes a compile time warning: comparison of distinct pointer types
//   lacks a cast [enabled by default] - evaluates as false
//c. evaluates as true
//d. evaluates as true
//e. causes a compile error: expected identifier before '&' token

