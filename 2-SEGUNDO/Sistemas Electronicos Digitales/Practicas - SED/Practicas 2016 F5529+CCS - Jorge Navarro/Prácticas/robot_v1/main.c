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
	conf_PORTS();
	MoveF();
	__bis_SR_register(LPM0_bits + GIE); // CPU off
}
#pragma vector=PORT2_VECTOR
__interrupt void Port2_ISR(void){
	Stop();
	// TODO: Configurar el timers (usar polling CCIFG, Up mode, ACLK)
	TA0CTL = TASSEL_1 + MC_1 + ID_0 + TACLR;//Aclk + Up mode + ACLK/1 + Clear timer
	TA0CCTL0 &= ~CCIFG; // Clear the flag
	// …
	__delay_cycles(10000);
	TurnR();
	__delay_cycles(10000);
	MoveB();
	// TODO: comprobar CCIFG continuamente hasta que el tiempo expire
	// …
	TA0CCR0 = 62000; // configure for 2sec
	do{
		if((TA0CCTL0 & CCIFG)==1){
			TA0CTL = MC_0;//Stop timerA
		}
	}while((TA0CCTL0 & CCIFG)==0);

	TurnL();
	MoveF();
	P2IFG &= ~BIT1; //clear Bumper int. flag
}
void conf_PORTS (void){
	// LEDs configuration
	P1DIR |= BIT0; //Set P1.0 as output
	P1OUT &= ~BIT0; // LED red off
	P4DIR |= BIT7; // Set P4.7 as output
	P4OUT &= ~BIT7; // LED green off
	// Button (bumper) configuration
	P2DIR &= ~BIT1; // Set P2.1 to input direction
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
/* robotv1.0 */
/*#include <msp430.h>
volatile unsigned char NState;
volatile unsigned int Bump;
volatile unsigned int EndT;
void conf_PORTS (void);
void Stop(void);
void MoveF(void);
void MoveB(void);
void TurnR(void);
void TurnL(void);
void StartTA(void);

void main(void){
	int CState;
	CState=0;
	WDTCTL = WDTPW + WDTHOLD; // Stop WatchDog
	//by default SMCLK=MCLK=DCOCLK ~1.045MHz , ACLK=32.768Hz (~32KHz)
	NState=1;
	Bump=0;
	conf_PORTS();
	__bis_SR_register(GIE); //Enable Interrupts
	MoveF();

	for(;;){
		//Check_timer() // update EndT
		CState=NState;
		switch (CState){
		case 1://MOVF:
			MoveF();
			if (Bump==1) {
				NState=2;//STOP;
				Bump=0;
			}
			//else {__bis_SR_register(LPM0_bits); }
			break;
		case 2://STOP:
			Stop();
			NState=3;//ST;
			break;
		case 3://ST:
			StartTA();
			NState=4;//MOVB;
			break;
		case 4://MOVB:
			MoveB();
			if (EndT==1) {
				NState=1;//MOVF;
				EndT=0;
			}
			break;
		default:
			NState=1;//MOVF
			break;
		}
	}
}

// Timer0 A0 interrupt service routine
#pragma vector=TIMER0_A0_VECTOR
__interrupt void TIMER_ISR(void)
{
	EndT=1;
	TA0CCTL0 &= ~CCIFG; // Clear the flag.
}

#pragma vector=PORT2_VECTOR
__interrupt void Port2_ISR(void){
	Bump=1;
	P2IFG &= ~BIT1;
}

void conf_PORTS (void){
	// LEDs configuration
	P1DIR |= BIT0; //Set P1.0 as output
	P1OUT &= ~BIT0; // LED red off
	P4DIR |= BIT7; // Set P4.7 as output
	P4OUT &= ~BIT7; // LED green off
	// Button (bumper) configuration
	P2DIR &= ~BIT1; // Set P2.1 to input direction
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
	TurnR();
	MoveB();
	TA0CTL = MC_0;//Stop timerA
	Bump=0;
	NState=1;
}

void TurnR(void){
	P4OUT |= BIT7; // LEDg on
	P1OUT |= BIT0; // LEDr on
}

void TurnL(void){
	P4OUT |= BIT7; // LEDg on
	P1OUT |= BIT0; // LEDr on
}

void StartTA(void){
	//Timer
	TA0CTL = MC_0;//Stop timerA
	TA0CTL = TASSEL_1 + MC_1 + ID_0 + TACLR;//Aclk + Up mode + ACLK/1 + Clear timer
	TA0CCR0 = 62000; // configure for 2sec
	TA0CCTL0 &= ~CCIFG; // Clear the flag avoid spurious flags
}
 */
