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

;-------------------------------------------------------------------------------
RESET       mov.w   #__STACK_END,SP         ; Initialize stackpointer
StopWDT     mov.w   #WDTPW|WDTHOLD,&WDTCTL  ; Stop watchdog timer


;-------------------------------------------------------------------------------
; Main loop here
;-------------------------------------------------------------------------------
			bis.b 	#0x80,&P4DIR		; Configura P4.7 como salida
          	bic.b 	#0x02,&P2DIR		; Configura P2.1 como entrada
          	bis.b 	#0x02,&P2OUT		; Pone a 1 P2.1 para esperar a un 0 (Resistencia Pull-Up seleccionada)
          	bic.b 	#0x80,&P4OUT		; Pone a 0 P4.7 (Led Apagado)
          	bis.b 	#0x02,&P2REN		; Resistencia pull-up
          	bic.b	#0x02,&P1DIR		; Configura P1.1 como entrada
          	bis.b	#0x02,&P1OUT		; Pone a 1 P1.1 para esperar a un 0 (Resistencia Pull-Up seleccionada)
          	bis.b	#0x02,&P1REN		; Resistencia pull-up
			call	#boton				; Subrutina del testeo boton
;-------------------------------------------------------------------------------
; Subrutina Botón
;-------------------------------------------------------------------------------
boton
test		nop							;Etiqueta sin ninguna operación
ledoff		bit.b	#0x02,&P2IN			;Comprueba el valor del puerto P2.1
			jnz		ledon				;Salta si no es cero el resultado anterior
			call	#LedOn				;Llama a la rutina Led
ledon		bit.b	#0x02,&P1IN			;Comprueba el valor del puerto P1.1
			jnz		ledoff				;Salta si no es cero el resultado anterior
			call	#LedOff				;Llama a la rutina Led
			jmp		test				;Bucle infinito de testeo
			ret
;-------------------------------------------------------------------------------
; Bucles Led
;-------------------------------------------------------------------------------

LedOn		bis.b	#0x80,&P4OUT		;Pone un "1" Lógico en el puerto P4.7
			ret							;Sale de la subrutina del led On

LedOff		bic.b	#0x80,&P4OUT		;Pone un "0" Lógico en el puerto P4.7
			ret							;Sale de la subrutina del led Off


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
            
