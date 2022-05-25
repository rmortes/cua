#include <msp430.h>
char cadena[4];
char cadena[]="OK" ;
char j = 0;
float gradosC, Voltios;

int unidades;
int temp;

int main(void){


    //CONFIGURACION DE LOS PUERTOS
    P1DIR &=~BIT1; //Configuración como entrada
    P1REN|=BIT1;   // Resistencia Pull down
    P1DIR |= BIT0; // P1.0 como Salida (led rojo)
    P4DIR |= BIT7; // P4.7 como Salida (led verde)
    P1OUT =0x00; //empiezan apagados
    P4OUT =0x00; //empiezan apagados


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
    __bis_SR_register(LPM3_bits + GIE); // Modo LPM3, interrupciones habilitadas
    __no_operation(); // Para debug


}


#pragma vector=USCI_A0_VECTOR
__interrupt void USCI_A0_ISR(void)
{
    switch(UCA0IV)
    {
    case 0:break; // Vector 0 - sin interrupción
    case 2: // Vector 2 - RXIFG
        temp = UCA0RXBUF;
        Voltios = (1.5/4096.0)*temp;
        gradosC = (Voltios*25)/0.850;

         if(gradosC >35){
            P1OUT=BIT0; //Led Rojo
            P4OUT&=~BIT7;
         }else{
             P4OUT=BIT7;  //LED Verde
             P1OUT=~BIT0;
         }
        break;
    case 4: // Vector 4 - TXIFG

         if (P2IN & BIT1)  { // Comprobamos el pulsador activado
             UCA0TXBUF = cadena[i++]; // Transmitimos hasta completar la cadena
            }
    default: break;
    }
}


