#include <msp430.h>
int main(void) {
	WDTCTL = WDTPW + WDTHOLD; //paramos el watchdog
	P1DIR |= 0x01; //ponemos P1.0 como salida

	TA0CTL &= ~TAIFG; //Eliminamos posibles interrupcciones
	//pendientes del Registro de control del Timer A

	TA0CTL = TASSEL_1 + MC_2 + ID_2 + TACLR; //config del Timer
	//TASSEL_1 = ACLK (0=TACLK  2=SMCLK  3=INCLK)
	//MC_2 = Modo continuo hasta 0FFFFh (0=parada, 1=hasta TACCR0)
	//ID_2 = divide la frec de Reloj/4 (0=f/1  1=f/2  3=f/8)
	//TACLR = borra la cuenta

	//puesto que cuenta desde hasta FFFF#h=65500#d
	//con una frec de 32000Hz/4=8000Hz
	//655000/8000=8segundos
	//PARPADEA CADA 8 SEGUNDOS !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	while(1){

		while ((TA0CTL & TAIFG)==0){//mientras el timer esté a 0
			// no se hace nada
		}
		//cuando llega al final de la cuenta se cambia el estado
		TA0CTL &= ~TAIFG; //eliminar interrupciones pendientes
		P1OUT ^= 0x01; //parpadeo P1.0
	}
}
