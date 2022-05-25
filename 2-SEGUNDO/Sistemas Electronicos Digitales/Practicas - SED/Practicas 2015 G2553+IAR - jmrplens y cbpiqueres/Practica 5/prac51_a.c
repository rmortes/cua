/*
Practica 5 a - Sin interrupcion de NMI/Reset
*/

#include "io430.h"
#include "LCD4bits.c"

/* Declaracion de variables para la cuenta atras */
int i,j,parar=0;

/* Funcion para mostrar en el LCD la cuenta atras desde 99 a 0 */
void CONT (void)
{
  for (j = 9; j >= 0; j--){               // Bucle para las decenas
    LCD_FilaColumna (0,11);
    LCD_Caracter (j+48);                  // Imprime el caracter en la posicion 0,11
    __delay_cycles(250000);               // Retardo de 0,25 segundos
      for (i = 8; i >= 0; i--){           // Bucle para las unidades
            for(;parar==1;){}             // Bucle infinito cuando parar valga 1. Su valor cambia al pulsar 2.6
        LCD_FilaColumna (0,12);
        LCD_Caracter (i+48);              //Imprime el caracter en la posicion 0,12  
        __delay_cycles(250000);           // Retardo de 0,25 segundos
        if(i==0){                         // Si las unidades han llegado a 0 imprime un 9 despues del retardo
          LCD_FilaColumna (0,12);
          LCD_Caracter (57);
      }     
    }
  } 
}

/* Programa Principal */
int main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                       // Apagamos el Watch dog
  P1DIR |= 0xFF;                                  // Configura el puerto 1 como salida
  P1OUT &= ~0xFF;                                 // Todo el puerto 1 a 0.
  P2SEL =0x00;                                    // Puerto 2 como I/O general
  LCD_INI (Dos_Lineas_5x8, Derecha_NoDesplaza);   // Configuramos el msp para funcionar con el LCD
  LCD_Control (CurOFF_BliOFF); 
  LCD_Control(ClearDisplay);                      // Borra el display
  LCD_Control(ClearDisplay);                      // Borra el display
  LCD_Cadena ("Esperando...");                    // Imprime esperando
  P2DIR &= ~0xC0;                                 // P2.7 y P2.6 como I/O general (GPIO)
  P2REN |= 0xC0;                                  // P2.7 y P2.6 resistencia habilitada
  P2OUT |= 0xC0;                                  // P2.7 y P2.6 como entrada
  P2IES |= 0xC0;                                  // Flanco de bajada en P2.7 y P2.6
  P2IFG &= ~0xC0;                                 // P2.7 y P2.6 resistencia pull-up
  P2IE |= 0xC0;                                   // Interrupciones locales habilitadas en P2.7 y P2.6
  __enable_interrupt() ;                          // Activa las interrupciones
  __bis_SR_register(LPM0_bits);                   // Bajo consumo
}
#pragma vector=PORT2_VECTOR       // Vector de interrupcion vector=0xFFE6

/* Funcion que se ejecuta en la interrupcion de una entrada del puerto 2 */
__interrupt void P2_Interrupt(void)
{
  if (P2IFG & BIT7) {       // Si pulsa P2.7
    __low_power_mode_off_on_exit();
    __enable_interrupt() ;        // Activa las interrupciones
    P2IFG &= ~0x80;               // Borra el flag del P2.7
    P1OUT = 0x04;
    LCD_Control (ClearDisplay);   // Borra el display
    LCD_FilaColumna(0,1);      
    LCD_Cadena ("Contando..");    // Imprime en pantalla el texto Contando..
    LCD_FilaColumna (0,11); 
    LCD_Cadena ("99");            // Añadimos en la posicion 0,11 la cadena 99 para que se visualice la primera cifra antes de decrementar
    for(;;)CONT();                // Bucle infinito para que realice la cuenta atras continuamente
  }
  if (P2IFG & BIT6) {       // Si pulsa P2.6
    P2IFG &= ~0x40;               // Borra el flag del P2.6
    __enable_interrupt() ;        // Activa las interrupciones
    parar^=1;                     // Variable para saber si es primera o segunda pulsacion. Afecta a la funcion CONT
    if (parar==1){                // Si es la primera vez se imprime en pausa
      LCD_FilaColumna(0,1);      
      LCD_Cadena ("En pausa..");  // Imprime en pantalla el texto En pausa.. 
    }else{                        // si es la segunda vez imprime Contando
      LCD_FilaColumna(0,1);       
      LCD_Cadena ("Contando..");  // Imprime en pantalla el texto Contando..
    }
  }
}
