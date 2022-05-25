#include <msp430.h>
#define Rojo1 BIT3
#define Ambar1 BIT4
#define Verde1 BIT4
#define Rojo2 BIT0
#define Ambar2 BIT1
#define Verde2 BIT2

void retardo_ms(unsigned int ms);
void config_port(void);
/* ______________	_____________
 * |		S1		|	|	S2		|
 * |R	O	P3.3|	|R	O	P3.0|	|Rojo
 * |A	O	P3.4|	|A	O	P3.1|	|Ambar
 * |V	O	P6.5|	|V	O	P3.2|	|Verde
 * |____________|	|___________|
 */
void main(void)
{
	int i;
	WDTCTL=WDTPW+WDTHOLD;
	config_port();
	for(;;){
		/* Estado 1 */				// S1 Rojo y S2 Verde durante 5 segundos
		P3OUT |= Rojo1;				// Rojo del S1 encendido
		P3OUT |= Verde2;			// Verde del S2 encendido
		retardo_ms(5000);

		/* Estado 2 */				// S1 Rojo y S2 Verde parpadeando a 4 Hz 6 veces (1,5 segundos)
		for (i=6;i>0;i--){			// Bucle para realizar 6 parpadeos (6 veces encendido y apagado) a 4 Hz
			P3OUT ^= Verde2;
			retardo_ms(125);
			P3OUT ^= Verde2;
			retardo_ms(125);
		}

		/* Estado 3 */				// S1 Rojo y S2 en ambar 1 segundo
		P3OUT &= ~Verde2;			// Verde S2 apagado
		P3OUT |= Ambar2;			// Ambar S2 encendido
		retardo_ms(1000);			// Retardo de un segundo

		/* Estado 4 */				// S1 Verde y S2 Rojo durante 6 segundos
		P3OUT &= ~Ambar2;			// Ambar S2 apagado
		P3OUT &= ~Rojo1;			// Rojo S1 apagado
		P6OUT |= Verde1;			// Verde S1 encendido
		P3OUT |= Rojo2;				// Rojo S2 encendido
		retardo_ms(6000);

		/* Estado 5 */				// S2 Rojo y S1 Verde parpadeando a 4 Hz 10 veces (2,5 segundos)
		for (i=10;i>0;i--){			// Bucle para realizar 10 parpadeos (10 veces encendido y apagado) a 4 Hz
			P6OUT ^= Verde1;
			retardo_ms(125);
			P6OUT ^= Verde1;
			retardo_ms(125);
		}

		/* Estado 6 */				// S2 Rojo y S1 en Ambar 1 segundo
		P6OUT &= ~Verde1;			// Verde S1 apagado
		P3OUT |= Ambar1;			// Ambar S1 encendido
		retardo_ms(1000);			// Retardo de un segundo

		/* Reset para repeticion de bucle */
		P3OUT &= ~0x1F;         	// P3.0 a P3.4 a 0.
		P6OUT &= ~0x20;      		// P6.5 a 0.
	}
}
void config_port(void)
{
	P3SEL &= ~0x1F;					// P3.0 a P3.4 como I/O general (GPIO)
	P3DIR |= 0x1F; 					// P3.0 a P3.4 como salida
	P3OUT &= ~0x1F;         		// P3.0 a P3.4 a 0.
	P6SEL &= ~0x20;   				// P6.5 como I/O general (GPIO)
	P6DIR |= 0x20;             	 	// P6.5 como salida
	P6OUT &= ~0x20;      			// P6.5 a 0.
}
void retardo_ms(unsigned int ms)
{
	while (ms)
	{
		__delay_cycles(1000); 		// 1000 para 1MHz y 16000 para 16MHz
		ms--;
	}
}
