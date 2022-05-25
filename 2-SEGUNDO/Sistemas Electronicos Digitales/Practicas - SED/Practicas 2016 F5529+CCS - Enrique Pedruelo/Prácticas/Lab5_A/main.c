#include <msp430.h> 

#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void){
	P1OUT &= ~BIT0; //P1.0 -> "0" Logic
	P1IFG &= ~BIT1; //Interrup P1.1 -> 0
}

#pragma vector=PORT2_VECTOR
__interrupt void Port_2(void){
	P1OUT |= BIT0;	//P1.0 ->  "1" Logic
	P2IFG &= ~BIT1;	//Interrup P2.1 -> 0
}

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

    P1DIR |= BIT0;	//P1.0 -> Output
    P2DIR &= ~BIT1;	//P2.1 -> Input
    P1DIR &= ~BIT1;	//P1.1 -> Input
    P2REN |= BIT1;	//P1.0 -> Pull-up resistor
    P1REN |= BIT1;	//P1.0 -> Pull-up resistor

    P1OUT &= ~BIT0;	//P1.0 ->  "0" Logic
    P2OUT |= BIT1;	//P2.1 ->  "1" Logic
    P1OUT |= BIT1;	//P1.1 ->  "1" Logic

	//Interrupt
	P2IES |= BIT1;	//Interrup P2.1 -> High to low
	P2IFG &= ~BIT1;	//Interrup P2.1 -> 0
	P2IE |= BIT1;	//Interrup P2.1 -> Enable
	P1IES |= BIT1;	//Interrup P1.1 -> High to low
	P1IFG &= ~BIT1;	//Interrup P1.1 -> 0
	P1IE |= BIT1;	//Interrup P1.1 -> Enable

    __bis_SR_register(GIE);	//Enable Interrupts
	return 0;
}


