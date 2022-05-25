#include<msp430.h>
#include "LCD4bits.c"
int pulsaciones=0,time=5,a=0;
void config_port(void)
{
  P2SEL = 0;                              // P2 como I/O general (GPIO)
  P2DIR &= ~0x80;                         // P2.7 y P2.6 como I/O general (GPIO)
  P2REN |= 0x80;                          // P2.7 y P2.6 resistencia habilitada
  P2OUT |= 0x80;    
  P1DIR |= 0xFF;                          // Configura el puerto 1 como salida
  P1OUT &= ~0xFF;                         // Todo el puerto 1 a 0.
  P2IES = BIT7;                           // Flanco de bajada para P2.7
  P2IFG &= ~0x80;                         // Borra flags de interrupcion para P2.7
  P2IE |= 0x80;                           // Interrupciones locales habilitadas para P2.7 
}
/* Funcion para configurar la pantalla */
void config_screen (void)
{
  LCD_INI (Dos_Lineas_5x8, Derecha_NoDesplaza);   // Configuramos el msp para funcionar con el LCD
  LCD_Control (CurOFF_BliOFF); 
  LCD_Control(ClearDisplay);                      // Borra el display
}

void config_aclk (void)
{
  BCSCTL3=LFXT1S_2;                       // ACLK = VLOCLK 12KHz
  BCSCTL1=DIVA0+DIVA1;                    // ACLK/2
}
void suma_binaria(void)
{
  time=5;
  WDTCTL=WDTPW+WDTCNTCL+WDTSSEL+WDTIS0;   // Reinicia la supervision del WD
  pulsaciones++;              
  P1OUT=(int)pulsaciones;                 // Salida por P1 
  __delay_cycles(30000);                  // Retardo para prevenir falsas pulsaciones
}
void main(void)
{
  WDTCTL=WDTPW+WDTCNTCL;                  // Configuro WD para supervisar desbordamiento
  config_port();
  config_aclk();
  config_screen();                    // Configura la pantalla
  __enable_interrupt();
  LCD_FilaColumna (0,0);
  LCD_Cadena("Pulsaciones:");
  LCD_FilaColumna (1,0);
  LCD_Cadena("Reinicio en:");

  for(;;){
    a++;
    if(a==4){if(time>0)time--;a=0;}
    LCD_FilaColumna (0,13);
    LCD_Entero (pulsaciones);   
    LCD_FilaColumna (1,13);
    LCD_Entero (time);    // Imprime el caracter en la posicion 0,11
    LCD_FilaColumna (1,15);
    LCD_Cadena("s");
  }
}
#pragma vector=PORT2_VECTOR
__interrupt void Salida(void){

  suma_binaria();
  P2IFG &=~BIT7;
}