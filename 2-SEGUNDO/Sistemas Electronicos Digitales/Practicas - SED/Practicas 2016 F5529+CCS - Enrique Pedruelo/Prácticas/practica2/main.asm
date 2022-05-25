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
Vector		.space 	10					;Reservamos 10 bytes sin datos.
Datos		.word	0xFFA1,0x0011,0xFFB2,0x004D,0x0077,0x0033,0xFFD4, 0x007A, 0xFFE5,0x007F ;Numeros En bytes
					;-95,   17,   -78,    77,    119,   51,    -44,    122,   -27,     127
;-------------------------------------------------------------------------------
            .text                           ; Assemble into program memory.
RESET       mov.w   #__STACK_END,SP         ; Initialize stackpointer
StopWDT     mov.w   #WDTPW|WDTHOLD,&WDTCTL  ; Stop watchdog timer



			mov.w	#02430h,R5

			mov.w	#Datos,R4				;Asigna los valores en la memoria R4
bucle		mov.w	#0000Ah,R15				;Inicia un valor para decrementar el loop
Loop		addc.w	@R4+,0(R5)				;Mueve el contenido de la direccion
											; de memoria a la memoria R5
											; e incrementamos en 2 R4
			dec.w	R15						;Decrementa el valor R15
			jnz		Loop					;Salta a la direccion de memoria
											;donde se encuentre Loop


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
