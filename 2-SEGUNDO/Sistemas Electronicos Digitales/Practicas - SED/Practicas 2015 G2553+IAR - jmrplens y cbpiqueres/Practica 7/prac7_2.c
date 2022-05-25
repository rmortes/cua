#include <msp430.h>

// El ADC10MEM es igual a 3FF cuando la tension de entrada es igual o mayor a Vr+ (refencia), y es 0 cuando es igual o menor a Vr- (Habitualmente 0V)
// Para calcular el numero en decimal de ADC10MEM que habra segun la comparacion, hay que saber que ADC10MEM=(Vin/Vr+)*1023.
// Para una referencia de 2.5V, si a la entrada ponemos 2.5V, tendremos el maximo que es 1023 (3FFh)
// Ahora se nos pide que cuando ADC10MEM sea mayor que 0x52 con Vr=2.5V con Vin en 1.2 (CA2), se encienda un led, despejamos de la ecuacion
// Vin, y nos da 0.2V, si en P1.2 introducimos mas de 0,2V se encendera el led, sino no.

int main(void) 
{
    WDTCTL = WDTPW + WDTHOLD;
    ADC10CTL0 = ADC10ON + REFON + REF2_5V;
    ADC10CTL1 = INCH_2;
    ADC10AE0 |= BIT2;
    P1DIR |= BIT6;
    
    for (;;){

        ADC10CTL0 |= ENC + ADC10SC;
        if (ADC10MEM > 0x52){
            P1OUT |= BIT6;
        }else{
            P1OUT &= ~BIT6;
        }
    }
}
