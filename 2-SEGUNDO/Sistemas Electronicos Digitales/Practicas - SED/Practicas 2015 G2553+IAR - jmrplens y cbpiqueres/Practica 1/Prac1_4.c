#include <msp430g2553.h> //Dispositivo especifico que vamos a utilizar
#define LEDROJO BIT0
#define LEDVERDE BIT6
volatile unsigned int i;
void main (void)
{
WDTCTL = WDTPW | WDTHOLD; // Stop Watchdog Timer
P1DIR |= 0x01 + 0x40; //Configura P1.0 como salida (LED1)
P1OUT = 0x00;
for (;;)
  {
    if(P1OUT==LEDROJO){//Si el led rojo esta encendido lo cambia por el verde
      P1OUT = LEDVERDE;}
    else{//sino lo cambia por el rojo
      P1OUT = LEDROJO;}
  i=50000; 
  do{
    i--;
  }while (i!=0);
  
  }
}