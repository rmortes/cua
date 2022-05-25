/*
Practica 5 b mejorada
*/

#include "io430.h"
#include "LCD4bits.c"

/* Declaracion de variables para la cuenta atras */
int i,j,run=0;

/* Funcion para configurar los puertos de entrada y salida */
void config_port (void)
{
  P1DIR |= 0xFF;                                  // Configura el puerto 1 como salida
  P1OUT &= ~0xFF;                                 // Todo el puerto 1 a 0.
  P2SEL =0x00;                                    // Puerto 2 como I/O general
  IE1 |= NMIIE;                                   // Activa el NMI
}

/* Funcion para configurar los botones */
void config_buttons(void)
{
  P2DIR &= ~0xC0;                                 // P2.7 y P2.6 como I/O general (GPIO)
  P2REN |= 0xC0;                                  // P2.7 y P2.6 resistencia habilitada
  P2OUT |= 0xC0;                                  // P2.7 y P2.6 como entrada
  P2IES |= 0xC0;                                  // Flanco de bajada en P2.7 y P2.6
  P2IFG &= ~0xC0;                                 // P2.7 y P2.6 resistencia pull-up
  P2IE |= 0xC0;                                   // Interrupciones locales habilitadas en P2.7 y P2.6
}

/* Funcion para configurar la pantalla */
void config_screen (void)
{
  LCD_INI (Dos_Lineas_5x8, Derecha_NoDesplaza);   // Configuramos el msp para funcionar con el LCD
  LCD_Control (CurOFF_BliOFF); 
  LCD_Control(ClearDisplay);                      // Borra el display
}

/* Programa Principal */
int main(void)
{
  WDTCTL = WDTPW + WDTHOLD + WDTNMI;  // Apagamos el Watch dog y ponemos a 1 el WDTNMI para activar la patilla RST/NMI como NMI
  config_port();                      // Configura los puertos de entrada y salida
  config_screen();                    // Configura la pantalla
  __enable_interrupt() ;              // Habilita las interrupciones
  
  for(;;){
    if(run==1){
      LCD_Control(ClearDisplay);      // Borra el display
      LCD_FilaColumna(0,1);
      LCD_Cadena ("Contando..");      // Imprime contando
      for (j = 9; j >= 0; j--){       // Bucle para las decenas
        LCD_FilaColumna (0,11);
        LCD_Caracter (j+48);          // Imprime el caracter en la posicion 0,11
        __delay_cycles(250000);       // Retardo de 0,25 segundos
        for (i = 8; i >= 0; i--){     // Bucle para las unidades
          for(;run==0;);              // Bucle infinito si la variable run es igual a 0, se queda parado aqui
          LCD_FilaColumna (0,12);
          LCD_Caracter (i+48);        //Imprime el caracter en la posicion 0,12  
          __delay_cycles(250000);     // Retardo de 0,25 segundos
          if(i==0){                   // Si las unidades han llegado a 0 imprime un 9 despues del retardo
          LCD_FilaColumna (0,12);
          LCD_Caracter (57);
          }     
        }
      } 
    }
  }
}

#pragma vector=NMI_VECTOR         // Vector de interrupcion vector=0xFFFC

/* Funcion que se ejecuta en la interrupcion del boton Reset */
__interrupt void nmi_ (void)
{
  LCD_Control(ClearDisplay);      // Borra el display
  LCD_Cadena ("Esperando...");    // Imprime esperando
  IFG1 &= ~NMIIFG;                // Borra el flag del NMI
  IE1 |= NMIIE;                   // Activa el NMI
  config_buttons();               // Configura los botones en 2.6 y 2.7
  __enable_interrupt() ;          // Activa las interrupciones
  __bis_SR_register(LPM0_bits);   // Bajo consumo
}

#pragma vector=PORT2_VECTOR       // Vector de interrupcion vector=0xFFE6

/* Funcion que se ejecuta en la interrupcion de una entrada del puerto 2 */
__interrupt void P2_Interrupt(void)
{
  if (P2IFG & BIT7) {               // Si pulsa P2.7
    __low_power_mode_off_on_exit(); // Sale del modo bajo consumo
    P2IFG &= ~0x80;                 // Borra el flag del P2.7
    run=1;
  }
  if (P2IFG & BIT6) {               // Si pulsa P2.6
    P2IFG &= ~0x40;                 // Borra el flag del P2.6
    run^=1;
    if (run==0){                    // Si no estaba pausado
      P2IE = 0x40;                  // Solo 2.6 tendra interrupcion para que 2.7 no reactive la cuenta, solo 2.6
      LCD_FilaColumna(0,1);      
      LCD_Cadena ("En pausa..");    // Imprime en pantalla el texto En pausa.. 
    }else{                          // Si ya estaba pausado
      P2IE = 0xC0;                  // Interrupciones locales habilitadas para P2.7 y P2.6
      LCD_FilaColumna(0,1);       
      LCD_Cadena ("Contando..");    // Imprime en pantalla el texto Contando..
    }
  }
}

