#include <msp430.h>

char cadena[3];
char j = 0;
float temp;


int main(void){

    //CONFIGURACION DE LOS PUERTOS
    P1DIR &=~BIT1; //Configuración como entrada
    P1REN|=BIT1;   // Habilitar Resistencia
    P1OUT &=  BIT1; //Resistencia pull-up

    //CONFIGURACION DE LOS LEDS
    P1DIR |= BIT0; // P1.0 como Salida (led rojo)
    P4DIR |= BIT7; // P4.7 como Salida (led verde)
    P4OUT =~BIT7;
    P1OUT =~BIT0;


    //CONFIGURACIÓN UART
    WDTCTL = WDTPW + WDTHOLD; // Paramos el WDT
    P3SEL |= BIT3+BIT4; // Seleccionamos P3.3-4 como USCI_A0 TXD/RXD
    UCA0CTL1 |= UCSWRST; // Colocamos la Máquina de Estados en Reset
    UCA0CTL1 |= UCSSEL_1; // ACLK como fuente de Reloj
    UCA0BR0 = 0x03; // 32768 Hz 9600 baudios (Tabla 36-4 de la
    UCA0BR1 = 0x00; // User Guide)
    UCA0MCTL |= UCBRS_3 + UCBRF_0; // Modulacion UCBRSx=3, UCBRFx=0
    UCA0CTL1 &= ~UCSWRST; // Iniciamos la Máquina de Estados
    UCA0IE |= UCRXIE; // Habilitamos la interrupción USCI_A0 RX


    // CONFIGURACIÓN ADC INTERNA
     REFCTL0 &= ~REFMSTR; // Reset REFMSTR para control por parte del ADC12
    // Activamos el ADC, la referencia a 1,5 V y establecemos el muestreo
     ADC12CTL0 = ADC12ON+ADC12REFON+ADC12SHT0_2;
     ADC12CTL1 = ADC12SHP; //Timer de muestreo
     ADC12MCTL0 = ADC12INCH_10 + ADC12SREF_1; // A10 = Sensor temperatura
     ADC12IE = 0x01; // Habilitamos ADC12IFG.1
     __delay_cycles(100); // retardo para el establecimiento de la referencia
    ADC12CTL0 |= ADC12ENC; // Habilitación de la conversión
    ADC12CTL0 |= ADC12SC;

    __bis_SR_register(  GIE); // Modo LPM3, interrupciones habilitadas
    __no_operation(); // Para debug
}

#pragma vector=ADC12_VECTOR
__interrupt void ADC12ISR (void)
{
 switch(ADC12IV)
 {
 case 0: break; // Vector 0: No interrupt
 case 2: break; // Vector 2: ADC overflow
 case 4: break; // Vector 4: ADC timing overflow
 case 6: // Vector 6: ADC12IFG0
 {temp = ADC12MEM0;}
 default: break;
 }
}
#pragma vector=USCI_A0_VECTOR
__interrupt void USCI_A0_ISR(void)
{
    switch(UCA0IV)
    {
    case 0:break; // Vector 0 - sin interrupción
    case 2: // Vector 2 - RXIFG
        cadena[j++] = UCA0RXBUF;
        if (j > sizeof cadena - 1) // Guardamos hasta completar el tamaño
        {   j = 0;

        if(cadena[0]=="O"&& cadena[1]=="K"){ //Comprobación de la cadena
            //Encender Led
            P4OUT = BIT7;
            }else {P4OUT = ~BIT7;}
        }
        break;
    case 4: // Vector 4 - TXIFG

         if (P1IN & BIT1) // Comprobamos el pulsador activado
         {
             UCA0TXBUF=temp;
         }
    default: break;
    }
}



