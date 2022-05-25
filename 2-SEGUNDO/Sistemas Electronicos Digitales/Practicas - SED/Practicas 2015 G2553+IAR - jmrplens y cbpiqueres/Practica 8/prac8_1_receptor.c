#include <io430.h>
#include "LCD4bits.c"

char buffer[16];                        // Cadena de caracteres que recibe la temperatura
int rx_flag;			        // Flag para saber si se ha terminado la recepcion
char rx_char;			        // Caracter que se recibe a traves de la UART

/****************** Cabeceras de funciones *************************/
void config_screen();
void config_uart(void);
unsigned char uart_leec();
void uart_lees(char* cadena, int length);
/*******************************************************************/
/********************** Funcion principal *************************/
int main(void)
{
    WDTCTL = WDTPW + WDTHOLD;           // Paramos WatchDog
    BCSCTL1 = CALBC1_1MHZ;              // Reloj a 1MHz
    DCOCTL = CALDCO_1MHZ;
    config_screen();                    // Configuracion de la pantalla
    config_uart();                      // Configuracion de la UART
    __enable_interrupt();		// Interrupciones habilitadas	
    LCD_FilaColumna(1,0);        
    LCD_Cadena ("TCPUremo:");
    for(;;){
        uart_lees(buffer,16);           // Lee una cadena de caracteres que va a recibir
        LCD_FilaColumna(1,9);
        LCD_Cadena (buffer);            // Imprime la cadena de caracteres
        LCD_FilaColumna(1,14);
        LCD_Cadena ("^C");
    }
}
/*******************************************************************/
/****************** Configuracion del LCD  *************************/
void config_screen(){
    LCD_INI (Dos_Lineas_5x8, Derecha_NoDesplaza);
    LCD_Control (CurOFF_BliOFF);
    LCD_Control (ClearDisplay);
}
/*******************************************************************/
/****************** Configuracion de la UART **********************/
void config_uart(void)
{
    P1SEL = BIT1;		        // Configuramos P1.1 como receptor de datos
    P1SEL2 = BIT1;
    UCA0CTL1 |= UCSSEL_2;               // Reloj SMCLK
    UCA0BR0 = 104;                      // SMCLK/9600=104
    UCA0BR1 = 0;
    UCA0MCTL = UCBRS0;                  // Modulacion UCBRSx. Ver tabla 15-4 del User Guide, "Typical Baud Rates and Errors"
    UCA0CTL1 &= ~UCSWRST;               // Maquina de estado de la USCI
    IE2 |= UCA0RXIE;	                // Activa interrupciones de recepcion
    rx_flag = 0;
}
/*******************************************************************/
/*************** Funcion para leer un caracter *********************/
unsigned char uart_leec()				
{
    while (rx_flag == 0);               // Espera a que la recepcion de la UA este disponible
    rx_flag = 0;			// Borra el flag
    return rx_char;                     // Devuelve el caracter leido
}
/*******************************************************************/
/*************** Funcion para leer una cadena  *********************/
void uart_lees(char* cadena, int length)     
{
    int i = 0;
    while((i < length)){		// Recorre la cadena en toda su longitud y lo envia a leer caracter
        cadena[i] = uart_leec();
        if(cadena[i] == '\r'){		// Si se recibe un retorno, se termina de transmitir la cadena
          for( ; i < length ; i++){	// Borra el resto de la cadena, incluido el /r recibido
                cadena[i] = '\0';
            }
            break;                      // Sale del While
        }
        i++;
    }
}
/*******************************************************************/
/*************** Interrupcion de recepcion *************************/
#pragma vector = USCIAB0RX_VECTOR		
__interrupt void USCI0RX_ISR(void)
{
    rx_char = UCA0RXBUF;		// Copia un caracter al buffer del recepcion
    rx_flag = 1;			// Configuramos el flag de recepcion
}
/*******************************************************************/