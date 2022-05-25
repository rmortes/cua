#include <msp430.h>
int main(void)
{
	WDTCTL = WDTPW + WDTHOLD;
	P1DIR |= 0x01;
	TA0CCTL0 = CCIE; //Enable timer0 interrupts
	TA0CCR0 = 1000;
	TA0CCTL0 &= ~CCIFG;
	//TA0CTL &= ~TAIFG;
	TA0CTL = TASSEL_1 + MC_2 + ID_2 + TACLR;
	while(1){
		while ((TA0CCTL0 & CCIFG)==0){
			// do nothing
		}
		TA0CCTL0 &= ~CCIFG;
		/*while ((TA0CTL & TAIFG)==0){ // do nothing
				}*/
		TA0CTL &= ~TAIFG;
		P1OUT ^= 0x01;
	}
}
