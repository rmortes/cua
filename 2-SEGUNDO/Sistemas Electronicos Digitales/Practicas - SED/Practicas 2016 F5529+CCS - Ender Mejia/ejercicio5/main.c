#include <msp430.h>

int main(void) {

	WDTCTL = WDTPW | WDTHOLD;

	P3DIR |= BIT0;	//P4.0 SALIDA (Motor)
	P3OUT &= ~BIT0;	//apagamos al inicio

	//P2.0
	P2DIR &= ~BIT0;	//P2.2 ENTRADA (boton de encendido)
	P2REN |= BIT0;	//se habilita la resistencia pull-up
	P2OUT |= BIT0;
	P2IE|=BIT0;		//HABILITA INTERRUPCIONES
	P2IES|=BIT0;	//FLANCO DE BAJADA
	P2IFG &=~BIT0;	//flag a 0, no hay interrupciones pendientes

	//P2.2
	P2DIR &= ~BIT2; //P2.2 ENTRADA (boton de apagado)
	P2REN |= BIT2;	//pull-up
	P2OUT |= BIT2;
	P2IE|=BIT2;		//HABILITA INTERRUPCIONES
	P2IES|=BIT2;	//FLANCO DE BAJADA
	P2IFG &=~BIT2;	//flag a 0, no hay interrupciones pendientes


	__bis_SR_register(LPM0_bits + GIE);//habilitamos interrupciones generales  IMPORTANTE!!!
	__no_operation(); //para depurar

}

//interrupcion
#pragma vector=PORT2_VECTOR
__interrupt void MiInterrupcion(){



	if((P2IN & BIT0)==0){
		__delay_cycles(250000);//retardo antirrebote
		__delay_cycles(9750000);//10 segundos retardo(contando el antirrebote)
		P3OUT |= BIT0; //encendemos el motor
	}
	if((P2IN & BIT2)==0){
		__delay_cycles(250000);//retardo antirrebote
		P3OUT &= ~BIT0;//apagamos el motor
	}
	//no es necesario realizar ninguna acción con la entrada P4.2

	P2IFG &= ~BIT1;


}
