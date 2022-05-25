#include <msp430.h> 

volatile unsigned int v;
/*
 * main.c
 */
int main(void){
	WDTCTL = WDTPW + WDTHOLD; // Stop WDT
	v=250;
	//Port
	P1DIR |= BIT2; // P1.2 -> output
	P1SEL |= BIT2; // P1.2 -> option select TA0.1
	//Interrupt
	TA1CCTL0 = CCIE;
	TA1CCR0 = 3200;
	TA1CCTL0 &= ~CCIFG;
	TA1CTL = TASSEL_1 + MC_2 + ID_2 + TACLR;
	//Timer
	TA0CTL = TASSEL_2 + ID_0 + MC_1 + TACLR; // SMCLK, upmode
	TA0CCTL1 = OUTMOD_2; // PWM output mode: 1 'SET' o 'Toggle(nº4)'
	// Conf2: 4KHz / DC25%
	__delay_cycles(10000);
	TA0CCR0 = 250;
	TA0CCR1 = v;
	__bis_SR_register(LPM0_bits+GIE);
}

#pragma vector= TIMER1_A0_VECTOR
__interrupt void TIMER_ISR(void)
{
	if(v>0){
		v-=25;
	}
	TA1CCTL0 &= ~CCIFG;
}

