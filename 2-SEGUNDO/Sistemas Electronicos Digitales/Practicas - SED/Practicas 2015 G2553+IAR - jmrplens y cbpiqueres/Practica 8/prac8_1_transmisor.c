#include <io430.h>
#include "LCD4bits.c"

unsigned int mem;                       // Volcamos el valor de la memoria del ADC aqui
volatile float temperatura;             // Para calcular la temperatura
static char cadena_temp[27];            // Cadena que almacena el valor de la temperatura
int tx_flag;			        // Flag para saber si se ha terminado la transmision
char tx_char;			        // Caracter que se envia a traves de la UART

/****************** Cabeceras de funciones *************************/
void config_ADC();
void temp();
void config_uart();
void uart_enviac(unsigned char c);
void uart_envias(char *str);
/*******************************************************************/
/********************** Funcion principal *************************/
int main(void)
{
    WDTCTL = WDTPW + WDTHOLD;           // Paramos WatchDog
    BCSCTL1 = CALBC1_1MHZ;              // Reloj a 1MHz
    DCOCTL = CALDCO_1MHZ;
    config_ADC();                       // Configuramos el ADC
    config_uart();                      // Configuramos la UART
    
  P1REN |=0x08; // Resistencia en entrada P1.3
  P1OUT |=0x08; // Resistencia de pull-up en P1.3
    __enable_interrupt();		// Interrupciones habilitadas
    for(;;){                            // Bucle infinito
        if((P1IN&BIT3)==0){
        __delay_cycles(500000);
        temp();                         // Calcula la temperatura
        uart_envias(cadena_temp);       // Envia la cadena con la temperatura
        uart_envias("\r");              // Final de cadena
        }
    }
}
/*******************************************************************/
/****************** Configuracion del ADC *************************/
void config_ADC()
{
    // INCH_10 es el Vout de el sensor de temperatura, 3.55mv/C.
    ADC10CTL1 = INCH_10;
    // VR+ = VREF+ . 64?ADC10CLKs . Referencia activada a 1.5V
    ADC10CTL0 = SREF_1 + ADC10SHT_3 + REFON + ADC10ON;
}
/*******************************************************************/
/****************** Calculo de la temperatura **********************/
void temp(){
    ADC10CTL0 |= ENC + ADC10SC;
    mem = ADC10MEM;
    // gCentigrados=((Vout_sensor/1024)*Vref)-Voffset_sensor)/V_centigrado=
    //  = ((ADC10MEM/1024)*1500mV)-986mV)/3.55mV
    temperatura = (float)((mem * 1500.00)/1024.00 - 986.60)/3.55;
    // Convierte el float a una cadena de caracteres
    sprintf(cadena_temp, "%.2f", temperatura); 
}
/*******************************************************************/
/****************** Configuracion de la UART **********************/
void config_uart(void)
{
    P1SEL = BIT2;		        // Configuramos P1.2 como emisor de datos
    P1SEL2 = BIT2;
    UCA0CTL1 |= UCSSEL_2;               // Reloj SMCLK
    UCA0BR0 = 104;                      // SMCLK/9600=104
    UCA0BR1 = 0;
    UCA0MCTL = UCBRS0;                  // Modulacion UCBRSx. Ver tabla 15-4 del User Guide, "Typical Baud Rates and Errors"
    UCA0CTL1 &= ~UCSWRST;               // Maquina de estado de la USCI
    IE2 |= UCA0TXIE;	                // Activa interrupciones de emision
    tx_flag = 0;
}
/*******************************************************************/
/*************** Funcion para enviar un caracter *******************/
void uart_enviac(unsigned char c)
{
    tx_char = c;			// Envia un caracter a la UART
    IE2 |= UCA0TXIE; 			// Activa las interrupciones de transmision
    while(tx_flag == 1);		// Espera a que se envie el caracter
    tx_flag = 1;			// Reactivamos el flag para el proximo envio
}
/*******************************************************************/
/****************** Funcion para enviar una cadena *****************/
void uart_envias(char *str)		
{
    while(*str) uart_enviac(*str++);	// Recorre la cadena y envia cada caracter a enviar caracter
}
/*******************************************************************/
/****************** Interrupcion de transmision ********************/
#pragma vector = USCIAB0TX_VECTOR		
__interrupt void USCI0TX_ISR(void)
{
    UCA0TXBUF = tx_char;		// Copia un caracter al buffer del transmision
    tx_flag = 0;			// Borra el flag de transmision
    IE2 &= ~UCA0TXIE; 			// Desactiva la interrupcion para no sobrecargar con envios vacios
}
/*******************************************************************/