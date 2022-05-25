#include <msp430.h> 

/*
 * main.c
 */
int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	P1DIR |= 0x01;
	
	for(;;){
		volatile unsigned int i;

		P1OUT ^= 0x01;

		i = 1890;
		do i--;
		while(i !=0);
	}
	return 0;
}
