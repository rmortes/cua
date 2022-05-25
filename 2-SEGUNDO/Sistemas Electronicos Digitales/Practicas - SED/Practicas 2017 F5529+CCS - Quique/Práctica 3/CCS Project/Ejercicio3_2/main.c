#include <msp430.h> 

/*
 * main.c
 */
int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	        // Stop watchdog timer
    P1DIR |= BIT2;                      // Configuramos P1.1 como salida.
    P1SEL |= BIT2;                      // Seleccionamos el modo en P1.2 para sacar TA0.1.
    TA0CTL = TASSEL_2+MC_1+TACLR;       // SMCLK, upmode
    TA0CCTL1 = OUTMOD_2;                // PWM output mode: 2
    TA0CCR1 = 260;                      // Inicializamos CCR1
    unsigned int i,v;
    for (i=1; i<=10; i++){              // Aumentamos el 10% del DC en cada iteración
    __delay_cycles(1000000);            // Introducimos un retardo de un segundo
    TA0CCR0 = 260;                      // Inicializamos CCR0
    v=0;                                // Borramos el valor de v de la iteracción anterior
    v=TA0CCR0*(1.0/10.0);               // Calculamos el 10%
    TA0CCR1 = TA0CCR1-v;                // Calculamos TA0CCR1 para esa iteración
    }
	return 0;
}
