//Ejercicio 1.3.2
#include <msp430.h>


int main(void)
{
	WDTCTL = WDTPW + WDTHOLD; 					// Stop WDT

	//Configuración patilla salida
	P1DIR |= BIT2; 								// P1.2 salida
	P1SEL |= BIT2; 								// P1.2 selecciona la función TA0.0

	//Configuramos timer
	TA0CTL = TASSEL_2 + MC_1 + ID_0 + TACLR; 			// SMCLK, modo ascendente, clear TAR
	//TASSEL_2 = SCLK (0=TACLK  1=ACLK  3=INCLK)
	//MC_1 = creciente hasta TACCR0 (0=parada, 2=hasta FFFF)
	//ID_0 = divide la frec de Reloj/1 (0=f/1  1=f/2  2=f/4  3=f/8)
	//TACLR = borra la cuenta

	TA0CCTL1 = OUTMOD_7;
	//PWM OUTPUT MODE:
	//0=ValorDeBit	1=Set		2=Toggle/Reset	3=Set/Reset
	//4=Toggle		5=Reset		6=Toggle/Set	7=Reset/Set

	//Configuración para 4Khz
	TA0CCR0 = 250;							// ncycles = f_trabajo/f_solicitada = 1Mhz/4Khz
	TA0CCR1 = 50;							// DC = 18% de 250 (TA0CCR0) para que arranque

	int i;
	for(i=0;i<10;i++){
		__delay_cycles(1000000);
		TA0CCR1 = TA0CCR1+20;

	}
}
