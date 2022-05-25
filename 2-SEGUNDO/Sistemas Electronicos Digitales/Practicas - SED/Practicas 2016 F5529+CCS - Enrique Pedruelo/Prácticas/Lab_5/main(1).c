#include <msp430.h>

int main(void){
	WDTCTL = WDTPW + WDTHOLD; //Stop Watchdog
	P1DIR |= BIT0;	//P1.0 as output
	P2DIR &= ~BIT1; //P2.1 as imput
	P2REN |= BIT1;	//P2.1 pull-up resistor
	P2OUT |= BIT1;	//P2.1 high value
	P2IES |= BIT1;	//Interrup in P2
	P2IFG &= ~BIT1;	//Interrupt Flag in P2.1
	P2IE |= BIT1;	//Interrup P2
	__bis_SR_register(LPM4_bits + GIE); //LPW
}

#pragma vector=PORT2_VECTOR
__interrupt void Port_2(void)
{
	P1OUT ^= BIT0; //P1.0 Change state
	P2IFG &= ~BIT1;	//Erase Flag Interrup P2.1
}

//Hay un momento que hace una cosa rara,
//Primero esta el led apagado y al pulsar se enciende
//Pero en un momento al pulsar el led se enciende y
//apaga. Y en ese momento ocurre el efecto contrario.
