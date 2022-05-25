#include <msp430.h> 

/*
 * main.c
 */
int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	        // Stop watchdog timer
    P1DIR |= BIT2;                      // Configuramos P1.2 como salida.
    P1SEL |= BIT2;                      // Seleccionamos el modo en P1.2 para sacar TA0.1.
    TA0CTL = TASSEL_2+MC_1+TACLR;       // SMCLK, upmode
    TA0CCTL1 = OUTMOD_2;                // PWM output mode: 2
    // Conf2: 4KHz /
    unsigned int v=17;                  // Variable v
    float DC=v/100.0;                   // Porcentaje DC
    TA0CCR0 = 260;                      // Registro CCR0
    TA0CCR1 = 260-(260*DC);             // Registro CCR1
    _bis_SR_register(LPM0_bits);        // CPU off
	return 0;
}
