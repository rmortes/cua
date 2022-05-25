#include <msp430.h> 

/*
 * main.c
 */

#include <msp430.h>
int main(void){
WDTCTL = WDTPW + WDTHOLD;
P1DIR |= BIT0;
P1OUT ^= BIT0;
for ( ; ; ) ;
//__bis_SR_register(LPM3_bits);
return 0;
}



/*
int main(void) {
    WDTCTL = WDTPW + WDTHOLD;	// Stop watchdog timer
    P1DIR |= BIT0;
    P1OUT ^= BIT0;

//    WDTCTL = WDTPW+WDTSSEL0+WDTIS2+WDTIS0;
    for (;;);

    //__bis_SR_register(LPM3_bits);
	
	return 0;
}*/



//Ejercicio1.2 a)    The LED doesn´t turn on because it has an infinite loop
//					and the watchdog finish the execution.

//Ejercicio1.2 b)   The LED it never stops blinking because the watchdog
//					don´t finish the execution.

//Ejercicio1.2 c)    The LED doesn´t change the state But So much slowly.
//					I don´t know.

//Ejercicio1.2 d)   The LED it never stops blinking because the watchdog
//					don´t finish the execution.

