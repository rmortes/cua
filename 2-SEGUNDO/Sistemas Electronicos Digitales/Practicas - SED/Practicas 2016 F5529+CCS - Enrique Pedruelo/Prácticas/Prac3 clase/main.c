#include <msp430.h> 
#define D1 BIT4 // Diodo 1 -> P6.4
#define D2 BIT4 // Diodo 2 -> P3.4
#define D3 BIT3 // Diodo 3 -> P3.3
#define D4 BIT6 // Diodo 4 -> P1.6
#define D5 BIT6 // Diodo 5 -> P6.6
#define D6 BIT2 // Diodo 6 -> P3.2
#define D7 BIT1 // Diodo 7 -> P3.1
#define D8 BIT0 // Diodo 8 -> P3.0
#define S3 BIT0 // Pulsador 3 -> P2.0
#define S4 BIT2 // Pulsador 4 -> P2.2
void secu_original();
/*
 * main.c
 */
unsigned int i;
/* Retardo en milisegundos */
void retardo_ms(unsigned int ms)
{
	while (ms)
	{
		__delay_cycles(1000); 		// 1000 para 1MHz y 16000 para 16MHz
		ms--;
	}
}

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	P2DIR &= ~(S3+S4);
	P2REN |= S3+S4;
	P2OUT |= S3+S4; //pone a 1 S3 y S4 para activar  la resistencia de pull-up


	//lEDS
	P1DIR |= D4;	//CONFIGURA P1.6 COMO SALIDA
	P1OUT &= ~D4;	//pONE A 0 LA SALIDA

	P3DIR |= D2+D3+D6+D7+D8; //cONFIGURA LAS PATILLAS COMO SALIDAS
	P3OUT &= ~(D2+D3+D6+D7+D8); //sE APAGAN

	P6DIR |= D1+D5; // Pa k quieres saber eso jaja Salu2
	P6OUT &= ~(D1+D5);
	
	//PROGRAMA
	for(;;){
			secu_original();//Función original


	}

	return 0;
}
void secu_inverso(){
	unsigned int R4,R5,R6,i;// Variables para almacenar el estado de los leds y para parpadeo
	//R4,R5,R6 no son registros son variables.

	/* Se almacena el estado de los leds en 3 variables por que usamos 3 puertos distintos */
		R4 = P6OUT;
		R5 = P3OUT;
		R6 = P1OUT;

		/* A 0 todos los led */
		P1OUT &= ~D4;
		P3OUT &= ~(D2+D3+D6+D7+D8);
		P6OUT &= ~(D1+D5);

		/* Inicio de secuencia inversa */
		retardo_ms(200);
		P6OUT |= D1;
		retardo_ms(500);
		P3OUT |= D2;
		retardo_ms(500);
		P3OUT |= D3;
		retardo_ms(500);
		P1OUT |= D4;
		retardo_ms(500);
		P6OUT |= D5;
		retardo_ms(500);
		P3OUT |= D6;
		retardo_ms(500);
		P3OUT |= D7;
		retardo_ms(500);
		P3OUT |= D8;
		retardo_ms(500);

		/* Bucle para realizar 10 parpadeos de 1 segundo (0,5s apagado, 0,5s encendido) */
		for (i=0;i<20;i++){
			P1OUT ^= D4;
			P3OUT ^= D2+D3+D6+D7+D8;
			P6OUT ^= D1+D5;
			retardo_ms(500);
		}
		/* Devolver el estado anterior a los leds */
		P6OUT = R4;
		P3OUT = R5;
		P1OUT = R6;
}
	void secu_original(){
		retardo_ms(500); //misma ejecucion"__delay_cycles(Numero de ciclos en decimal o hexadecimal)"
					P3OUT |= D8;
					if (~P2IN & S3)secu_inverso(); //Comprueba si el boton esta pulsado
					retardo_ms(500);
					P3OUT |= D7;
					if (~P2IN & S3)secu_inverso(); //Comprueba si el boton esta pulsado
					retardo_ms(500);
					P3OUT |= D6;
					if (~P2IN & S3)secu_inverso(); //Comprueba si el boton esta pulsado
					retardo_ms(500);
					P6OUT |= D5;
					if (~P2IN & S3)secu_inverso(); //Comprueba si el boton esta pulsado
					retardo_ms(500);
					P1OUT |= D4;
					if (~P2IN & S3)secu_inverso(); //Comprueba si el boton esta pulsado
					retardo_ms(500);
					P3OUT |= D3;
					if (~P2IN & S3)secu_inverso(); //Comprueba si el boton esta pulsado
					retardo_ms(500);
					P3OUT |= D2;
					if (~P2IN & S3)secu_inverso(); //Comprueba si el boton esta pulsado
					retardo_ms(500);
					P6OUT |= D1;
					if (~P2IN & S3)secu_inverso(); //Comprueba si el boton esta pulsado
					retardo_ms(500);
					P1OUT &= ~D4;
					P3OUT &= ~(D2+D3+D6+D7+D8);
					P6OUT &= ~(D1+D5);

}

