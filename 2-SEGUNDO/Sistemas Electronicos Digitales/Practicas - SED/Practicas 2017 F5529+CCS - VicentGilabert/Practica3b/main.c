#include <msp430.h>

int main(void){
	int vel;
	WDTCTL = WDTPW + WDTHOLD; 		// Stop WDT.

	P1DIR |= BIT2; 					// Configuramos P1.2 como salida.
	P1SEL |= BIT2; 					// Seleccionamos el modo en P1.2 para sacar TA0.0.

	TA0CTL = TASSEL_2+MC_1+TACLR; 	// Configuramos el timer con la señal SMCLK, modo continuo.
									//TASSEL ->->->  0-> TACL ; 1-> ACLK ; 2-> SMCLK (1 Mhz) ; 3->INCLK
									// MC_0 parado; MC_1 cuenta hasta TACCR0 ; MC_2 cuenta hasta FFFF
									//TACLR borra la cuenta
									// ID_0=divide la frec de reloj/2^n || (0=f/1 ; 1=f/2 ; 2=f/4 ; 3=f/8)

	TA0CCTL1 = OUTMOD_7; 			// Seleccionamos el modo PWM 7.
	TA0CCR0 = 250; 					// Asignamos los valores previamente calculados para generar la señal..
									//Trabajamos a 1MHz/400Khz = 250

	/*for(;;){
		for(vel=0;vel<101;vel++){		//Esto se realizaria una vez, si quisiera que fuese infinito se podria hacer con un bucle infinito.
			TA0CCR1 = vel*TA0CCR0/100; 	// Asignamos el DC. Siempre tiene que ser mayor de 18% para que funcione. En este caso seria el 75%.
			__delay_cycles(1000000/6);
		}
	}*/

	for(vel=0;vel<101;vel++){		//Esto se realizaria una vez, si quisiera que fuese infinito se podria hacer con un bucle infinito.
			TA0CCR1 = vel*TA0CCR0/100; 	// Asignamos el DC. Siempre tiene que ser mayor de 18% para que funcione. En este caso seria el 75%.
			__delay_cycles(1000000/6);
			if(vel==100){
				vel=0;
			}
		}
	_bis_SR_register(LPM0_bits); 	// Entramos modo bajo consumo.
}
