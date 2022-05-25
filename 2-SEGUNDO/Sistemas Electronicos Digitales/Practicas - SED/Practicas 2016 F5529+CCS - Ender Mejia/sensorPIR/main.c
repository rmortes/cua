#include <msp430.h>

int PVez=0;
int veces;

// función sirena() que genera dos frecuencias
// determinadas por los valores de TA0CCR0 y TA0CCR1
// la salida se produce en P1.2 que se utiliza como TA0.1

void sirena(int veces) {
	// Programa principal
	int t;
	for (t=0;t<veces;t++){   // repite veces las frecuencias
		if (PVez==0){
			TA0CCR0 = 999;    //f1 = fSMCLK/TA0CCR0 = 106/1000= 1KHZ
			TA0CCR1 = 499;    //DC= TA0CCR1/TA0CCR0 = (500/1000)% = 50%
			PVez++;
			__delay_cycles(500000);  //duración de la frecuencia 1; 0,5s
		}
		else{
			TA0CCR0 = 799;   //f2 = fSMCLK / TA0CCR0 = 106/800 = 1,25KHZ
			TA0CCR1 = 399;   // DC= TA0CCR1/TA0CCR0 = (400/800)% = 50%
			PVez=0;
			__delay_cycles(500000);  //duración de la frecuencia 2; 0,5s
		}
		TA0CCR0 =0;                  // PARA QUE SE PARE LA SIRENA
		TA0CCR1 = 0;                // PARA QUE SE PARE LA SIRENA }
	}
}
// Programa principal
int main(void) {
	WDTCTL = WDTPW | WDTHOLD; // Stop watchdog timer

	// CONFIGURACIÓN DEL P1.2 COMO SALIDA DE TA0.1
	P1SEL = BIT2;		// Configuramos P1.2 como salida del Timer
	P1DIR |= BIT2;      // Y la habilitamos como salida

	// CONFIGURACIÓN DEL TIMER
	TA0CCTL1 = OUTMOD_7;
	// Registro Captura/Compara 1 del Timer A0
	// el modo Salida Reset/Set

	TA0CTL = TASSEL_2 + MC_1;   //modo ascendente y SMCLK fuente del reloj

	P1DIR |=BIT0;     // P1.0 como salida LED rojo cuando movimiento
	P1OUT =0x0;
	P6DIR &=~BIT6;    // P6.6 entrada que viene del sensor PIR

	while(1){
		if (P6IN & BIT6) {  // si hay movimiento
			sirena(10);
			P1OUT |= BIT0;
		}
		else {
			P1OUT &= ~BIT0;
		}
	}
}
