#include <msp430.h> 
int main(void) {
	WDTCTL = WDTPW + WDTHOLD;//paramos el watchdog

	P1DIR |= 0x01; //ponemos P1.0 como salida

	TA0CCTL0 = CCIE; //habilita interrupcion en CCR0
	TA0CCR0 = 10000;
	TA0CTL &= ~CCIFG; //elimina interrupciones pendientes

	TA0CTL = TASSEL_1 + MC_1 + ID_2 + TACLR; //config del Timer
	//TASSEL_1 = ACLK (0=TACLK  2=SMCLK  3=INCLK)
	//MC_1 = creciente hasta TACCR0 (0=parada, 2=hasta FFFF)
	//ID_2 = divide la frec de Reloj/4 (0=f/1  1=f/2  3=f/8)
	//TACLR = borra la cuenta

	__bis_SR_register(LPM0_bits + GIE);//modo lpm0 +...
	//...+ interrupciones generales habilitadas
}
// Timer0 A0 interrupt service routine
#pragma vector=TIMER0_A0_VECTOR //interrupcion con el timer
__interrupt void TIMER_ISR(void) {
	P1OUT ^= 0x01; //parpadeo P1.0
}
