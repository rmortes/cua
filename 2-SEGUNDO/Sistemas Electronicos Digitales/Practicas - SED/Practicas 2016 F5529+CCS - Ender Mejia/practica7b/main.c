/*+
 * PRACTICA 7
 * Ejercicio 2.
 * Utilización del ADC12 Escribe un programa para que el led conectado a P1.0
 * se encienda cuando la tensión de entrada colocada en P6.3 >0,5*Vcc
 */
void ConfigADC (void);

#include <msp430.h>
int main(void){

	WDTCTL = WDTPW + WDTHOLD; 				// Stop WDT

	ConfigADC();// A partir de aquí no se puede cambiar
	// la configuración


	P6SEL |= BIT0; 							// P6.0 seleccionado como entrada del ADC
	P1DIR |= BIT0; 							// P1.0 salida
	while (1)
	{
		ADC12CTL0 |= ADC12SC; 				// Inicia el muetreo y la conversión
		__bis_SR_register(LPM0_bits + GIE); // LPM0, habilita int globales
		__no_operation(); 					// que se para para depurar
	}
}
#pragma vector = ADC12_VECTOR
__interrupt void ADC12_ISR(void)
{
	switch(ADC12IV) {
	case 0: break; 							// Vector 0: No interrupt
	case 2: break; 							// Vector 2: ADC overflow
	case 4: break; 							// Vector 4: ADC timing overflow
	case 6: 								// Vector 6: ADC12IFG0
		if (ADC12MEM0 >= 0x7ff){ 			// ADC12MEM = A0 > 0.5AVcc?
			P1OUT |= BIT0; 					// una vez superado, encendemos el led P1.0
		}
		else{
			P1OUT &= ~BIT0; 				// si no se supera, apagamos el led P1.0
		}
		__bic_SR_register_on_exit(LPM0_bits); // Sale y activa la CPU

	case 8: break; 							// Vector 8: ADC12IFG1
	case 10: break; 						// Vector 10: ADC12IFG2
	case 12: break; 						// Vector 12: ADC12IFG3
	case 14: break; 						// Vector 14: ADC12IFG4
	case 16: break; 						// Vector 16: ADC12IFG5
	case 18: break;							// Vector 18: ADC12IFG6
	case 20: break; 						// Vector 20: ADC12IFG7
	case 22: break; 						// Vector 22: ADC12IFG8
	case 24: break; 						// Vector 24: ADC12IFG9
	case 26: break; 						// Vector 26: ADC12IFG10
	case 28: break; 						// Vector 28: ADC12IFG11
	case 30: break; 						// Vector 30: ADC12IFG12
	case 32: break; 						// Vector 32: ADC12IFG13
	case 34: break; 						// Vector 34: ADC12IFG14
	default: break;
	}
}

void ConfigADC(void){

	ADC12CTL0 = ADC12SHT02 + ADC12ON;
	//ADC12SHT02 = muestrea cada 16 ciclos
	//ADC12ON = habilita ADC12
	ADC12CTL1 = ADC12SHP; 					// Utiliza el Timer para el muestreo
	ADC12IE |= BIT0; 						// Habilita interrupción de ADC12MEM0
	ADC12CTL0 |= ADC12ENC;


}
