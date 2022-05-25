#include <msp430.h> 

/*
 * main.c
 */
int main(void) {
    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer
    P4DIR |= BIT7;              //P4.7 como salida
    P2DIR &= ~BIT1;             //P2.1 como entrada
    P3DIR |= BIT0;              //P3.0 como salida
    P3OUT &= ~BIT0;             //P3.0 empieza apagado

    P1DIR &= ~BIT1;             //P1.1 como entrada
    P3DIR |= BIT1;              //P3.1 como salida
    P3OUT &= ~BIT1;             //P3.1 empieza apagado

   //CONFIGUGACION DE P1.1 COMO INTERRUPCION POR FLANCO DE BAJADA
       P1REN |= BIT1;              //P1.1 resistencia interna habilitada
       P1OUT |= BIT1;              //P1.1 resistencia como pull-up
       P1IES |= BIT1;              //P1.1 configurado como flanco de bajada
       P1IFG &= ~BIT1;             //P1.1 a cero para evitar interrupciones pendientes
       P1IE |= BIT1;               //P1.1 interrupcion habilitada



//CONFIGUGACION DE P2.1 COMO INTERRUPCION POR FLANCO DE BAJADA
    P2REN |= BIT1;              //P2.1 resistencia interna habilitada
    P2OUT |= BIT1;              //P2.1 resistencia como pull-up
    P2IES |= BIT1;              //P2.1 configurado como flanco de bajada
    P2IFG &= ~BIT1;             //P2.1 a cero para evitar interrupciones pendientes
    P2IE |= BIT1;               //P2.1 interrupcion habilitada


//PROGRAMA PRINCIPAL
while(1){
    __enable_interrupt();

       P4OUT |=BIT7;
       __delay_cycles(1000000);
       P4OUT &=~BIT7;
       __delay_cycles(1000000);






}
}

//RUTINA DE INTERRUPCION DE P2.1
#pragma vector=PORT2_VECTOR
__interrupt void Port_2(void)
{
    P4OUT&= ~BIT7;
    for(;;){
        __delay_cycles(720);
        P3OUT ^= BIT0;
        __delay_cycles(80);
        P3OUT ^= BIT0;
        P2IFG &= ~BIT1;
    }

}

//RUTINA DE INTERRUPCIÓN DE P1.1
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
    P4OUT&= ~BIT7;
    for(;;){
        __delay_cycles(150);
        P3OUT ^= BIT1;
        __delay_cycles(350);
        P3OUT ^= BIT1;
        P1IFG &= ~BIT1;
    }

}


