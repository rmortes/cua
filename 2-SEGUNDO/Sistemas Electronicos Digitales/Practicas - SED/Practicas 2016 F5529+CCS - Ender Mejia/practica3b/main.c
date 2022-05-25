#include <msp430.h> 

unsigned int i;

int main(void) {

	WDTCTL = WDTPW | WDTHOLD;

	P6DIR |= BIT5;//D1;
	P3DIR |= BIT4;//D2;
	P3DIR |= BIT3;//D3;
	P1DIR |= BIT6;//D4;
	P6DIR |= BIT6;//D5;
	P3DIR |= BIT2;//D6;
	P3DIR |= BIT1;//D7;
	P3DIR |= BIT0;//D8;

	P2DIR &= ~BIT0;

	P2REN |= BIT0;			//se habilita la resistencia pull-up
	P2OUT |= BIT0;

	P2IE|=BIT0; //HABILITA INTERRUPCIONES
	P2IES|=BIT0;//FLANCO DE BAJADA
	P2IFG &=~BIT0;//flag a 0, no hay interrupciones pendientes
	_BIS_SR(GIE);//habilitamos interrupciones generales  IMPORTANTEEEEEEEEEEEEEEEEERL

	for(;;){

		//se inicializan todos los leds a 0
		P6OUT &= ~BIT5;
		P3OUT &= ~BIT4;
		P3OUT &= ~BIT3;
		P1OUT &= ~BIT6;
		P6OUT &= ~BIT6;
		P3OUT &= ~BIT2;
		P3OUT &= ~BIT1;
		P3OUT &= ~BIT0;
		__delay_cycles(1048576/2);

		P3OUT |= BIT0;
		__delay_cycles(1048576/2);

		P3OUT |= BIT1;
		__delay_cycles(1048576/2);

		P3OUT |= BIT2;
		__delay_cycles(1048576/2);

		P6OUT |= BIT6;
		__delay_cycles(1048576/2);

		P1OUT |= BIT6;
		__delay_cycles(1048576/2);

		P3OUT |= BIT3;
		__delay_cycles(1048576/2);

		P3OUT |= BIT4;
		__delay_cycles(1048576/2);

		P6OUT |= BIT5;
		__delay_cycles(1048576/2);
	}

}
//interrupcion
#pragma vector=PORT2_VECTOR
__interrupt void P2_Interrupt(){

	//se inicializan todos los leds a 0
	P6OUT &= ~BIT5;
	P3OUT &= ~BIT4;
	P3OUT &= ~BIT3;
	P1OUT &= ~BIT6;
	P6OUT &= ~BIT6;
	P3OUT &= ~BIT2;
	P3OUT &= ~BIT1;
	P3OUT &= ~BIT0;
	__delay_cycles(1048576/2);

	P6OUT |= BIT5;
	__delay_cycles(1048576/2);

	P3OUT |= BIT4;
	__delay_cycles(1048576/2);

	P3OUT |= BIT3;
	__delay_cycles(1048576/2);

	P1OUT |= BIT6;
	__delay_cycles(1048576/2);

	P6OUT |= BIT6;
	__delay_cycles(1048576/2);

	P3OUT |= BIT2;
	__delay_cycles(1048576/2);

	P3OUT |= BIT1;
	__delay_cycles(1048576/2);

	P3OUT |= BIT0;
	__delay_cycles(1048576/2);

	for(i=0;i<10;i++){

		P6OUT &= ~BIT5;
		P3OUT &= ~BIT4;
		P3OUT &= ~BIT3;
		P1OUT &= ~BIT6;
		P6OUT &= ~BIT6;
		P3OUT &= ~BIT2;
		P3OUT &= ~BIT1;
		P3OUT &= ~BIT0;
		__delay_cycles(1048576);

		P6OUT |= BIT5;
		P3OUT |= BIT4;
		P3OUT |= BIT3;
		P1OUT |= BIT6;
		P6OUT |= BIT6;
		P3OUT |= BIT2;
		P3OUT |= BIT1;
		P3OUT |= BIT0;
		__delay_cycles(1048576);

	}

	P2IFG &= ~BIT0;

}
