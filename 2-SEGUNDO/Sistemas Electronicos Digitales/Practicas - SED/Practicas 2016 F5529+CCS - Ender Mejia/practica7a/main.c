/*+
 * PRACTICA 7
 * Ejercicio 1. Utilización del comparador B
 * Programa para que el led conectado a P1.0 parpadeé a 8Hz cuando la tensión
 * de entrada colocada en P6.1(CB1) > 2,5v y apagado en cualquier otro caso.
 * NOTA: Utilizar una salida PWM para generar el parpadeo del led
 */
#include <msp430.h> 

unsigned int estado=0;
void ConfigTimer(void);
void ConfigCompB(void);

int main(void) {
	WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

	P1DIR |= BIT0; //p1.0 como salida led
	P1OUT &= ~BIT0;//apagado al inicio

	ConfigTimer();
	ConfigCompB();
	while(1){
		if(estado==1){
			P1OUT ^= BIT0;//led P1.0 encendido mientras se supere Vcref (2,5v)
			estado = 0;//ponemos el estado a 0 para que se vuelva a comrpbar
			//si se sugue superando Vcref
		}
		else{
			P1OUT &= ~BIT0;//se apaga cuando no se supera Vcref
		}

	}
}

//  Interrupcion comparador cuando P6.1 > 2,5v   ///////////////////////////////////////////
#pragma vector=COMP_B_VECTOR
__interrupt void Comparador_B_ISR (void){

	CBCTL1 ^= CBIES;
	CBINT &= ~CBIFG;
	estado=1; //en caso de superarse Vcref, se activará
}
///////////////////////////////////////////////////////////////////////////////////////////

void ConfigTimer(void){

	//Configuramos timer  ----------------------------------------

	//TA0.0-->P1.1
	//TA0.1-->P1.2
	P1DIR |= BIT2;	//P1.2 como salida --> TA0.1
	P1SEL |= BIT2;

	TA0CTL = TASSEL_2 + MC_1 + ID_2 + TAIE;
	//TASSEL_2 = SMCLK (0=TACLK  1=ACLK  3=INCLK)
	//MC_1 = creciente hasta TACCR0 (0=parada, 2=hasta FFFF)
	//ID_2 = divide la frec de Reloj/4 (0=f/1  1=f/2  2=f/4  3=f/8)
	//TAIE = habilita la interrupcion del timer

	//CCR0 = TiempoNecesario/TiempoCLK
	// SMCLK/4 = 1MHz/4 = 1/250000 segundos
	// queremos que funcione a 8Hz= 1/8s
	// CCR0= (1/8)/(1/250000)= 125000
	TA0CCR0 = 31250;
	TA0CCR1 = 31250/2; //duty 50%

	TA0CCTL1 = OUTMOD_7;
	//OUTMOD_2 para que se meta en una interrupcion
	//OUTMOD_7 para una cuenta

	//------------------------------------------------------------
}


void ConfigCompB(void){

	// Configuración del Comparador B   ----------------------------------------------------------------
		CBCTL0 |= CBIPEN + CBIPSEL_1; 	// habilita V+, canal de entrada P6.1/CB0  (si fuese P6.x-->CBIPSEL_x)
		CBCTL1 |= CBPWRMD_1;         	// modo normal alimentación
		CBCTL2 |= CBRSEL;             	// VREF se aplica al terminal
		CBCTL2 |= CBRS_3+CBREFL_3;    	// Escalera de R deshabilitada
		//CBREFL_1-->Vcref =1,5v
		//CBREFL_2-->Vcref =2v
		//CBREFL_3-->Vcref =2,5v
		CBCTL3 |= BIT1;   // Buffer Entrada Deshabilitado @P6.1/CB0
		//BIT1 -->P6.1
		__delay_cycles(75);           // retardo para la estabilización

		CBINT &= ~(CBIFG + CBIIFG);   // borra cualquier interrupción pendiente
		CBINT  |= CBIE;               // Habilita la interrupción de CompB
		//por flanco de bajada   de CBIFG (CBIES=0)

		CBCTL1 |= CBON;               // Conecta el ComparatorB

		__bis_SR_register(LPM0_bits+GIE);          // Modo LPM4 y habilita interrupciones
		__no_operation();                      // para el debug

//--------------------------------------------------------------------------------------------
}

