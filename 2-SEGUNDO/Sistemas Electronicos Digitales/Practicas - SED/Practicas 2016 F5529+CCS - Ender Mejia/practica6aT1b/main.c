#include <msp430.h>
int main(void)
{
	WDTCTL = WDTPW + WDTHOLD;
	P1DIR |= 0x01;

	TA0CCR0 = 1000;
	TA0CCTL0 &= ~CCIFG;
	TA0CTL = TASSEL_1 + MC_1 + ID_2 + TACLR; //config del Timer
	//TASSEL_1 = ACLK (0=TACLK  2=SMCLK  3=INCLK)
	//MC_2 = Modo continuo hasta 0FFFFh (0=parada, 1=hasta TACCR0)
	//ID_2 = divide la frec de Reloj/4 (0=f/1  1=f/2  3=f/8)
	//TACLR = borra la cuenta

	//la frec es 32000Hz/4= 8000Hz
	//1000/8000= 1/8 segundos
	//PARPADEA CADA 1/8 SEGUNDOS !!!!!!!!!!!!!!!!!!!!!!!!!!

	while(1){
		while ((TA0CCTL0 & CCIFG)==0){
			// do nothing
		}
		TA0CCTL0 &= ~CCIFG;

		P1OUT ^= 0x01;
	}
}
