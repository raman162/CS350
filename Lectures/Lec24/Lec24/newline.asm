; CS 350, Spring 2014
;
; newline.asm: Sample subroutine that prints a newline
;
; Illinois Institute of Technology, (c) 2013, James Sasaki

; The main program exercises the NewLine subroutine to make
; sure it actually prints out a newline.
;
          .ORIG     x3000
           LEA      R0, string1   ; print first message
           PUTS
           JSR      NewLine       ; print newline
; Alternate version for long jump to subroutine:
;           LD       R2, NLptr     ; Pt R2 to NewLine subr
;           JSRR     R2            ; print newline

           LEA      R0, string2   ; print second message
           PUTS
           JSR      NewLine       ; print newline

           PUTS                   ; reprint second message
           JSR      NewLine       ; print newline
           HALT

string1   .STRINGZ  "Hello,"
string2   .STRINGZ  "world"

; For alternate version:
;NLptr    .FILL     NewLine      ; &NewLine subroutine
;         .BLKW     2000

; NewLine: subroutine to print a newline character.
; Uses/restores R0.
;
NewLine    ST       R0, NLsave0  ; Save R0
           ST       R7, NLsave7  ; Save R7
           LD       R0, NLchar   ; Get newline into R0
           OUT                   ; and print it
           LD       R7, NLsave7  ; Restore R7
           LD       R0, NLsave0  ; Restore R0
           RET                   ; ... and return

NLchar    .FILL     x0A          ; ASCII newline char

; Save area for registers
NLsave0   .BLKW     1            ; Save area for R0
NLsave7   .BLKW     1            ; Save area for R7
          .END
