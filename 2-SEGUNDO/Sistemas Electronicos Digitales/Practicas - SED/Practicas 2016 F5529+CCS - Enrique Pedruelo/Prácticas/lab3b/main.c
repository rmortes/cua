#include <msp430.h> 


//Definimos etiquetas para hacerlo más simple de entender
#define D1 BIT5 // Diodo 1 -> P6.5
#define D2 BIT4 // Diodo 2 -> P3.4
#define D3 BIT3 // Diodo 3 -> P3.3
#define D4 BIT6 // Diodo 4 -> P1.6
#define D5 BIT6 // Diodo 5 -> P6.6
#define D6 BIT2 // Diodo 6 -> P3.2
#define D7 BIT1 // Diodo 7 -> P3.1
#define D8 BIT0 // Diodo 8 -> P3.0
#define S3 BIT1 // Pulsador 3 -> P2.0
#define S4 BIT2 // Pulsador 4 -> P2.2

//Utilizamos esta variable global
unsigned int i;
//Utilizamos un vector global para saber los leds encendidos
unsigned int vec[8];

//Función que retarda los ciclos
void delay_ms(unsigned int ms){
	while(ms){
		__delay_cycles(1000);
		ms--;
	}
}

//Función parpadeo
int parpadeo(){
	//Parpadeo 10 veces
	for(i=0; i<20; i++){
		P1DIR ^= D4;	//P1.6 Cambia el estado de la salida
		P3DIR ^= D2;	//P3.4 Cambia el estado de la salida
		P3DIR ^= D3;	//P3.3 Cambia el estado de la salida
		P3DIR ^= D6;	//P3.2 Cambia el estado de la salida
		P3DIR ^= D7;	//P3.1 Cambia el estado de la salida
		P3DIR ^= D8;	//P3.0 Cambia el estado de la salida
		P6DIR ^= D1;	//P6.5 Cambia el estado de la salida
		P6DIR ^= D5;	//P6.6 Cambia el estado de la salida
		delay_ms(1000); //Hacemos retardo de 1 segundo
	}
	return 1; //Devolvemos 1 para el booleano
}

//Función Inversa
void sec_inverse(){
	int bool; //Variable que evita que se vuelva a meter si se pulsa otra vez
	bool=0; //Se inicializa a 0
	P6OUT |= D1; //P6.5 encendido
	delay_ms(500); //Hacemos retardo de 0,5 segundos
	if(vec[6]==1 && bool==0){ //Comprueba el estado del siguiente led
		//y si ha hecho el parpadeo
		bool=parpadeo();//Ver Leds Encendidos
		P6OUT &= ~D1;	//Pone un 0 a la salida P6.5
	}

	P3OUT |= D2; //P6.5 encendido
	delay_ms(500); //Hacemos retardo de 0,5 segundos
	if(vec[5]==1 && bool==0){ //Comprueba el estado del siguiente led
		//y si ha hecho el parpadeo
		bool=parpadeo();//Ver Leds Encendidos
		P3OUT &= ~D2;	//Pone un 0 a la salida P3.4
		P6OUT &= ~D1;	//Pone un 0 a la salida P6.5
	}

	P3OUT |= D3; //P6.5 encendido
	delay_ms(500); //Hacemos retardo de 0,5 segundos
	if(vec[4]==1 && bool==0){ //Comprueba el estado del siguiente led
		//y si ha hecho el parpadeo
		bool=parpadeo();//Ver Leds Encendidos
		P3OUT &= ~D2;	//Pone un 0 a la salida P3.4
		P3OUT &= ~D3;	//Pone un 0 a la salida P3.3
		P6OUT &= ~D1;	//Pone un 0 a la salida P6.
	}

	P1OUT |= D4; //P6.5 encendido
	delay_ms(500); //Hacemos retardo de 0,5 segundos
	if(vec[3]==1 && bool==0){ //Comprueba el estado del siguiente led
		//y si ha hecho el parpadeo
		bool=parpadeo();//Ver Leds Encendidos
		P1OUT &= ~D4;	//Pone un 0 a la salida P1.6
		P3OUT &= ~D2;	//Pone un 0 a la salida P3.4
		P3OUT &= ~D3;	//Pone un 0 a la salida P3.3
		P6OUT &= ~D1;	//Pone un 0 a la salida P6.5
	}

	P6OUT |= D5; //P6.5 encendido
	delay_ms(500); //Hacemos retardo de 0,5 segundos
	if(vec[2]==1 && bool==0){ //Comprueba el estado del siguiente led
		//y si ha hecho el parpadeo
		bool=parpadeo();//Ver Leds Encendidos
		P1OUT &= ~D4;	//Pone un 0 a la salida P1.6
		P3OUT &= ~D2;	//Pone un 0 a la salida P3.4
		P3OUT &= ~D3;	//Pone un 0 a la salida P3.3
		P6OUT &= ~D1;	//Pone un 0 a la salida P6.5
		P6OUT &= ~D5;	//Pone un 0 a la salida P6.6
	}

	P3OUT |= D6; //P6.5 encendido
	delay_ms(500); //Hacemos retardo de 0,5 segundos
	if(vec[1]==1 && bool==0){ //Comprueba el estado del siguiente led
		//y si ha hecho el parpadeo
		bool=parpadeo();//Ver Leds Encendidos
		P1OUT &= ~D4;	//Pone un 0 a la salida P1.6
		P3OUT &= ~D2;	//Pone un 0 a la salida P3.4
		P3OUT &= ~D3;	//Pone un 0 a la salida P3.3
		P3OUT &= ~D6;	//Pone un 0 a la salida P3.2
		P6OUT &= ~D1;	//Pone un 0 a la salida P6.5
		P6OUT &= ~D5;	//Pone un 0 a la salida P6.6
	}

	P3OUT |= D7; //P6.5 encendido
	delay_ms(500); //Hacemos retardo de 0,5 segundos
	if(vec[0]==1 && bool==0){ //Comprueba el estado del siguiente led
		//y si ha hecho el parpadeo
		bool=parpadeo();//Ver Leds Encendidos
		P1OUT &= ~D4;	//Pone un 0 a la salida P1.6
		P3OUT &= ~D2;	//Pone un 0 a la salida P3.4
		P3OUT &= ~D3;	//Pone un 0 a la salida P3.3
		P3OUT &= ~D6;	//Pone un 0 a la salida P3.2
		P3OUT &= ~D7;	//Pone un 0 a la salida P3.1
		P6OUT &= ~D1;	//Pone un 0 a la salida P6.5
		P6OUT &= ~D5;	//Pone un 0 a la salida P6.6
	}
}

//Función Original
void sec_orig(){
	//Encender leds D8 hasta D1 con retardo
	P3OUT |= D8; //P3.0 encendido
	delay_ms(500); //Hacemos retardo de 0,5 segundos
	vec[0]=1; //Asigna 1 al vector
	if((P2IN & S3)==0) sec_inverse();//P2.1 pulsado ->Hacer el inverso

	P3OUT |= D7; //P3.1 encendido
	delay_ms(500); //Hacemos retardo de 0,5 segundos
	vec[1]=1; //Asigna 1 al vector
	if((P2IN & S3)==0) sec_inverse();//P2.1 pulsado ->Hacer el inverso

	P3OUT |= D6; //P3.2 encendido
	delay_ms(500); //Hacemos retardo de 0,5 segundos
	vec[2]=1; //Asigna 1 al vector
	if((P2IN & S3)==0) sec_inverse();//P2.1 pulsado ->Hacer el inverso

	P6OUT |= D5; //P6.6 encendido
	delay_ms(500); //Hacemos retardo de 0,5 segundos
	vec[3]=1; //Asigna 1 al vector
	if((P2IN & S3)==0) sec_inverse();//P2.1 pulsado ->Hacer el inverso

	P1OUT |= D4; //P1.6 encendido
	delay_ms(500); //Hacemos retardo de 0,5 segundos
	vec[4]=1; //Asigna 1 al vector
	if((P2IN & S3)==0) sec_inverse();//P2.1 pulsado ->Hacer el inverso

	P3OUT |= D3; //P3.3 encendido
	delay_ms(500); //Hacemos retardo de 0,5 segundos
	vec[5]=1; //Asigna 1 al vector
	if((P2IN & S3)==0) sec_inverse();//P2.1 pulsado ->Hacer el inverso

	P3OUT |= D2; //P3.4 encendido
	delay_ms(500); //Hacemos retardo de 0,5 segundos
	vec[6]=1; //Asigna 1 al vector
	if((P2IN & S3)==0) sec_inverse();//P2.1 pulsado ->Hacer el inverso

	P6OUT |= D1; //P6.5 encendido
	delay_ms(500); //Hacemos retardo de 0,5 segundos
	vec[7]=1; //Asigna 1 al vector
	if((P2IN & S3)==0) sec_inverse();//P2.1 pulsado ->Hacer el inverso


	P1OUT &= ~D4;	//Pone un 0 a la salida P1.6
	P3OUT &= ~D2;	//Pone un 0 a la salida P3.4
	P3OUT &= ~D3;	//Pone un 0 a la salida P3.3
	P3OUT &= ~D6;	//Pone un 0 a la salida P3.2
	P3OUT &= ~D7;	//Pone un 0 a la salida P3.1
	P3OUT &= ~D8;	//Pone un 0 a la salida P3.0
	P6OUT &= ~D1;	//Pone un 0 a la salida P6.5
	P6OUT &= ~D5;	//Pone un 0 a la salida P6.6

	//Borramos todos los datos del vector
	for(i=0;i<8;i++){
		vec[i]=0;
	}
}

/*
 * main.c
 */
int main(void) {
	WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

	P2DIR |= ~S3; //P2.1 Salida
	P2DIR |= ~S4; // P2.2 Salida
	P2REN |= S3; //P2.1 Resistencia pull-up =1
	P2REN |= S4; // P2.2 Resistencia pull-up =1
	P2OUT |= S3; //P2.1 Valor a 1
	P2OUT |= S4; // P2.2 Valor a 1

	P1DIR |= D4;	//CONFIGURA P1.6 COMO SALIDA
	P1OUT &= ~D4;	//Pone un 0 a la salida

	P3DIR |= D2;	//CONFIGURA P3.4 COMO SALIDA
	P3OUT &= ~D2;	//Pone un 0 a la salida
	P3DIR |= D3;	//CONFIGURA P3.3 COMO SALIDA
	P3OUT &= ~D3;	//Pone un 0 a la salida
	P3DIR |= D6;	//CONFIGURA P3.2 COMO SALIDA
	P3OUT &= ~D6;	//Pone un 0 a la salida
	P3DIR |= D7;	//CONFIGURA P3.1 COMO SALIDA
	P3OUT &= ~D7;	//Pone un 0 a la salida
	P3DIR |= D8;	//CONFIGURA P3.0 COMO SALIDA
	P3OUT &= ~D8;	//Pone un 0 a la salida

	P6DIR |= D1;	//CONFIGURA P6.5 COMO SALIDA
	P6OUT &= ~D1;	//Pone un 0 a la salida
	P6DIR |= D5;	//CONFIGURA P6.6 COMO SALIDA
	P6OUT &= ~D5;	//Pone un 0 a la salida

	//Pone a 0 todo el vector inicialmente
	for(i=0;i<8;i++){
		vec[i]=0;
	}

	//Bucle infinito de la secuencia original
	for(;;){
		sec_orig();
	}

	return 0;
}
