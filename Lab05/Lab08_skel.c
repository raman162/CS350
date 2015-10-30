//Raman Walwyn-Venugopal - Section 01
// CS 350, Spring 2014
// Lab 8: SDC Simulator
//
// Illinois Institute of Technology, (c) 2013, James Sasaki

#include <stdio.h>
#include <string.h>

// Prototypes
    void helpMsg(void);
    void initCPU(void);
    void readMemory(void);
    void dumpControlUnit(/*int pc, int ir, */ int regs[]);
    void dumpRegisters(int regs[]);
    void dumpMemory(int mem[]);
    void instruction_cycle(void);

// CPU declarations -- note we're being horrible and using global variables; after we
// see structures and pointers, we'll clean things up.
//
#define NBR_REGS 10
#define MEMLEN 100
    int running;          // true iff instruction cycle is active
	int regs[NBR_REGS];   // general-purpose registers
	int mem[MEMLEN];      // main memory

// Main program: Initialize the cpu, read initial memory values,
// and execute the read-in program starting at location 00.
//
int main(void) {
	printf("CS 350 Lab 8, Raman Walwyn-Venugopal\n");
	initCPU();
	readMemory();

	 char prompt[] = ">99 ";
	printf("\nBeginning execution:\n");
	printf("At the %sprompt, press return to execute the next instruction\n", prompt);
	printf("(or d to dump registers and memory, q to quit, or h or ? for help)\n");

	char command[80];       // User inputted command line
	char cmd_char;          // 'q' for quit etc.
	int simulator_quit = 0; // Have we seen simulator quit command?
	int nbr_read;           // Number of items read by sscanf
	int commands_done=0;  
	while (!commands_done) {
		printf("%s", prompt);
		fgets(command, sizeof command, stdin);   // Read through end of current line.
		nbr_read = sscanf(command, "%c", &cmd_char);

		if (nbr_read > 0) {
			printf("*** STUB *** read in %c command\n");
		}
		else {
			printf("*** STUB *** read in a number or empty line\n");
		}
	}
	
	// When we see the quit command, dump the control unit and memory
	// and quit
	//
	printf("*** STUB *** quitting'n");
}

// Print out the instruction set architecture for the SDC.
//
void helpMsg(void) {
	printf("*** STUB *** helpMsg\n");
}


// Initialize cpu registers, memory, pc, and ir (all to zeros).
// Initialize the running flag to true.
//
void initCPU(void) {
	printf("*** STUB *** initCPU\n");

	int i;
	for (i = 0; i < NBR_REGS; i++)
		regs[i] = 0;
	for (i = 0; i < MEMLEN; i++)
		mem[i] = 0;
}

// Read and dump initial values for memory
//
void readMemory(void) {
	int loc = 0;
	printf("Read memory: At the prompt, enter the value for the indicated\n");
	printf("memory address.  Enter a number > 9999 or < -9999 when you're done.\n");

	printf("*** STUB *** readmemory\n");

// *** You might need this after reading the sentinel ***
//	fgets(skip, sizeof skip, stdin);   // Clear the \n at end of terminating line

	printf("\nInitial value of memory:\n");
	dumpMemory(mem);
}


// dumpControlUnit(/*pc,ir,*/regs): Dump the control unit (pc, ir, and data registers).
// 
void dumpControlUnit(/*pc,ir,*/int regs[]) {
	// *** STUB ***
	printf("*** STUB *** dumpControlUnit\n");
	dumpRegisters(regs);
}


// dumpRegisters(regs): Print register values in two rows of five.
//
void dumpRegisters(int regs[]) {
	// *** STUB *** Hint: How do printf formats %d, %5d, %-5d, %05d, and % 05d differ?
	printf("*** STUB *** dumpRegisters\n");
}

// dumpMemory(mem): Print memory values in a table, ten per row,
// with a space between each group of five columns and with a header
// column of memory locations.
//
void dumpMemory(int mem[]) {
	printf("*** STUB *** dumpMemory\n");
}


// Execute one instruction cycle.
//
void instruction_cycle(void) {
	printf("*** STUB *** instruction_cycle\n");
	// if pc is out of range, complain and halt machine, otherwise
	// set ir to instruction at pc, increment pc
	// if ir < 0 ....
	// get opcode, register, and address fields of ir
	// echo instruction
	// switch on opcode, case for each opcode ...
	return;
}
