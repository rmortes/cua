
#include <msp430.h>

int main(void)

{
WDTCTL = WDTPW | WDTHOLD; // stop watchdog timer
P3DIR |= BIT1;
P3OUT &=~BIT1;
P1DIR &=~BIT1; //Generamos la entrada del pulsador
P1REN |= BIT1; //Activamos la resistencia
P1OUT |= BIT1; // La configuramos en Pull Up
P1IES |= BIT1; //Configura la interrucion de P1.1 con de bajada 1/0
P1IFG &=~BIT1; //Borra el flag para no autodispararse
P1IE |= BIT1; // habilita la interrupción de la patilla P1.1
__bis_SR_register(LPM4_bits + GIE); //Modo LMP4 (Bajo consumo) y habilita Interrupciones globales
}

#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void){
if((P1IN & BIT1) == 0){ // Si se activa el pulsador lo ejecuta
P3OUT |= BIT1; //Genera un 1 en la señal
__delay_cycles(350); // La mantiene el tiempo deseado
P3OUT &=~BIT1; // Genera el 0 para la señal
__delay_cycles(150);// La mantiene el tiempo deseado
}else{
P1IFG &=~BIT1; // Borra el flag , para poder atender una nueva interrupción

}

}