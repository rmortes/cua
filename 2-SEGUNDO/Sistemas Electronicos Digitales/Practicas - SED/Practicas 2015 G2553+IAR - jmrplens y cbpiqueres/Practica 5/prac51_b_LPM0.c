/*
Practica 5 b - Con la pausa generada por la activacion del bajo consumo
*/

#include "io430.h"
#include "LCD4bits.c"

/* Declaracion de variables para la cuenta atras */
int i,j,parado=0;

/* Funcion para mostrar en el LCD la cuenta atras desde 99 a 0 */
void CONT (void)
{
  for (j = 9; j >= 0; j--){               // Bucle para las decenas
    LCD_FilaColumna (0,11);
    LCD_Caracter (j+48);                  // Imprime el caracter en la posicion 0,11
    __delay_cycles(250000);               // Retardo de 0,25 segundos
      for (i = 8; i >= 0; i--){           // Bucle para las unidades
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
void config_port (void)
{
  
  
  
}
/* Programa Principal */
int main(void)
{
  WDTCTL = WDTPW + WDTHOLD + WDTNMI;              // Apagamos el Watch dog y ponemos a 1 el WDTNMI para activar la patilla RST/NMI como NMI
  P1DIR |= 0xFF;                                  // Configura el puerto 1 como salida
  P1OUT &= ~0xFF;                                 // Todo el puerto 1 a 0.
  P2SEL =0x00;                                    // Puerto 2 como I/O general
  IE1 |= NMIIE;                                   // Activa el NMI
  LCD_INI (Dos_Lineas_5x8, Derecha_NoDesplaza);   // Configuramos el msp para funcionar con el LCD
  LCD_Control (CurOFF_BliOFF); 
  LCD_Control(ClearDisplay);                      // Borra el display
  __enable_interrupt() ;
  for(;;);                                        // Bucle infinito hasta que empiece una interrupcion
}

#pragma vector=NMI_VECTOR         // Vector de interrupcion vector=0xFFFC

/* Funcion que se ejecuta en la interrupcion del boton Reset */
__interrupt void nmi_ (void)
{
  LCD_Control(ClearDisplay);      // Borra el display
  LCD_Cadena ("Esperando...");    // Imprime esperando
  IFG1 &= ~NMIIFG;                // Borra el flag del NMI
  IE1 |= NMIIE;                   // Activa el NMI
  // Ponemos aqui la activacion de interrupcion de P2.7 para que solo se ejecute cuando se haya pulsado el reset antes
  P2DIR &= ~0xC0;                                 // P2.7 y P2.6 como I/O general (GPIO)
  P2REN |= 0xC0;                                  // P2.7 y P2.6 resistencia habilitada
  P2OUT |= 0xC0;                                  // P2.7 y P2.6 como entrada
  P2IES |= 0xC0;                                  // Flanco de bajada en P2.7 y P2.6
  P2IFG &= ~0xC0;                                 // P2.7 y P2.6 resistencia pull-up
  P2IE |= 0xC0;                                   // Interrupciones locales habilitadas en P2.7 y P2.6
  
  __enable_interrupt() ;          // Activa las interrupciones
  __bis_SR_register(LPM0_bits);   // Bajo consumo
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
    if(parado==0){                // Si se pulsa por primera vez pausa el contador
      LCD_FilaColumna(0,1);      
      LCD_Cadena ("En pausa.."); 
      parado=1;
      __bis_SR_register(LPM0_bits);// Bajo consumo
    }
    if(parado==1){                // Si se pulsa por segunda vez continua con la cuenta
      parado=0;
      __low_power_mode_off_on_exit();
      LCD_FilaColumna(0,1);      
      LCD_Cadena ("Contando..");  
    }
  }
}
