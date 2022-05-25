#include <msp430.h>
int i=0;
void OutMCLK (void) 
{ 
  P1DIR |= BIT2;              // P1.2 como salida
  for (;;)P1OUT ^= BIT2;      // Cambiamos el estado de P1.2 a la misma velocidad que el reloj de la cpu que es MCLK
} 
void OutSMCLK (void) 
{ 
  P1DIR |= BIT4;  
  P1SEL |= BIT4;              // SMCLK como salida en P1.4
} 
void OutACLK (void) 
{ 
  P1DIR |= BIT0; 
  P1SEL |= BIT0;              // ACLK como salida en P2.0 (Para F2132) (Para G2553 en P1.0)
} 
void speed (void)             // Al pulsar 2.7 se cambia el divisor del MCLK
{
  i++;
  switch(i){
  case 1:
    BCSCTL2 = DIVM_0;        // MCLK = LFXT1/1
    break;
  case 2:
    BCSCTL2 = DIVM_1;        // MCLK = LFXT1/2
    break;
  case 3:
    BCSCTL2 = DIVM_2;        // MCLK = LFXT1/4
    break;
  case 4:
    BCSCTL2 = DIVM_3;        // MCLK = LFXT1/8
    i=0;
    break;
  } 
}

int main(void)
{
  WDTCTL = WDTPW + WDTHOLD;   // Paramos el WDT
  BCSCTL1 = CALBC1_1MHZ;      // DCO A 1MHz = SMCLK = MCLK
  DCOCTL = CALDCO_1MHZ;
  BCSCTL3 |= LFXT1S_2;        // LFXT1 = VLO = 12KHz PARA SACAR aclk CUANDO NO HAY CRISTAL PUESTO, quitar esta linea si se pone cristal
  P2SEL = 0;                              // P2 como I/O general (GPIO)
  P2DIR &= ~0x80;                         // P2.7 y P2.6 como I/O general (GPIO)
  P2REN |= 0x80;                          // P2.7 y P2.6 resistencia habilitada
  P2OUT |= 0x80;    
  P2IES = BIT7;                           // Flanco de bajada para P2.7
  P2IFG &= ~0x80;                         // Borra flags de interrupcion para P2.7
  P2IE |= 0x80;                           // Interrupciones locales habilitadas para P2.7 
  __enable_interrupt();
   OutACLK();                  // ACLK 
  OutSMCLK();                 // SMCLK
  OutMCLK();                  // MCLK
  
}
#pragma vector=PORT2_VECTOR
__interrupt void P2 (void){
 speed();                     // Selecciona velocidad para MCLK
 __delay_cycles(500000);
 P2IFG &=~BIT7;               // Borra el flag de 2.7
}