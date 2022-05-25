#include "io430.h"
#include "LCD4bits.c"
/* Funciones de Configuracio´n
Ahora vienen las definiciones de los prototipos de las funciones. */
void conf_CLK (void); 
void RETARDO (void); 
int p = 0;
void main(void) {
  //Configuracio´n del reloj //Retardo para temporizaciones
  WDTCTL = WDTPW + WDTHOLD; //Paramos el WatchDog
  P1IE |= 0x08; //Habilito interrupcio´n en P1.3 
  P1IES |= 0x08; //Flanco de bajada
  P1IFG &= ~0x08; // Flag de peticio´n a cero
  P1REN |=0x08; // Resistencia en entrada P1.3
  P1OUT |=0x08; // Resistencia de pull-up en P1.3
  P2SEL =0x00; // para P2.6 y P2.7 GPIO
  conf_CLK();

  // Inicializamos el LCD
  LCD_INI (Dos_Lineas_5x8, Derecha_NoDesplaza); 
  LCD_Control (CurOFF_BliOFF); LCD_FilaColumna(0,1);
  LCD_Cadena ("Parado. Pulsa"); 
  LCD_FilaColumna(1,1);
  LCD_Cadena ("para iniciar");
  // Hab. las interrupciones y deshabi la CPU y MCLK 
__enable_interrupt(); // para el include io430.h hay 
__bis_SR_register(LPM0_bits); //que poner las dos lineas
}


#pragma vector=PORT1_VECTOR // Rutina de servicio para la interrupcio´n del Puerto 1 
__interrupt void Port_1(void){
  /*No voy a trabajar con nu´meros sino que voy a utilizar el co´digo ascii de cada cara´cter a presentar.
  Como los co´digos de los nu´meros van del 30h (el 0, 48d) en adelante, utilizo este valor como punto de
  partida y voy sumando para calcular el co´digo del valor a representar en cada momento */
  int i = 0;
  int j = 0;
  p++;
  LCD_Control (ClearDisplay); 
  LCD_FilaColumna(0,1); 
  LCD_Cadena ("Contando..");
  for (j =0 ; j < 10; j++){
    LCD_FilaColumna (0,11);
    LCD_Caracter (j+48); //sumo 48 para el 0 y sucesivos
    RETARDO();
    {
      for (i = 0; i < 10; i++){
        LCD_FilaColumna (0,12); 
        LCD_Caracter (i+48);
        RETARDO();
      } 
    }
    P1IFG &= ~0x08;
  }
  LCD_Control (ClearDisplay); 
  LCD_FilaColumna(0,1); 
  LCD_Cadena ("Parado. Pulsa"); 
  LCD_FilaColumna(1,1); 
  LCD_Cadena ("para repetir"); 
  LCD_FilaColumna(1,14); 
  LCD_Entero (p);
}
/* Configuramos la frecuencia de reloj a 1 MHz. */
void conf_CLK (void){
  DCOCTL = CALDCO_1MHZ; // calibra a 1MHz 
  BCSCTL1 = CALBC1_1MHZ;
}

void RETARDO(void) {
  int r = 0xFFFF;
  do (r--);
  while (r != 0); 
}