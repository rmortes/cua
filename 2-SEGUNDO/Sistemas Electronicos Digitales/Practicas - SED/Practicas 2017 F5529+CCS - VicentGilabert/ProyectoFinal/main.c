/*PROYECTO FINAL SED*/
#include <msp430.h>
#include <stdio.h>
#include <stdlib.h>

#define LED1 BIT2
#define LED2 BIT4
#define LED3 BIT5
#define SENSOR BIT1
#define CALADC12_15V_30C *((unsigned int *)0x1A1A) //Calibracion sensor -30ºC
#define CALADC12_15V_85C *((unsigned int *)0x1A1C) //Calibracion sensor -85ºC

unsigned int result,unidades,decimales,reset=0,vent=0;
volatile float gradosC,TempV;
//int results[5],suma;
char inicio[]="\n**El sistema esta Activado**\n1-> Temperatura interna CPU\n2-> Temperatura externa\n3-> Encender sirena\n4-> Activar/Desactivar ventilador\n5-> Reiniciar sistema\nIntroduce una opcion: \n";
char recibido=' ';
char gradosC_char[];
char ALARMA[]="\nAlarma activada\n";
char MAL[]="\nOpcion incorrecta\n";

void sirena(int time){
	int i;
	for (i=0;i<time;i++){   // Se repite 10 veces este bucle -> 10 segundos

		TA0CCR0 = 699;  //f1 = fSMCLK/TA0CCR0 = 1048576/700 = 1,5KHZ aprox
		TA0CCR1 = 399;  //DC = TA0CCR1/TA0CCR0 = 50% -> 400/800 = 50%
		P2OUT |= LED1; 	//LED ON
		__delay_cycles(500000);	//duración de f1 -> 0,5s

		TA0CCR0 = 999;  //f2 = fSMCLK/TA0CCR0 = 1048576/1000 = 1KHZ aprox
		TA0CCR1 = 499;	//DC = TA0CCR1/TA0CCR0 = 50% -> 500/1000 = 50%
		P2OUT &=~LED1; 	//LED OFF
		__delay_cycles(500000);  //duración de f2 -> 0,5s
	}
	TA0CCR0 = 0;        // Lo ponemos a 0 para parar la sirena.
	TA0CCR1 = 0;        // Lo ponemos a 0 para parar la sirena.
}

void LED_RGB_ON(float gradosC){
    if(gradosC<=15){
            P3OUT |= BIT7; //ENCENDEMOS LED AZUL
    }
    if(gradosC>=30){
            P3OUT |= BIT0;	//ENCENDEMOS LED ROJO
			P2OUT |= BIT5;	//ENCENDEMOS EL VENTILADOR
			vent=1;
			//Mensaje al movil advirtiendod de la temperatura elevada.
			transmitir("\nTemperatura elevada\n");
            sirena(5);	//Hacemos sonar la sirena durante 5 segundos
    }
    if(gradosC>15 && gradosC<30){
            P3OUT |= BIT1;	//ENCENDEMOS LED VERDE
    }
}

void LED_RGB_OFF(){
    P3OUT &=~BIT7; //APAGAMOS LED AZUL
    P3OUT &=~BIT0;	//APAGAMOS LED ROJO
    P3OUT &=~BIT1;	//APAGAMOS LED VERDE
}

void transmitir(const char *str) {
	while (*str != 0) {		// Hace esto mientras que el elemento actual recibido no sea igual al caracter nulo
		while (!(UCTXIFG & UCA0IFG));	// Asegura que el flag de transmisión está a 1
			UCA0TXBUF = *str++;			// Carga UCA0TXBUF con el elemento actual y luego apunta al siguiente
	}
}

void temp_int(){
	//CONFIGURACION ADC12 PARA LA TEMPERATURA INTERNA CPU
	REFCTL0 &= ~REFMSTR; // Reset REFMSTR para control por parte del ADC12
	ADC12CTL0 &=~ADC12SC;						//Paramos la conversion por si estuviera encendida.
	ADC12CTL0 = ADC12REFON+ADC12SHT0_8+ADC12ON; //La referencia a 1.5V, establecemos el muestreo y activamos el ADC,
	ADC12CTL1 = ADC12SHP;						//Timer de muestreo
	ADC12MCTL0 = ADC12INCH_10 + ADC12SREF_1;	// A10 = Sensor temperatura, ref+=vref
	ADC12IE = BIT0;								// Habilitamos ADC12IFG.0
	__delay_cycles(1000);						// retardo para el establecimiento de la referencia

}

void temp_ext(){
	//CONFIGURACION ADC12 PARA LA TEMPERATURA EXTERNA (LM35)
	REFCTL0 &=~REFMSTR; 		// Reset REFMSTR para control por parte del ADC12
	ADC12CTL0 &=~ADC12SC;						//Paramos la conversion por si estuviera encendida.
	ADC12CTL0 = ADC12REFON+ADC12SHT0_8+ADC12ON; // Activamos el ADC, la referencia a 1.5V, esstablecemos el muestreo
	ADC12CTL1 = ADC12SHP;						//Timer de muestreo
	P6SEL |= BIT0;					//Entrada del puerto para convertir P6.0-> A0
	ADC12MCTL0 = ADC12INCH_0 + ADC12SREF_1;		// canal -> A0 = P6.0
	ADC12IE = BIT0;								// Habilitamos interupciones en ADC12MEM0
	__delay_cycles(1000);						// retardo para el establecimiento de la referencia

}

void Conf_UART(){
	//CONFIGURACION PINES PARA HC05
	P3SEL |= BIT3; 		// P3.3 -> TX
	P3DIR |= BIT3;		// P3.3 -> Definido como salida
	P3SEL |= BIT4; 		// P3.4 -> RX
	P3DIR &=~BIT4;		// P3.4 -> Definido como entrada

	UCA0CTL1 |= UCSWRST; // **Put state machine in reset**
    UCA0CTL1 |= UCSSEL_2; // SMCLK
    UCA0BR0 = 6; // 1MHz 9600 (see User's Guide)
    UCA0BR1 = 0; // 1MHz 9600
    UCA0MCTL = UCBRS_0 + UCBRF_13 + UCOS16;
    UCA0CTL1 &= ~UCSWRST; // **Initialize USCI state machine**
	UCA0IE = BIT0;
}

void Conf_IO(void){
	// CONFIGURACIÓN DEL P1.2 COMO SALIDA DE TA0.1
	P1SEL |= BIT2;	//Seleccionamos la opcion del timer
	P1DIR |= BIT2; 	//P1.2 -> Definimos como salida

	//CONFIGURACION LED1 PARA LA SIRENA
	P2DIR |= LED1; 		//Definimos como salida en P2.2 para el LED
	P2OUT &=~LED1; 	//Empezamos con el LED Apagado.

	//CONFIGURACION LED2 PARA LA CERRADURA ELECTRONICA
	P2DIR |= LED2; 		//Definimos como salida en P2.4 para el LED
	P2OUT &=~LED2; 		//Empezamos con el LED Apagado.

	//CONFIGURACION LED3 PARA EL VENTILADOR
	P2DIR |= LED3;		//Definimos como salida en P2.5 para el LED
	P2OUT &=~LED3;		//Empezamos con el LED Apagado.

	//LED RESET
	P1DIR |= BIT0;
	P1OUT &=~BIT0;

	//CONFIGURACION DEL BOTON P1.1 PARA SIMULAR EL SENSOR PIR
	P1DIR &=~SENSOR; 	//P1.1 -> Definimos como entrada
    P1REN |= SENSOR;	//P1.1 -> Activamos la resistencia interna
	P1OUT |= SENSOR;	//Resistencia Pull-Up
	P1IE  |= SENSOR;	//Interrupciones habilitadas en Pulsador
	P1IES |= SENSOR;	//Interrupcion de 0 a 1.
	P1IFG &=~SENSOR;	//Flag de interrupcion del Pulsador a 0.

	//CONFIGURACION LED RGB
	//COLOR ROJO
    P3DIR |= BIT0;	//Definimos como salida en P3.0 para el LED
    P3OUT &=~BIT0;	//Empezamos con P3.0 OFF
	// COLOR VERDE
    P3DIR |= BIT1;	//Definimos como salida en P3.1 para el LED
    P3OUT &=~BIT1;	//Empezamos con P3.1 OFF
	//COLOR AZUL
    P3DIR |= BIT7;	//Definimos como salida en P3.7 para el LED
    P3OUT &=~BIT7;	//Empezamos con P3.7 OFF

}

void Conf_TA0(){
	// CONFIGURACIÓN DEL TIMER
	TA0CCTL1 = OUTMOD_7;		//Ponemos el modo Reset/Set
	TA0CTL = TASSEL_2 + MC_1;   //TASSEL_2 -> SMCLK fuente del reloj // MC_1 -> Modo ascendente
}

int main(void) {
	WDTCTL = WDTPW + WDTHOLD; 	// Stop watchdog timer
	Conf_IO();					//Funcion de la configuracion de los puertos
	Conf_TA0();					//Funcion de la configuracion del timer
	Conf_UART();				//Funcion de la configuracion de la UART
	__enable_interrupt();		// Activamos las interrupciones
	transmitir(inicio);			//Enviamos mensaje de inicio.

	/*Cuando se reinicie el sistema entrara en este if, para enviar el mensaje por pantalla.*/
	if(reset==1){
		transmitir("\n.\n.\nEl sistema se ha reiniciado correctamente.\n.\n.\n");
		__delay_cycles(100000);
		reset=0;
	}
	/*Para comprobar que se reinincia el sistema, lo podemos hacer con este LED
	y un tiempo de retardo antes para ver como se apaga y se enciende*/
	__delay_cycles(1000000);
	P1OUT |= BIT0;		//LED RESET Encendido

	for(;;){
		if(recibido != ' '){
			switch(recibido) {
				//Temperatura interna
				case '1':
					temp_int();		//Configuracion del ADC12 para la temperatura interna
					ADC12CTL0 |= ADC12ENC+ADC12SC;		//ADC12 encendido y empieza la conversion
					__delay_cycles(10000);				//Retardo para que le de tiempo a saltar la interrupcion
					gradosC=(float)(((long)result-CALADC12_15V_30C)*(85-30))/(CALADC12_15V_85C-CALADC12_15V_30C)+30.0f;
					__no_operation();
					unidades=(int)gradosC;	//Obtenemos solo el valor de real (no decimal) de gradosC (float)
					decimales=(int)((gradosC-unidades)*100);	//Obtenemos solo el valor decimal de gradosC (float)
					//Definimos los grados si queremos probar si tranmite correctamente
					//gradosC =23.76;
					//Convertimos la medida de int a char para poder enviarla.
					sprintf(gradosC_char, "\nTemperatura Interna: %d'%d grados.\n", unidades,decimales);
					transmitir(gradosC_char); 	//Llamamos a la funcion transmitir para enviar la temperatura.
					LED_RGB_ON(gradosC);		//Encendemos el LED RGB dependiendo de la temperatura que marque el sensor.
					__delay_cycles(5000000);	//Retardo de 5 segundos, donde estara el LED encendido y el mensaje en la pantalla.
				break;
				
				//Temperatura externa (LM35)
				case '2':
					temp_ext();		//Configuracion del ADC12 para la temperatura externa (LM35)
					ADC12CTL0 |= ADC12ENC+ADC12SC;		//ADC12 encendido y empieza la conversion
					__delay_cycles(10000);				//Retardo para que le de tiempo a saltar la interrupcion
					//Definimos los grados si queremos probar si tranmite correctamente
					//gradosC =30.96;
					//Conversion a voltios y a grados.
					TempV=(result*1.5)/4096.0;
					gradosC=TempV*100.0;
					unidades=(int)gradosC;		//Obtenemos solo el valor de real (no decimal) de gradosC (float)
					decimales=(int)((gradosC-unidades)*100);	//Obtenemos solo el valor decimal de gradosC (float)
					//Convertimos la medida a char para poder enviarla.
					sprintf(gradosC_char, "\nTemperatura Externa: %d'%d grados.\n", unidades,decimales);
					transmitir(gradosC_char); 	//Llamamos a la funcion transmitir para enviar la temperatura.
					LED_RGB_ON(gradosC);		//Encendemos el LED RGB dependiendo de la temperatura que marque el sensor.
					__delay_cycles(5000000);	//Retardo de 5 segundos, donde estara el LED encendido y el mensaje en la pantalla.
				break;
				
				//Encender la alarma
				case '3':
					transmitir(ALARMA);		//Transmitimos mensaje de alarma activada.
					sirena(10);				//La alarma sonara durante 10 segundos.
				break;
				
				//Encender o Apagar ventilador
				case '4':
					if(vent==1){		//Variable vent estara activa si el ventilador esta activo, donde controlaremos el poder apagarlo.
						transmitir("\nVentilador apagado.\n");		//Transmitimos mensaje de ventilador apagado.
						P2OUT &=~BIT5;	//APAGAMOS EL VENTILADOR
						vent=0;			//Ponemos la varaible a 0, que indica que el ventilador esta apagado.
						__delay_cycles(2000000);	//Retardo de 2 segundos para ver mensaje en la pantalla.
					}else {
						P2OUT |= BIT5;	//ENCENDEMOS EL VENTILADOR
						transmitir("\nVentilador encendido.\n");	//Transmitimos mensaje.
						vent=1;		//Ponemos la varaible a 1, que indica que el ventilador esta encendido.
						__delay_cycles(2000000);	//Retardo de 2 segundos para ver mensaje en la pantalla.
					}
				break;

				//Reiniciar sistema
				case '5':
					transmitir("\nReiniciando sistema...\n");	//Transmitimos mensaje de reiniciar sistema.
					reset=1;
					__delay_cycles(2000000);		//Retardo 2 seg para poder ver el mensaje.
					//Cuando llamamos al WDT, si no se introduce su contraseña 5A en hexadecimal,
					//se produce un reinicio del sistema. Asi conseguimos reiniciar el sistema:
					WDTCTL = 0;
				break;
				
				//Opcion incorrecta
				default :
					transmitir(MAL);	//Mensaje diciendo que has introducido una opcion no valida.
					__delay_cycles(2000000);	//Retardo para ver el mensaje
				break;
			}
			LED_RGB_OFF();		//Paramos el LED que este encendido
			recibido=' ';		//Volvemos a poner como valor de recibido el incial
			ADC12CTL0 &=~ADC12SC;	//Paramos la conversion de ADC12
			transmitir(inicio);		//Transmitimos el mensaje de inicio
		}
		__bis_SR_register(GIE);		//habilita interrupciones generales
		__no_operation();
	}
}

/* Interrupcion del sensor de movimiento (boton) */
#pragma vector=PORT1_VECTOR
__interrupt void SENSOR_PIR(void){
	P2OUT |= LED2; 	//LED ON CERRADURA
	transmitir("Presencia en la zona");
	sirena(10);		//Sirena activada durante 10 segundos
	P2OUT &=~LED2; 	//LED OFF CERRADURA
	P1IFG &=~SENSOR;	//FLAG INTERRUPCIONES DEL SENSOR A OFF
}

/* Interrupcion del ADC12 */
#pragma vector=ADC12_VECTOR
__interrupt void ADC12ISR (void){
	switch(__even_in_range(ADC12IV,34)){
		case  6:                                  	// Vector  6:  ADC12IFG0
			result = ADC12MEM0;                     // Guardamos el resultado en la variable global result
			__bic_SR_register_on_exit(LPM4_bits);   // Exit active CPU
		break;
		default: break;
	}
}

/* Interrupcion de recepcion del HC05 */
#pragma vector=USCI_A0_VECTOR
__interrupt void USCI0RX_ISR(void){
	recibido = UCA0RXBUF;	// Recibido desde el HC05
}

/*
//Para las medidas de los sensores, tambien se pueden tomar 5 medidas y hacer una media:
	//int i;
	for(i=0;i<5;i++){
		ADC12CTL0 |= ADC12ENC+ADC12SC;
		__delay_cycles(100000);
		results[i]=ADC12MEM0;
		suma=suma+results[i];
		ADC12CTL0 &=~ADC12SC;
	}
	result=suma/5;
*/
