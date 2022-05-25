#include <msp430.h> 

volatile unsigned int v;
/*
 * main.c
 */
int main(void){
	WDTCTL = WDTPW + WDTHOLD; // Stop WDT
	//Port
	P1DIR |= BIT1; // P1.1 -> output
	P1SEL |= BIT1; // P1.1 -> option select TA0.0
	//Timer
	TA0CTL = TASSEL_2 +ID_0 + MC_1 + TACLR; // SMCLK, upmode
	TA0CCTL0 = OUTMOD_1; // PWM output mode: 1 'SET' o 'Toggle(nº4)'
	// Conf2: 4KHz / DC25%
	v=250;
	TA0CCR0 = v;
	__bis_SR_register(LPM0_bits); // CPU off
return 0;
}
