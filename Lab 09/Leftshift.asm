; CS 350
;
; leftshift.asm
;
; Shift a value in X N amount of places and store the shifted values into another place
;
;
;
	.ORIG x3000
	LD	R2	X	;value to left shift y2 = X
	AND 	R4	R4 0 	;y1=0
	LD 	R5	MASK	;MASK
	LD	R3	N	;x=N (loop count)
	
	myloop
	 BRZ endofloop		;while X(!=0)		
	 AND R4 R2 R5		; Adding left most digit og R0 into R2
	 ADD R2 R2 R2;		; Left shifting values
 	 ADD R3 R3 -1;		; decreasing counter
	 BR myloop		;restarts the loop	
	endofloop		;ends the loop
	
	HALT
	MASK .FILL x8000
	X .FILL xFFFF
	N .FILL 5; Number of times of left shifts
	.END



