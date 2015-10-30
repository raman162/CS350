// ** Skeleton, version of 2014-01-28 11:19 AM ** <-- remove this line and complete the program

// CS 350, Spring 2014
// Lab 2 -- Converting an integer to a given base
//
// Illinois Institute of Technology, (c) 2014, James Sasaki
//

// This program repeatedly converts a value to a given base.
// The value is converted to an equivalent array of digits
// (each >= 0 and < base), and then we print the array.
// We convert value & base pairs until the value is < 1 or base < 2.

#include <stdio.h>
#include <strings.h>

#define ARRAYLEN 16

// Prototypes
void convert_to_base(int value, int base, int digits[], int len);
void print_digits(int digits[], int n);

int main() {
	printf("CS 350 Lab 2 for %s\n\n", "***Fill in your name and section ***");  // <-- Fill in

	int value, base;
	int digits[ARRAYLEN];

	// Read an integer value to convert and the base to
	// convert it to 
	//
	printf("Enter an integer and base (int < 1 or base < 2 to quit): ");
	scanf("%d %d", &value, &base);

	// Quit if the value is < 1 or the base is < 2. 
	// Otherwise, call convert_to_base to fill the digits
	// array with values and then call print_digits to print
	// out the array.  Then prompt, read another input, and
	// repeat.
	//
	while (value >= 1 && base >= 2) {
		// STUB: call convert_to_base(value, ....)
		// STUB: call print_digits(....)
		printf("Enter an integer and base (int < 1 or base < 2 to quit): ");
		scanf("%d %d", &value, &base);
	}
}

// convert_to_base(value, base, digits, digits_len) finds
// the representation of the value in the given base and
// stores it as a sequence of digits in the digits array.
//
// For example, if value = 5 and base = 2, the array is set
// to 0 0 ... 0 1 0 1.
//
// If the value is too big, then once we fill up the array,
// we stop and print an error message that gives the part we
// couldn't represent.  Example: If value = 31, base = 2,
// and the array had length 3 then we set the array to 1 1 1
// and print out 24 as the value left over.  (You'd have to
// set ARRAYLEN to 3 to replicate this example.)
//
void convert_to_base(int value, int base, int digits[], int len) {
	// We'll fill in the digits from right to left;
	// the next digit to fill in is at digits[position].
	//
	// If leftover = value - the number represented by the
	// digits we've filled in so far, then remain =
	// (value - leftover) / base ^ (len - position).
	//
	// posn_value = the value represented by a 1 at the
	// current position (i.e., base ^ (len - position))
	//
	int position = len-1;
	int posn_value = 1;
	int remain = value;
	
	// Pseudocode:
	// while remain > 0 and position >= 0,
	//     Calculate remain/base, put remainder
	//        into digits, update position, and
	//        set remain to the quotient
	// if remain is 0
	//     We're done? (Oops! what about the rest of the
	//     digits?)
	// else
	//     Calculate the leftover value and
	//         complain about it

	// HINT: It might help to introduce a new variable to
	// keep track of the leftover value as the loop runs
}

// print_digits takes an array of integers and the length of
// the array and prints out the integers on one line,
// separated by a space.
//
void print_digits(int digits[], int n) {
	// *** STUB: Replace this comment with code. ***
}