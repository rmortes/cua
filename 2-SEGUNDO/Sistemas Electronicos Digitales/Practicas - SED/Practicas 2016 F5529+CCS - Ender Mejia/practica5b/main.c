#include <msp430.h> 

unsigned int i;

unsigned int retardo;

int main(void){

	WDTCTL = WDTPW + WDTHOLD;

	P1DIR |= BIT0; //P1.0 de SALIDA

	//Boton +0.1 Hz
	P2DIR &= ~BIT1;//P2.1 de ENTRADA
	P2REN |= BIT1;//pull-up
	P2OUT |= BIT1;
	P2IES |= BIT1;//habilita interrupcion
	P2IFG &= ~BIT1;
	P2IE |= BIT1;

	__bis_SR_register(GIE);//modo LPM4 y habilita interrupciones generales
	__no_operation(); //para depurar

	i=1;

	for(;;){

		retardo=10000000/i;
		//retardo=[1/(0.1*i)]*1000000
		//calculo del retardo para ajustar frecuencia
		for(;retardo>0;retardo--){//retardo frecuencia
			__delay_cycles(1);//1 ciclo
			//0.1 Hz = 1/0.1 = 10 segundos
			//0.2 Hz = 1/0.2 = 5 segundos
		}
		P1OUT ^= BIT0;//parpadeo
	}
}
//cuando se pulsa el boton P2.1, se incrementa en i, por lo que
//el retardo que hay antes de la XOR (que marca la frec de parpadeo)
//se reduce, al ser el retardo=10.000.000/i
//Al inicio con i=1 -->se hara un delay que dura 10s = 0,1Hz
#pragma vector=PORT2_VECTOR
__interrupt void IncremFrecu(void) {
	i++;

	P2IFG &= ~BIT1;//borramos flag
}
