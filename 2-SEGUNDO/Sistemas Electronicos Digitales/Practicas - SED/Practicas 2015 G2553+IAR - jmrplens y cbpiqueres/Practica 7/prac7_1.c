#include <msp430.h>

// El ADC10MEM es igual a 3FF cuando la tension de entrada es igual o mayor a Vr+ (refencia), y es 0 cuando es igual o menor a Vr-
// Para calcular el numero en decimal de ADC10MEM que habra segun la comparacion, hay que saber que ADC10MEM=(Vin/Vr+)*1023.
// Para una referencia de 2.5V, si a la entrada ponemos 2.5V, tendremos el maximo que es 1023 (3FFh)
// Como queremos que se active cuando la tension es mayor a 0.5*Vcc, no activamos la referencia del ADC10, asi usara como refencia el Vcc.
// como tenemos 3.3V de Vcc, el valor que habra en ADC10MEM sera 1FF

int main(void)
{
    WDTCTL = WDTPW + WDTHOLD;
    ADC10CTL0 = ADC10ON;
    ADC10CTL1 = INCH_1;
    ADC10AE0 |= BIT1;
    P1DIR |= BIT6;

    for (;;){

        ADC10CTL0 |= ENC + ADC10SC;
        if (ADC10MEM > 0x1FF){
            P1OUT |= BIT6;
        }else{
            P1OUT &= ~ BIT6;
        }
    }
}

