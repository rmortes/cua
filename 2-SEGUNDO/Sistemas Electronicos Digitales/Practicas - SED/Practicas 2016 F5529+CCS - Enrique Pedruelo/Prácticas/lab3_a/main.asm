
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

			bis.b 	#0x01,&P1DIR		; Configura P1.0 como salida
          	bic.b 	#0x02,&P2DIR		; Configura P2.1 como entrada
          	bic.b 	#0x01,&P1OUT		; Pone a 0 P1.0 (Led Apagado)
          	bis.b 	#0x02,&P2OUT		; Pone a 1 P2.1 para esperar a un 0 (Resistencia Pull-Up seleccionada)
          	bis.b 	#0x02,&P2REN		;Resistencia pull-up

read_but	bit.b	#0x02,&P2IN			; Testea si el boton esta a 0
			jnz     read_but			; Bucle que lee continuamente el
										; boton
			call	#Led				; Llama a la subrutina del led

;-------------------------------------------------------------------------------
; Subrutina Led
;-------------------------------------------------------------------------------

Led
toggle		xor.b	#0x01, &P1OUT			;Cambiamos el estado del led
			mov		#0x000A,R14				;Asignamos el valor de R14
retardo2	mov		#0x8235,R15				;Asignamos el valor de R15
retardo1	dec		R15						;Decrementamos el valor de R15
			jnz		retardo1				;Retardo de 100000 ciclos
			dec		R14						;Decrementamos el valor de R14
			jnz		retardo2				;Retardo de 1 segundo
			jmp		toggle					;Bucle infinito
			ret

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


