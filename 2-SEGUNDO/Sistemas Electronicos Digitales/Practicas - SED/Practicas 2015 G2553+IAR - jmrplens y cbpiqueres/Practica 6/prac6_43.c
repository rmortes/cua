#include <msp430.h>
int tono=0;

void config_but (void)
{
  P1DIR |= BIT2;                  // BIT6 output
  P1SEL |= BIT2;                  // TA0.1 CCR Output
  P2SEL = 0;                      // P2 como I/O general (GPIO)
  P2DIR &= ~0x80;                 // P2.7 y P2.6 como I/O general (GPIO)
  P2REN |= 0x80;                  // P2.7 y P2.6 resistencia habilitada
  P2OUT |= 0x80;                  // P2.7 y P2.6 como entrada
  P2IES |= 0x80;                  // Flanco de bajada en P2.7 y P2.6
  P2IFG &= ~0x80;                 // P2.7 y P2.6 resistencia pull-up 
  P2IE |= 0x80;                           // Interrupciones locales habilitadas para P2.7 

}
/*CONFIGURACIÓN DEL TIMER*/
void timer (void)
{
  TA0CCTL1 = OUTMOD_7;            // Registro Captura/Compara 1 del Timer A0 el modo Salida Reset/Set
  TA0CTL = TASSEL_2 + MC_1;       // modo ascendente y SMCLK fuente del reloj
}
/*SIRENA*/
void sirena (void)
{
  int t;
  for (t=0;t<20;t++){             // sonará 10s pues cada tono suena 0,5s
    if (tono==0){
      TA0CCR0 = 999;              // f1 = fSMCLK / TA0CCR0 = 10e6/1000=1KHZ
      TA0CCR1 = 500;              // DC=TA0CCR1/TA0CCR0=(500/1000)%=50%
      tono++;
      __delay_cycles(500000);     // Duración de la frecuencia 1; 0,5s
    }else{
      TA0CCR0 = 799;              // f2 = fSMCLK / TA0CCR0 =10e6/800=1,25KHZ
      TA0CCR1 = 400;              // DC=TA0CCR1/TA0CCR0=(400/800)%=50%
      tono=0;
      __delay_cycles(500000);     // Duración de la frecuencia 2; 0,5s
      
    }
  }
}
int main(void)
{
  WDTCTL = WDTPW + WDTHOLD;           // Paramos el WDT
  BCSCTL1 = CALBC1_1MHZ;              // f=1Mhz
  DCOCTL = CALDCO_1MHZ;
  config_but();                       // Configuramos botones
  timer();                            // Configuramos el timer
  __enable_interrupt(); 
  __bis_SR_register(LPM2_bits + GIE); // LPM2 y habilita interrupciones
}

#pragma vector=PORT2_VECTOR
__interrupt void P2(void)
{
  sirena();                           // Hace sonar la sirena
  P2IFG &= ~0x80;                     // Borra el flag de 2.7
}
