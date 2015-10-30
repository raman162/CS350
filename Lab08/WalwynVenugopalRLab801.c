
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
    void dumpControlUnit(int pc, int ir,  int regs[]);
    void dumpRegisters(int regs[]);
    void dumpMemory(int mem[]);
void instruction_cycle(void);

// CPU declarations -- note we're being horrible and using global variables; after we
// see structures and pointers, we'll clean things up.
//
#define NBR_REGS 10
#define MEMLEN 100
    int running=1;          // true iff instruction cycle is active
	int regs[NBR_REGS];   // general-purpose registers
	int mem[MEMLEN];      // main memory
int pc;
int ir;
// Main program: Initialize the cpu, read initial memory values,
// and execute the read-in program starting at location 00.
//
int main(void) {
	printf("CS 350 Lab 8, Raman Walwyn-Venugopal\n");
	initCPU();
	readMemory();
	char prompt[]="> ";
	printf("\nBeginning execution:\n");
	printf("At the %sprompt, press return to execute the next instruction\n", prompt);
	printf("(or d to dump registers and memory, q to quit, or h or ? for help)\n");

	char command[80];       // User inputted command line
	char cmd_char;          // 'q' for quit etc.
	int simulator_quit = 0; // Have we seen simulator quit command?
	int nbr_read;           // Number of items read by sscanf
	int commands_done=0;  
	char c;
	while (!commands_done) {
		printf("%s", prompt);
		fgets(command, sizeof command, stdin);   // Read through end of current line.
		//nbr_read = sscanf(command, "%c", &cmd_char); 

		
		if (strcmp(command,"h\n") == 0 || strcmp(command,"?\n")==0){
		    helpMsg();
		  }
		else if (strcmp(command, "d\n")==0){
		    dumpControlUnit(pc, ir, regs);
		    dumpMemory(mem);
		  }
		else if (strcmp(command,"q\n")==0){
		    commands_done=1;
		  }
		  else if (isdigit(command[0])){
		    int cycles=atoi(command);
		    int d;
		    for (d=0;d<cycles;d++){
		      instruction_cycle();
		      
		    }
		  }
		  else if(strcmp(command, "\n")==0){
		    instruction_cycle();
		  }
		  else{
		    printf("Error! Please enter an appropiate value or h for help\n");
		    
		  }
	}
	
	dumpControlUnit(pc, ir, regs);
	dumpMemory(mem);
	printf("GOODBYE!\n");
}

// Print out the instruction set architecture for the SDC.
//
void helpMsg(void) {
	printf("Simulator Commands:\n");
	printf("h or ? for help (prints this message)\n");
	printf("d to dump the control unit\n");
	printf("An integer >0 to execute that many instruction cycles\nOr just return, which executes one instruction cycle\n");

	printf("SDC Instruction set: \n");
	printf(" 0xxx: HALT\n");
	printf(" 1RMM: Load R <- M[MM]\n");
	printf(" 2RMM: Store M[MM]\n");
	printf(" 3RMM: Add M[MM]\n");
	printf(" 4Rxx: Negate R\n");
	printf(" 5RMM: Load Immediate R <- R +MM\n");
	printf(" 6RMM: Add Immediate R <-R +MM\n");
	printf(" 7xMM: Branch to  MM\n");
	printf(" 8RMM: Branch Positive to MM if R\n");
	printf(" 90xx: Read char into R0\n");
	printf(" 91xx: Print char in R0");
	printf(" 92MM: Print string starting at MM\n");
	printf(" 93MM: Dump control unit.\n");
	printf(" 94MM: Dump Memory. \n");
}


// Initialize cpu registers, memory, pc, and ir (all to zeros).
// Initialize the running flag to true.
//
void initCPU(void) {
	printf("Initiliazing cpu registers, memory, pc,\n");
	int i;
	for (i = 0; i < NBR_REGS; i++)
		regs[i] = 0;
	for (i = 0; i < MEMLEN; i++)
		mem[i] = 0;
	running=1;
	pc=0;
	ir=0;
}


// Read and dump initial values for memory
//
void readMemory(void) {
	int loc = 0;
	printf("Read memory: At the prompt, enter the value for the indicated\n");
	printf("memory address.  Enter a number > 9999 or < -9999 when you're done.\n");
	int num=0;
	while (num<=9999 && num>=-9999 && loc < 100){
	  printf("\nLoc %d: ",loc);
	  // fgets(line,MEMLEN, stdin);
	  scanf("%d", &num);
	  if (num<=9999 && num>=-9999){
	  mem[loc]=num;
	  }
	  loc++;
	}
// *** You might need this after reading the sentinel ***
//	fgets(skip, sizeof skip, stdin);   // Clear the \n at end of terminating line
	printf("\nInitial value of memory:\n");
	dumpMemory(mem);
	char gar[100];
	fgets(gar, sizeof gar, stdin);
}



// dumpControlUnit(/*pc,ir,*/regs): Dump the control unit (pc, ir, and data registers).
// 
void dumpControlUnit(int pc,int ir,int regs[]) {
	
  printf("PC: %d\tIR: %5d\n", pc, ir);
	dumpRegisters(regs);
}


// dumpRegisters(regs): Print register values in two rows of five.
//
void dumpRegisters(int regs[]) {
	// *** STUB *** Hint: How do printf formats %d, %5d, %-5d, %05d, and % 05d differ?
  int i=0;                                                                           
  int r;
  int c;
  for(r=0; r<2; r++) {
    printf("\n");
    for(c=0; c<5; c++) {
      printf("R%d: %d \t",i, regs[i] );
      i++;
    }
  }
  printf("\n");
}

// dumpMemory(mem): Print memory values in a table, ten per row,
// with a space between each group of five columns and with a header
// column of memory locations.
//
void dumpMemory(int mem[]) {
  int i=0;
  int r;
  int c;
  for(r=0; r<10; r++) {
    printf("\n");
    printf("%d0\t", r);
    for(c=0; c<10; c++) {
      if (mem[i]==0){
	printf("0000\t");
      }
      else{
	printf("%4d\t",mem[i] );
      }
      i++;
    }
  }

  printf("\n");
}


// Execute one instruction cycle.
//
void instruction_cycle(void) { 
  running=1;
  if (pc>100){
    printf("HALT!!\n");
    running=0;
  }
  if (running){
    //     printf("%d pc\n", pc);
    ir=mem[pc];
    // printf("%d ir\n", ir);
    char abc[100];
    char a;
    int str;
    int mod;
    int R;
    int MM;
    int op=ir/1000;
    // printf("%d op \n", op);
    if ((op<0 )){
	 op= op*-1;
	}
    //printf("going to perform %d case\n", op);
      if (op!=0){
      switch (op){
      case 1:
	printf("performing case 1\n");
	mod=mem[pc]%1000;
	R=mod/100;
	MM=mod%100;
	printf("As %d instr %d: LD R%d <-M[%d]=%d\n", pc, ir, R, MM, mem[MM]);
	regs[R]=mem[MM];
	pc++;
	break;
      case 2:
	mod=mem[pc]%1000;
        R=mod/100;
        MM=mod%100;
	printf("As %d instr %d: ST M[%d] <-R%d =%d\n", pc, ir, MM, R, regs[R]);
	mem[MM]=regs[R];
	pc++;
	break;
      case 3:
	 mod=mem[pc]%1000;
         R=mod/100;
         MM=mod%100;
	printf("As %d instr %d: ADD R%d <-R%d + M[%d]=%d+%d=%d\n", pc, ir, R,R, MM,regs[R], mem[MM],regs[R]+mem[MM]);
	regs[R]=regs[R]+mem[MM];
	pc++;
	break;
      case 4:
	 mod=mem[pc]%1000;
         R=mod/100;
	printf("As %d instr %d: NEG R%d <- -(R%d)= -%d\n", pc, ir, R, R, regs[R]);
        regs[R]=regs[R]*-1;
	pc++;
	break;
      case 5:
      case -5:
	 mod=mem[pc]%1000;
         R=mod/100;
         MM=mod%100;
	 if (ir<0){
	   MM=MM*-1;
	 }
	printf("As %d instr %d: LDM R%d <-%d\n",pc, ir, R, MM);
	regs[R]=MM;
	pc++;
	break;
      case 6:
      case -6:
	 mod=mem[pc]%1000;
         R=mod/100;
         MM=mod%100;
	 if (ir<0){
	   R=R*-1;
	 }
	 str=regs[R]+MM;
	 printf("As %d instr %d: ADDM R%d <-R%d + %d = %d +%d = %d \n", pc,ir, R,R, MM, regs[R], MM, str);
	regs[R]=str;
	pc++;
	break;
      case 7:
	 mod=mem[pc]%1000;
         R=mod/100;
         MM=mod%100;
	printf("As %d instr %d: BR %d \n", pc, ir, MM); 
	pc=MM;
       	break;
      case 8:
	 mod=mem[pc]%1000;
         R=mod/100;
         MM=mod%100;
	if (regs[R]>0){
	  pc=MM;
	  printf("As %d instr %d: BRP %d if R%d = %d>0 : Yes\n", pc, ir, MM, R, regs[R]);
	  break;
	}
	printf("As %d instr %d: BRP %d if R%d = %d>0 : NO\n", pc, ir, MM, R, regs[R]);
	pc++;
	break;
      case 9:
	 str;
	 mod=mem[pc]%1000;
         R=mod/100;
         MM=mod%100;
	if (R==0){
	  printf("As %d instr %d: I/O Read Char \n", pc,ir );
	  printf("Enter a char (and press return): ");
	  scanf("%c", &a );
	  str=(int)a;
	  printf("\nR0 <- %d\n",str); 
	  regs[0]=str;
	  pc++;
	}
	else if (R==1){
	  printf("As %d instr %d: I/O 1 Print Char in R0 (%d):", pc, ir, regs[0]);
	  a=(char)regs[0];
	  printf("%c\n" ,a);
	  pc++;
	}
	else if (R==2){
	  printf("\nAs %d instr %d: I/O 2 %d", pc, ir, regs[0]);
          printf("Print string: ");
	  while(mem[MM]!=0){
	    a=(char)mem[MM];
	    printf("%c", a);
	    MM++;
	  }
	  printf("\n");
	  pc++;
	}
	else if (R==3){
	  printf("As %d instr %d: Dump Control Unit", pc, ir);
	  dumpControlUnit(pc, ir, regs);
	  pc++;
	}
	else if (R==4){
	  printf("As %d instr %d: Dump Memory", pc, ir);
	  dumpMemory(mem);
	  pc++;
	}
	else{
	  printf("Inappropiate command\n");
	  pc++;
	}
	break;
      }
      }
      else{
	printf("HALT!!\n");
	running=0;
      }      
  }
 //	printf("At %d instr %d:");
	// if pc is out of range, complain and halt machine, otherwise
	// set ir to instruction at pc, increment pc
	// if ir < 0 ....
	// get opcode, register, and address fields of ir
	// echo instruction
	// switch on opcode, case for each opcode ...

  return;
  
}



