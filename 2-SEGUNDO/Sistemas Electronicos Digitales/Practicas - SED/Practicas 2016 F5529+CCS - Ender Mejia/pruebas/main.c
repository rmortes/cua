#include <msp430.h>

void ConfigPort(void);

unsigned char count=0;
//Bt1--> cada 0,5s = 2Hz count++;
//Bt2--> para
unsigned int start=0;

unsigned int n=0;
void DelayMilisec(int n);

int main(void) { // d)
	WDTCTL = WDTPW | WDTHOLD;  // Stop watchdog timer

	ConfigPort();

	DelayMilisec(n);

	while(start==1){
		//cada 0,5segundos = 500ms
		DelayMilisec(500);
		count++;

	}

	__bis_SR_register(LPM1 + GIE);//modo LPM4 y habilita interrupciones generales
	__no_operation(); //para depurar

}
void ConfigPort(void){ // a)
	//configuracion Bt1(P2.1) y Bt2(P1.1)
	P2DIR &= ~BIT0;	//Bt1 P2.o como entrada
	P2REN |= BIT0;                 	//Habilita la resistencia en P2.1
	P2OUT &= ~BIT0;                 	//Resistencia --> pull-down
	P2IE |= BIT0;                 	//P2.1 habilitar interrupciones
	P2IES |= BIT0;                 	//por flanco de subida
	P2IFG &= ~BIT0;                	// borramos interr pendientes

	P2DIR &= ~BIT1;	//Bt2 P2.1 como entrada
	P2REN |= BIT1;                 	//Habilita la resistencia en P1.1
	P2OUT &= ~BIT1;                 	//Resistencia --> pull-down
	P2IE |= BIT1;                 	//P1.1 habilitar interrupciones
	P2IES |= BIT1;                 	//por flanco de subida
	P2IFG &= ~BIT1;                	// borramos interr pendientes

}

void DelayMilisec(int n){ // b)
	//Configuramos timer  ----------------------------------------
	//funcion para retardar n milisegundos

	TA0CTL = TASSEL_2 + MC_1 + ID_2 + TACLR;
	//TASSEL_2 = SMCLK (0=TACLK  1=ACLK  3=INCLK)
	//MC_1 = upmode hasta TACCR0 (0=parada, 2=hasta FFFF)
	//ID_2 = divide la frec de Reloj/4 (0=f/1  1=f/2  2=f/4  3=f/8)
	//TACLR = borra TAR

	//CCR0 = TiempoNecesario/TiempoCLK
	// SMCLK/4 = 1MHz/4 = 1/250000 segundos
	// queremos que retarde n*(10^-3) segundos
	// TACCR0= (n*10^-3)/(1/250000)= n*250000*10^-3 = n*250
	TA0CCR0 = n*250;
	while((TA0CCTL0 & CCIFG)==0){

	}
	TA0CCTL0 &= ~CCIFG;

	//------------------------------------------------------------
}

#pragma vector=PORT2_VECTOR // c)
__interrupt void Buttons_ISR(){
	if(P2IFG & BIT0){ //si esta pulsado el P2.0

		start=1; //iniciamos la cuenta continua de count
		P2IFG &= ~BIT0; //borra el flag

	}
	if(P2IFG & BIT1){ //si esta pulsado el P2.1

		start=0; //paramos la cuenta
		P2IFG &= ~BIT1;	//borra el flag
	}
}
