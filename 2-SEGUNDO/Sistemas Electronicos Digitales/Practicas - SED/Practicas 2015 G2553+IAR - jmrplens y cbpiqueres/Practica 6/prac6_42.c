#include <msp430.h>
//fSAL=fSMCLK/TA0CCR0=2KHz --> TA0CCR0=fSMCLK/fSAL=106/2000=500 -->499(0 a 499) --> 75% de 500=375
int main(void)
{
  WDTCTL = WDTPW + WDTHOLD; // Paramos el WDT
  BCSCTL1 = CALBC1_1MHZ;    // f=1Mhz
  DCOCTL = CALDCO_1MHZ;
  P1SEL = BIT2;             // Configuramos P1.2 como salida del Timer
  P1DIR = BIT6;             // Y habilitamos la salida por P1.6
  TA0CCTL1 = OUTMOD_7;      // Registro Captura/Compara 1 del Timer A0 el modo Salida Reset/Set, TA0CCR0 determina el periodo, TA0CCR1 determina el flanco
  TA0CCR0 = 499;
  TA0CCR1 = 375;
  TA0CTL = TASSEL_2 + MC_1; // modo ascendente y SMCLK fuente del reloj
  _BIS_SR(LPM0_bits);       // habilitamos el modo 0 de bajo consumo
}