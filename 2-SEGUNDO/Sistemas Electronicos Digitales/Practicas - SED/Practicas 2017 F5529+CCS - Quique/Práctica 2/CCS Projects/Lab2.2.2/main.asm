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

			bis.b	#0x80, &P4DIR			; Direcciono P4.7
			bic.b 	#0x80, &P4OUT			; Activo P4.7

			bic.b 	#0x02, &P2DIR			; Direcciono P2.1 como entrada
			bis.b	#0x02, &P2REN			; Active pull up
			bis.b 	#0x02, &P2OUT			; Activo P2.1

			bic.b 	#0x02, &P1DIR			; Direcciono P1.1 como entrada
			bis.b	#0x02, &P1REN			; Active pull up
			bis.b 	#0x02, &P1OUT			; Activo P1.1


EF			bit.b	#0x02, &P2IN			; Condicional encendido
			jnz EF
			jz Loop
IF			bit.b	#0x02, &P1IN			; Condicional apagado
			jnz IF

Loop 		xor.b #080h,&P4OUT 				; change the value in P4.7
			jnz IF
			jz EF

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
