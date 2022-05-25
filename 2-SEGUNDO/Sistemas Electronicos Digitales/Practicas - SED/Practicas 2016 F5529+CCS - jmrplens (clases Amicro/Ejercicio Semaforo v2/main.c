#include <msp430.h>
#define Rojo1 	BIT3
#define Ambar1 	BIT4
#define Verde1 	BIT4
#define Rojo2 	BIT0
#define Ambar2 	BIT1
#define Verde2 	BIT2
#define PRojo 	BIT6
#define PVerde 	BIT6
#define Pulsador	BIT2
unsigned int i;
void retardo_ms(unsigned int ms);
void config_port(void);
/* ______________	_____________
 * |		S1		|	|	S2		|
 * |R	O	P3.3	|	|R	O	P3.0	|	|Rojo
 * |A	O	P3.4	|	|A	O	P3.1	|	|Ambar
 * |V	O	P6.4	|	|V	O	P3.2	|	|Verde
 * |____________	|	|___________	|
 *
 * Peatones
 * ______________
 * |		P		|			|	   _
 * |R	O	P6.6	|	|Rojo	|	__/^\__	Pulsador P2.2 (Conectado a masa)
 * |V	O	P1.6	|	|Verde	|
 * |____________	|			|
 */
void main(void)
{
	WDTCTL=WDTPW+WDTHOLD;
	config_port();
	__enable_interrupt(); 		// Activa el uso de interrupciones en el programa
	for(;;){
		/* Estado 1 */			// S1 Rojo y S2 Verde durante 5 segundos
		P3OUT |= Rojo1;			// Rojo del S1 encendido
		P3OUT |= Verde2;			// Verde del S2 encendido
		P1OUT |= PVerde;			// Verde peatones encendido
		retardo_ms(5000);

		/* Estado 2 */			// S1 Rojo y S2 Verde parpadeando a 4 Hz 6 veces (1,5 segundos)
		for (i=6;i>0;i--){		// Bucle para realizar 6 parpadeos (6 veces encendido y apagado) a 4 Hz
			P3OUT ^= Verde2;
			retardo_ms(125);
			P3OUT ^= Verde2;
			retardo_ms(125);
		}

		/* Estado 3 */			// S1 Rojo y S2 en ambar 1 segundo
		P3OUT &= ~Verde2;		// Verde S2 apagado
		P3OUT |= Ambar2;			// Ambar S2 encendido
		retardo_ms(1000);		// Retardo de un segundo

		/* Estado 4 */			// S1 Verde y S2 Rojo durante 6 segundos
		P3OUT &= ~Ambar2;		// Ambar S2 apagado
		P3OUT &= ~Rojo1;			// Rojo S1 apagado
		P6OUT |= Verde1;			// Verde S1 encendido
		P3OUT |= Rojo2;			// Rojo S2 encendido
		P1OUT &= ~PVerde;		// VerdePeatones apagado
		P6OUT |= PRojo;			// RojoPeatones encendido
		retardo_ms(6000);

		/* Estado 5 */			// S2 Rojo y S1 Verde parpadeando a 4 Hz 10 veces (2,5 segundos)
		for (i=10;i>0;i--){		// Bucle para realizar 10 parpadeos (10 veces encendido y apagado) a 4 Hz
			P6OUT ^= Verde1;
			retardo_ms(125);
			P6OUT ^= Verde1;
			retardo_ms(125);
		}

		/* Estado 6 */			// S2 Rojo y S1 en Ambar 1 segundo
		P6OUT &= ~Verde1;		// Verde S1 apagado
		P3OUT |= Ambar1;			// Ambar S1 encendido
		retardo_ms(1000);		// Retardo de un segundo

		/* Reset para repeticion de bucle (No es necesario pero protege ante fallos) */
		P3OUT &= ~(Rojo1+Ambar1+Rojo2+Ambar2+Verde2);	// S2 a 0 y Rojo y Ambar de S1 a 0
		P6OUT &= ~(Verde1+PRojo);						// Verde S1 y Rojo Peatones a 0.
		P1OUT &= ~PVerde;								// Verde peatones a 0
	}
}

void peticion()
{
	unsigned int R4,R5,R6;
	/* Almacena en 3 enteros los valores en los 3 puertos usados para los leds */
	R4 = P1OUT;
	R5 = P3OUT;
	R6 = P6OUT;
	retardo_ms(4000);			// A los 4 segundos de la peticion realiza la funcion
	for(i=0;i<10;i++){			// 5 parpadeos a 4 Hz (125 apagado + 125 encendido = 250ms = 4Hz)
		P1OUT ^= PVerde;			// Alterna el estado del verde de peatones
		retardo_ms(125);
	}
	P1OUT |= PVerde;				// Verde peatones encendido. No se sabe con seguridad si sale activo o no del bucle.
	P3OUT |= Ambar1;				// Ambar S1 encendido
	P3OUT &= ~Rojo1;				// Rojo S1 apagado
	P6OUT &= ~Verde1;			// Verde S1 apagado
	retardo_ms(2000);
	P3OUT |= Rojo1;				// Rojo S1 encendido
	P3OUT &= ~Ambar1;			// Ambar S1 apagado
	P6OUT &= ~PRojo;				// Rojo peatones encendido
	retardo_ms(20000);
	/* Devuelve el estado de los leds a como estaban antes de entrar a esta funcion */
	P1OUT = R4;
	P3OUT = R5;
	P6OUT = R6;

}

#pragma vector=PORT2_VECTOR
__interrupt void P2_Interrupt()
{
	if (P2IFG & BIT2){
		P2IFG &= ~BIT2;
		peticion();
	}
}
void config_port(void)
{
	P1SEL &= ~PVerde;							// Verde peatones como I/O general (GPIO)
	P1DIR |= PVerde; 							// Verde peatones como salida
	P1OUT &= ~PVerde;         					// Verde peatones a 0.
	P3SEL &= ~(Rojo1+Ambar1+Rojo2+Ambar2+Verde2);// S2 y Rojo/Ambar de S1 como I/O general (GPIO)
	P3DIR |= Rojo1+Ambar1+Rojo2+Ambar2+Verde2; 	// S2 y Rojo/Ambar de S1 como salida
	P3OUT &= ~(Rojo1+Ambar1+Rojo2+Ambar2+Verde2);// S2 y Rojo/Ambar de S1 a 0.
	P6SEL &= ~(Verde1+PRojo);   					// Verde S1 y Rojo Peatones como I/O general (GPIO)
	P6DIR |= Verde1+PRojo;             	 		// Verde S1 y Rojo Peatones como salida
	P6OUT &= ~(Verde1+PRojo);      				// Verde S1 y Rojo Peatones a 0.
	P2SEL &= ~Pulsador;							// Pulsador como I/O general (GPIO)
	P2DIR &= ~Pulsador;							// Configura Pulsador como entrada
	P2REN |= Pulsador;							// Pone a 1 el Pulsador en P2REN (Resistencia Habilitada)
	P2OUT |= Pulsador;							// Pone a 1 el Pulsador para esperar a un 0 (Resistencia Pull-Up seleccionada)
	P2IE  |= Pulsador;							// Interrupciones habilitadas en Pulsador
	P2IES |= Pulsador;							// Interrupcion por flanco de bajada en Pulsador (Espera un 0)
	P2IFG &= ~Pulsador;							// Reset del flag de interrupcion en Pulsador
}
void retardo_ms(unsigned int ms)
{
	while (ms)
	{
		__delay_cycles(1000); 		// 1000 para 1MHz y 16000 para 16MHz
		ms--;
	}
}
