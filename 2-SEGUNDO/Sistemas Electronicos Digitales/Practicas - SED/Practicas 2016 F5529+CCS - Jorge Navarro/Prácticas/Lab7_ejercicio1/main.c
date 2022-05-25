#include <msp430.h> 
int main(void) {
	WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	//Comparador
	P1DIR|=BIT0;	// Configuramos salida.
	P1SEL|=BIT0;	// Selecciona funcion CBOUT.
	P1OUT&= ~BIT0;	// Inicialmente apagado

	P1DIR|=BIT2;
	P1SEL|=BIT2;

    CBCTL1 |= CBON;
    CBCTL3 = BIT0; //Select CB1 and the port P6.0

    CBCTL0 |= CBIPEN + CBIPSEL_0; //Multiplexor IP + Bit1 imput
    CBCTL2 |= CBRSEL+CBRS_3+CBREFL_3;//1 OP-AMP -Vref2.5v
	__delay_cycles(75);

	while(1){
		// Es como sensor de bateria, si
		if(CBCTL1 & CBOUT){
			//Señal LPM
			TA0CTL=TASSEL_2+ID_2+MC_1+TACLR;
			TA0CCTL1=OUTMOD_2;
			TA0CCR0=31250;
			TA0CCR1=23428;
		}else{
			TA0CCTL1=OUTMOD_0;
			TA0CCTL1 &= ~OUT; // Material consulta pag 26
		}
		return 0;
	}
}

