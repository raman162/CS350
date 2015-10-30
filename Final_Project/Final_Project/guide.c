
1
2
3
4
5
6
7
8
9
10
11
12
13
14
15
16
17
18
19
20
21
22
23
24
25
26
27
28
29
30
31
32
33
34
35
36
37
38
39
40
41
42
43
44
45
46
47
48
49
50
51
52
53
54
55
56
57
58
59
60
61
62
63
64
65
66
67
68
69
70
71
72
73
74
75
76
77
78
79
80
81
82
83
84
85
86
87
88
89
90
91
92
93
94
95
96
97
98
99
100
101
102
103
104
105
106
107
108
109
110
111
112
113
114
115
116
117
118
119
120
121
122
123
124
125
126
127
128
129
130
131
132
133
134
135
136
137
138
139
140
141
142
143
144
145
146
147
148
149
150
151
152
153
154
155
156
157
158
159
160
161
162
163
164
165
166
167
168
169
170
171
172
173
174
175
176
177
178
179
180
181
182
183
184
185
186
187
188
189
190
191
192
193
194
195
196
197
198
199
200
201
202
203
204
205
206
207
208
209
210
211
212
213
214
215
216
217
218
219
220
221
222
223
224
225
226
227
228
229
230
231
232
233
234
235
236
237
238
239
240
241
242
243
244
245
246
247
248
249
250
251
252
253
254
255
256
257
258
259
260
261
262
263
264
265
266
267
268
269
270
271
272
273
274
275
276
277
278
279
280
281
282
283
284
285
286
287
288
289
290
291
292
293
294
295
296
297
298
299
300
301
302
303
304
305
306
307
308
309
310
311
312
313
314
315
316
317
318
319
320
321
322
323
324
325
326
327
328
329
330
331
332
333
334
335
336
337
338
339
340
341
342
343
344
345
346
347
348
349
350
351
352
353
354
355
356
357
358
359
360
361
362
363
364
365
366
367
368
369
370
371
372
373
374
375
376
377
378
379
380
381
382
383
384
385
386
387
388
389
390
391
392
393
394
395
396
397
398
399
400
401
402
403
404
405
406
407
408
409
410
411
412
413
414
415
416
417
418
419
420
421
422
423
424
425
426
427
428
429
430
431
432
433
434
435
436
437
438
439
440
441
442
443
444
445
446
447
448
449
450
451
452
453
454
455
456
457
458
459
460
461
462
463
464
465
466
467
468
469
470
471
472
473
474
475
476
477
478
479
480
481
482
483
484
485
486
487
488
489
490
491
492
493
494
495
496
497
498
499
500
501
502
503
504
505
506
507
508
509
510
511
512
513
514
515
516
517
518
519
520
521
522
523
524
525
526
527
528
529
530
531
532
533
534
535
536
537
538
539
540
541
542
543
544
545
546
547
548
549
550
551
552
553
554
555
556
557
558
559
560
561
562
563
564
565
566
567
568
569
570
571
572
573
574
575
576
577
578
579
580
581
582
583
584
585
586
587
588
589
590
591
592
593
594
595
596
597
598
599
600
601
602
603
604
605
606
607
608
609
610
611
612
613
614
615
616
617
618
619
620
621
622
623
624
625
626
627
628
629
630
631
632
633
634
635
636
637
638
639
640
641
642
643
644
645
646
647
648
649
650
651
652
653
654
655
656
657
658
659
660
661
662
663


// CS 350, Final Project, Fall 2013 (skeleton file)
// Jamal Kharrat
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
		Word instr_reg;		//CURRENT INSTRUCTION REGISTER :: IMPORTANT
		Address pgm_counter;	//PC Instruction counter
		Word condition_number;
		int running;         // running = 1 iff CPU is executing instructions
	} CPU;





// Prototypes
//
	// CPU manipulation and status dump functions
	//
	void init_CPU(CPU *cpu);   // Simulate power-up
	void dump_CPU(CPU *cpu);
	void dump_control_unit(CPU *cpu);
	void dump_memory(CPU *cpu, Address from, Address to, int nonzero_only);
	char get_condition_code(CPU *cpu);
	void set_condition_code(CPU *cpu, Word value);
	void dump_registers(CPU *cpu);
	void set_register(CPU *cpu, int regNbr, Word newValue);
	Word get_register(CPU *cpu, int regNbr);
	Word get_memory(CPU *cpu, Address addr);
    void set_memory(CPU *cpu, Address addr, Word value);
    int bitshift(Word content,int left,int right,int needsign);

	// Instruction cycle functions
	//

	void instruction_cycle(CPU *cpu);      // Simulate entire instruction cycle
	void fetch_instr(CPU *cpu);            // Simulate fetch instruction part of cycle
	// *** STUB *** You may want other routines (you may not)

	// Functions for accessing parts of an instruction
	//
	Word op(Word w);                       // Opcode of an instruction
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
	int  readchar();
	void printInf();             // TRAP reads a character for GETC, IN
	void helpMsg();
	Address readFile (CPU *cpu);	//Reading file 


	int nonzero_only;
	Address _from;
	Address _to;




//Method to read the file and display the contents .....
Address readFile (CPU *cpu)
{
	char fname[100];
        printf("name of file?：");
        scanf("%s",fname);
    FILE *f;
    unsigned int num[80];

    f=fopen(fname,"r");
    while (f==NULL){
            printf("\nfile doesnt exist?!\n");
                        printf("name of file?：");
                        scanf("%s",fname);
             f=fopen(fname,"r");
    }
    unsigned int temp =0;
    fscanf(f,"%x",&temp);
    cpu->pgm_counter = temp;
    int i = temp;
    cpu->memory[i] = temp;
    Address end = 0;
    while (fscanf(f,"%x",&temp) != EOF){
      cpu->memory[i] = temp;
      i++;
      end++;
    }
                end +=cpu->pgm_counter;
    fclose(f);
    end--;
    return end;
	}


//Print infotmation about the Final Project
void printInf()
{
	printf("Jamal Kharrat Full LC-3 simulator\n");
	printf("File to read from:  ");
}







// -------------------- MAIN PROGRAM --------------------
//
// The main program creates and initializes a CPU, loads a program,
// and executes it step by step (until it halts or the user quits).
// The CPU is dumped before and after executing the program
//
int main() {
	// Create and initialize the  CPU, read initial memory, dump CPU
	// CPU cpu_struct, *cpu;
	// cpu = &cpu_struct;


	printInf();
	  CPU cpu;
  init_CPU(&cpu);
  Address end =  readfile(&cpu);
  Address origin  = cpu.pgm_counter;
        printf("origin = %x ; end = %x \n",origin,end);
        printf("\nRegisters:\n");
        dump_registers(&cpu);

        printf("\nMemory:\n");
        dump_memory(&cpu,cpu.pgm_counter,end,0);
  
        printf("\nBeginning execution:\n");
        printf("At the > prompt, press return to execute the next instruction (or q to quit or h or ? for help).\n");
        char prompt[] = "> ";
        char command[80];
        fgets(command, sizeof command, stdin);        
        while(cpu.running==1){
                printf("%s", prompt);
                fgets(command, sizeof command, stdin);                // Read past end of current line.
         
               char op = command[0];                
                          unsigned int from=0;
                                unsigned int too = 0;
                switch(op){
                        case 'q':
                                cpu.running = 0;
                                break;                
                        case 'h':
                                helpMsg();
                                break;
                        case '?':
                                helpMsg();
                                break;
                        case 'r':
                                printf("\nRegisters:\n");
                                dump_registers(&cpu);
                                break;
                        case 'd':
                          sscanf(command,"m %x %x",&from,&too);
                          dump_memory(&cpu,(Address)from,(Address)too,1);
                          break;
                        default:
                          instruction_cycle(&cpu);
                          break;
                }
        }
/*
                if(command[0] == 'q'){
                        c.running = 0;
                }else if(command[0] == 'h'||command[0]=='?'){
                        helpMsg();
                }else{
                        c.running=instruction_cycle(&c);
                }
*/


        
        

        printf("\nRegisters:\n");
        dump_registers(&cpu);

        printf("\nMemory:\n");
        dump_memory(&cpu,origin,end,1);
        printf("\nAll done!\n");
}



// -------------------- CPU ROUTINES --------------------
//
//



void helpMsg(void)
{
    printf("Commands:\n");
    printf("\th - Help\n");
    printf("\tq - Quit\n");
    printf("\tr - Dump registers\n");
    printf("\tm - mem hex_n1 hex_n2 - Dump memory values from hex_n1 - hex_n2\n");
    printf("\tnbr - execute nbr of instructions\n");
    printf("\t(carriage return) - execute one instruction if CPU is running.\n");
  
}







// init_CPU(cpu) simulates power-on initialization: Program counter
// and instruction register are set to 0, as are memory and registers;
// condition code = Z, and the CPU will run the instruction cycle.
//
void init_CPU(CPU *cpu)
{
    cpu->pgm_counter = 0;
	cpu->instr_reg = 0;
	cpu->condition_code = 0;   // Z condition code on power-up
	cpu->running = 1;                // instruction cycle is running

	int regNbr;
	for (regNbr = 0; regNbr < NBR_REGS; regNbr++) {
		cpu->reg[regNbr] = 0;	// Fixed 2013-11-13
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
		cpu->memory[addr++] = 0;
	}
}


void set_register(CPU *cpu, int regNbr, Word newValue)
{
cpu->reg[regNbr] = newValue;    
}


Word get_register(CPU *cpu, int regNbr)
{
    return cpu->reg[regNbr];
  }



char get_condition_code(CPU *cpu)
{
    return cpu->condition_code;
 }


 void set_condition_code(CPU *cpu, Word value){
                cpu->condition_number = value;
                Word condition = 0;
                if(value>0){
                        condition =1;
                }
                if(value==0){
                        condition = condition|2;
                }
                if(value<0){
                        condition = condition|4;
                }
        cpu->condition_code = condition;
        }

// -------------------- INSTRUCTION ROUTINES --------------------

// Fetch instruction:
//   Copy instruction pointed to by program counter to instruction register
//   Increment program counter (wraparound addresses).
//
void fetch_instr(CPU *cpu) {
	cpu->instr_reg = cpu->memory[cpu->pgm_counter];
	cpu->pgm_counter = cpu->pgm_counter + 1;		// unsigned overflow will wraparound to 0
}

// Execute an instruction cycle
//   Fetch an instruction
//   Decode the instruction opcode
//   Execute the instruction
//
void instruction_cycle(CPU *cpu) {
	// Get current instruction to execute and its loc,
	// echo them out.
	//
	Address old_pc = cpu->pgm_counter;
	fetch_instr(cpu);
	printf("x%04hX: x%04hX  ", old_pc, cpu->instr_reg);

	// Execute instruction; set cpu running = 0 if CPU execution
	// is to stop (because of TRAP HALT or an internal error).
	//

	//>>>>>>>>>>>>>>>>SWITCH CASE MUST BE EDITED  Compliar error
	switch (cpu->instr_reg) {
	case  0: instr_BR(cpu);   break;
    case  1: instr_ADD(cpu);   break;
    case  2: instr_LD(cpu);   break;
    case  3: instr_ST(cpu);   break;
    case  4: instr_JSR(cpu);   break;
    case  5: instr_AND(cpu);   break;
    case  6: instr_LDR(cpu);   break;
    case  7: instr_STR(cpu);   break;
    case  8: instr_RTI(cpu);   break;
    case  9: instr_NOT(cpu);   break;
    case  10: instr_LDI(cpu);   break;
    case  11: instr_STI(cpu);   break;
    case  12: instr_RTI(cpu);   break;
    case  13: instr_STI(cpu);   break;
    case  14: instr_LEA(cpu);   break;
	case  15: instr_TRAP(cpu);   break;
    default: printf("Bad opcode: %d; quitting\n", op(cpu->instr_reg)); cpu->running = 0; break;
        }
}

// Execute branch instruction: Bitwise AND instruction's mask and
// cpu's condition code, branch iff result is nonzero.
//
// Echo kind of branch, current cc, whether or not the branch happened,
// and if so, the target of the branch.
//



        void instr_ADD (CPU *cpu)        {
                int type = bitshift(cpu->instr_reg,5,5,0);
                int dst = bitshift(cpu->instr_reg,11,9,0);
                int src1 = bitshift(cpu->instr_reg,8,6,0);
                if(type==0){
                        int src2 = bitshift(cpu->instr_reg,2,0,0);
                        cpu->reg[dst] = cpu->reg[src1]+cpu->reg[src2];
                        printf("ADD  R%d R%d 0 R%d;reg[%d] = %x+%x = %x\n",dst,src1,src2,dst,cpu->reg[src1],cpu->reg[src2],cpu->reg[src1]+cpu->reg[src2]);
                }else{
                        int imm5 =bitshift(cpu->instr_reg,4,0,1);
                        cpu->reg[dst] = cpu->reg[src1]+imm5;
                        printf("ADD R%d R%d 1 %d; reg[%d] = %x +%x\n",dst,src1,imm5,dst,cpu->reg[src1],imm5,cpu->reg[src1]+imm5);
                }
                set_condition_code(cpu,cpu->reg[dst]);
        }
  void instr_AND (CPU *cpu) {
                int type = bitshift(cpu->instr_reg,5,5,0);
                int dst = bitshift(cpu->instr_reg,11,9,0);
                int src1 = bitshift(cpu->instr_reg,8,6,0);
                if(type==1){
                        int src2 = bitshift(cpu->instr_reg,2,0,0);
                        cpu->reg[dst] = cpu->reg[src1]&cpu->reg[src2];
                        printf("AND R%d R%d 0 R%d; reg[%x]<-reg[%x]&&reg[%x] = %x\n",dst,src1,src2,dst,src1,src2,cpu->reg[src1]&cpu->reg[src2]);
                }else{
                        int imm5 =bitshift(cpu->instr_reg,4,0,0);
                        cpu->reg[dst] = cpu->reg[src1]&imm5;
                        printf("AND R%d R%d 1 %x;  reg[%x]<-reg[%x]&&%x = %x\n",dst,src1,imm5,dst,src1,imm5,cpu->reg[src1]&imm5);
                }
                set_condition_code(cpu,cpu->reg[dst]);
        }
        void instr_BR  (CPU *cpu)        {
                int mask = bitshift(cpu->instr_reg,11,9,0);
                char maskcode[30];
                switch(mask){
                        case 0 :
                                strcpy(maskcode,"NOP");

                                break;
                        case 1 :
                                strcpy(maskcode,"NOP");

                                break;
                        case 2 :
                                strcpy(maskcode,"Z '=0'");

                                break;
                        case 3 :
                                strcpy(maskcode,"PZ '>=0'");

                                break;
                        case 4 :
                                strcpy(maskcode,"N '<0'");

                                break;
                        case 5 :
                                strcpy(maskcode,"NP '!=0'");

                                break;
                        case 6 :
                                strcpy(maskcode,"NZ '<=0'");

                                break;
                        case 7 :
                                strcpy(maskcode,"BR 'unconditional'");

                                break;
                }
                int pcoffset = bitshift(cpu->instr_reg,8,0,1);
                if(mask&get_condition_code(cpu)!=0){
                        int oldcounter = cpu->pgm_counter;
                        cpu->pgm_counter += pcoffset;
                        printf("BR number:%d %s ;condition satisify! New pgm_counter = %x + %x = %x\n",cpu->condition_number,maskcode,oldcounter,pcoffset,cpu->pgm_counter);
                }else{                
                        printf("BR number:%d %s ;condition NOT satisify!\n",cpu->condition_number,maskcode);
                }
        }
        void instr_err (CPU *cpu)     

           {
            printf("Im working..");
        }
        void instr_JMP (CPU *cpu)        
        {
                int base = bitshift(cpu->instr_reg,8,6,0);
                cpu->pgm_counter = cpu->reg[base];
                printf("JMP New pgm_counter = reg[%d] = %x\n",base,cpu->reg[base]);
        }
        void instr_JSR (CPU *cpu)        
        {
            printf("Im working..");
        }
        void instr_LD  (CPU *cpu)        {
                int dst = bitshift(cpu->instr_reg,11,9,0);
                int pcoffset = bitshift(cpu->instr_reg,8,0,1);
                cpu->reg[dst] = cpu->memory[cpu->pgm_counter+pcoffset];
                printf("LD R%d %d ; reg[%x]<- memory[%x] = %x ,\n",dst,pcoffset,dst,cpu->pgm_counter+pcoffset,cpu->memory[cpu->pgm_counter+pcoffset]);
                set_condition_code(cpu,cpu->reg[dst]);
        }
        void instr_LDI (CPU *cpu)    
            {
                int dst = bitshift(cpu->instr_reg,11,9,0);
                int pcoffset = (int)bitshift(cpu->instr_reg,8,0,1);
                cpu->reg[dst] = cpu->memory[cpu->memory[pcoffset+cpu->pgm_counter]];
                printf("LDI R%d %x %x ; reg[%x] <- memory[memory[%x+%x]] = %x \n",dst,pcoffset,cpu->pgm_counter,dst,pcoffset,cpu->pgm_counter,cpu->memory[cpu->memory[pcoffset+cpu->pgm_counter]]);
                set_condition_code(cpu,cpu->reg[dst]);
        }
        void instr_LDR (CPU *cpu)    
            {
                int dst = bitshift(cpu->instr_reg,11,9,0);
                int base = bitshift(cpu->instr_reg,8,6,0);
                int offset = (int)bitshift(cpu->instr_reg,5,0,1);
                cpu->reg[dst] = cpu->memory[cpu->reg[base]+offset];
                printf("LDR R%d %x %x ; reg[%x] <-memory[reg[%x]+%x] = %x\n",dst,base,offset,dst,base,offset,cpu->memory[cpu->reg[base]+offset]);
                set_condition_code(cpu,cpu->reg[dst]);
        }
        void instr_LEA (CPU *cpu)    
            {
                int dst = bitshift(cpu->instr_reg,11,9,0);                
                int pcoffset = (int)bitshift(cpu->instr_reg,8,0,1);
                cpu->reg[dst] = cpu->pgm_counter+pcoffset;
                printf("LEA R%d %x %x ; Reg[%x] <- %x + %x = %x \n",dst,cpu->pgm_counter,pcoffset,dst,cpu->pgm_counter,pcoffset,cpu->pgm_counter+pcoffset);
                set_condition_code(cpu,cpu->reg[dst]);
        }
        void instr_NOT (CPU *cpu)  
              {
                int dst = bitshift(cpu->instr_reg,11,9,0);
                int src = bitshift(cpu->instr_reg,8,6,0);
                cpu->reg[dst] = ~cpu->reg[src];
                printf("NOT R%d R%d ; reg[%x]<-~reg[%x] = \n",dst,src,dst,src,~cpu->reg[src]);
                set_condition_code(cpu,cpu->reg[dst]);
        }
        void instr_RTI (CPU *cpu)        
        {
            printf("Im working..");
        }
        void instr_ST  (CPU *cpu)        {
                int src = bitshift(cpu->instr_reg,11,9,0);
                int pcoffset = bitshift(cpu->instr_reg,8,0,1);
                cpu->memory[cpu->pgm_counter+pcoffset] = cpu->reg[src];

                printf("ST R%d %x %x ; memory[%x] <-reg[%x] = %x,\n",src,cpu->pgm_counter,pcoffset,src,cpu->pgm_counter+pcoffset,cpu->reg[src]);
        }
        void instr_STI (CPU *cpu)        {
                int src = bitshift(cpu->instr_reg,11,9,0);
                int pcoffset = bitshift(cpu->instr_reg,8,0,1);
                cpu->memory[cpu->memory[pcoffset+cpu->pgm_counter]] = cpu->reg[src];
                printf("STI R%d %x ; memory[memory[%x+%x]]<-reg[%x] = %x \n",src,pcoffset,cpu->pgm_counter,pcoffset,src,cpu->reg[src]);
        }
        void instr_STR (CPU *cpu)        {
                int dst = bitshift(cpu->instr_reg,11,9,0);
                int base = bitshift(cpu->instr_reg,8,6,0);
                int offset = bitshift(cpu->instr_reg,5,0,1);
                cpu->memory[base+offset] = cpu->reg[dst];
                printf("STR R%d R%d %x ; memory[%x+%x] = reg[%x]= %x\n",dst,base,offset,offset,cpu->pgm_counter,dst,cpu->reg[dst]);
        }
        void instr_TRAP(CPU *cpu)        {
                int vectors = bitshift(cpu->instr_reg,7,0,0);
                Word pointer;
                char temp;
                switch(vectors){
                        case 32:
                                printf("input a char:");
                                scanf("%c",&temp);
                                cpu->reg[0] = cpu->reg[0]&0;
                                cpu->reg[0] =temp;
                    printf("read a char '%c'\n",temp);
                                break;
                        case 33:
                                temp = cpu->reg[0];
                                printf("%c",temp);
                                break;
                        case 34:

                                pointer = cpu->reg[0];
                                while(cpu->memory[pointer]){
                                        printf("%c",cpu->memory[pointer]);
                                        pointer++;
                                }
                                break;
                        case 35:
                                printf("Input a char:");
                                scanf("%c",&temp);
                                cpu->reg[0] = cpu->reg[0]&0;
                                cpu->reg[0] =temp;
                    printf("read a char '%c'\n",temp);
                                break;
                        case 37:
                                cpu->running = 0;
                                break;
                }
                printf("\n");
        }




        Word op(Word opcode)
        {
        Word op = opcode>>12;
  		return op;
		}





/* *** STUB *** */


// Read and return a character from standard input.  User must
// enter return after the char.  Just pressing return causes '\n'
// to be returned.  Any extra characters after the first are ignored.
//
int read_char() {
	char buffer[3] = "";
	fgets(buffer, sizeof buffer, stdin);
	return buffer[0];
}

void dump_memory(CPU *cpu, Address from, Address to, int nonzero_only)
{
if(nonzero_only==1){
      Address i;
      for(i=from;i<=to;i++){
                                if(cpu->memory[i]!=0){
                                  printf("  x%04hX: x%04hX\n", i, cpu->memory[i]);
                                }
      }
    }else{
      Address i ;
      for(i=from;i<=to;i++){
                          printf("  x%04hX: x%04hX\n", i, cpu->memory[i]);
      }
    }
  }



 // void helpMsg(void){
 //        printf("Commands:\n");        
 //        printf("  h - Help\n");        
 //        printf("  q - Quit\n");        
 //        printf("  r - Dump registers\n");        
 //        printf("  m hex_n1 hex_n2 - Dump memory values from hex_n1 - hex_n2\n");        
 //        printf("(carriage return) - execute one instruction if CPU is running.\n");        
 //        }

        int bitshift(Word content,int left,int right,int needsign){
                int mask = (1<<left+1)-1;
                int result = content&mask;
                result = result >>right;
                if(needsign==1){
                                if(result&(1<<(right-left))!=0){
                                result=result-power2(left-right+1);                        
                                printf("negative number!");
                                }
                }
                return result;
}
int power2(int point){
  int i;
  long result = 1;
  for(i =0;i<point;i++){
    result = result*2;
  }
  return result;
}


void dump_registers(CPU *cpu)
{
    printf("PC = x%04d   IR = x%04d   CC = Z\n", cpu->reg[0], cpu->instr_reg);
	int i, j, loc = 0;
    for(i = 0; i < 4; i++)
    {
        printf("R%d ", loc);
        loc++;
        printf("x%04hu  %d       ", cpu->reg[i], cpu->instr_reg);
    }
    printf("\n");
    //second row 6 - 10
    for(j = 0; j < 4; j++)
    {
        printf("R%d ", loc);
        loc++;
        printf("x%04hu  %d       ", cpu->reg[i], cpu->instr_reg);
        i++;
    }
    printf("\n");
    
}
