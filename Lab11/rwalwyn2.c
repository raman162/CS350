#include <stdio.h>
typedef struct Node {
  char c;
  int v[3];
  struct Node *next;
} Node;

main() {
  Node t1, t2, *p, *q;
  int *r;
  t1.c = 'a';
  t1.v[0]=4;
  t1.v[1]=6;
  t1.v[2]=8;
  p=&t1;
  q=&t2;
  t2.c = 'b';
  t2.v[0]=6;
  t2.v[1]=9;
  t2.v[2]=12;
  r=&t2.v[1];
  p -> next = q;
  q -> next = NULL;
  /* Part 2 (replace this with code) */
  /* Here */
}
