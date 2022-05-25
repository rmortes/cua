/*
  Vldr = [Rldr/(R1+Rldr)]*Vcc
  Rldr(con 3lx)= 20 Kohms
  Vldr = [20.000/(R1+20.000)]*5
  para obtener un Vldr de 1,5v, para aplicarlo como Vcref...
  calculamos el valor de R1
  1,5 = 5*20.000/(R1+20.000)
  1,5 = 100.000/(R1+20.000)
  R1 = [100.000/1,5]-20.000
  R1 = 46.666 ohms = 46 Kohms

 */

#include <msp430.h> 

unsigned int estado=0;
void ConfigComp (void);
/*
 * main.c
 */
int main(void) {
	WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

	P4DIR |= BIT2; //P1.0 como salida led
	P4OUT &= ~BIT2; //apagamos led

	ConfigComp();

	while(1){

		if (estado==1){
			P4OUT |= BIT2; //encendemos cuando se supera Vcref
			estado=0;//IMPORTANTE: ponemos a 0 para apagarlo en caso de que
			//no se supere Vcref en la siguiente comprobacion
		}
		else{
			P4OUT &= ~BIT2; //apagamos led cuando no se supera Vcref
		}

		__bis_SR_register(LPM4_bits+GIE);
		__no_operation();

	}
}

void ConfigComp(void){
	CBCTL0 |= CBIPEN + CBIPSEL_0;
	CBCTL1 |= CBPWRMD_1;
	CBCTL2 |= CBRSEL;
	CBCTL2 |= CBRS_3+CBREFL_1;//Vcref 1,5

	CBCTL3 |= BIT0;
	__delay_cycles(75);

	CBINT &= ~(CBIFG+CBIIFG);
	CBINT |= CBIE;

	CBCTL1 |= CBON;
}

#pragma vector=COMP_B_VECTOR
__interrupt void Comp_B_ISR (void){

	CBCTL1 ^= CBIES;
	CBINT &= ~CBIFG;
	estado=1; //en caso de superarse Vcref, se activará
}
