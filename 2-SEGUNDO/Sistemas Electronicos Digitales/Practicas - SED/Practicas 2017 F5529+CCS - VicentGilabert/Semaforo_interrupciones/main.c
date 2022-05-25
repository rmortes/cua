#include <msp430.h>
#define Rojo1 BIT3
#define Ambar1 BIT4
#define Verde1 BIT5
#define Rojo2 BIT0
#define Ambar2 BIT1
#define Verde2 BIT2
#define Pulsador BIT1
#define RojoPeatones  BIT2
#define VerdePeatones  BIT3

unsigned int i,R2,R3;

int main(void) {
	WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	__enable_interrupt(); 		// Activa el uso de interrupciones en el programa

	//Configuraciones de los puertos para los LEDS
	P3DIR |= (Rojo2 + Ambar2 + Verde2 + Rojo1 + Ambar1 + Verde1);
	P2DIR |= (RojoPeatones + VerdePeatones);

	//Configuracion Pulsador en el puerto 2.1
	P2DIR &=~Pulsador;			// Configura Pulsador como entrada
	P2REN |= Pulsador;			// 1-> Resistencia interna Habilitada
	P2OUT |= Pulsador;			// 1-> Resistencia Pull-Up seleccionada
	P2IE  |= Pulsador;			// Interrupciones habilitadas en Pulsador
	P2IES |= Pulsador;			// Interrupcion por flanco de bajada.
	P2IFG &=~Pulsador;			// Flag de interrupcion en Pulsador a 0.

	for(;;){
		//**Estado 1** --> S1 Rojo / S2 Verde / Peatones Verde
		P3OUT |= Rojo1;			//S1 Rojo ON
		P3OUT &= ~Ambar1;		//S1 Ambar OFF
		P3OUT &= ~Verde1; 		//S1 Verde OFF
		P3OUT &= ~Rojo2;		//S2 Rojo OFF
		P3OUT &= ~Ambar2; 		//S2 Ambar OFF
		P3OUT |= Verde2;		//S2 Verde ON
		P2OUT &= ~RojoPeatones;	//SP Rojo OFF
		P2OUT |= VerdePeatones;	//SP Verde ON
		__delay_cycles(1048576*4); 	//Retardo de 4 segundos

		//**Estado 2** --> Parpadeo S2 durante 5 veces.
		for(i=5;i>0;i--){
			P3OUT &= ~Verde2;	//S2 Verde OFF
			__delay_cycles(1048576/6);
			P3OUT |= Verde2; 	//S2 Verde ON
			__delay_cycles(1048576/6);
		}

		//**Estado 3** --> S2 Ambar durante un segundo
		P3OUT |= Ambar2;		//S2 Ambar ON
		P3OUT &= ~Verde2;		//S2 Verde OFF
		__delay_cycles(1048576); //retardo de 1 segundo

		//**Estado 4** --> S1 Verde / S2 Rojo / Peatones Rojo
		P3OUT &= ~Ambar2;		//S2 Ambar OFF
		P3OUT |= Rojo2;			//S2 Rojo ON
		P3OUT &= ~Rojo1;		//S1 Rojo OFF
		P3OUT |= Verde1;		//S1 Verde ON
		P2OUT |= RojoPeatones;	//SP Rojo ON
		P2OUT &= ~VerdePeatones;//SP Verde OFF
		__delay_cycles(1048576*6);		//retardo de 6 segundos

		//**Estado 5** -->S1 Parpadeo durante 5 veces.
		for(i=5;i>0;i--){
			P3OUT &= ~Verde1;	//S1 Verde OFF
			__delay_cycles(1048576/6);
			P3OUT |= Verde1; 	//S1 Verde ON
			__delay_cycles(1048576/6);
		}

		//**Estado 6** --> S1 Ambar durante un segundo
		P3OUT |= Ambar1;		//S1 Ambar ON
		P3OUT &= ~Verde1;		//S1 Verde OFF
		__delay_cycles(1048576); 	//retardo de 1 segundo
	}
}

#pragma vector=PORT2_VECTOR
	__interrupt void BOTON_SEMAFORO(void){
		/* Almacena en enteros los valores de los puertos usados para los leds
		del esatdo de antes de entrar en la interrupcion*/
		R2 = P2OUT;
		R3 = P3OUT;

		__delay_cycles(1048576*3);		//retardo de 3 segundos

		P2OUT &= ~VerdePeatones; //VerdePeatones OFF ->
		/*Si pulsan el boton estando encendido VerdePeatones, se apagara para que no se quede encendido.
		Aunque tiene poco sentido que lo pulsen estando ya activado el paso de cebra.*/

		//Pardapeo RojoPeatones durante tres veces.
		for(i=3;i>0;i--){
			P2OUT &= ~RojoPeatones;	//RojoPeatones OFF
			__delay_cycles(1048576/6);
			P2OUT |= RojoPeatones; 	//RojoPeatones ON
			__delay_cycles(1048576/6);
		}

		//Ambar 1 ON durante dos segundos
		P3OUT &= ~Rojo1;		//S1 Rojo OFF
		P2OUT &= ~VerdePeatones; //VerdePeatones OFF ->
		/*Si pulsan el boton estando encendido VerdePeatones, se apagara para que no se quede encendido.
		Aunque tiene poco sentido que lo pulsen estando ya activado el paso de cebra.*/
		P3OUT &= ~Verde1; 		//S1 Verde OFF
		P3OUT |= Ambar1;
		__delay_cycles(1048576*2);	//retardo de 2 segundos

		P2OUT &= ~RojoPeatones;	//RojoPeatones OFF
		P3OUT &= ~Rojo2;		//S2 Rojo OFF
		P3OUT &= ~Ambar2; 		//S2 Ambar OFF
		P3OUT &= ~Verde2;		//S2 Verde OFF

		//Apagamos Ambar 1 y encendemos Rojo1, Verde2 y VerdePeatones durante 20 segundos.
		P3OUT &= ~Ambar1;			//S1 Ambar OFF
		P3OUT |= Rojo1;				//S1 Rojo ON
		P3OUT |= Verde2;			//S2 Verde ON
		P2OUT |= VerdePeatones; 	//VerdePeatones ON
		__delay_cycles(1048576*5);	//retardo de 20 segundos
		P2OUT &= ~VerdePeatones; 	//VerdePeatones OFF

		/* Devuelve el estado de los leds a como estaban antes de entrar en la interrupcion */
		P3OUT=R3;
		P2OUT=R2;

		P2IFG &= ~BIT1; //Ponemos el flag a 0.
	}
