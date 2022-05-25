#include <msp430.h> 

volatile unsigned int n; //Global Variable

void delay(){
	__delay_cycles(250);//0,25 ms delay
}

void ledblink(){
	volatile unsigned int i,t;
	t=(1000000*(10/n));//Calculate the period
	for(i=0;i<t;i++){
		delay();
	}
	P1OUT ^= BIT0;//P1.0 -> Change state
}


int main(void){
	WDTCTL = WDTPW + WDTHOLD; //Stop Watchdog

	P1DIR |= BIT0;	//P1.0 -> output
	P2DIR &= ~BIT1; //P2.1 -> imput
	P2REN |= BIT1;	//P2.1 -> pull-up resistor

	P2OUT |= BIT1;	//P2.1 -> "1" Logic

	//Interrupt
	P2IES |= BIT1;	//Interrup P2.1 -> High to low
	P2IFG &= ~BIT1;	//Interrup P2.1 -> 0
	P2IE |= BIT1;	//Interrup P2.1 -> Enable

	n=1; //mHz Number of turns

	__bis_SR_register( GIE);	//Enable interrupt

	while(1){
		ledblink();
	}

}

//Interruption for P2.1
#pragma vector=PORT2_VECTOR
__interrupt void Button1(void)
{
	n=n+1;	//Decrement number of turns
	P2IFG &= ~BIT1;	//Erase P2.1 Interrupt
}

