// CS 350, Spring 2014
// Lab 10: arrays_ptrs.c
//
// Illinois Institute of Technology, (c) 2014, James Sasaki
#include <stdio.h>
#define LEN 8

int main() {
	int b[LEN];
	int *p;

	// Set b = 1 3 5 7 9 11 13 15
	//
	int i;
	for (i = 0; i < LEN; i++) {
		*(b+i) = 2*i + 1; //changed from b[i]
	}

	// Print b, comma-separated
	//
	printf("%d", b[0]); //changed from *b
	for (i = 1; i < LEN; i++) {
		printf(", %d", b[i]);  //changed from *(b+i)
	}
	printf("\n");

	// Starting with the next-to-last element of b
	// and going leftwards, take the element to the
	// right and add it to the current element.
	//
	int loc =LEN-2;
	p = b+loc;    //changed from p = &b[LEN-2]
	while (p >= b) { //changed from &p[0] >= &b[0]
		*p= +p + *(p+1); //changed from p[0] = p[0] + p[1]
		p--;//changed from p = &p[-1]
	}

	// Print b
	//
	printf("%d", b[0]);//changed from *b
	&p[0] = &b[1];//changed from p = b+1
	for (i = 1; i < LEN; i++) {
		printf(", %d", p[0]);// changed from *p
		p=&p[1];	// i.e., p = p+1; changed from p++
	}
	printf("\n");
}

// Output
// 
// 1, 3, 5, 7, 9, 11, 13, 15
// 64, 63, 60, 55, 48, 39, 28, 15
