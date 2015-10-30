; CS 350, J. Sasaki, Illinois Institute of Technology
;
; power.asm
;
; Calculate 2^N where N >= 0 (and ^ means exponentiation).
; If N is too large, this calculation overflows.
;
; Properties of values:
;   0 ≤ x ≤ N and p * 2^x = 2^N  (These hold every time
;   we hit the loop test.)
;
; Register usage:
;   R... = p; R... = x (specify whichever registers you decide to use)
;
; Pseudocode:
;   p <- 1   ; Establish x and p initially
;   x <- N
; Loop  while x ≠ 0 do
;          p <- p + p
;          x <- x - 1
;   end Loop
;   result <- p
;   HALT
; N    .FILL  a value ≥ 0
; result .BLKW 1

        	.Orig x3000
		AND R2 R2 0; p=0
		ADD R2 R2 1; p=1
		LD R3 N

		myloop

		BRZ endofloop
		ADD R2 R2 R2';
		ADD R3 R3 -1;
		BR myloop
		endofloop

		ST R2 Result
		HALT

N .Fill 5 
Result .BLKW 1   ; gets set =2*n
        .END
