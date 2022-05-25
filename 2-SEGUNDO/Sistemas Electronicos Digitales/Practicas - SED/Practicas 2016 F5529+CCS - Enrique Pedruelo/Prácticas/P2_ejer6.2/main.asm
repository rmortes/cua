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
			.data
NUMEROS		.word	0x1234,0x5678,0x9ABC,0x5432,0xFEDC ;5 numeros de 16bits

;-------------------------------------------------------------------------------

            .text                           ; Assemble into program memory.

RESET       mov.w   #__STACK_END,SP         ; Initialize stackpointer
StopWDT     mov.w   #WDTPW|WDTHOLD,&WDTCTL  ; Stop watchdog timer

			mov.w	#NUMEROS,R4
			clrc						;Cambiamos el valor del contador a 0
LOOP		cmp.w 	#A000h,	R4			;comparamos si tiene un 1 en el bit mas significativo.
			jne		else
			rrc		R4					;desplazamos a la derecha
			jmp		despues
else
			rla		R4
despues
			inc.w	R4
			jmp 	LOOP
;-------------------------------------------------------------------------------
; Stack Pointer definition
;-------------------------------------------------------------------------------
            .global __STACK_END
            .sect   .stack
            
;-------------------------------------------------------------------------------
; Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET
            
