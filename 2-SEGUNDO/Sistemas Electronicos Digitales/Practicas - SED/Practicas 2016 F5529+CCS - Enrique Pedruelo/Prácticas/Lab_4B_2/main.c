#include <msp430.h> 

/*
 * main.c
 */
int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	
    P1DIR |= BIT0;
    P4DIR |= BIT7;
    P2DIR &= ~BIT1;
    P2IN |= BIT1;
    P1OUT &= ~BIT0;
    P4OUT &= ~BIT7;

    int i;
for(;;){
    for(i=0; i<1200000; i++){
    	if((P2IN &= ~BIT1)==0){
    		P4OUT ^= BIT7;
    		P2IN |= BIT1;
    		i=0;
    	}
    }
}
	return 0;
}
