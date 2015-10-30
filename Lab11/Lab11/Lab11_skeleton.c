// ** Skeleton ** <-- remove this line and complete the program
// *** Your name and section (replace this with the correct information ***
// (Also rename this file to Lab11_YourName_Section.c and remove this comment line)

// CS 350, Spring 2014
// Lab 11: SDC simulator using structures and pointers
//
// Illinois Institute of Technology, (c) 2014, James Sasaki

#include <stdio.h>
#include <string.h>

// CPU Declarations -- a CPU is a structure with fields for the
// different parts of the CPU.
//
	typedef int Word;
	typedef int Address;

	#define MEMLEN 100
	#define NBR_REGS 10

	typedef struct {
		Word mem[MEMLEN];
		Word reg[NBR_REGS];  // Note: "register" is a reserved word
		Address pc;          // Program Counter
		Word ir;             // Instruction Register
		int running;         // running = 1 iff CPU is executing instructions
	} CPU;

// Prototypes
    void helpMsg(void);
	void initCPU(CPU *cpu);
    void readMemory(CPU *cpu);
    void dumpControlUnit(CPU *cpu);
    void dumpRegisters(CPU *cpu);
    void dumpMemory(CPU *cpu);
    void instruction_cycle(CPU *cpu);

// Main program: Initialize the cpu, read initial memory values,
// and execute the read-in program starting at location 00.
//
int main(void) {
	printf("*** STUB *** CS 350 Lab 11, Your name\n");
	CPU cpu_value;
	CPU *cpu = &cpu_value;
	initCPU(cpu);
	readMemory(cpu);

	char prompt[] = "> ";
	printf("\nBeginning execution:\n");
	printf("At the %sprompt, press return to execute the next instruction\n", prompt);
	printf("or a number, to execute that many instructions\n");
	printf("(or d to dump registers and memory, q to quit, or h or ? for help)\n");

	char command[80];       // User inputted command line
	char cmd_char;          // 'q' for quit etc.
	int simulator_quit = 0; // Have we seen simulator quit command?
	int nbr_read;           // Number of items read by sscanf

	while (!commands_done) {
		printf("%s", prompt);
		fgets(command, sizeof command, stdin);   // Read through end of current line.
		nbr_read = sscanf(command, "%c", &cmd_char);

		if (nbr_read > 0) {
			printf("*** STUB *** read in %c command or digit\n");
		}
		else {
			printf("*** STUB *** read in empty line\n");
		}
		// *** STUB look at cmd_char and process it? Or carriage return
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
void initCPU(CPU *cpu) {
	int i;
	for (i = 0; i < NBR_REGS; i++)
		cpu->reg[i] = 0;
	for (i = 0; i < MEMLEN; i++)
		cpu->mem[i] = 0;
	cpu->pc = 0;
	cpu->ir = 0;        // Might as well initialize it to something.
	cpu->running = 1;
}

// Read and dump initial values for memory
//
void readMemory(CPU *cpu) {
	int loc = 0;
	printf("Read memory: At the prompt, enter the value for the indicated\n");
	printf("memory address.  Enter a number > 9999 or < -9999 when you're done.\n");

	printf("*** STUB *** readmemory\n");
	// *** STUB *** Hint: use cpu->mem[m] to access memory location m

// *** You might need this after reading the sentinel ***
//	fgets(skip, sizeof skip, stdin);   // Clear the \n at end of terminating line

	printf("\nInitial value of memory:\n");
	dumpMemory(cpu);
}


// dumpControlUnit(cpu): Dump the control unit (pc, ir, and data registers).
//
void dumpControlUnit(CPU *cpu) {
	// *** STUB *** Hint 2: use cpu->reg[r] to access register number r
	printf("*** STUB *** dumpControlUnit\n");
	dumpRegisters(cpu);
}

// dumpRegisters(cpu): Print register values in two rows of five.
//
void dumpRegisters(CPU *cpu) {
	printf("*** STUB *** dumpRegisters\n");
}

// dumpMemory(cpu): Print memory values in a table, ten per row,
// with a space between each group of five columns and with a header
// column of memory locations.
//
void dumpMemory(CPU *cpu) {
	// *** STUB *** Hint: use cpu->mem[m] to access memory location m
	printf("*** STUB *** dumpMemory\n");
}


// Execute one instruction cycle.
//
void instruction_cycle(CPU *cpu) {
	// *** STUB *** Hint: Use cpu->pc, cpu->ir, cpu->running and so on.
	printf("*** STUB *** instruction_cycle\n");

	// if pc is out of range, complain and halt machine, otherwise
	// set ir to instruction at pc, increment pc
	// if ir < 0 ....
	// get opcode, register, and address fields of ir
	// switch on opcode, case for each opcode ...
	return;
}
