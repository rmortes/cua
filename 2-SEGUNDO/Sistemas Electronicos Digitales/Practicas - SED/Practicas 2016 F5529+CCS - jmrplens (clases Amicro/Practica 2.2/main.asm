;-------------------------------------------------------------------------------
; MSP430 Assembler Code Template for use with TI Code Composer Studio
;
;
;-------------------------------------------------------------------------------
            .cdecls C,LIST,	"msp430.h"      ; Include device header file
;-------------------------------------------------------------------------------
            .def    RESET                   ; Export program entry-point to
                                            ; make it known to linker.
			.text
            .data
			.bes 10
Datw			.word		0xA111,0xB222,0xC333,0xD444,0xE555,0xF666,0xFFFF
			.bes 22							; Reservo espacio para tener libres las posiciones de memoria donde voy a copiar los datos
;-------------------------------------------------------------------------
RESET		mov.w	#__STACK_END,SP			;Iniciar Stack Pointer
			mov.w	#WDTPW|WDTHOLD,&WDTCTL	;Detener Wtchdog Timer
			mov.w 	#0x0240A,R4 				;Guardamos en el registro R4 la direccion de memoria donde esta el primer dato guardado
MOVER		mov 		@R4+,14h(R4) 			;-> Usamos el modo de direccionamiento indirecto a registro, lo indica la arroba.
											;se mueve el dato de la posicion de memoria que esta en R4 a la posicion de memoria R4+16, es decir
											;lo moveremos a una posicion 16h mayor que la albergada en R4, si R4 tiene 0x0240A copiara los datos de esa direccion a
											; 0x0240A+0x00016=0x02420. Al terminar de mover el dato se realiza un autoincremento en R4 determinado por el signo + en @R4+
											; cada vez que se ejecuta el mov, mueve dato y suma 2 a R4.
			cmp.w 	#0FFFFh, &0x0242C 		; Comprueba si en la direccion de memoria 0x0242C (direccion final donde se copian los datos) esta el ultimo dato que es 0xFFFF.
			jnz 		MOVER 					; Si la comparacion anterior no es igual Z=0 y salta a MOVER, si es igual, sale del bucle y termina
			jmp		$						; Aqui termina el programa
			nop
;--------------------------------------------------------------------
; Subrutinas
;--------------------------------------------------------------------
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
