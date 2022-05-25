#include <msp430.h> 

/*
 * main.c
 */
int main(void) {
    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer
    P2DIR &= ~BIT1;             //P2.1 como entrada
    P3DIR |= BIT0;              //P3.0 como salida
    P3OUT &= ~BIT0;             //P3.0 empieza apagado

//CONFIGUGACION DE P2.1 COMO INTERRUPCION POR FLANCO DE BAJADA
    P2REN |= BIT1;              //P2.1 resistencia interna habilitada
    P2OUT |= BIT1;              //P2.1 resistencia como pull-up
    P2IES |= BIT1;              //P2.1 configurado como flanco de bajada
    P2IFG &= ~BIT1;             //P2.1 a cero para evitar interrupciones pendientes
    P2IE |= BIT1;               //P2.1 interrupcion habilitada


//PROGRAMA PRINCIPAL
while(1){
    __bis_SR_register(LPM0_bits + GIE); //Modo LPM4 y habilita interrupciones globales
    __no_operation();
}
}

//RUTINA DE INTERRUPCION DE P2.1
#pragma vector=PORT2_VECTOR
__interrupt void Port_2(void)
{
    for(;;){
        __delay_cycles(720);
        P3OUT ^= BIT0;
        __delay_cycles(80);
        P3OUT ^= BIT0;
        P2IFG &= ~BIT1;
    }

}
