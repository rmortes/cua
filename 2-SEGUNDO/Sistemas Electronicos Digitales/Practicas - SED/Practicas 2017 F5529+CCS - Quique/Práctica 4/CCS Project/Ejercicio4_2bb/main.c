#include <msp430.h> 

/*
 * main.c
 */
int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	    // Stop watchdog timer
    P2DIR |= BIT2;                  // SMCLK set out to pins
    P2SEL |= BIT2;
    __bis_SR_register(SCG0);        // Disable the FLL control loop
    UCSCTL1 = DCORSEL_5;            // Select DCO range (4, 5 or 6)
    UCSCTL2 = FLLD_0+304;           // Set N for 10MHz
    __bic_SR_register(SCG0);        // Enable the FLL control loop
	return 0;
}
