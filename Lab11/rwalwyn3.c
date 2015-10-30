#include <stdio.h>
typedef struct Node {
  char c;
  int v[3];
  struct Node *next;
} Node;

main() {
  Node t1, t2, *p, *q;
  int *r;
  t1.c = 'z';
  t1.v[0]=4;
  t1.v[1]=6;
  t1.v[2]=88;
  p=&t1;
  q=&t2;
  t2.c = 'z';
  t2.v[0]=6;
  t2.v[1]=9;
  t2.v[2]=123;
  r=&t2.v[2];
  p -> next = NULL;
  q -> next = q;
  /* Part 2 (replace this with code) */
  /* Here */
}
