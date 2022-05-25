#include <msp430.h> 

/*
 * main.c
 */
int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	    // Stop watchdog timer
    P1DIR |= BIT0;                  // ACLK set out to  pins
    P1SEL |= BIT0;
    P2DIR |= BIT2;                  // SMCLK set out to pins
    P2SEL |= BIT2;
	return 0;
}
