#include <msp430.h> 

/*
 * main.c
 */
int main(void) {
	WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

	//----------------------------------------------------------

	/*
	P1DIR |= BIT0;				//ACLK
	P1SEL |= BIT0;
	//UCSCTL4 = SELA_0;			//El cristal XT1CLK
	//UCSCTL4 = SELA_1;			//El oscilador de baja frecuencia VLO
	//UCSCTL4 = SELA_2;			//El oscilador de referencia REFO
	*/

	//----------------------------------------------------------

	/*
	P2DIR |= BIT2;				//SMCLK
	P2SEL |= BIT2;
	//UCSCTL4 = SELS_0;			//El cristal XT1CLK
	//UCSCTL4 = SELS_1;			//El oscilador de baja frecuencia VLO
	UCSCTL4 = SELS_2;			//El oscilador de referencia REFO

	*/

	//----------------------------------------------------------
	//El MCLK no se puede medir con el osciloscopio debido a que no tenemos
	//patilla P7.7, pero deducimos que funciona correctamente.

	P7DIR |= BIT7;				//MCLK
	P7SEL |= BIT7;
	UCSCTL4 = SELM_0;			//El cristal XT1CLK.
	//UCSCTL4 = SELM_1;			//El oscilador de baja frecuencia VLO
	//UCSCTL4 = SELM_2;			//El oscilador de referencia REFO
	P1DIR |= BIT0;				//P1.0 como salida para MCLK
	for(;;){
	P1OUT ^= BIT0;
	}



}
