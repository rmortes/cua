/* robotv2.0 */
#include <msp430.h>
#define MOVF 1
#define STOP 2
#define ST 3
#define MOVB 4
void conf_PORTS (void);
void MoveF(void);
void MoveB(void);
void Stop (void);
void Check_timer(void);
void StartTA(void);
int EndT, Bump; // GLOBAL VARS
void main(void)
{
	int CState; int NState;
	WDTCTL = WDTPW + WDTHOLD; // Stop WatchDog
	conf_PORTS();
	NState=MOVF;
	EndT=0; Bump=0;
	__bis_SR_register(GIE); // GIE enable
	for(;;){
		Check_timer();
		CState=NState;
		switch (CState){
		case MOVF:
			MoveF(); P2IE |= BIT1;
			if (Bump==1) {NState=STOP; Bump=0; P2IE &= ~BIT1;}
			else {__bis_SR_register(LPM0_bits); }
			break;
		case STOP:
			Stop();
			NState=ST;
			break;
		case ST:
			StartTA();
			NState=MOVB;
			break;
		case MOVB:
			MoveB();
			if (EndT==1) {NState=MOVF; EndT=0;}
			else {NState=MOVB;}
			break;
		default:
			NState=MOVF;
			break;
		}
	}
}
void Check_timer(void){ // comprueba si el tiempo expira y actualiza EndT
	if((TA0CCTL0 & 1)==1){
		TA0CTL =MC_0;//Stop Timer
		EndT=1;
	}
	 // stop the timer
	// TODO
	// …
}
void StartTA(void){
	TA0CTL =MC_0; // stop the timer
	TA0CTL = MC_1+TASSEL_1+ID_0+TACLR;
	// Configure&Start the timer= Up Mode, ACLK/1 (32KHz), Clear
	TA0CCR0 = 62000; // configure for 2sec
	TA0CCTL0 &= ~CCIFG; // Clear the flag avoid spurious flags
}
#pragma vector=PORT2_VECTOR
__interrupt void Port2_ISR(void){ //actualiza Bump
	// TODO
	// …
	// ATENCIÓN: la siguiente instrucción hace que al regresar de la ISR
	// la CPU pasa a modo activo, ejecutando el resto de instrucciones
	Bump=1;
	P2IFG &= ~BIT1;
	__bic_SR_register_on_exit(LPM0_bits);
}
void conf_PORTS (void){
	// LEDs configuration
	P1DIR |= BIT0; //Set P1.0 as output
	P1OUT &= ~BIT0; // LED red off
	P4DIR |= BIT7; // Set P4.7 as output
	P4OUT &= ~BIT7; // LED green off
	// Button (bumper) configuration
	P2DIR &= ~BIT1; // Set P2.1 toinput direction
	P2REN |= BIT1; // Enable P2.1 internal resistance
	P2OUT |= BIT1; // Set P2.1 as pull-Up resistance
	P2IES |= BIT1; // P2.1 Hi/Lo edge
	P2IFG &= ~BIT1; // P2.1 IFG cleared
	P2IE |= BIT1; // P2.1 interrupt enabled
}
void MoveF(void){
	P4OUT |= BIT7; // LEDg on
	P1OUT &=~BIT0; // LEDr off
}
void MoveB(void){
	P1OUT |= BIT0; // LEDr on
	P4OUT &=~BIT7; // LEDg off
}
void Stop(void){
	P1OUT &= ~BIT0; // LEDr off
	P4OUT &= ~BIT7; // LEDg off
}
void TurnR(void){
	P4OUT |= BIT7; // LEDg on
	P1OUT |= BIT0; // LEDr on
}
void TurnL(void){
	P4OUT |= BIT7; // LEDg on
	P1OUT |= BIT0; // LEDr on
}
