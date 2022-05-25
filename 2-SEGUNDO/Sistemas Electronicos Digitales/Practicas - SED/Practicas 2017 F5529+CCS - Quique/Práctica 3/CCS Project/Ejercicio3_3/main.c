#include <msp430.h> 

/*
 * main.c
 */
void configport (){
    P2DIR &= ~BIT1;             // P2.1 como entrada
    P1DIR &= ~BIT1;             // P1.1 como entrada

    P2REN |= BIT1;              //Resistencia pull up botón 1
    P2OUT |= BIT1;              //Resistencia pull up botón 1

    P1REN |= BIT1;              //Resistencia pull up botón 2
    P1OUT |= BIT1;              //Resistencia pull up botón 2

    P1DIR |= BIT2;             // P1.2 como salida
    P1SEL |= BIT2;             // P1.2 TA0.1
}

int configtimer(float v){
    TA0CTL = TASSEL_2 + MC_1 + TACLR;    // ACLK, Up Mode, Clear
    TA0CCTL1 = OUTMOD_2;                 //Toggle/reset
    float DC=v/100.0;                    // Porcentaje DC
    TA0CCR0 = 260;                       // Registro CCR0
    TA0CCR1 = 260-(260*DC);              // Registro CCR1
}

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer
    configport();
    float v=0.0;                // Inicializamos v
    configtimer(v);
    while (1){

        if((P2IN & 0x02)==0){               //Comprobamos si el botón S1 está pulsado
            v=v+5;                          //Aumentamos v+5
            float DC=v/100.0;               //Porcentaje DC
            TA0CCR1=260-(260*DC);           //Registro CCR1
            if(TA0CCR1>260){                //Si CCR1 se desborda lo reseteamos a 260
                TA0CCR1=260;
            }
            __delay_cycles(250000);         //Para que de tiempo a pulsar S1 sin llegar al valor máximo
        }
        if((P1IN & 0x02)==0){               //Comprobamos si el botón S2 está pulsado
            v=v-5;                          //Aumentamos v-5
            float DC=v/100.0;               // Porcentaje DC
            TA0CCR1=260-(260*DC);           // Registro CCR1
            if(TA0CCR1<0){                  // Si CCR1 se desborda lo reseteamos a 0
                TA0CCR1=0;
            }
             __delay_cycles(250000);        //Para que de tiempo a pulsar S2 sin llegar al valor máximo
        }
    }

	return 0;
}
