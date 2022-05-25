#include <msp430.h> 

volatile unsigned int f; //Global Variable

void delay(){

	__delay_cycles(250);//0,25 ms delay
}

void ledblink(){
	volatile unsigned int i,n;
	n=(1000000*(10/f));//Calculate the number of cycles
	for(i=0;i<n;i++){
		delay();
	}
	P1OUT ^= BIT0;//P1.0 -> Change state
}


int main(void){
	WDTCTL = WDTPW + WDTHOLD; //Stop Watchdog

	P1DIR |= BIT0;	//P1.0 -> output
	P1DIR &= ~BIT1; //P1.1 -> imput
	P1REN |= BIT1;	//P1.1 -> pull-up resistor
	P2DIR &= ~BIT1; //P2.1 -> imput
	P2REN |= BIT1;	//P2.1 -> pull-up resistor

	P1OUT |= BIT1;	//P1.1 -> "1" Logic
	P2OUT |= BIT1;	//P2.1 -> "1" Logic

	//Interrupt
	P2IES |= BIT1;	//Interrup P2.1 -> High to low
	P2IFG &= ~BIT1;	//Interrup P2.1 -> 0
	P2IE |= BIT1;	//Interrup P2.1 -> Enable
	P1IES |= BIT1;	//Interrup P1.1 -> High to low
	P1IFG &= ~BIT1;	//Interrup P1.1 -> 0
	P1IE |= BIT1;	//Interrup P1.1 -> Enable

	f=1;	//Frecuency x10

	__bis_SR_register(GIE);	//Enable interrupt

	while(1){
		ledblink();
	}

}

//Interruption for P1.1
#pragma vector=PORT1_VECTOR
__interrupt void Button2(void)
{
	f=f-1;	//Increment de frecuency 0,1
	P1IFG &= ~BIT1;	//Erase P1.1 Interrupt
}

//Interruption for P2.1
#pragma vector=PORT2_VECTOR
__interrupt void Button1(void)
{
	f=f+1;	//Decrement de frecuency 0,1
	P2IFG &= ~BIT1;	//Erase P2.1 Interrupt
}
