#include <msp430g2553.h> //Dispositivo especifico que vamos a utilizar
#define LEDROJO BIT0
#define LEDVERDE BIT6
volatile unsigned int i;
void main (void)
{
WDTCTL = WDTPW | WDTHOLD; // Stop Watchdog Timer (Impide bucles infinitos)
P1DIR |= 0x41 ; //Configura P1.0 y P1.6 como salida (LEDS rojo y verde)
P1OUT = 0x00; // Inicializamos la salida poniendo los registros a cero 
for (;;)
  {
  P1OUT ^= LEDROJO+LEDVERDE; //Cambia el estado de las dos variables
  i=50000; //Variable de retardo
  do{
    i--;
  }while (i!=0);
  
  }
}