#include <msp430.h> 

/*
 * main.c
 */

int main(void) {
	WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

	P3DIR |= (BIT0 + BIT1 + BIT2 + BIT3 + BIT4);
	P6DIR |= BIT5;

	unsigned int i;

	for(;;){
		//Estado 1 -->Rojo-Verde -----------------------------
		P3OUT |= BIT3;	//enciendo rojo SEMAFORO 1
		P3OUT &= ~BIT4;	//apago ambar SEMAFORO 1
		P6OUT &= ~BIT5; //apago verde SEMAFORO 1

		P3OUT &= ~BIT0;	//apago rojo SEMAFORO 2
		P3OUT &= ~BIT1; //apago ambar SEMAFORO 2
		P3OUT |= BIT2;	//enciendo verde SEMAFORO 2

		__delay_cycles(1048576*5); //retardo de 5 segundos


		//Estado 2 -->Rojo-Parpadeo ---------------------------
		for(i=0;i<6;i++){
			P3OUT &= ~BIT2;	//apago verde SEMAFORO 2
			__delay_cycles(1048576/4);
			P3OUT |= BIT2; 	//enciendo verde SEMAFORO 2
			__delay_cycles(1048576/4);
		}


		//Estado 3 -->Rojo-Ambar ------------------------------
		//SEMAFORO 1 está ya en rojo

		P3OUT |= BIT1;	//enciendo ambar SEMAFORO 2
		P3OUT &= ~BIT2;	//apago verde SEMAFORO 2

		__delay_cycles(1048576); //retardo de 1 segundo

		//Estado 4 -->Verde-Rojo -------------------------------
		P3OUT &= ~BIT3;	//apago rojo SEMAFORO 1
		P6OUT |= BIT5;	//enciendo verde SEMAFORO 1

		P3OUT |= BIT0;	//enciendo rojo SEMAFORO 2
		P3OUT &= ~BIT1;	//apago ambar SEMAFORO 2

		__delay_cycles(1048576*6);//retardo de 6 segundos

		//Estado 5 -->Parpadeo-Rojo -----------------------------
		for(i=0;i<6;i++){
			P6OUT &= ~BIT5;	//apago verde SEMAFORO 2
			__delay_cycles(1048576/4);
			P6OUT |= BIT5; 	//enciendo verde SEMAFORO 2
			__delay_cycles(1048576/4);
		}

		//Estado 6 -->Ambar-Rojo----------------------------------
		P3OUT |= BIT4;//enciendo ambar SEMAFORO 1
		P6OUT &= ~BIT5;//apago verde SEMAFORO 1

		//SEMAFORO 2 ya está rojo
		__delay_cycles(1048576); //retardo de 1 segundo


	}

	//return 0;
}
