#include <msp430.h> 


int main(void)
{
    WDTCTL = WDTPW + WDTHOLD;   // stop watchdog timer

    P2DIR |= BIT0; // Selección de salida en P2.0
    P2SEL |= BIT0; // P2.0 como salida


    TA1CCR0 = 20000-1; // Periodo del PWM 50Hz
    TA1CCTL1 = OUTMOD_7; // CCR1 reset/set
    TA1CTL = TASSEL_2 + MC_1 + TACLR; // SMCLK, Modo Ascendente, 

    do{
        for(i=0;i<180;i++){
            TA1CCR1=(i*11)+499;
            __delay_cycles(150000);
        }
    }while(1);}
