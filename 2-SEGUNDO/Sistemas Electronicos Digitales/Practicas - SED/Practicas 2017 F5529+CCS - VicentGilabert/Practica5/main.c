#include <msp430.h>

#define SP3 BIT4
#define SP2 BIT3
#define SP1 BIT2
#define SP0 BIT0
#define MSUBE BIT7
#define MBAJA BIT0
#define BLLP3 BIT3
#define BLLP2 BIT2
#define BLLP1 BIT1

void DeclaracionPuertos(void){
	//**MOTOR SUBIDA**
    P4DIR &=~MSUBE; //P4.7 -> Definimos como entrada
    P4REN |= MSUBE;	//P4.7 -> Activamos la resistencia interna
   	P4OUT &=~MSUBE; 	//Asignamos es estado inicial del motor a 0.

    //**MOTOR BAJADA**
    P1DIR &=~MBAJA; //P1.0 -> Definimos como entrada
    P1REN |= MBAJA;	//P1.0 -> Activamos la resistencia interna
    P1OUT &=~MBAJA; //Asignamos es estado inicial del motor a 0.

    //**SENSOR 3**
    P2DIR &=~SP3; 	//P2.4 -> Definimos como entrada
    P2REN |= SP3;	//P2.4 -> Activamos la resistencia interna
    P2OUT &=~SP3;	//Resistencia Pull-Up

    //**SENSOR 2**
    P2DIR &=~SP2; 	//P2.3 -> Definimos como entrada
    P2REN |= SP2;	//P2.3 -> Activamos la resistencia interna
    P2OUT &=~SP2;	//Resistencia Pull-Up

    //**SENSOR 1**
    P2DIR &=~SP1; 	//P2.2 -> Definimos como entrada
    P2REN |= SP1;	//P2.2 -> Activamos la resistencia interna
    P2OUT &=~SP1;	//Resistencia Pull-Up

    //**SENSOR 0**
    P2DIR &=~SP0; 	//P2.0 -> Definimos como entrada
    P2REN |= SP0;	//P2.0 -> Activamos la resistencia interna
    P2OUT &=~SP0;	//Resistencia Pull-Up

    //**BOTON PLANTA 3**
    P1DIR &=~BLLP3; //P1.3 -> Definimos como entrada
    P1REN |= BLLP3;	//P1.3 -> Activamos la resistencia interna
    P1OUT |= BLLP3;	//Resistencia Pull-Down

    //**BOTON PLANTA 2**
    P1DIR &=~BLLP2; //P1.2 -> Definimos como entrada
    P1REN |= BLLP2;	//P1.2 -> Activamos la resistencia interna
    P1OUT |= BLLP2;	//Resistencia Pull-Down

    //**BOTON PLANTA 1**
    P1DIR &=~BLLP1; //P1.1 -> Definimos como entrada
    P1REN |= BLLP1;	//P1.1 -> Activamos la resistencia interna
    P1OUT |= BLLP1;	//Resistencia Pull-Down
}
void BajarMotor(void){
	//Funcion que activa el motor de bajada
	P1OUT |= MBAJA; //P1.0 -> "1" -> Habilitamos el motor de bajada
}
void SubirMotor(void){
	//Funcion que activa el motor de subida
	P4OUT |= MSUBE;	//P4.7-> "1" -> Habilitamos el motor de subida
}
void PararMotores(void){
	//Funcion para parar los dos motores
	P4OUT &=~MSUBE; //Paramos el motor 4.7
	P1OUT &=~MBAJA; //Paramos el motor 1.0
}
void retardo_seg(void){
	__delay_cycles(10000000); 	// 1000000=1segundo -> para 10 segundos -> 10000000
}

void ejecucion(int i){
	SubirMotor();
	for(;i==1;){
		//PLANTA 3
		if(((P2IN & BIT4) && (P1IFG & BIT3))==1){
			PararMotores(); //Paramos el motor
			retardo_seg();	//Ejecutamos la funcion retardo que sera de 10 segundos
			P1IFG &= ~BIT3; // Ponemos el flag de la interrupcion a 0.
			if(((P1IFG & BIT2)||(P1IFG & BIT1))==1){
				BajarMotor();	//P4.7-> "1" -> Habilitamos el motor de subida
			}
			else{
				BajarMotor();	//P1.0-> "1" -> Habilitamos el motor de bajada
			}
		}
		//PLANTA 2
		if(((P2IN & BIT3) && (P1IFG & BIT2))==1){
			PararMotores();	//Paramos el motor
			retardo_seg();	//Ejecutamos la funcion retardo que sera de 10 segundos
			P1IFG &= ~BIT2; // Ponemos el flag de la interrupcion a 0.
			if((P1IFG & BIT3)==1){
				SubirMotor();	//P4.7-> "1" -> Habilitamos el motor de subida
			}
			if((P1IFG & BIT1)==1){
				BajarMotor();	//P1.0-> "1" -> Habilitamos el motor de bajada
			}
			else{
				BajarMotor();
			}
		}
		//PLANTA 1
		if(((P2IN & BIT2) && (P1IFG & BIT1))==1){
			PararMotores(); //Paramos el motor
			retardo_seg();	//Ejecutamos la funcion retardo que sera de 10 segundos
			P1IFG &= ~BIT1; // Ponemos el flag de la interrupcion a 0.
			if(((P1IFG & BIT3) || (P1IFG & BIT2))==1){
				SubirMotor();	//P4.7-> "1" -> Habilitamos el motor de subida
			}
			else{
				BajarMotor();	//P1.0-> "1" -> Habilitamos el motor de bajada
			}
		}
		//PLANTA 0
		if((P2IN & BIT0)==1){
			PararMotores();	//Paramos el motor
			retardo_seg();	//Ejecutamos la funcion retardo que sera de 10 segundos
			i=0;			//Cambiamos el valor de la i, para salir del bucle y volver a la funcion principal.
		}
	}
}

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	DeclaracionPuertos();		//Funcion donde declaramos todos los puertos que vamos a utilizar.

	//INTERRUPCIONES BOTONES
    P1IE |= BLLP3+BLLP2+BLLP1; 	//Interrupciones Activadas
    P1IES |= BLLP3+BLLP2+BLLP1; //Transicion de interrupciones high to low. 1->0

	__bis_SR_register(LPM0_bits + GIE);		//Modo bajo consumo + escucha de interrupciones
}

#pragma vector=PORT1_VECTOR
	__interrupt void BOTONES(void){
		ejecucion(1); //Ejecutamos la funcion donde tenemos las acciones
	}
