/*
SIRENA CON SENSOR PIR
**Vicent Gilabert Mañó**
Descripcion: 	Cuando el sensor detecte movimiento, entonces se enviara un 1 a la salida y la sirena sonara.
				Aparte se encendera un LED que parpadeara juntamente con la sirena.
				La sirena sonara a la frecuencia de 1KHz y 1.25KHz durante 10 segundos,
				pero sonara cada segundo a una frecuencia diferente.
*/

#include <msp430.h>

int main(void) {
	WDTCTL = WDTPW | WDTHOLD; // Stop watchdog timer
	int i,aux=0;
	// CONFIGURACIÓN DEL P1.2 COMO SALIDA DE TA0.1
	P1SEL |= BIT2;	//Seleccionamos la opcion del timer
	P1DIR |= BIT2; 	//P1.2 -> Definimos como salida

	//CONFIGURACION LED
	P2DIR |= BIT2; 	//Definimos como salida en 2.2 para el LED
	//P2DIR &=~ BIT2; //Empezamos con el LED Apagado.

	//CONFIGURACION DE P2.0 PARA EL SENSOR
	P2DIR &=~BIT0; 	//P2.0 -> Definimos como entrada
    P2REN |= BIT0;	//P2.0 -> Activamos la resistencia interna
    P2OUT |= BIT0;	//Resistencia Pull-Up

	// CONFIGURACIÓN DEL TIMER
	TA0CCTL1 = OUTMOD_7;		//Ponemos el modo Reset/Set
	TA0CTL = TASSEL_2 + MC_1;   //TASSEL_2 -> SMCLK fuente del reloj // MC_1 -> Modo ascendente
	
	for(;;){
		if(P2IN & BIT0){			//Si el sensor detecta movimiento -> Sirena encendida
			for (i=0;i<10;i++){   	// Se repite 10 veces este bucle -> 10 segundos
				if (aux==0){
					TA0CCR0 = 799;  //f1 = fSMCLK/TA0CCR0 = 106/800 = 1,25KHZ
					TA0CCR1 = 399;  //DC = TA0CCR1/TA0CCR0 = (400/800)% = 50%
					aux=1;
					P2OUT |= BIT2; 	//LED ON
					__delay_cycles(500000);	//duración de f1 -> 0,5s
				}
				if (aux==1){
					TA0CCR0 = 999;  //f2 = fSMCLK/TA0CCR0 = 106/1000= 1KHZ
					TA0CCR1 = 499;	//DC = TA0CCR1/TA0CCR0 = (500/1000)% = 50%
					aux=0;
					P2OUT &=~BIT2; 	//LED OFF
					__delay_cycles(500000);  //duración de f2 -> 0,5s
				}
				TA0CCR0 = 0;        // Lo ponemos a 0 para parar la sirena.
				TA0CCR1 = 0;        // Lo ponemos a 0 para parar la sirena.
			}
		}
	}
}
