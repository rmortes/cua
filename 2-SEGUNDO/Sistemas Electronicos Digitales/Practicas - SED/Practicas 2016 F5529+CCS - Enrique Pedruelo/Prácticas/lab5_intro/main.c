#include <msp430.h>

volatile unsigned int n;

void retardo(){
	__delay_cycles(10000000);
}

int main(void){
	int i;

	WDTCTL = WDTPW + WDTHOLD;//Watchdog desactivado
	P1DIR |= BIT0;//P1.0 como salida
	P2DIR &= ~BIT1;//P2.1 como entrada
	P2REN |= BIT1;//P2.1 R pull-up
	P2OUT |= BIT1;//P2.1 High value "1"
	P2IES |= BIT1;//or flanco de bajada
	P2IFG &= ~BIT1;//No hay interrrupcion
	P2IE  |= BIT1;//Habilita interrupción P2.1
	P1IE  |= BIT1;
	P1DIR &= ~BIT1;
	P1REN |= BIT1;
	P1OUT &= ~BIT0;
	__bis_SR_register(GIE);//Bajo consumo   LPM4_bits +
	n=1;
	for(;;){
		for(i=0;i<n;i++){
			retardo();
			i++;
		}
		P1OUT ^= BIT0;
			// n ciclos     10000000
	}

}

#pragma vector=PORT2_VECTOR
__interrupt void Boton1(void)
{
	n=n-1;
	//P1OUT |= BIT0;
	P2IFG &= ~BIT1;//Quita la interrupcion

}


#pragma vector=PORT1_VECTOR
__interrupt void Boton2(void)
{
	n=n-1;
	//P1OUT &= ~BIT0;
	P1IFG &= ~BIT1;
}

