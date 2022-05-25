#include <msp430.h> 

/*
 * main.c
 */
int main(void) {
	WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

	/*
	--------------------------------------
	2,5 MHz = 2.500.000 Hz = 2^D*(N*1)*32.768
	D=2
	N=18 --> #18d = #12h
	DCORSEL=3
	--------------------------------------
	10 MHz = 10.000.000 Hz = 2^D*(N*1)*32.768
	D=4
	N=18 --> #18d = #12h
	DCORSEL=5
	--------------------------------------
	 */


	//MCLK>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	P7DIR |= BIT7;
	P7SEL |= BIT7;

	//2,5Mhz------------------------------
	//UCSCTL1 = DCORSEL_3;
	//UCSCTL2 = 0x2012;		//D=2  N=18d=12h
	//UCSCTL3 = SELREF_0;
	//UCSCTL4 = SELM_3;

	//10Mhz-------------------------------
	UCSCTL1 = DCORSEL_5;
	UCSCTL2 = 0x4012;		//D=4  N=18d=12h
	UCSCTL3 = SELREF_0;
	UCSCTL4 = SELM_3;

	P1DIR |= BIT0;	//mostrar MCLK por P1.0
	for(;;){
		P1OUT ^= BIT0;
	}



	//SMCLK>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	//P2DIR |= BIT2;
	//P2SEL |= BIT2;


	//2,5Mhz------------------------------
	//UCSCTL1 = DCORSEL_3;
	//UCSCTL2 = 0x2012;		//D=2  N=18d=12h
	//UCSCTL3 = SELREF_0;
	//UCSCTL4 = SELS_3;

	//10Mhz-------------------------------
	//UCSCTL1 = DCORSEL_5;
	//UCSCTL2 = 0x4012;		//D=4  N=18d=12h
	//UCSCTL3 = SELREF_0;
	//UCSCTL4 = SELS_3;

}
