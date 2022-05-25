#include <msp430.h> 

int main(void) {
	WDTCTL = WDTPW + WDTHOLD; // Stop WDT
	ADC12CTL0 = ADC12SHT02 + ADC12ON; // 1) Sampling time, ADC12 on
	ADC12CTL1 = ADC12SHP; // Use sampling timer
	ADC12IE = 0x01; // Enable interrupt of ADC12MEM0
	ADC12CTL0 |= ADC12ENC; // 2) Enable Conversion
	P6SEL |= 0x01; // Select P6.0(A0) as analog input
	P1DIR |= 0x01; // P1.0 output
	while (1) {
		ADC12CTL0 |= ADC12SC; // 3) Start sampling/conversion
		__bis_SR_register(LPM0_bits + GIE); // LPM0, ADC12_ISR will force exit
		__no_operation(); // For debugger
	}
}
