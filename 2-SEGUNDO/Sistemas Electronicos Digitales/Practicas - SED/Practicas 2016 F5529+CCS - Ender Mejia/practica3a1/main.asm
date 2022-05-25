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
            .retain                         ; Override ELF conditional linking
                                            ; and retain current section.
            .retainrefs                     ; And retain any sections that have
                                            ; references to current section.

;-------------------------------------------------------------------------------
RESET       mov.w   #__STACK_END,SP         ; Initialize stackpointer
StopWDT     mov.w   #WDTPW|WDTHOLD,&WDTCTL  ; Stop watchdog timer

;P1.0 como salida >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
			bis.b #BIT0, &P1DIR
			bic.b #BIT0, &P1OUT	;apagamos P1.0

;declarar entradas <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
			bic.b #BIT1, &P2DIR	;P2.1
			bis.b #BIT1, &P2OUT
			bis.b #BIT1, &P2REN


bucle
          	bit.b 	#BIT1,&P2IN		; Si se pulsa P2.1 --> parpadeo
          	jz 		parpadeo

          	jmp 	bucle

;-------------------------------------------------------------------------------
; funcion de pulsado
;-------------------------------------------------------------------------------
boton1

parpadeo	xor.b	#BIT0,&P1OUT

			mov.w	#00006h,R14

L2
			mov.w	#0E38Eh,R15

L1
			dec.w	R15
			jnz		L1
			dec.w	R14
			jnz		L2
			jmp		parpadeo

			jmp 	bucle


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
            
