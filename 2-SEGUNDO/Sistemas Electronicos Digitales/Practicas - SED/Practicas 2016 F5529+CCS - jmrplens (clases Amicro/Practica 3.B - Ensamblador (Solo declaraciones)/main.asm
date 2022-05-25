;-------------------------------------------------------------------------------
; MSP430 Assembler Code Template for use with TI Code Composer Studio
;
;
;-------------------------------------------------------------------------------
            	.cdecls C,LIST,"msp430.h"       	; Include device header file
D1 			.set 	BIT5						; Diodo 1 -> P6.5
D2			.set 	BIT4						; Diodo 2 -> P3.4
D3 			.set 	BIT3						; Diodo 3 -> P3.3
D4			.set 	BIT6						; Diodo 4 -> P1.6
D5 			.set 	BIT6						; Diodo 5 -> P6.6
D6			.set 	BIT2						; Diodo 6 -> P3.2
D7 			.set 	BIT1						; Diodo 7 -> P3.1
D8			.set 	BIT0						; Diodo 8 -> P3.0
S3 			.set 	BIT0						; Pulsador 3 -> P2.0
S4			.set 	BIT2						; Pulsador 4 -> P2.2
;-------------------------------------------------------------------------------
            	.def    RESET                   	; Export program entry-point to
                                            	; make it known to linker.
;-------------------------------------------------------------------------------
            .text                           	; Assemble into program memory.
;-------------------------------------------------------------------------------
RESET       	mov.w   #__STACK_END,SP         	; Initialize stackpointer
StopWDT     	mov.w   #WDTPW|WDTHOLD,&WDTCTL  	; Stop watchdog timer

			; CONFIGURACION PULSADORES S3 y S4
			bic.b 	#S3+S4 ,& P2DIR			; Configura P2.0 y P2.2 como entrada
			bis.b 	#S3+S4, & P2OUT			; Pone a 1 P2.0 y P2.2 para esperar a un 0 (Resistencia Pull-Up seleccionada)
          	bis.b 	#S3+S4, & P2REN			; Pone a 1 P2.0 y P2.2 en P2REN (Resistencia Habilitada)

			; CONFIGURACION DE DIODOS

			; DIODO 4 -> P1.6
          	bis.b 	#D6,&P1DIR				; Configura P1.6 como salida
          	bic.b 	#D6,&P1OUT				; Pone a 0 P1.6 (Led Apagado)

          	; DIODO 2 -> P3.4 ; DIODO 3 -> P3.3 ; DIODO 6 -> P3.2 ; DIODO 7 -> P3.1 ; DIODO 8 -> P3.0
          	bis.b 	#D2+D3+D6+D7+D8,&P3DIR	; Configura [P3.0,P3.1,P3.2,P3.3,P3.4] como salida
          	bic.b 	#D2+D3+D6+D7+D8,&P3OUT	; Pone a 0 [P3.0,P3.1,P3.2,P3.3,P3.4] (Led Apagado)

			; DIODO 1 -> P6.5 ; DIODO 5 -> P6.6
			bis.b 	#D1+D5,&P6DIR			; Configura [P6.5,P6.6] como salida
          	bic.b 	#D1+D5,&P6OUT			; Pone a 0 [P6.5,P6.6] (Led Apagado)


;-------------------------------------------------------------------------------
; Main loop here
;-------------------------------------------------------------------------------

                                            

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
            
