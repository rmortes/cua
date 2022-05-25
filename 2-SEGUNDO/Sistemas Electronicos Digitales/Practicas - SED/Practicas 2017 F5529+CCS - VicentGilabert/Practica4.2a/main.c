#include <msp430.h>
int main(void) {

	WDTCTL = WDTPW | WDTHOLD; 	// Stop watchdog timer

	P2DIR |= BIT2;			//Elección del SMCLK
	P2SEL |= BIT2;

	UCSCTL1 = DCORSEL_5;	//Buscando en la grafica del DRCORSEL
							//se selecciona la 5				//porque corresponde a los 2.5 MHz
	
	UCSCTL2 = 0x5008;		//FLLD=3
							//La N se calcula a través de la formula:
							//1000000=(2^3)*(N+1)*32768
							//N=8

	UCSCTL3 = SELREF_0;		//Usando la tabla de UCSCTL3 y se selecciona 						//XT1CLK
	UCSCTL4 = SELS_3;		//Usando la tabla de UCSCTL3 y se selecciona 						//DCOCLK

	return 0;
}
