;-------------------------------------------------------------------------------
; MSP430 Assembler Code Template for use with TI Code Composer Studio
;-------------------------------------------------------------------------------
            .cdecls C,LIST,"msp430.h"       ; Include device header file
RETAR1 		.set 	513 ; valor para el contador 1 estado alto
MRETAR1 		.set 	510 ; Multiplicador del valor del contador 1
;-------------------------------------------------------------------------------
            .def    RESET                   ; Export program entry-point to
                                            ; make it known to linker.
;-------------------------------------------------------------------------------
            .text                           ; Assemble into program memory.

RESET		mov.w	#__STACK_END,SP			;Iniciar Stack Pointer
			mov.w	#WDTPW|WDTHOLD,&WDTCTL	;Detener Wtchdog Timer

			bis.b	#BIT7,&P4DIR				; P1.0 como Salida
LOOP    		xor.b 	#BIT7,&P4OUT 			; Alterna P1.0 			| 3 Ciclos
        		call 	#RETARDO1      			; Retardo de 2 segundos 	| 5 Ciclos
        		jmp 		LOOP            			; Bucle infinito 		| 2 Ciclos
;--------------------------------------------------------------------
; Subrutinas
;--------------------------------------------------------------------
RETARDO1                    			; Rutina para un retardo de 1s
									; La ecuacion que define el retardo es: CiclosConsumidos=17+(RETAR1*4+4)*MRETAR1
									; Con RETAR1=513 y MRETAR1=510 el total de ciclos consumidos es 1.048.577 lo que hace
									; un retardo de 1 segundo casi exacto, ya que el reloj va a 1.048.576 Hz
        		mov.w 	#RETAR1,R14  	; 																			| 1 Ciclo
        		mov.w 	#MRETAR1,R15	;																			| 1 Ciclo
CONTADOR1                   			; En total consumira  1.048.560 ciclos teniendo RETAR1=513 y MRETAR1=510
									; Sumando los ciclos fuera del bucle da 1.048.577
        		dec.w 	R14           	; Decremento del valor en R14												| 1 Ciclo
        		nop						;																			| 1 Ciclo
        		jnz 		CONTADOR1		;																			| 2 Ciclos
        		mov.w 	#RETAR1,R14  	; Reiniciamos el valor en R14 con el valor del contador 						| 1 Ciclo
        		dec.w 	R15				;																			| 1 Ciclo
        		jnz 		CONTADOR1       	; Mientras R15 no sea 0 seguira repitiendo los decrementos en R14				| 2 Ciclos
        		ret						;																			| 5 ciclos
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
            
