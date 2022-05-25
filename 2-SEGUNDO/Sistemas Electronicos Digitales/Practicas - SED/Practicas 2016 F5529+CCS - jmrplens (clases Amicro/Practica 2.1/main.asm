;-------------------------------------------------------------------------------
; MSP430 Assembler Code Template for use with TI Code Composer Studio
;
;
;-------------------------------------------------------------------------------
            .cdecls C,LIST,	"msp430.h"      ; Include device header file
            
;-------------------------------------------------------------------------------
            .def    RESET                   ; Export program entry-point to
                                            ; make it known to linker.
;-------------------------------------------------------------------------------
            .text                           ; Assemble into program memory.

RESET		mov.w	#__STACK_END,SP			;Iniciar Stack Pointer
			mov.w	#WDTPW|WDTHOLD,&WDTCTL	;Detener Wtchdog Timer

			bis.b	#BIT7,&P4DIR			; P1.0 como Salida
LOOP    	bis.b 	#BIT7 ,& P4OUT 			; 0 en la patilla / On 	|
        	call 	#RETARDO2      			; Retardo de 2 segundos | 5 Ciclos
        	bic.b 	#BIT7 ,& P4OUT 			; 1 en la patilla / Off |
        	call 	#RETARDO1      			; Retardo de 1 segundo  | 5 Ciclos
        	jmp 	LOOP            		; Bucle infinito 		|
;--------------------------------------------------------------------
; Subrutinas
;--------------------------------------------------------------------
RETARDO2                    				; Rutina para mantener un 0 en la salida									|
        	mov.w #33330 ,R14  				; Mueve el numero del contador para el estado bajo a R14					| 1 Ciclo
CONTADOR2                   				; En total consumira  100.000 Ciclos										|
        	dec.w R14           			; Decremento del valor en R14												| 1 Ciclo
        	jnz CONTADOR2					;																			| 2 Ciclos
        	ret								;																			| 5 Ciclos
RETARDO1                    				; Rutina para mantener un 1 en la salida									|
       	 	mov.w #39996 ,R14  				; Mueve el numero del contador para el estado bajo a R14					| 1 Ciclo
CONTADOR1                   				;  En total consumira  120.000 Ciclos										|
        	dec.w R14           			; Decremento del valor en R14												| 1 Ciclo
        	jnz CONTADOR1       			; Mientras R15 no sea 0 seguira repitiendo los decrementos en R14			| 2 Ciclos
        	ret								;																			| 5 Ciclos
;-------------------------------------------------------------------------------
; Stack Pointer definition
;-------------------------------------------------------------------------------
            .sect	.stack					;Inicializa la pila con el valor de defecto
            .global __STACK_END				;Variable global definida en inicio de RAM
            
;-------------------------------------------------------------------------------
; Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .word  RESET
            
