// CS 350, Spring 2014
//
// ptr_arith.c: Basic pointer arithmetic
//
// Illinois Institute of Technology, (c) 2014, James Sasaki

// Array elements b[0], b[1], ... are adjacent in memory
// If we add 1 to the address of b[0], we get the address of b[1].
// (The 1 is converted to the number of bytes for an integer.)
// Adding 2 to &b[0] gives us &b[2], etc.
//
// Subtracting an integer also works: e.g. &b[5] - 1 is &b[4]
//
// You can also subtract two pointers and get the number
// of values between the two pointers: e.g. &b[3] - &b[1] = 2
//
#include <stdio.h>
int main() {
	int b[6], i;

	// Print addresses of b[0..5]
	//
	for (i = 0; i < 6; i++) {
		printf("&b[%d] = %p\n", i, &b[i]);
	}
	printf("\n");

	// Print (address of b[0]) + i (i = 0..5)
	// They match addresses of b[0..5]
	//
	for (i = 0; i < 6; i++) {
		printf("&b[0] + %d = %p\n", i,  &b[0]+i);
	}
	printf("\n");

	// Print (address of b[5]) - i (i = 5, 4, ..., 0)
	// They also match addresses of b[0..5]
	//
	for (i = 5; i >= 0; i--) {
		printf("&b[5] - %d = %p\n", i, &b[5]-i);
	}
	printf("\n");

	// If p is a pointer, then p+1 points to the
	// value after p in memory; p-1 points to the
	// value before p in memory.  Note below p-2
	// does not point to a legal value of array b.
	//
	int *p = &b[1];
	for (i = -2; i < 2; i++) {
		printf("p + %2d = %p\n", i, p+i);
	}
	printf("\n");

	// Subtraction: pointer - pointer gives the
	// number of values between the two addresses.
	// (The number is a long int.)
	//
	printf("&b[4] - &b[1] = %ld\n", &b[4]-&b[1]);
	printf("&b[1] - &b[4] = %ld\n", &b[1]-&b[4]);
}

/* Output

&b[0] = 0x7fff57894ab4
&b[1] = 0x7fff57894ab8
&b[2] = 0x7fff57894abc
&b[3] = 0x7fff57894ac0
&b[4] = 0x7fff57894ac4
&b[5] = 0x7fff57894ac8

&b[0] + 0 = 0x7fff57894ab4
&b[0] + 1 = 0x7fff57894ab8
&b[0] + 2 = 0x7fff57894abc
&b[0] + 3 = 0x7fff57894ac0
&b[0] + 4 = 0x7fff57894ac4
&b[0] + 5 = 0x7fff57894ac8

&b[5] - 5 = 0x7fff57894ab4
&b[5] - 4 = 0x7fff57894ab8
&b[5] - 3 = 0x7fff57894abc
&b[5] - 2 = 0x7fff57894ac0
&b[5] - 1 = 0x7fff57894ac4
&b[5] - 0 = 0x7fff57894ac8

p + -2 = 0x7fff53f84ab0
p + -1 = 0x7fff53f84ab4
p +  0 = 0x7fff53f84ab8
p +  1 = 0x7fff53f84abc

&b[4] - &b[1] = 3
&b[1] - &b[4] = -3
*/