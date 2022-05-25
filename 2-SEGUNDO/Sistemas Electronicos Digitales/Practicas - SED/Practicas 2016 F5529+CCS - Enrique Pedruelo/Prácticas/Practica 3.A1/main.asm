;-------------------------------------------------------------------------------
; MSP430 Assembler Code Template for use with TI Code Composer Studio
;
;
;-------------------------------------------------------------------------------
            .cdecls C,LIST,"msp430.h"       ; Include device header file
RETAR1 		.set 	866 ; valor para el contador 1 estado alto
MRETAR1 		.set 	302 ; Multiplicador del valor del contador 1
AJUSTE		.set		6	; Valor del bucle de ajuste para afinar el consumo de ciclos
;-------------------------------------------------------------------------------
            .def    RESET                   ; Export program entry-point to
                                            ; make it known to linker.
;-------------------------------------------------------------------------------
            .text                           ; Assemble into program memory.

RESET		mov.w	#__STACK_END,SP			;Iniciar Stack Pointer
			mov.w	#WDTPW|WDTHOLD,&WDTCTL	;Detener Wtchdog Timer
			clr.b 	&P1SEL        	; Puerto 1 como entrada/salida digital
			clr.b 	&P2SEL         	; Puerto 2 como entrada/salida digital
          	bis.b 	#BIT0,&P1DIR		; Configura P1.0 como salida
          	bic.b 	#BIT1,&P2DIR		; Configura P2.1 como entrada
          	bis.b 	#BIT1,&P2OUT		; Pone a 1 P2.1 para esperar a un 0 (Resistencia Pull-Up seleccionada)
          	bic.b 	#BIT0,&P1OUT		; Pone a 0 P1.0 (Led Apagado)
          	bis.b 	#BIT1,&P2REN		; Pone a 1 P2.1 en P2REN (Resistencia Habilitada)
Bucle                          		; Bucle infinito
          	bit.b 	#BIT1,&P2IN		; Comprueba el estado de P2.1, si esta pulsado Z=1
          	jz 		BOTON      		; Si Z=1 salta
          	jmp 		Bucle
;------------------------------------------------------------------------------
; EJECUCION PARA BOTON
;------------------------------------------------------------------------------
BOTON                              	; P2.1 pulsado
LOOP    		xor.b 	#BIT0,&P1OUT 	; Cambia el estado de la patilla		| 2 Ciclos
        		call 	#RETARDO1      	; Retardo de 1 segundo																| 4 Ciclos
        		jmp 		LOOP            	; Bucle infinito						| 2 Ciclos
;--------------------------------------------------------------------
; Subrutinas
;--------------------------------------------------------------------
RETARDO1                    			; Rutina para un retardo de 1s
									; La ecuacion que define el retardo es: CiclosConsumidos=14+(AJUSTE*3)+(RETAR1*4+8)*MRETAR1
									; Los 14 ciclos vienen del call+ret+mov+mov+mov.
									; Con RETAR1=866 , MRETAR1=302 y AJUSTE=6 el total de ciclos consumidos es 1.048.576 lo que hace
									; un retardo de 1 segundo exacto, ya que el reloj va a 1.048.576 Hz
									; [Medido con el contador de Ciclos de CCS da 1.048.576]
        		mov.w 	#RETAR1,R14  	; 																					| 2 Ciclos
        		mov.w 	#MRETAR1,R15		;																					| 2 Ciclos
        		mov.w	#AJUSTE,R13		;																					| 2 Ciclos
CONTADOR1
        		dec.w 	R14           	; Decremento del valor en R14					| 1 Ciclo	|				|
        		nop						;												| 1 Ciclo	|*RETAR1			|
        		jnz 		CONTADOR1		;												| 2 Ciclos	|				|
        								;																			|
        		mov.w 	#RETAR1,R14  	; Reiniciamos el valor en R14 									| 2 Ciclos	|
        		nop						;																| 1 Ciclo	|*MRETAR1
        		nop						;																| 1 Ciclo	|
        		nop						;																| 1 Ciclo	|
        		dec.w 	R15				;																| 1 Ciclo	|
        		jnz 		CONTADOR1       	; Mientras R15 no sea 0 seguira repitiendo los decrementos en R14	| 2 Ciclos	|
									;
AFINACION	dec.w	R13				;																					| 1 Ciclo	|
			jnz		AFINACION		;																					| 2 Ciclos	|*AJUSTE
									;
        		ret						;																					| 4 ciclos
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
            
