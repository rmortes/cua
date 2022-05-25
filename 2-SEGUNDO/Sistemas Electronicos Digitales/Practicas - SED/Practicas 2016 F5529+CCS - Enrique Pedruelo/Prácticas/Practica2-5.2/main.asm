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
Vector		.space 	10		; Reservamos 10 bytes sin datos.
Datos		.word	0xA111,0xB222,0xC333,0xD444,0xE555,0xF666,0xFFFF

;-------------------------------------------------------------------------------
            .text                           ; Assemble into program memory.
RESET       mov.w   #__STACK_END,SP         ; Initialize stackpointer
StopWDT     mov.w   #WDTPW|WDTHOLD,&WDTCTL  ; Stop watchdog timer


			mov.w	#02420h,R5

			mov.w	#Datos,R4				;Asigna los valores en la memoria R4
bucle		mov.w	#00007h,R15				;Inicia un valor para decrementar el loop
Loop		mov.w	@R4+,0(R5)				;Mueve el contenido de la direccion
											; de memoria a la memoria R5
											; e incrementamos en 2 R4
			incd.w	R5						;incrementa en 2 R5
			dec.w	R15						;Decrementa el valor R15
			jnz		Loop					;Salta a la direccion de memoria
											;donde se encuentre Loop
			jmp		bucle					;Bucle infinito.



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
            
