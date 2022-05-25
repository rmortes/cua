#include <msp430.h>
int vel=50; //Iniciamos el motor en su velocidad media 50 (entre 0 y 100).
int main(void){
	WDTCTL = WDTPW + WDTHOLD; // Stop WDT
	P2DIR &= ~BIT1; // Configuramos P2.1 como entrada.
	P1DIR &= ~BIT1; // Configuramos P1.1 como entrada.
	P2REN |= BIT1; // Habilitamos resistencia pull-up botón 1.
	P2OUT |= BIT1; // Habilitamos resistencia pull-up botón 1.
	P1REN |= BIT1; // Habilitamos resistencia pull-up botón 2.
	P1OUT |= BIT1; // Habilitamos resistencia pull-up botón 2.
	P2IES |= BIT1; // Tipo de flanco, transición uno a cero. flanco de bajada

	P2IE |= BIT1; // Habilitamos la interrupción.
	P1IES |= BIT1; // Tipo de flanco, transición uno a cero. flanco de bajada

	P1IE |= BIT1; // Habilitamos interrupción.
	P1DIR |= BIT2; // P1.1 output
	P1DIR |= BIT2; // P1.1 output
	P1SEL |= BIT2; // P1.1 option select TA0.0
	TA0CTL = TASSEL_2 + MC_1; // Configuramos timer.
	TA0CCTL1 = OUTMOD_7; // Seleccionamos el modo 7 del PWM.

	// Asignamos valores a los registros.
	TA0CCR0 = 250;
	TA0CCR1 = vel*TA0CCR0/100;
	__bis_SR_register(LPM0_bits+GIE); // Entramos modo bajo consumo pero pendientes de las interrupciones que puedan ocurrir.

}

// Interrupción del boton1.
#pragma vector=PORT1_VECTOR
	__interrupt void P1_Boton(void){
		if(vel<100){	//Cuando la vel es mayor que 0 entraria en el if, sino (cuando sea 0) saltaria a ejecutar el else.
			vel=vel+5;
			TA0CCR1 = vel*TA0CCR0/100;
		}
		else{
			vel=100;	//Asignamos la vel=100, aunque no haria falta ya que si entra aqui seria 100 ya.
			TA0CCR1 = vel*TA0CCR0/100;
		}
		__delay_cycles(50000); // Retardo para evitar los rebotes.
		P1IFG &= ~BIT1; // Ponemos el flag de la interrupcion a 0.
	}

// Interrupción del boton2.
#pragma vector=PORT2_VECTOR
	__interrupt void P2_Boton(void){
		if(vel>0){			//Cuando la vel es mayor que 0 entraria en el if, sino (cuando sea 0) saltaria a ejecutar el else.
			vel=vel-5;
			TA0CCR1 = vel*TA0CCR0/100;
		}
		else{
			vel=0;		//Asignamos la vel=0, aunque no haria falta ya que si entra aqui seria 0 ya.
			TA0CCR1 = vel*TA0CCR0/100;
		}
		__delay_cycles(50000); // Retardo para evitar los rebotes.
		P2IFG &= ~BIT1; // Ponemos el flag de la interrupcion a 0.
	}
