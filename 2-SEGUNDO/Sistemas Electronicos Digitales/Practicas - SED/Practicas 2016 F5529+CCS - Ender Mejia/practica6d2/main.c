//Ejercicio 1.3.3
#include <msp430.h>


int main(void)
{
	WDTCTL = WDTPW + WDTHOLD; 					// Stop WDT

	//Configuración patilla salida
	P1DIR |= BIT2; 								// P1.2 salida
	P1SEL |= BIT2; 								// P1.2 selecciona la función TA0.1

	//configuracion S1(P2.1) y S2(P1.1)
	P2DIR &= ~BIT1;	//S1
	P2REN |= BIT1;                 	//Habilita la resistencia en P2.1
	P2OUT |= BIT1;                 	//Resistencia --> pull-up
	P2IE |= BIT1;                 	//P2.1 habilitar interrupciones
	P2IES |= BIT1;                 	//P2.1 interrupciones
	P2IFG &= ~BIT1;                	// borramos interr pendientes

	P1DIR &= ~BIT1;	//S2
	P1REN |= BIT1;                 	//Habilita la resistencia en P1.1
	P1OUT |= BIT1;                 	//Resistencia --> pull-up
	P1IE |= BIT1;                 	//P1.1 habilitar interrupciones
	P1IES |= BIT1;                 	//P1.1 interrupciones
	P1IFG &= ~BIT1;                	// borramos interr pendientes

	__bis_SR_register(GIE); //interr generales

	//Configuramos timer
	TA0CTL = TASSEL_2 + MC_1 + ID_0 + TACLR;
	//TASSEL_2 = SMCLK (0=TACLK  1=ACLK  3=INCLK)
	//MC_1 = creciente hasta TACCR0 (0=parada, 2=hasta FFFF)
	//ID_0 = divide la frec de Reloj/1 (0=f/1  1=f/2  2=f/4  3=f/8)
	//TACLR = borra la cuenta

	TA0CCTL1 = OUTMOD_7;
	//PWM OUTPUT MODE:
	//0=ValorDeBit	1=Set		2=Toggle/Reset	3=Set/Reset
	//4=Toggle		5=Reset		6=Toggle/Set	7=Reset/Set
	//OUTMOD_2 para que se meta en una interrupcion
	//OUTMOD_7 para una cuenta

	//Configuración para 4Khz
	TA0CCR0 = 250;							// ncycles = f_trabajo/f_solicitada = 1Mhz/4Khz
	TA0CCR1 = 50;							// DC = 18% de 250 (TA0CCR0) para que arranque

}

#pragma vector=PORT2_VECTOR		//S1 (P2.1)
__interrupt void  PORT2_ISR(){
	TA0CCR1 = TA0CCR1 + 5; //aumentamos 5 la velocidad
	P2IFG &= ~BIT1; //borramos el flag
}

#pragma vector=PORT1_VECTOR
__interrupt void PORT1_ISR(){
	TA0CCR1 = TA0CCR1 - 5; //decrementamos 5 la velocidad
	P1IFG &= ~BIT1;//borramos el flag
}

