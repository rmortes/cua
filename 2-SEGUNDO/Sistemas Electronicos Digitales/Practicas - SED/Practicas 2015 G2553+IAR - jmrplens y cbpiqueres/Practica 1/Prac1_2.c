#include <msp430g2553.h> //Dispositivo especifico que vamos a utilizar
#define LEDVERDE BIT6
volatile unsigned int i;  // Creación de variable entera
void main (void)
{
WDTCTL = WDTPW | WDTHOLD; // Stop Watchdog Timer(Evitar bucle)
P1DIR |= 0x40 ; //Configura P1.6 como salida (LED Verde)
P1OUT = 0x00;

for (;;) //Bucle infinito
  {
  P1OUT ^= LEDVERDE; //Cambia el estado de la variable de salida mediante XOR
  i=50000; //Inicializamos la variable empleada para el retardo
  do{   // Bucle empleado para retardar la activacion del LED
    i--;  //Decremento de la variable empleada en el retardo    
  }while (i!=0);  //Condición de salida del bucle para el retardo
  }
}