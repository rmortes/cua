#include <msp430g2553.h> //Dispositivo especifico que vamos a utilizar
#define LEDROJO BIT0
volatile unsigned int i;  // Creación de variable entera
void main (void)
{
WDTCTL = WDTPW | WDTHOLD; //Stop Watchdog Timer(Evitar bucle)
P1DIR |= 0x01 ; //Configura P1.0 como salida (LED Rojo)
P1OUT = 0x00; //Salida nula (Reiniciar el led)

for (;;) //Bucle infinito
  {
  P1OUT ^= LEDROJO; //Cambia el estado de la variable de salida mediante XOR
  i=100; //Inicializamos la variable empleada para el retardo
  do{   // Bucle empleado para retardar la activacion del LED
    i--;  //Decremento de la variable empleada en el retardo    
  }while (i!=0);  //Condición de salida del bucle para el retardo
  }
}