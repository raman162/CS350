// *** Note: This file doesn't compile as is ***

// CS 350, Final Project, Spring 2014 (skeleton file)
//
// LC3 simulator

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Basic Declarations
//
	typedef short int Word;
	typedef unsigned short int Address;

	#define MEMLEN 65536
	#define NBR_REGS 8

	typedef struct {
		Word memory[MEMLEN];
		Word reg[NBR_REGS];  // Note: "register" is a reserved word
		int condition_code;  // positive, zero, or negative
		Word instr_reg;
		Address pgm_counter;
		int running;         // running = 1 iff CPU is executing instructions
	} CPU;


// Prototypes
//
	// CPU manipulation and status dump functions
	//
	void init_CPU(CPU *cpu);   // Simulate power-up
	void dump_CPU(CPU *cpu);
	void dump_register(CPU *cpu);
	void dump_control_unit(CPU *cpu);
	void dump_memory(CPU *cpu, Address from, Address to);
	char get_condition_code(CPU *cpu);
	void set_condition_code(CPU *cpu, Word value);
	void helpMsg(void);
	int bshifter (Word instr, int l, int r, int s);
	int getdst(CPU *cpu);
	int getpco9n(CPU *cpu);
	int getsrc(CPU *cpu);
Address filereader(CPU *cpu);

	


	// Instruction cycle functions
	//
	void instruction_cycle(CPU *cpu);      // Simulate entire instruction cycle
	void fetch_instr(CPU *cpu);            // Simulate fetch instruction part of cycle
	// *** STUB *** You may want other routines (you may not)

	// Functions for accessing parts of an instruction
	//
	int op(Word w);                       // Opcode of an instruction
	// *** STUB *** You probably want other routines

	// Functions for executing each instruction
	//
	void instr_ADD (CPU *cpu);
	void instr_AND (CPU *cpu);
	void instr_BR  (CPU *cpu);
	void instr_err (CPU *cpu);
	void instr_JMP (CPU *cpu);
	void instr_JSR (CPU *cpu);
	void instr_LD  (CPU *cpu);
	void instr_LDI (CPU *cpu);
	void instr_LDR (CPU *cpu);
	void instr_LEA (CPU *cpu);
	void instr_NOT (CPU *cpu);
	void instr_RTI (CPU *cpu);
	void instr_ST  (CPU *cpu);
	void instr_STI (CPU *cpu);
	void instr_STR (CPU *cpu);
	void instr_TRAP(CPU *cpu);
	char  read_char();             // Read a character for GETC, IN
	// *** STUB *** You may want other functions; depends on how you organize your code

// -------------------- MAIN PROGRAM --------------------
//
// The main program creates and initializes a CPU, loads a program,
// and executes it step by step (until it halts or the user quits).
// The CPU is dumped before and after executing the program
//
	
int main() {
	// Create and initialize the  CPU, read initial memory, dump CPU
	//
  printf("Raman Walwyn-Venugopal - LC3 Simulator\n\n");
  CPU cpu_struct, *cpu;
  cpu = &cpu_struct;
	init_CPU(cpu);
	Address end = filereader(cpu);
	Address begin = cpu->pgm_counter;
	char prompt[]= " >";
	printf("Origin = %x; end = %x \n" , begin, end);
	dump_memory(cpu,begin, end);
	dump_register(cpu);
	char command[80];       // User inputted command line
	char cmd_char;          // 'q' for quit etc.
	int commands_done=0;
	char m[1]="m";
	printf("At the > prompt, press return to execute the next instruction, q to quit, h or ? for help, or enter a number x to execute x amount of instructions\n");
		
		while (cpu->running==1) {
			printf("%s", prompt);
			fgets(command, sizeof command, stdin);// Read through end of currentline.              
			
			unsigned int starter =0;
			unsigned int endm = 0;
			char op = command[0];
			if (isdigit(op)){
			  int cycles=atoi(command);
			  int d;
			  for (d=0;d<cycles;d++){
			    instruction_cycle(cpu);
			  }
			}else{
			switch (op){
			case 'h' : case '?' :
			    helpMsg();
			  break;
			case 'q' :
			  cpu->running = 0;
			  break;
			case 'd':
			  dump_memory(cpu,begin,end);
			  break;
			case 'm':
			  sscanf(command, "m %x %x", &starter, &endm);
			  if (starter<0 && endm>starter && endm < 65537){
				dump_control_unit(cpu);
				dump_memory(cpu,(Address)starter, (Address)endm );		
				}else{
				  printf("Error entering values, correct way is (m 1000 2000\n");
				}
			  break;
			default:
			  instruction_cycle(cpu);
			  break;
			}
			
			}

		}
}

	


	
	
	/* *** STUB *** */


// -------------------- CPU ROUTINES --------------------
//
//

// init_CPU(cpu) simulates power-on initialization: Program counter
// and instruction register are set to 0, as are memory and registers;
// condition code = Z, and the CPU will run the instruction cycle.
//
Address filereader(CPU *cpu){
  char filename[256];
  printf("\nPlease enter the name of the file (eg. 'myfile.hex'):\n");
  scanf("%s", filename);
  printf("File to read from is '%s'\n", filename);
  FILE *myfile= fopen(filename, "r");
  Address end = cpu->pgm_counter;   
  Address begin = cpu->pgm_counter;
  if (myfile==NULL){
		printf("Error opening file!\n");
		strcpy(filename, "program.hex");
	}
	myfile=fopen(filename, "r");
	printf("Reading from %s:\n", filename);
	unsigned int nextInt=0;
	fscanf(myfile, "%x", &nextInt);
	cpu->pgm_counter = nextInt;
	int c = nextInt;
	end = cpu->pgm_counter;
	cpu->memory[c]=nextInt;
	while (fscanf(myfile, "%x", &nextInt) != EOF){
	  cpu->memory[c]=nextInt;
	  c++;
	  end++;
	  printf("%d\n", c);
	}
	end--;
	fclose(myfile);
	return end;
}
  


void init_CPU(CPU *cpu) {
	cpu -> pgm_counter = 0;
	cpu -> instr_reg = 0;
	cpu -> condition_code = 0;   // Z condition code on power-up
	cpu -> running = 1;                // instruction cycle is running

	int regNbr;
	for (regNbr = 0; regNbr < NBR_REGS; regNbr++) {
		cpu -> reg[regNbr] = 0;
	}

	// Implementation note: You can't use a while loop
	// that checks for addr >= MEMLEN because addr is an
	// unsigned short and hence always <= MEMLEN.
	// (I.e., if addr = MEMLEN, then addr++ sets addr to 0.)
	//
	// In any case, we want the last word of memory to contain a HALT.
	//
	Address addr = 0;
	while (addr < MEMLEN-1) {
		cpu -> memory[addr++] = 0;
	}
	// *** STUB ***
}

// -------------------- INSTRUCTION ROUTINES --------------------

// Fetch instruction:
//   Copy instruction pointed to by program counter to instruction register
//   Increment program counter (wraparound addresses).
//
void fetch_instr(CPU *cpu) {
	cpu -> instr_reg = cpu -> memory[cpu -> pgm_counter];
	++(cpu -> pgm_counter);		// unsigned overflow will wraparound to 0
}

// Execute an instruction cycle
//   Fetch an instruction
//   Decode the instruction opcode
//   Execute the instruction
//

void instruction_cycle(CPU *cpu) {
	// Get current instruction to execute and its location,
	// echo them out.
	//
	Address old_pc = cpu -> pgm_counter;
	fetch_instr(cpu);
	printf("x%04hX: x%04hX  ", old_pc, cpu -> instr_reg);
	// Execute instruction; set cpu running = 0 if CPU execution
	// is to stop (because of TRAP HALT or an internal error).
	//
	int instr = cpu-> instr_reg;
	//different functions that are called from the instruction cycle
	unsigned int op = instr>>12;
	//	printf("%d - Op\n", op);
	switch (op) {
	case  0x0: instr_BR(cpu);  
	 break;
	case  0x1: instr_ADD(cpu);
	break;
	case  0x2: instr_LD(cpu);
	break;
	case  0x3: instr_ST(cpu);
	break;
	case  0x4: instr_JSR(cpu);
	break;
	case 0x5: instr_AND(cpu);
	break;
	case 0x06: instr_LDR(cpu);
	break;
	case 0x07: instr_STR(cpu);
	break;
	case 0x08: instr_RTI(cpu);
	break;
	case 0x09: instr_NOT(cpu);
	break;
	case -6: instr_LDI(cpu);
	break;
	case -5: instr_STI(cpu);
	break;	
	case -4: instr_JMP(cpu);
	break;
	case -3: instr_err(cpu);
	break;
        case -2:  instr_LEA(cpu);
	break;
	case -1: instr_TRAP(cpu);
	break;
	


	default:
		printf("Bad opcode: %d; quitting\n", op);
		cpu -> running = 0;
	}
}

// Execute branch instruction: Bitwise AND instruction's mask and
// cpu's condition code, branch iff result is nonzero.
//
// Echo kind of branch, current cc, whether or not the branch happened,
// and if so, the target of the branch.
//

//this is used to shift the values of bits to get the op code and different sections of instructions
int bshifter(Word instr, int l, int r, int s){
  int shift = instr<<15-l;//shifts bits required amount of times to the left
  shift = shift>>15-l + r;//shifts bits required amount of times to the right to get specefic value
  //used if the sign of the value is needed
	if (s==1){	
		if(shift&(1<<(r-l))!=0){
		int p = l-r+1;
		int i;
		long num =1;
		for (i=0;i<p;i++){
			num = num*2;
		}
		shift=shift-num;
		}
	}
	return shift;
}

void set_condition_code(CPU *cpu, Word value){
  //sets the condition code to either 1(P), 2(0), 3(N)
	if (value>0){
	cpu->condition_code =1;
	}else if (value==0){
	cpu->condition_code =2;
	}
	else if (value<0){
	  cpu->condition_code =3;

}
}
//gets the destination from the instruction
int getdst(CPU *cpu){
	int d=bshifter(cpu->instr_reg, 11, 9, 0);
	return d;
	}
//gets the pc offset from the instruciton
int getpco9n(CPU *cpu){
	int p=bshifter(cpu->instr_reg, 8, 0, 1);
	return p;
	}
//gets the source/base from the instruction
int getsrc(CPU *cpu){
	int s=bshifter(cpu->instr_reg, 8,6,0);
	return s;
	}
//Branch instruction
void instr_BR(CPU *cpu) {
	
	int m = getdst(cpu);//mask
	int pco= getpco9n(cpu);
	char mc[100];//mask code
	switch (m){
	case 0 : case 1 :
			strcpy(mc, "NOP");
			break;
		case 2:
			strcpy(mc, "Z = 0");
			break;
		case 3: strcpy(mc, "PZ >= 0");
			break;
		case 4: strcpy(mc, "N <0");
			break;
		case 5: strcpy(mc, "NP !=0");
			break;	
		case 6: strcpy(mc, "NZ Z=0");
			break;
		case 7: strcpy(mc, "BR unconditional");
			break;
		default:
			printf("error!\n");
			break;
	}
	if (cpu->condition_code !=0){
		int old = cpu->pgm_counter;
		cpu->pgm_counter= cpu->pgm_counter + pco;
		printf("\tBR\t%d %s\tP go to %d + %d = %d\n",cpu->condition_code, mc, old, pco, cpu->pgm_counter);
}
		else{
		  printf("\tBR\t%d %s False condition\n", cpu->condition_code, mc);
		}
}
//add function
void instr_ADD(CPU *cpu){
	Word i=cpu->instr_reg;
	int t = bshifter (i,5,5,0);
	int dst = getdst(cpu);
	int s1 = getsrc(cpu);
	int s2=bshifter(i,2,0,0);
	int i5=bshifter(i,4, 0, 0);
	if(t==1){
	  cpu->reg[dst]=cpu->reg[s1]+cpu->reg[s2];//dst=source1+source2
		printf("\tADD\tR%d,  R%d,  %d;  R%d <- %x + %x = %x; CC = %d\n",dst, s1, t, s2, dst, cpu->reg[s1], cpu->reg[s2], cpu->reg[dst], cpu->condition_code);
		}else{
	  cpu->reg[dst] = cpu->reg[s2]&i5;//dst=source2 + i5
	printf("\tADD\tR%d,  R%d,  %x;  R%d <- %x + %x = %x; CC = %d\n",dst, s1, t, i5, dst,  cpu->reg[s1], i5, cpu->reg[dst], cpu->condition_code);
}
} 
		
//Ld function
void instr_LD (CPU *cpu){
	Word i=cpu->instr_reg;
	int dst = getdst(cpu);
	int pco = getpco9n(cpu);
	cpu->reg[dst]= cpu->memory[cpu->pgm_counter+pco];//dest = mem[PC+pco]
	set_condition_code(cpu, cpu->reg[dst]);
	printf("\tLD R%d, %d; R%d <- M[PC-%d] = M[%x] = %d; CC = %d\n", dst, pco, dst, pco, cpu->pgm_counter +pco, cpu->reg[dst] ,cpu->condition_code);
       
}


//store function
void instr_ST(CPU *cpu){
	Word i=cpu->instr_reg;
	int s = getdst(cpu);
	int pco = getpco9n(cpu);
	int sum=cpu->pgm_counter +pco; //sum = PC +pco
	cpu->memory[sum]=cpu->reg[s];//mem[sum] = reg[s]
	printf("\tST R%d, %d; M[PC + %d] = M[%x] < - %x; CC = %d\n", s, pco, pco, sum, cpu->memory[sum], cpu->condition_code);
	}

//jumps to a location
void instr_JSR(CPU *cpu){
	Word i = cpu->instr_reg;
	int t = bshifter(i, 11,11,0);
	if (t==1){
		int pco = bshifter(i, 10, 0,0);
		Address temp = cpu->pgm_counter;
		cpu->reg[7]=temp;
		cpu->pgm_counter += pco; //PC = PC + pco
		printf("\tJSR x%x+%d = x%x (R7=x%x)\n", temp, pco, cpu->pgm_counter, temp);
	}
else{
	int b = getsrc(cpu);
	cpu->reg[7]=cpu->pgm_counter;
	cpu->pgm_counter =cpu->reg[b]; // PC = reg[base]
	printf("\tJSRR R7 = x%x (R7 = x%x)\n", cpu->pgm_counter, cpu->reg[7]);
} 

	}
//bitwise & 
void instr_AND(CPU *cpu){
	Word i = cpu->instr_reg;
	int dst = getdst(cpu);
	int s1= getsrc(cpu);
	int t= bshifter(i,5,5,0);
	if (t==1){
	  int temp = cpu->reg[s1]&bshifter(i,4,0,0);//reg[dest]=reg[src]&[immm5]
	  cpu->reg[dst]= temp;
		printf("\tAND R%d, R%d %d; R%d <- %x+%x=%x; CC=%d\n", dst, s1, bshifter(i,4,0,0), dst, cpu->reg[s1], bshifter(i,4,0,0), cpu->reg[dst], cpu->condition_code); 
	}else{
		
	  cpu->reg[dst]=cpu->reg[s1]&cpu->reg[bshifter(i,2,0,0)];//reg[dest]=reg[src]&reg[b];
		int s2=bshifter(i,2,0,0);
		printf("\tAND R%d, R%d; R%d <- %x+%x=%x; CC=%d\n", dst, s1,s2, dst, cpu->reg[s1], cpu->reg[s2], cpu->reg[dst], cpu->condition_code);  
	
}
		}
//Load using base register
void instr_LDR(CPU *cpu){
	Word i = cpu->instr_reg;
	int dst = getdst(cpu);
	int b=getsrc(cpu);
	int o=bshifter(i, 5, 0, 0);
	cpu->reg[dst]=cpu->memory[cpu->reg[b]+o];//reg[dst]=mem[reg[base]+offset]
	set_condition_code(cpu, cpu->reg[dst]);
	printf("\tLDR R%d, R%d, %dl R%d <- M[%x+%d] = M[%x] = %x; CC = %d\b", dst, b, o, dst, b, o, b+o, cpu->reg[dst], cpu->condition_code);

	}
//store using register
void instr_STR(CPU *cpu){
	Word i = cpu->instr_reg;
	int s=getdst(cpu);
	int b = getsrc(cpu);
	int o = bshifter(i, 5, 0, 0);
	cpu->memory[b+o]= cpu->reg[s]; //mem[base+offset] = reg[src]
	printf("\tSTR R%d, R%d, %d; M[%x+%d] = M[%x] <- %x\n", s, b, o, b, o, b+o, cpu->memory[b+o]);
	}
	
//interrupt
void instr_RTI(CPU *cpu){
	printf("Busy!\n");
}

//Not instruction
void instr_NOT(CPU *cpu){
	Word i = cpu->instr_reg;
	int dst = getdst(cpu);
	int s = getsrc(cpu);
	cpu -> reg[dst] = ~cpu->reg[s];
	set_condition_code(cpu, cpu->reg[dst]);
	printf("\tNOT R%d, R%d; R%d <- NOT %x = %x ; CC = %d\n", dst, s, dst, s, cpu->reg[dst], cpu->condition_code);
	 
}

//Load Indirect
void instr_LDI(CPU *cpu){
	Word i= cpu ->instr_reg;
	int dst = getdst(cpu);
	int pco = getpco9n(cpu);
	Word temp = cpu->memory[cpu->pgm_counter+pco];
	cpu->reg[dst] = cpu->memory[temp];//reg[dest] = mem[mem[PC+pcoffset]]
	set_condition_code(cpu,cpu->reg[dst]);
	printf("\tLDI R%d, %d; R%d <-M[M[PC+%d]]=M[M[%x]]=M[%x] = %x; CC = %d\n", dst, pco, dst, pco, cpu->pgm_counter+pco, temp, cpu->reg[dst], cpu->condition_code);
}

//Store Indirect
void instr_STI(CPU *cpu){
	Word i= cpu->instr_reg;
	int s = getdst(cpu);
	int pco = getpco9n(cpu);
	Word temp = cpu->memory[cpu->pgm_counter + pco];
	cpu->memory[temp] = cpu->reg[s]; //mem[mem[PC +offset] = reg[src]
	printf("\tSTI R%d, %d; M[M[PC+%d]] = M[M[%x]] = M[%x] <- %x\n", s, pco, s, pco, s+pco, temp, cpu->memory[temp]);
	
}
//JMP to another location
void instr_JMP(CPU *cpu){
  cpu->pgm_counter = cpu->reg[getsrc(cpu)];//PC = reg[src]
	printf("\tJMP R%d; go to %x\n", cpu->reg[getsrc(cpu)], cpu->pgm_counter);
	}
//error
void instr_err(CPU *cpu){
	printf("\tDONT CARE!12\n");
	}
//Load effective address
void instr_LEA(CPU *cpu){
	Word i = cpu->instr_reg;
	int dst = getdst(cpu);
	int pco = getpco9n(cpu);
	cpu->reg[dst] = cpu->pgm_counter+pco;//reg[dst]=PC + offset
	set_condition_code(cpu, cpu->reg[dst]);
	printf("\tLEA R%d, %d, R%d <- PC = %d = %x; CC = %d", dst, pco, dst, pco, cpu->reg[dst], cpu->condition_code);
	}
//TRAP INSTRUCTIONS
void instr_TRAP(CPU *cpu){
	Word i = cpu->instr_reg;
	int tv = bshifter(i, 7, 0, 0);
	char c;
	switch (tv){
		case 0x20 : 
		  //getc
			printf(">");
		        c = read_char();
			cpu->reg[0]&=0;
			cpu->reg[0]=c;
			printf(" %c\n",c);
			break;
		case 0x21 :
		  //out
			c = cpu->reg[0];
			printf("%c", c);
			break;
	case 0x22 :
		 //puts
		  i = cpu->reg[0];
			while(cpu->memory[i]){			
			  printf("%c" , cpu->memory[i]);
				i++;
			}
			break;
	case 0x23 :
	  //in
		  i = cpu->reg[0];
			while(cpu->memory[i]){			
			  printf("%c" , cpu->memory[i]);
				i++;
			}
			printf(">");
			c = read_char();
			cpu->reg[0]&=0;	
			cpu->reg[0]=c;
			printf(" %c\n", c);
			break;
       
	case 0x25:
	  //HALT
			cpu->running =0;
			printf("HALT!\n");
			break;
		default:
			printf("ERROR!!\n");
			break;
}
}

									
			
			
			
			



 


// Read and return a character from standard input.  User must
// enter return after the char.  Just pressing return causes '\n'
// to be returned.  Any extra characters after the first are ignored.
//
char read_char() {
	char buffer[3] = "";
	fgets(buffer, sizeof buffer, stdin);
	return buffer[0];
}

//the help message that pops up when the user decides to select h
void helpMsg(void){
	printf("Commands:\n ");
	printf("h - Help \n");
	printf("q - Quit \n");
	printf("d - Dump control unit) \n");
	printf("m xNNNN xNNNN - Dump memory values from/to\n");
	printf("nbr - execute nbr of instructions\n");
	printf("(carriage return) - execute one instruction\n");
}

//dumping the memory
void dump_memory(CPU *cpu, Address from, Address to){
 Address i;
 if (from<to && from>-1){
 for (i=from; i<=to;i++){
   printf(" x%04x: x%04x   %d\n", i, (Address)cpu->memory[i], (Address)cpu->memory[i]);
	   }
 }
 else{
   printf("ERROR!!!\n");
 }
}
//dumping the registers
void dump_register(CPU *cpu){
 
  int i=0;
  int r;//number of rows
  int c;//number of colums
  for (r=0; r<2; r++){
    for (c=0; c<5; c++){
      printf("R%d: x%04x %d\t", i, cpu->reg[i], cpu->reg[i]);
      i++;
    }
  }
  printf("\n");
}

void dump_control_unit(CPU *cpu){
  printf("PC = x%x\tIR = x%x\tCC = %d\n", cpu->pgm_counter, cpu->instr_reg, cpu->condition_code); 
  dump_register(cpu);
}


	
 
	

/* *** STUB *** */
