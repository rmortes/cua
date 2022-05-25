
//void fade (void)
//{
//  while((P1IN&BIT3)==0){                    // Mientras esta pulsado seguira haciendo el fade
//      static int direction = 1;
//      TA0CCR1 += direction*10;              // Valor del Duty-Cycle (velocidad de fade)
//      if( TA0CCR1 > 980 || TA0CCR1 < 20 ){  E Y SINO VICEVERSA
//        direction = -direction;
//      }
//      __delay_cycles(10000);  
//  };
//}

#include  <msp430.h>
int inout = 1;

void fade (void)
{
  for(;;){
    if((P1IN&BIT3)==0){
      
      TA0CCR1 += inout*10;                  // Valor del Duty-Cycle (cantidad de cambio en cada paso, minimo 10)
      if( TA0CCR1 > 990 || TA0CCR1 < 10 ){  // Antes de llegar al maximo o a 0, cambia la direccion, si estaba subiendo->baja y viceversa
        inout = -inout;
      }
      __delay_cycles(20000);                // Velocidad de aumento o disminucion de Duty_Cycle
    }else{
      return;                               // Si se deja de pulsar, saldra de la interrupcion despues de volver a donde se le ha llamado
    }
  }
}
void config_port(void)
{
  P1DIR |= BIT6;                            // Pin de TA0.1 y lED como salida
  P1SEL |= BIT6;                            // Salida del Timer A0.1 por la patilla conectada al LED
  P1DIR &= ~BIT3;                           // P1.3 como I/O general (GPIO)
  P1REN |= BIT3;                            // P1.3 resistencia habilitada
  P1OUT |= BIT3;                            // P1.3 como entrada
  P1IES |= BIT3;                            // Flanco de bajada para P1.3
  P1IFG &= ~BIT3;                           // Borra flags de interrupcion para P1.3
  P1IE |= BIT3;                             // Interrupciones locales habilitadas para P1.3  
}
void config_pwm(void)
{
  TA0CCR0 = 1000;                           // Periodo PWM
  TA0CCR1 = 1;                              // Duty-Cycle (inicial)
  TA0CCTL1 = OUTMOD_7;                      // PWM reset/set
  TA0CTL = TASSEL_2 + MC_1;                 // Timer A: SMCLK (1MHz) y CCR0 ascendente 
}
int main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Paramos el WDT
  config_port();                            // Configuramos los puertos
  config_pwm();                             // Configuracion de la PWM
  _BIS_SR(LPM0_bits + GIE);                 // Bajo consumo y activa las interrupciones 
}

#pragma vector=PORT1_VECTOR
__interrupt void P1(void) 
{
  if(P1IFG & BIT3){
   fade();                                  // Llama a la funcion para aumentar o disminuir el brillo
   P1IFG &= ~BIT3;                          // Borra flags de interrupcion para P2.7
  }
}