///Raman Walwyn-Venugopal CS 350 section -1
//

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
	printf("CS 350 Lab 11, Raman Walwyn-Venugopal\n");
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
	int commands_done=0;
	while (!commands_done) {
	  printf("%s", prompt);
	  fgets(command, sizeof command, stdin);   // Read through end of curren\
t line.                                                                                
  //nbr_read = sscanf(command, "%c", &cmd_char);                         


  if (strcmp(command,"h\n") == 0 || strcmp(command,"?\n")==0){
    helpMsg();
  }
  else if (strcmp(command, "d\n")==0){
    dumpControlUnit(cpu);
    dumpMemory(cpu);
  }
  else if (strcmp(command,"q\n")==0){
    commands_done=1;
  }
  else if (isdigit(command[0])){
    int cycles=atoi(command);
    int d;
    for (d=0;d<cycles;d++){
      instruction_cycle(cpu);

    }
  }
  else if(strcmp(command, "\n")==0){
    instruction_cycle(cpu);
  }
  else{
    printf("Error! Please enter an appropiate value or h for help\n");

  }
        }

        dumpControlUnit(cpu);
        dumpMemory(cpu);
        printf("GOODBYE!\n");
}

 //printf("%s", prompt);
	  //	fgets(command, sizeof command, stdin);   // Read through end of current line.
	  //	nbr_read = sscanf(command, "%c", &cmd_char);

	  //	if (nbr_read > 0) {
	  //		printf("*** STUB *** read in %c command or digit\n");
	  //	}
	  //	else {
	  //		printf("*** STUB *** read in empty line\n");
	  //	}
		// *** STUB look at cmd_char and process it? Or carriage return
	  //	}
	
	// When we see the quit command, dump the control unit and memory
	// and quit
	//
	  //	printf("*** STUB *** quitting'n");


// Print out the instruction set architecture for the SDC.
//
void helpMsg(void) {
  printf("Simulator Commands:\n");
  printf("h or ? for help (prints this message)\n");
  printf("d to dump the control unit\n");
  printf("An integer >0 to execute that many instruction cycles\nOr just return,\
 which executes one instruction cycle\n");

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

	int num=0;
	while (num<=9999 && num>=-9999 && loc < 100){//checking to see if number is out of range
          printf("\nLoc %d: ",loc);
          // fgets(line,MEMLEN, stdin);                                                
          scanf("%d", &num);
          if (num<=9999 && num>=-9999){
	    cpu->mem[loc]=num;
          }
          loc++;
        }



// *** You might need this after reading the sentinel ***
//	fgets(skip, sizeof skip, stdin);   // Clear the \n at end of terminating line

	printf("\nInitial value of memory:\n");
	dumpMemory(cpu);
	char gar[100];
	fgets(gar, sizeof gar, stdin);
}




// dumpControlUnit(cpu): Dump the control unit (pc, ir, and data registers).
//
void dumpControlUnit(CPU *cpu) {
	// *** STUB *** Hint 2: use cpu->reg[r] to access register number r
  printf("PC: %d\tIR: %5d\n:", cpu->pc, cpu->ir);
	dumpRegisters(cpu);
}

// dumpRegisters(cpu): Print register values in two rows of five.
//
void dumpRegisters(CPU *cpu) {
  int i=0;
  int r;
  int c;
  for(r=0; r<2; r++) {
    printf("\n");
    for(c=0; c<5; c++) {
      printf("R%d: %d \t",i, cpu->reg[i] );
      i++;
    }
  }
  printf("\n");

}

// dumpMemory(cpu): Print memory values in a table, ten per row,
// with a space between each group of five columns and with a header
// column of memory locations.
//
void dumpMemory(CPU *cpu) {
	// *** STUB *** Hint: use cpu->mem[m] to access memory location m
  int i=0;
  int r;
  int c;
  for(r=0; r<10; r++) {
    printf("\n");
    printf("%d0\t", r);
    for(c=0; c<10; c++) {
      if (cpu->mem[i]==0){
        printf("0000\t");
      }
      else{
        printf("%4d\t",cpu->mem[i] );
      }
      i++;
    }
  }
  printf("\n");
}


// Execute one instruction cycle.
//
void instruction_cycle(CPU *cpu) {
	// *** STUB *** Hint: Use cpu->pc, cpu->ir, cpu->running and so on.
	//printf("*** STUB *** instruction_cycle\n");

	// if pc is out of range, complain and halt machine, otherwise
	// set ir to instruction at pc, increment pc
	// if ir < 0 ....
	// get opcode, register, and address fields of ir
	// switch on opcode%, case for each opcode ...
	cpu->running=1;
	if (cpu->pc>100){
	  printf("HALT!!\n");
	  cpu->running=0;
	}
	if (cpu->running){
	  //     printf("%d pc\n", pc);                                                      
	  cpu->ir=cpu->mem[cpu->pc];
	  // printf("%d ir\n", ir);                                                          
	  char abc[100];
	  char a;
	  int str;
	  int mod;
	  int R;
	  int MM;
	  int op=cpu->ir/1000;//recognizes the opcode that the user entered
	  // printf("%d op \n", op);            OB                                             
	  if ((op<0 )){
	    op= op*-1;
	  }
	  //printf("going to perform %d case\n", op);                                        
	  if (op!=0){
	    switch (op){
	      //These are the different sets of cases that the user can select while operating the sdc
	    case 1:
	      //      printf("performing case 1\n");                                         
	      mod=cpu->mem[cpu->pc]%1000;
	      R=mod/100;   //register
	      MM=mod%100;// memory location
	      printf("As %d instr %d: LD R%d <-M[%d]=%d\n", cpu->pc, cpu->ir, R, MM, cpu->mem[MM]);
	      cpu->reg[R]=cpu->mem[MM];
	      cpu->pc++;
	      break;
	    case 2:
	      mod=cpu->mem[cpu->pc]%1000;
	      R=mod/100;
	      MM=mod%100;
	      printf("As %d instr %d: ST M[%d] <-R%d =%d\n", cpu->pc, cpu->ir, MM, R, cpu->reg[R]);
	      cpu->mem[MM]=cpu->reg[R];
	      cpu->pc++;
	      break;
	      break;
	    case 3:
	      mod=cpu->mem[cpu->pc]%1000;
	      R=mod/100;
	      MM=mod%100;
	      str=cpu->reg[R]+cpu->mem[MM];
	      str=str%10000;
	      printf("As %d instr %d: ADD R%d <-R%d + M[%d]=%d+%d=%d\n", cpu->pc, cpu->ir, R,R, MM,cpu->reg[R], cpu->mem[MM],str);
	      cpu->reg[R]=str;
	      cpu->pc++;
	      break;
	    case 4:
	      mod=cpu->mem[cpu->pc]%1000;
	      R=mod/100;
	      printf("As %d instr %d: NEG R%d <- -(R%d)= -%d\n", cpu->pc, cpu->ir, R, R, cpu->reg[R]);
	      cpu->reg[R]=cpu->reg[R]*-1;
	      cpu->pc++;
	      break;
	    case 5:
	    case -5:
	      mod=cpu->mem[cpu->pc]%1000;
	      R=mod/100;
	      MM=mod%100;
	      if (cpu->ir<0){
		R=R*-1;
	      }
	      printf("As %d instr %d: LDM R%d <-%d\n",cpu->pc, cpu->ir, R, MM);
	      cpu->reg[R]=MM;
	      cpu->pc++;
	      break;
	    case 6:
	    case -6:
	      mod=cpu->mem[cpu->pc]%1000;
	      R=mod/100;
	      MM=mod%100;
	      if (cpu->ir<0){
		R=R*-1;
	      }
	      str=cpu->reg[R]+MM;
	      printf("As %d instr %d: ADDM R%d <-R%d + %d = %d +%d = %d \n", cpu->pc,cpu->ir, R,R, MM\
		     , cpu->reg[R], MM, str%10000);
	      cpu->reg[R]=str%10000;
	      cpu->pc++;
	      break;
	    case 7:
	      mod=cpu->mem[cpu->pc]%1000;
	      R=mod/100;
	      MM=mod%100;
	      printf("As %d instr %d: BR %d \n", cpu->pc, cpu->ir, MM);
	      cpu->pc=MM;
	      break;
	    case 8:
	      mod=cpu->mem[cpu->pc]%1000;
	      R=mod/100;
	      MM=mod%100;
	      if (cpu->reg[R]>0){
		cpu->pc=MM;
		printf("As %d instr %d: BRP %d if R%d = %d>0 : Yes\n", cpu->pc, cpu->ir, MM, R, cpu->reg[R]);
		break;
	      case 9:
		str;
		mod=cpu->mem[cpu->pc]%1000;
		R=mod/100;
		MM=mod%100;
		if (R==0){
		  printf("As %d instr %d: I/O Read Char \n", cpu->pc,cpu->ir );
		  printf("Enter a char (and press return): ");
		  scanf("%c", &a );
		  str=(int)a;
		  printf("\nR0 <- %d\n",str);
		  cpu->reg[0]=str;
		  cpu->pc++;
		}
		else if (R==1){
		  printf("As %d instr %d: I/O 1 Print Char in R0 (%d):", cpu->pc, cpu->ir, cpu->reg[0]);
		  a=(char)cpu->reg[0];
		  printf("%c\n" ,a);
		  cpu->pc++;
		}
		else if (R==2){
		  printf("\nAs %d instr %d: I/O 2 %d", cpu->pc, cpu->ir, cpu->reg[0]);
		  printf("Print string: ");
		  while(cpu->mem[MM]!=0){
		    a=(char)cpu->mem[MM];
		    printf("%c", a);
		    MM++;
		  }
		  printf("\n");
		  cpu->pc++;
		}
		else if (R==3){
		  printf("As %d instr %d: Dump Control Unit", cpu->pc, cpu->ir);
		  dumpControlUnit(cpu);
 		  cpu->pc++;
		}
		else if (R==4){
		  printf("As %d instr %d: Dump Memory", cpu->pc, cpu->ir);
		  dumpMemory(cpu);
		  cpu->pc++;
		}
		else{
		  printf("Inappropiate command\n");
		  cpu->pc++;
		}
		break;
	      }
	    }
	  }
	    else{
	      printf("HALT!!\n");
	      cpu->running=0;
	    }
	  }
	  //     printf("At %d instr %d:");                                                     
	  // if pc is out of range, complain and halt machine, otherwise                 
	  // set ir to instruction at pc, increment pc                                   
	  // if ir < 0 ....                                                              
	  // get opcode, register, and address fields of ir                              
	  // echo instruction                                                            
	  // switch on opcode, case for each opcode ...                                  


	return;
}
