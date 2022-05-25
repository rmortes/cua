#include <msp430.h>

int main(void)
{
    WDTCTL = WDTPW + WDTHOLD;   // stop watchdog timer

    P2DIR |= BIT0; // Selección de salida en P2.0
    P2SEL |= BIT0; // P2.0 como salida

    TA1CCR0 = 20000-1; // Periodo del PWM 50Hz
    TA1CCTL1 = OUTMOD_7; // CCR1 reset/set
    TA1CCR1 = 500-1;      //PWM duty cycle 500 para 0.5ms, 1500 para 1.5ms, 2500 para 2.5ms




    TA1CTL = TASSEL_2 + MC_1 + TACLR; // SMCLK, Modo Ascendente, clear TAR
    __bis_SR_register(LPM0_bits); // Modo LPM0
    __no_operation(); // para debug

}
