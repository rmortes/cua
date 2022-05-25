#include <msp430.h>
#define Rojo1 BIT3
#define Ambar1 BIT4
#define Verde1 BIT5
#define Rojo2 BIT0
#define Ambar2 BIT1
#define Verde2 BIT2

int main(void) {
	WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	P3DIR |= (Rojo2 + Ambar2 + Verde2 + Rojo1 + Ambar1);
	P6DIR |= Verde1;

	unsigned int i;
	for(;;){
		//**Estado 1** --> S1 Rojo / S2 Verde
		P3OUT |= Rojo1;			//S1 Rojo ON
		P3OUT &= ~Ambar1;		//S1 Ambar OFF
		P6OUT &= ~Verde1; 		//S1 Verde OFF
		P3OUT &= ~Rojo2;		//S2 Rojo OFF
		P3OUT &= ~Ambar2; 		//S2 Ambar OFF
		P3OUT |= Verde2;		//S2 Verde ON
		__delay_cycles(1048576*4); 	//Retardo de 4 segundos

		//**Estado 2** --> Parpadeo S2 durante 5 veces.
		for(i=5;i>0;i--){
			P3OUT &= ~Verde2;	//S2 Verde OFF
			__delay_cycles(1048576/5);
			P3OUT |= Verde2; 	//S2 Verde ON
			__delay_cycles(1048576/5);
		}

		//**Estado 3** --> S2 Ambar durante un segundo
		P3OUT |= Ambar2;		//S2 Ambar ON
		P3OUT &= ~Verde2;		//S2 Verde OFF
		__delay_cycles(1048576); //retardo de 1 segundo

		//**Estado 4** --> S1 Verde / S2 Rojo
		P3OUT &= ~Ambar2;		//S2 Ambar OFF
		P3OUT |= Rojo2;			//S2 Rojo ON
		P3OUT &= ~Rojo1;		//S1 Rojo OFF
		P6OUT |= Verde1;		//S1 Verde ON
		__delay_cycles(1048576*6);		//retardo de 6 segundos

		//**Estado 5** -->S1 Parpadeo durante 5 veces.
		for(i=5;i>0;i--){
			P6OUT &= ~Verde1;	//S1 Verde OFF
			__delay_cycles(1048576/5);
			P6OUT |= Verde1; 	//S1 Verde ON
			__delay_cycles(1048576/5);
		}

		//**Estado 6** --> S1 Ambar durante un segundo
		P3OUT |= Ambar1;		//S1 Ambar ON
		P6OUT &= ~Verde1;		//S1 Verde OFF
		__delay_cycles(1048576); 	//retardo de 1 segundo
	}
}
