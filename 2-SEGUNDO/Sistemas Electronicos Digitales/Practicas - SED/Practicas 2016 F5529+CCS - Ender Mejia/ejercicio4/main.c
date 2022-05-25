#include <msp430.h> 

int main(void) {

	WDTCTL = WDTPW | WDTHOLD;

	P4DIR |= BIT0;	//P4.0 SALIDA (Motor)
	P4OUT &= ~BIT0;	//apagamos al inicio

	P2DIR &= ~BIT1;	//P2.1 ENTRADA (boton de control)
	P2REN |= BIT1;	//se habilita la resistencia pull-up
	P2OUT |= BIT1;

	P2IE|=BIT1;		//HABILITA INTERRUPCIONES
	P2IES|=BIT1;	//FLANCO DE BAJADA
	P2IFG &=~BIT1;	//flag a 0, no hay interrupciones pendientes

	__bis_SR_register(LPM0_bits + GIE);
	//habilitamos interrupciones generales  IMPORTANTE!!!
	//modo LPM0
	__no_operation(); //para depurar

}

//interrupcion
#pragma vector=PORT2_VECTOR
__interrupt void Encender(){

	//se inicializan todos los leds a 0
	__delay_cycles(10000000); //retardo 5 segundos
	P4OUT |= BIT0; //encendemos el motor
	//no es necesario realizar ninguna acción con la entrada P4.2

	P2IFG &= ~BIT1; //borramos el flag

}
