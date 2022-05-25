#include "msp430.h"
/* Constantes para facilitar el uso de los pines en el codigo */
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
/* Declaracion de las funciones */
void config_leds ();
void config_buttons();
void retardo_ms(unsigned int ms);
void secu_original();
void secu_inversa ();

/* Programa Principal */
int main()
{
	WDTCTL=WDTPW+WDTHOLD;
	config_leds();                	// Configura los leds
	config_buttons();      			// Configura los botones
	__enable_interrupt();			// Activa las interrupciones
	for(;;)secu_original();			// Bucle infinito que realiza la secuencia original
}

/* Funcion que se ejecuta en la interrupcion de una entrada del puerto 2 */
#pragma vector=PORT2_VECTOR       	// Vector de interrupcion vector=0xFFE6
__interrupt void P2_Interrupt()
{
	if (P2IFG & S3) {               	// Si pulsa P2.0
		P2IFG &= ~S3;            	// Borra el flag del P2.0
		secu_inversa();				// Llama a la funcion que realiza la secuencia inversa
	}
	if (P2IFG & S4) {               	// Si pulsa P2.2
		P2IFG &= ~S4;              	// Borra el flag del P2.2
	}
}

/* Funcion que realiza la secuencia original. Enciende los leds de D8 a D1 */
void secu_original()
{
	/* Inicio de secuencia */
	retardo_ms(500);
	P3OUT |= D8;
	retardo_ms(500);
	P3OUT |= D7;
	retardo_ms(500);
	P3OUT |= D6;
	retardo_ms(500);
	P6OUT |= D5;
	retardo_ms(500);
	P1OUT |= D4;
	retardo_ms(500);
	P3OUT |= D3;
	retardo_ms(500);
	P3OUT |= D2;
	retardo_ms(500);
	P6OUT |= D1;
	retardo_ms(500);
	/* Apagar los leds */
	P1OUT &= ~D4;
	P3OUT &= ~(D2+D3+D6+D7+D8);
	P6OUT &= ~(D1+D5);
}

/* Funcion que realiza la secuencia inversa. 1. Almacena el estado de los leds. 2. Enciende los leds de D1 a D8. 3. Devuelve el estado */
void secu_inversa ()
{
	unsigned int R4,R5,R6,i;			// Variables para almacenar el estado de los leds y para parpadeo

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

/* Funcion para configurar los puertos de los led */
void config_leds ()
{
	/* DIODO 4 -> P1.6 */
	P1SEL &= ~D4;					// P1.6 como I/O general (GPIO)
	P1DIR |= D4;						// Configura P1.6 como salida
	P1OUT &= ~D4;					// Pone a 0 P1.6 (Led Apagado)

	/* DIODO 2 -> P3.4 ; DIODO 3 -> P3.3 ; DIODO 6 -> P3.2 ; DIODO 7 -> P3.1 ; DIODO 8 -> P3.0 */
	P3SEL &= ~(D2+D3+D6+D7+D8);		// [P3.0,P3.1,P3.2,P3.3,P3.4] como I/O general (GPIO)
	P3DIR |= D2+D3+D6+D7+D8;			// Configura [P3.0,P3.1,P3.2,P3.3,P3.4] como salida
	P3OUT &= ~(D2+D3+D6+D7+D8);		// Pone a 0 [P3.0,P3.1,P3.2,P3.3,P3.4] (Led Apagado)

	/* DIODO 1 -> P6.5 ; DIODO 5 -> P6.6 */
	P6SEL &= ~(D1+D5);				// [P6.5,P6.6] como I/O general (GPIO)
	P6DIR |= D1+D5;					// Configura [P6.5,P6.6] como salida
	P6OUT &= ~(D1+D5);				// Pone a 0 [P6.5,P6.6] (Led Apagado)
}

/* Funcion para configurar los botones */
void config_buttons()
{
	P2SEL &= ~(S3+S4);				// P2.0 y P2.2 como I/O general (GPIO)
	P2DIR &= ~(S3+S4);				// Configura P2.0 y P2.2 como entrada
	P2REN |= S3+S4;					// Pone a 1 P2.0 y P2.2 en P2REN (Resistencia Habilitada)
	P2OUT |= S3+S4;					// Pone a 1 P2.0 y P2.2 para esperar a un 0 (Resistencia Pull-Up seleccionada)
	P2IES |= S3+S4;               	// Interrupcion por flanco de bajada en P2.0 y P2.2 (Espera un 0)
	P2IFG &= ~(S3+S4);				// Reset del flag de interrupcion en P2.0 y P2.2
	P2IE |= S3+S4;					// Interrupciones habilitadas en P2.0 y P2.2
}

/* Retardo en milisegundos */
void retardo_ms(unsigned int ms)
{
	while (ms)
	{
		__delay_cycles(1000); 		// 1000 para 1MHz y 16000 para 16MHz
		ms--;
	}
}

