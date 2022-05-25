#include <msp430.h>

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;		// Stop watchdog timer

    P1DIR|=BIT0;				//Reloj auxiliar ACLK
    P1SEL|=BIT0;

    UCSCTL4 = SELA_0;			//Observando la tabla de UCSCTL4
    						//se sabe que 0 es el Cristal XT1CLK
	return 0;
}

/*
#include <msp430.h>

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;		// Stop watchdog timer

    P1DIR|=BIT0;				//Reloj auxiliar ACLK
    P1SEL|=BIT0;

    UCSCTL4 = SELA_1;			//Observando la tabla de UCSCTL4
    						//se sabe que 0 es el Oscilador VLO
	return 0;
}

*/

/*
#include <msp430.h>

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;		// Stop watchdog timer

    P1DIR|=BIT0;				//Reloj auxiliar ACLK
    P1SEL|=BIT0;

    UCSCTL4 = SELA_2;			//Observando la tabla de UCSCTL4
    						//se sabe que 0 es el Oscilador REFO
	return 0;
}
*/
