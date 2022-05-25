#include <msp430.h>
// f=1000000; 1000000/2=500000 --> T= 2us; cuento 50000 pulsos*2us=0,1s
int main(void)
{
  WDTCTL = WDTPW + WDTHOLD;         // Paramos el WDT
  DCOCTL = CALDCO_1MHZ;             //calibra la f a 1MHz
  BCSCTL1 = CALBC1_1MHZ;
  P1DIR |= 0x01;                    // P1.0 como salida para el LED
  TA1CCTL0 = CCIE;                  // Habilito la interrupciones del Registro Captura/Compara 0 del Timer A1
  TA1CCR0 = 50000;                  // Y cargo este registro con el número de ciclos que quiero contar
  TA1CTL = TASSEL_2 + ID_1 + MC_2;  // Seleccionamos SMCLK como fuente de reloj, la divido por dos y modo continuo
                                    // Como voy a trabajar en modo comparación no hace falta que modifique el bit CAP
  _BIS_SR(LPM0_bits + GIE);         // habilitamos el modo 0 de bajo consumo y habilitamos las interrupciones
}

// Rutina de servicio de la interrupción del Timer 1
#pragma vector=TIMER1_A0_VECTOR
__interrupt void Timer_A0 (void)
{
  P1OUT ^= 0x01;                    // Hacemos cambiar al LED
  TA1CCR0 += 50000;                 // Se recarga el registro con 50000, valor que tardara en contar 0.1s
}