#include <msp430.h>
#include <stdio.h>
#include <stdbool.h>
#include "MSP_Serial.h"

#define Pulsador BIT1
#define LEDVERDE BIT7
#define LEDROJO BIT0

volatile unsigned int results[3],ref[3]={0,0,0};
int sys=0;

int PararBuzzer(){
	if((P1IN & Pulsador)==0){
		sys=0;		//Apagamos todo el sistema.
		//Ponemos las tres referencias a 0 para cuando vuelva a iniciarse vuelva a guardar las referencias de ese momento.
		ref[0]=0;
		ref[1]=0;
		ref[2]=0;
		P1IFG &=~Pulsador;		//FLAG INTERUPCION a 0.
		P4OUT &=~LEDVERDE;		//LED VERDE OFF
		P1OUT &=~ LEDROJO;		//LED ROJO OFF
		return 100;
	}
}

void buzzer(){
	int i,aux=0;
	for (i=0;i<60;i++){   // Se repite 60 veces este bucle -> 60 segundos
		if (aux==0){
			TA2CCR0 = 3494;  //f1 = fSMCLK/TA0CCR0 = 1048576/3495 = 300HZ aprox
			TA2CCR2 = 1747;  //DC = TA0CCR1/TA0CCR0 = 50% -> 1748/3495 = 50%
			aux=1;
			P1OUT |= LEDROJO;		//LED ROJO ON
			__delay_cycles(500000);	//Retardo de 0,5s
			i=PararBuzzer();
		}
		if (aux==1){
			TA2CCR0 = 1612;  //f2 = fSMCLK/TA0CCR0 = 1048576/1613 = 650HZ aprox
			TA2CCR2 = 806;	 //DC = TA0CCR1/TA0CCR0 = 50% -> 807/1612 = 50%
			aux=0;
			P1OUT &=~LEDROJO;		 //LED ROJO OFF
			__delay_cycles(500000);  //Retardo de 0,5s
			i=PararBuzzer();
		}
		TA2CCR0 = 0;        // Lo ponemos a 0 para parar la sirena.
		TA2CCR2 = 0;        // Lo ponemos a 0 para parar la sirena.
	}
}

void Conf_IO(){
	//PULSADOR
	P1DIR &=~Pulsador;		// 0-> Configura Pulsador como entrada
	P1REN |= Pulsador;		// 1-> Resistencia interna Habilitada
	P1OUT |= Pulsador;		// 1-> Resistencia Pull-Up seleccionada
	P1IE  |= Pulsador;		// Interrupciones habilitadas en Pulsador
	P1IES |= Pulsador;		// Interrupcion por flanco de bajada.
	P1IFG &=~Pulsador;		// Flag de interrupcion del Pulsador a 0.

	//LED VERDE
	P4DIR |= LEDVERDE;		//P1.1-> LED VERDE como salida
	P4OUT &=~LEDVERDE;		//LED VERDE OFF

	//LED ROJO
	P1DIR |= LEDROJO;		//P1.0-> LED ROJO como salida
	P1OUT &=~LEDROJO;		//LED ROJO OFF

	//BUZZER
	P2DIR |= BIT5; 			//P2.5-> BUZZER como salida
	P2SEL |= BIT5;			//Configuramos P2.5 como TA2.2

}

void Conf_TA2(){
	// CONFIGURACIÓN DEL TIMER
	TA2CCTL2 = OUTMOD_7;		//Ponemos el modo Reset/Set
	TA2CTL = TASSEL_2 + MC_1;   //TASSEL_2 -> SMCLK fuente del reloj , MC_1-> Up Mode
}

void Conf_ADC12(){
	P6SEL = BIT0+BIT1+BIT2;                     // Activamos las tres entradas A/D que necesitaremos para este programa.
												//P6.0->A0, P6.1->A1, P6.2->A2
	ADC12CTL0 = ADC12ON+ADC12MSC+ADC12SHT0_2; 	// ADC12 activo, conversion multiple, 8 ADC12CLK ciclos de muestreo
	ADC12CTL1 = ADC12SHP+ADC12CONSEQ_1;       	// Use sampling timer, Secuencia
	ADC12MCTL0 = ADC12INCH_0;                 	// ref+=AVcc, Canal = A0
	ADC12MCTL1 = ADC12INCH_1;        			// ref+=AVcc, Canal = A1
	ADC12MCTL2 = ADC12INCH_2 + ADC12EOS;		// ref+=AVcc, Canal = A2, final de secuencia
	ADC12IE = BIT1;                           	// Habilitamos las interupciones en ADC12IFG.1
	ADC12CTL0 |= ADC12ENC;                    	// Activamos las conversiones
}

int main(void){
	WDTCTL = WDTPW+WDTHOLD;                   // Stop watchdog timer
	Conf_IO();
	Conf_TA2();
	Conf_ADC12();
	__enable_interrupt(); 					// Activamos las interrupciones

	while(1){
		if(sys==1){
			ADC12CTL0 &=~ADC12SC;			//Conversion desactivada
			ADC12CTL0 |= ADC12SC;           // Empieza la conversion
			__bis_SR_register(LPM4_bits + GIE);     // Bajo consumo activado + interrupciones activadas
			__delay_cycles (10000);
		}
	}
}

#pragma vector=PORT1_VECTOR
	__interrupt void Boton(void){
		//Con el boton activaremos o no el sistema. Con la variable sys en 1, quedara activado todo y realizara tres parpadeos el LED verde y se quedara fijo.
		//Con sys en 0, los LEDS estaran apagados y el sistema tambien.
		int i;
		if (sys==0){
			sys=1;		//Ponemos un 1 en sys para activar el sistema.
			for(i=0;i<6;i++){			//Creamos el bucle de durara 3 segundos
				P4OUT ^= LEDVERDE;		//Parpadeo del LED
				__delay_cycles(500000);	//Retardo de 0,5s
			}
			P4OUT |= LEDVERDE;			//LED VERDE ON
		}
		else{
			sys=0;					//Ponemos un 0 en sys para desactivar el sistema.
			P4OUT &=~LEDVERDE;		//LED VERDE OFF
			P1OUT &=~LEDROJO;		//LED ROJO OFF
		}
		__delay_cycles (100000);	//Retardo 0.1s
		P1IFG &=~Pulsador;
	}

#pragma vector=ADC12_VECTOR
__interrupt void ADC12ISR (void){
	switch(__even_in_range(ADC12IV,34)){
		case  0: break;                           // Vector  0:  No interrupt
		case  2: break;                           // Vector  2:  ADC overflow
		case  4: break;                           // Vector  4:  ADC timing overflow
		case  6: break;                           // Vector  6:  ADC12IFG0
		case  8:                                  // Vector  8:  ADC12IFG1
			results[0] = ADC12MEM0;               // Guardamos en vector results los valores que nos vienen del ADC12 provinientes de el acelerometro.
			results[1] = ADC12MEM1;
			results[2] = ADC12MEM2;

			if(ref[0]==0 && ref[1]==0 && ref[2]==0)		//La referencia siempre estara a 0 al principio de la ejecucion,
														//guardaremos el primer resultado obtenido como referencia para comparalo con los proximos resultados.
			{
				ref[0]=results[0];
				ref[1]=results[1];
				ref[2]=results[2];
			}
			//Deteccion de movimiento -> Si los resultados del vector varian +200 o -200 de la referencia
			//significara que se ha movido el acelerometro y por tanto debera sonar la alarma.
			//Podria ajustarse con un numero mayor para que no salte la alarma tan facil, pero yo lo he dejado asi ya que para las pruebas me resultaba mejor.
			if (results[0]<ref[0]-200 || results[0]>ref[0]+200 ||
				results[1]<ref[1]-200 || results[1]>ref[1]+200 ||
				results[2]<ref[2]-200 || results[2]>ref[2]+200)
			{
				buzzer();
				__delay_cycles(2000000);  //Retardo 2 segundos despues de parar la alarma para que no se vuelva a iniciar el sistema sin querer.
			}
			__bic_SR_register_on_exit(LPM4_bits);   // Exit active CPU
			break;
		default: break;
	}
}


