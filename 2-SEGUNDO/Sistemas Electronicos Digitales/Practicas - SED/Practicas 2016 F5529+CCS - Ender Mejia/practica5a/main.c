#include <msp430.h> 
int main(void){
	WDTCTL = WDTPW + WDTHOLD;
	P1DIR |= BIT0; //P1.0 de SALIDA

	//Boton ENCENDER
	P2DIR &= ~BIT1;//P2.1 de ENTRADA
	P2REN |= BIT1;//pull-up
	P2OUT |= BIT1;
	P2IES |= BIT1;//habilita interrupcion
	P2IFG &= ~BIT1;
	P2IE |= BIT1;

	//Boton APAGAR
	P1DIR &= ~BIT1;//P1.1 de ENTRADA
	P1REN |= BIT1;//pull-up
	P1OUT |= BIT1;
	P1IES |= BIT1;//habilita interrupcion
	P1IFG &= ~BIT1;
	P1IE |= BIT1;

	__bis_SR_register(LPM4_bits + GIE);//modo LPM4 y habilita interrupciones generales
	__no_operation(); //para depurar
}
#pragma vector=PORT2_VECTOR
__interrupt void Encender(void) {
	P1OUT |= BIT0;//encendemos P1.0

	P2IFG &= ~BIT1;//borramos flag
}

#pragma vector=PORT1_VECTOR
__interrupt void Apagar(void) {
	P1OUT &= ~BIT0;//apagamos P1.0
	
	P2IFG &= ~BIT1;//borramos flag
}
