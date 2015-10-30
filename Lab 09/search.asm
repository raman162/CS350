; CS 350, J. Sasaki, Illinois Institute of Technology
;
; search.asm
;
; Prompts user to enter a charcter that they search for in a string. It tells the user 
; the number of occurences of that certain character within the string
;
;
; 	.ORIG x3000
	LEA R0 GREET    ;
	IN		;prints greet to user
	OUT		;echoes char back to 
	AND R2 R0 R0	;storing value in register 2
	AND R1 R1 0 	;setting count to 0
	AND R3 R3 0	;
	LEA R0 10
	PUTS		;prints new line
	LEA R0 STR
	PUTS
	myloop 	
	 GETC
	 PUTC
	 LD R7 nlcomp
	 ADD R7 R7 R0
	 BRZ FINISH			

	 STR R0, R3, R1	;storing charachter
	 ADD R1 R1 1;	;incrementing memory location
	 ADD R4 R2 -R0  ;check to see if charachter is equal
	 BRNP AFTERELSE
	  ADD R3 R3 1; incrementing counter if value is equal
	 AFTERELSE 
	BR myloop
	
	FINISH
	LEA R0 COUNT
	PUTS
	ADD R3 R3 48
	LD R0 R3
	PUTS
	HALT
	




	
	GREET: .stringz "Char to search for: "
	STR: .stringz "String to search through: "
	nlcomp .fill xfff6
	COUNT: .stringz "The count was: "
	.END
