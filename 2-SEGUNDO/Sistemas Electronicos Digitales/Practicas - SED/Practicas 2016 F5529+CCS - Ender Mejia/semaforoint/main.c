#include <msp430.h> 

/*
 * main.c
 */

unsigned int i;

int main(void) {
	WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

	//declaramos los pins de los leds como salida
	P3DIR |= (BIT0 + BIT1 + BIT2 + BIT3 + BIT4);
	P6DIR |= (BIT5 + BIT6);
	P1DIR |= BIT6;


	//declaramos el boton P2.1 como entrada
	//he cambiado el pin del boton para poder comprobarlo con la placa
	//si se desea poner uno externo solo hay que cambiar el BIT1 por
	P2DIR &= ~BIT1;
	P2REN |= BIT1; //Habilita resistencia
	P2OUT |= BIT1; //Activa la de pullup - espera a un 0

	P2IE |= BIT1;	//Habilita interrupciones
	P2IES |= BIT1;	//FLANCO DE BAJADA
	P2IFG &= ~BIT1; //flag a cero, no hay INT pendiente

	_BIS_SR(GIE);	//Habilitamos interrupciones generales, IMPORTANTE!

	for(;;){

		//SEGURIDAD (todo rojo durante 1 segundo)-----------------------------
		P3OUT |= BIT3;	//enciendo rojo SEMAFORO 1
		P3OUT &= ~BIT4;	//apago ambar SEMAFORO 1
		P6OUT &= ~BIT5; //apago verde SEMAFORO 1

		P3OUT |= BIT0;	//enciendo rojo SEMAFORO 2
		P3OUT &= ~BIT1; //apago ambar SEMAFORO 2
		P3OUT &= ~BIT2;	//apago verde SEMAFORO 2

		P6OUT |= BIT6;	//enciendo rojo PEATON
		P1OUT &= ~BIT6;	//apago verde PEATON
		__delay_cycles(1048576); //hacemos que los dos semaforos estén en rojo durante 1 segundo


		//Estado 1 -->Rojo-Verde -----------------------------
		P3OUT |= BIT3;	//enciendo rojo SEMAFORO 1
		P3OUT &= ~BIT4;	//apago ambar SEMAFORO 1
		P6OUT &= ~BIT5; //apago verde SEMAFORO 1

		P3OUT &= ~BIT0;	//apago rojo SEMAFORO 2
		P3OUT &= ~BIT1; //apago ambar SEMAFORO 2
		P3OUT |= BIT2;	//enciendo verde SEMAFORO 2

		P6OUT &= ~BIT6;	//apago rojo PEATON
		P1OUT |= BIT6;	//enciendo verde PEATON

		__delay_cycles(1048576*5); //retardo de 5 segundos


		//Estado 2 -->Rojo-Parpadeo ---------------------------
		for(i=0;i<6;i++){
			P3OUT &= ~BIT2;	//apago verde SEMAFORO 2
			P1OUT &= ~BIT6;	//apago verde PEATON
			__delay_cycles(1048576/4);
			P3OUT |= BIT2; 	//enciendo verde SEMAFORO 2
			P1OUT |= BIT6;	//enciendo verde PEATON
			__delay_cycles(1048576/4);
		}


		//Estado 3 -->Rojo-Ambar ------------------------------
		P3OUT |= BIT3;	//enciendo rojo SEMAFORO 1
		P3OUT &= ~BIT4;	//apago ambar SEMAFORO 1
		P6OUT &= ~BIT5; //apago verde SEMAFORO 1

		P3OUT &= ~BIT0;	//apago rojo SEMAFORO 2
		P3OUT |= BIT1; //enciendo ambar SEMAFORO 2
		P3OUT &= ~BIT2;	//apago verde SEMAFORO 2

		P6OUT &= ~BIT6;	//apago rojo PEATON
		P1OUT |= BIT6;	//enciendo verde PEATON

		__delay_cycles(1048576); //retardo de 1 segundo

		//SEGURIDAD (todo rojo durante 1 segundo)---------------

		P3OUT |= BIT3;	//enciendo rojo SEMAFORO 1
		P3OUT &= ~BIT4;	//apago ambar SEMAFORO 1
		P6OUT &= ~BIT5; //apago verde SEMAFORO 1

		P3OUT |= BIT0;	//enciendo rojo SEMAFORO 2
		P3OUT &= ~BIT1; //apago ambar SEMAFORO 2
		P3OUT &= ~BIT2;	//apago verde SEMAFORO 2

		P6OUT |= BIT6;	//enciendo rojo PEATON
		P1OUT &= ~BIT6;	//apago verde PEATON
		__delay_cycles(1048576); //hacemos que los dos semaforos estén en rojo durante 1 segundo


		//Estado 4 -->Verde-Rojo -------------------------------

		P3OUT &= ~BIT3;	//apgao rojo SEMAFORO 1
		P3OUT &= ~BIT4;	//apago ambar SEMAFORO 1
		P6OUT &= ~BIT5; //enciendo verde SEMAFORO 1

		P3OUT |= BIT0;	//enciendo rojo SEMAFORO 2
		P3OUT &= ~BIT1; //apago ambar SEMAFORO 2
		P3OUT &= ~BIT2;	//apago verde SEMAFORO 2

		P6OUT |= BIT6;	//enciendo rojo PEATON
		P1OUT &= ~BIT6;	//apago verde PEATON

		P3OUT &= ~BIT3;	//apago rojo SEMAFORO 1
		P6OUT |= BIT5;	//enciendo verde SEMAFORO 1

		__delay_cycles(1048576*6);//retardo de 6 segundos

		//Estado 5 -->Parpadeo-Rojo -----------------------------
		for(i=0;i<6;i++){
			P6OUT &= ~BIT5;	//apago verde SEMAFORO 2
			__delay_cycles(1048576/4);
			P6OUT |= BIT5; 	//enciendo verde SEMAFORO 2
			__delay_cycles(1048576/4);
		}

		//Estado 6 -->Ambar-Rojo----------------------------------
		P3OUT &= ~BIT3;	//apago rojo SEMAFORO 1
		P3OUT |= BIT4;	//enciendo ambar SEMAFORO 1
		P6OUT &= ~BIT5; //apago verde SEMAFORO 1

		P3OUT |= BIT0;	//enciendo rojo SEMAFORO 2
		P3OUT &= ~BIT1; //apago ambar SEMAFORO 2
		P3OUT &= ~BIT2;	//apago verde SEMAFORO 2

		P6OUT |= BIT6;	//enciendo rojo PEATON
		P1OUT &= ~BIT6;	//apago verde PEATON
		__delay_cycles(1048576); //retardo de 1 segundo
	}

	//return 0;
}

#pragma vector=PORT2_VECTOR
__interrupt void P2_Interrupt(){

	//-------------------------3 EN ROJO
	P3OUT |= BIT3;	//enciendo rojo SEMAFORO 1
	P3OUT &= ~BIT4;	//apago ambar SEMAFORO 1
	P6OUT &= ~BIT5; //apago verde SEMAFORO 1

	P3OUT |= BIT0;	//enciendo rojo SEMAFORO 2
	P3OUT &= ~BIT1; //apago ambar SEMAFORO 2
	P3OUT &= ~BIT2;	//apago verde SEMAFORO 2

	P6OUT |= BIT6;	//enciendo rojo PEATON
	P1OUT &= ~BIT6;	//apago verde PEATON

	__delay_cycles(1048576*3);//3 segundos todo rojo
	//------------------------------------------------

	//Rojo-Verde---(verde para el peaton)
	P3OUT |= BIT2;	//enciendo verde SEMAFORO 2
	P3OUT &= ~BIT0;	//apago rojo SEMAFORO 2

	P1OUT |= BIT6; 	//enciendo verde PEATON
	P6OUT &= ~BIT6;	//apago rojo PEATON

	__delay_cycles(1048576*8); //retardo de 8 segundos (8seg encendido verde PEATON)


	//Rojo-Ambar---(5 parpadeos verde PEATON)
	P3OUT |= BIT1;	//enciendo ambar SEMAFORO 2
	P3OUT &= ~BIT2;	//apago verde SEMAFORO 2

	for(i=0;i<5;i++){
		P1OUT &= ~BIT6;	//apago verde PEATON
		__delay_cycles(1048576/4);
		P1OUT |= BIT6; 	//enciendo verde PEATON
		__delay_cycles(1048576/4);
	}

	//Verde-Rojo---(rojo para el peaton)
	P3OUT |= BIT0;	//enciendo rojo SEMAFORO 2
	P3OUT &= ~BIT1;	//apago ambar SEMAFORO 2
	P1OUT &= ~BIT6;	//apago verde PEATON
	P6OUT |= BIT6;	//enciendo rojo PEATON
	__delay_cycles(1048576); //hacemos que todos los semaforos estén en rojo durante 1 segundo

	P3OUT &= ~BIT3;	//apago rojo SEMAFORO 1
	P6OUT |= BIT5;	//enciendo verde SEMAFORO 1

	__delay_cycles(1048576*6);//6seg PEATON en rojo


	//Ambar-Rojo---(rojo para el peaton)
	P6OUT &= ~BIT5;//apago verde SEMAFORO 1
	P3OUT |= BIT4;	//enciendo ambar SEMAFORO 1
	__delay_cycles(1048576);//1seg en ambar

	//-------------------------APAGAR TODOS
	//Así aseguro que el programa continue donde se interrumpió de forma correcta
	P3OUT &= ~BIT3;	//apago rojo SEMAFORO 1
	P3OUT &= ~BIT4;	//apago ambar SEMAFORO 1
	P6OUT &= ~BIT5; //apago verde SEMAFORO 1

	P3OUT &= ~BIT0;	//apago rojo SEMAFORO 2
	P3OUT &= ~BIT1; //apago ambar SEMAFORO 2
	P3OUT &= ~BIT2;	//apago verde SEMAFORO 2

	P6OUT &= ~BIT6;	//apago rojo PEATON
	P1OUT &= ~BIT6;	//apago verde PEATON
	//------------------------------------------------


	P2IFG &= ~BIT1; //Al salir de la interrupción
	//SIEMPRE es necesario borrar el flag
}
