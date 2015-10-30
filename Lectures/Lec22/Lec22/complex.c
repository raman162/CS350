// CS 350, Spring 2014
//
// complex.c: Functions on complex number structures
//
// Illinois Institute of Technology, (c) 2014, James Sasaki

#include <stdio.h>

// Declare Complex to be the name of a structure type
// with real and imag fields
//
typedef struct {
	double real;
	double imag;
} Complex;

// prototypes - note structure arguments are passed using pointers
//
void cpx_print(Complex *p);
Complex *bad_make_cpx(double r, double i);
void set_cpx(Complex *p, double r, double i);

// Create and manipulate a complex value
//
int main() {
	// Declare and allocate a Complex,
	// then initialize its real & imaginary
	// fields, then print it
	//
	Complex cpx_value;
	cpx_value.real = 0.0;
	cpx_value.imag = 1.0;
	printf("cpx_value: %f + %f i\n",
		cpx_value.real, cpx_value.imag );

	// Get a pointer to the Complex
	// value and pass it to a subroutine
	//
	Complex *cpx;
	cpx = &cpx_value;
	cpx_print(cpx);

	// cpx = bad_make_cpx(1.1, 2.2); // BUG
	set_cpx(cpx, 1.1, 2.2);
	cpx_print(cpx);
}

// Print a complex number as (real + imag i)
//
void cpx_print(Complex *p) {
	printf("(%f + %f i)\n", p->real, p->imag);
	// The above uses the -> shorthand syntax for
	// printf("(%f + %f i)\n", (*p).real, (*p).imag);
}

// set_cpx(&x, a, b) sets x to a + bi
//
void set_cpx(Complex *x, double a, double b) {
   x->real = a;
   x->imag = b;
}

// Bad routine to take x and create and return x + yi. It's
// bad because it returns the address of a local variable.
// The space for the variable is deallocated when we
// return from the function.
//
Complex * bad_make_cpx(double x, double y) {
	Complex result;
	result.real = x;
	result.imag = y;
	return &result;	// <-- BUG: Don’t return pointer
					//     to a local variable !
}

/* Output

x.real = 0.000000, x.imag = 1.000000
(0.000000 + 1.000000 i)
(1.100000 + 2.200000 i)

*/
