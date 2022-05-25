#include <msp430.h> 

int main(void)
    {
        WDTCTL = WDTPW + WDTHOLD;   // stop watchdog timer

        P1DIR &= ~BIT1; // Configuramos P1.1 como entrada.
        P2DIR &= ~BIT1; // Configuramos P2.1 como entrada.
        P2DIR |= BIT0; // Selección de salida en P2.0
        P2SEL |= BIT0; // P2.0 como salida

        TA1CCR0 = 20000-1; // Periodo del PWM 50Hz
        TA1CCTL1 = OUTMOD_7; // CCR1 reset/set
        TA1CCR1 = 1500-1;   //Inicialmente en 90 grados

        //CONFIGUGACION DE P1.1 COMO INTERRUPCION POR FLANCO DE BAJADA
        P1REN |= BIT1;              //P1.1 resistencia interna habilitada
        P1OUT |= BIT1;              //P1.1 Resistencia como pull-up
        P1IES |= BIT1;              //P1.1 configurado como flanco de bajada
        P1IFG &= ~BIT1;             //P1.1 a cero para evitar interrupciones pendientes
        P1IE |= BIT1;               //P1.1 interrupción habilitada

        //CONFIGUGACION DE P2.1 COMO INTERRUPCION POR FLANCO DE BAJADA
        P2REN |= BIT1;              //P2.1 resistencia interna habilitada
        P2OUT |= BIT1;              //P2.1 Resistencia como pull-up
        P2IES |= BIT1;              //P2.1 configurado como flanco de bajada
        P2IFG &= ~BIT1;             //P2.1 a cero para evitar interrupciones pendientes
        P2IE |= BIT1;               //P2.1 interrupción habilitada

        TA1CTL = TASSEL_2 + MC_1 + TACLR; // SMCLK, Modo Ascendente, clear TAR
        __bis_SR_register(LPM0_bits+GIE); //LPM0 interrupciones habilitada
    }

    //RUTINA DE INTERRUPCION DE P1.1
    #pragma vector=PORT1_VECTOR
    __interrupt void Port_1(void)
    {
        TA1CCR1 += 1000; //Incrementa a 180 grados
        P1IFG &= ~BIT1;
    }

    //RUTINA DE INTERRUPCION DE P2.1
    #pragma vector=PORT2_VECTOR
    __interrupt void Port_2(void)
    {

        TA1CCR1 -= 1000; //Decrementa a 0 grados
        P2IFG &= ~BIT1;  }
