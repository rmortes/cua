//Ejercicio 1.2.1
/* robotv1.0 */
#include <msp430.h>
void conf_PORTS (void);
void Stop(void);
void MoveF(void);
void MoveB(void);
void TurnR(void);
void TurnL(void);

void main(void){
	WDTCTL = WDTPW + WDTHOLD; // Stop WatchDog
	//by default SMCLK=MCLK=DCOCLK ~1.045MHz , ACLK=32.768Hz (~32KHz)

	conf_PORTS();//primera instruccion ejecutada
	//se configuran los leds como salida (rojo y verde)
	//se habilitan las interrupciones con P2.1

	//se mueve frontalmente hasta que se habilite la interrupcion
	MoveF();//mover FRONT

	__bis_SR_register(LPM0_bits + GIE); //Modo LPM0 + interr generales

}
//interrupcion al pulsar P2.1
#pragma vector=PORT2_VECTOR
__interrupt void Port2_ISR(void){
	//una vez habilitada la interrupcion, ejecutamos la funcion STOP
	//por lo que apagamos todos los leds
	Stop();//no se aprecia este estado

	// TODO: Configurar el timers (usar polling CCIFG, Up mode, ACLK)
	//config del TA0CCR0 para la config del timer
	TA0CCR0=64000;//para que sean 2 segundos
	//2s=x*1/32000s-->x=2*32000=64000
	TA0CCTL0 &= ~CCIFG;
	TA0CTL = TASSEL_1 + MC_1 + ID_0 + TACLR;//config del timer
	//CONFIG = ACLK  + up mode + frec/1 + borra la cuenta
	// …


	TurnR();//no se aprecia este estado
	MoveB();//permanece 2 segundos por el retardo del timer

	// TODO: comprobar CCIFG continuamente hasta que el tiempo expire
	//retardo de 2 segundos
	while ((TA0CCTL0 & CCIFG)==0){//mientras el timer esté a 0
		// no se hace nada
	}
	TA0CCTL0 &= ~CCIFG; //eliminar interrupciones pendientes
	// …

	TurnL();
	MoveF();

	P2IFG &= ~BIT1;         		//clear Bumper int. flag
}

void conf_PORTS (void){//primera instruccion ejecutada
	// LEDs configuration
	P1DIR |= BIT0; 					//P1.0 como SALIDA
	P1OUT &= ~BIT0;					//Apaga P1.0 (led.rojo) al inicio
	P4DIR |= BIT7;					//P4.7 como SALIDA
	P4OUT &= ~BIT7; 				//Apaga P4.7 (led.verd) al inicio

	//Config del Boton Bumper (de choque)
	P2DIR &= ~BIT1;					//P2.1 como ENTRADA
	P2REN |= BIT1;                 	//Habilita la resistencia en P2.1
	P2OUT |= BIT1;                 	//Resistencia --> pull-up
	P2IES |= BIT1;                 	//P2.1 interrupciones
	P2IFG &= ~BIT1;                	// borramos interr pendientes
	P2IE |= BIT1;                 	// P2.1 habilitar interrupciones
}
void MoveF(void){//FRONT-->encendemos led verde (P4.7)
	P4OUT |= BIT7;  // LEDg on
	P1OUT &=~BIT0;  // LEDr off
}
void MoveB(void){//BACK-->encendemos led rojo (P1.0)
	P1OUT |= BIT0;  // LEDr on
	P4OUT &=~BIT7;  // LEDg off
}
void Stop(void){//STOP-->apagamos los 2 leds
	P1OUT &= ~BIT0; // LEDr off
	P4OUT &= ~BIT7; // LEDg off
}
void TurnR(void){//RIGHT-->encendemos los 2 leds
	P4OUT |= BIT7;  // LEDg on
	P1OUT |= BIT0;  // LEDr on
}
void TurnL(void){//LEFT-->encendemos los 2 leds
	P4OUT |= BIT7;  // LEDg on
	P1OUT |= BIT0;  // LEDr on
}

