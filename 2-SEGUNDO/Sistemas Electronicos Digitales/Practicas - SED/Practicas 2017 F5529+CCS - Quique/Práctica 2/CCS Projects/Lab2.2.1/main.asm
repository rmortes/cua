;-------------------------------------------------------------------------------
; MSP430 Assembler Code Template for use with TI Code Composer Studio
;
;
;-------------------------------------------------------------------------------
            .cdecls C,LIST,"msp430.h"       ; Include device header file
            
;-------------------------------------------------------------------------------
            .def    RESET                   ; Export program entry-point to
                                            ; make it known to linker.
;-------------------------------------------------------------------------------
            .text                           ; Assemble into program memory.
RESET       mov.w   #__STACK_END,SP         ; Initialize stackpointer
StopWDT     mov.w   #WDTPW|WDTHOLD,&WDTCTL  ; Stop watchdog timer

			bis.b	#0x01, &P1DIR			; Direcciono P1.0
			bic.b 	#0x01, &P1OUT			; Activo P1.0
			bic.b 	#0x02, &P2DIR			; Direcciono P2.1 como entrada
			bis.b	#0x02, &P2REN			; Active pull up
			bis.b 	#0x02, &P2OUT			; Activo P2.1

IF			bit.b	#0x02, &P2IN			; Condicional
			jnz IF

Loop 		xor.b #001h,&P1OUT 				; change the value in P1.0
			mov.w #0014Dh,R14 				; initialization of delay counter R15
L2			mov.w #003E8h,R15
L1 			dec.w R15 						; counter decrement
			jnz L1 							; has the counter reached to zero?
 			dec.w R14 						; counter decrement
			jnz L2 							; has the counter reached to zero?
			jmp Loop 						; if yes jump to Loop
;-------------------------------------------------------------------------------
; Stack Pointer definition
;-------------------------------------------------------------------------------
            .sect   .stack 					;default initialization of stack
            .global __STACK_END				;
;-------------------------------------------------------------------------------
; Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".reset"                ; initialization of .reset section
            .word  RESET
