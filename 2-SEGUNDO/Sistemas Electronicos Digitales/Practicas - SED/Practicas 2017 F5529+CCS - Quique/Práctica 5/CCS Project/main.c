#include <msp430.h> 

/*
 * main.c
 */
#define PLANTA0 1
#define SUBE 2
#define ESPERA 3
#define BAJA 4
int boton1, boton2, boton3;
int sensor0, sensor1, sensor2, sensor3;
int planta0, planta1, planta2, planta3;
int NState;
void configports(){
    P2DIR &= ~BIT4;             // P2.4 como entrada
    P2REN |= BIT4;              // Resistencia pull up P2.4
    P2OUT |= BIT4;              // Resistencia pull up P2.4
    P2IES |= BIT4;              // Configuramos Interrupción
    P2IFG &= ~BIT4;
    P2IE  |= BIT4;

    P2DIR &= ~BIT3;             // P2.3 como entrada
    P2REN |= BIT3;              // Resistencia pull up P2.3
    P2OUT |= BIT3;              // Resistencia pull up P2.3
    P2IES |= BIT3;              // Configuramos Interrupción
    P2IFG &= ~BIT3;
    P2IE  |= BIT3;

    P2DIR &= ~BIT2;             // P2.2 como entrada
    P2REN |= BIT2;              // Resistencia pull up P2.2
    P2OUT |= BIT2;              // Resistencia pull up P2.2
    P2IES |= BIT2;              // Configuramos Interrupción
    P2IFG &= ~BIT2;
    P2IE  |= BIT2;

    P2DIR &= ~BIT0;             // P2.0 como entrada
    P2REN |= BIT0;              // Resistencia pull up P2.0
    P2OUT |= BIT0;              // Resistencia pull up P2.0
    P2IES |= BIT0;              // Configuramos Interrupción
    P2IFG &= ~BIT0;
    P2IE  |= BIT0;

    P1DIR &= ~BIT3;             // P1.3 como entrada
    P1REN |= BIT3;              // Resistencia pull up P1.3
    P1OUT |= BIT3;              // Resistencia pull up P1.3
    P1IES |= BIT3;              // Configuramos Interrupción
    P1IFG &= ~BIT3;
    P1IE  |= BIT3;

    P1DIR &= ~BIT2;             // P1.2 como entrada
    P1REN |= BIT2;              // Resistencia pull up P1.2
    P1OUT |= BIT2;              // Resistencia pull up P1.2
    P1IES |= BIT2;              // Configuramos Interrupción
    P1IFG &= ~BIT2;
    P1IE  |= BIT2;

    P1DIR &= ~BIT1;             // P1.1 como entrada
    P1REN |= BIT1;              // Resistencia pull up P1.1
    P1OUT |= BIT1;              // Resistencia pull up P1.1
    P1IES |= BIT1;              // Configuramos Interrupción
    P1IFG &= ~BIT1;
    P1IE  |= BIT1;

    P1DIR |= BIT0;              // P1.0 como salida
    P1OUT &= ~BIT0;             // Desactivamos el LED 1.0
    P4DIR |= BIT7;              // P4.7 como salida
    P4OUT &= ~BIT7;             // Desactivamos el LED 4.7
}
void AscPlanta0(void){
    P1OUT &= ~BIT0;             // Desactivamos el LED 1.0
}
void AscSubiendo(void){
    P4OUT |= BIT7;              // Activamos el LED 4.7
}
void AscBajando(void){
    P1OUT |= BIT0;              // Activamos el LED 1.0
}
void StartTA(void){
    TA0CTL = MC_1+TASSEL_1+ID_3+TACLR; // Up Mode, ACLK/8, Clear
    TA0CCR0 = 40000;                   // Configuramos para 10s
    TA0CCTL0 &= ~CCIFG;
    TA0CCTL0 |= CCIE;                  // Activamos la interrupción del timer
    __bis_SR_register(LPM0_bits);      // Low power mode
    TA0CTL = MC_0;                     // Paramos el timer
}
void AscEsperando(void){
    P1OUT &= ~BIT0;                    // Desactivamos el LED 1.0
    P4OUT &= ~BIT7;                    // Desactivamos el LED 4.7
    StartTA();
}
void CompBoton(void){
    if(boton1==1){                     // Boton 1 pulsado
        NState=SUBE;
        planta1=1;
        boton1=0;
    }else{
        __bis_SR_register(LPM0_bits);}
    if(boton2==1){                     // Boton 2 pulsado
        NState=SUBE;
        planta2=1;
        boton2=0;
    }else{
        __bis_SR_register(LPM0_bits);}
    if(boton3==1){                     // Boton 3 pulsado
        NState=SUBE;
        planta3=1;
        boton3=0;
    }else{
        __bis_SR_register(LPM0_bits);}
}

int main(void) {
    int CState;
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
    configports();
    NState=PLANTA0;             // Inicializamos las variables
    boton1=0; boton2=0; boton3=0;
    sensor0=0; sensor1=0; sensor2=0; sensor3=0;
    planta0=0; planta1=0; planta2=0; planta3=0;
    __bis_SR_register(GIE);     // GIE activado
    for(;;){                    // Bucle infinito
        CState=NState;          // Nuevo estado
        switch(CState){
            case PLANTA0:       // Estado planta 0
                AscPlanta0();   // Apagamos el LED 1.0
                CompBoton();    // Comprobamos los botones pulsados
                break;
            case SUBE:
                AscSubiendo();  // Encendemos el LED 1.0
                CompBoton();    // Comprobamos los botones pulsados
                // Comprobamos todas las prioridades de subida
                if(planta1==1){
                    if(planta3==1 || planta2==1){
                    }else{
                        if(sensor1==1){
                            NState=ESPERA;
                            planta1=0;}
                    }
                }
                if(planta2==1){
                    if(planta3==1){
                    }else{
                        if(sensor2==1){
                            NState=ESPERA;
                            planta2=0;}
                    }
                }
                if(planta3==1){
                    if(sensor3==1){
                        NState=ESPERA;
                        planta3=0;}
                }
                break;
            case ESPERA:
                AscEsperando(); // Apagamos los LEDs y activamos el timer
                NState=BAJA;
                break;
            case BAJA:
                AscBajando();   // Encendemos el LED 4.7
                CompBoton();    // Comprobamos los botones pulsados
                // Comprobamos todas las prioridades de bajada
                if(planta2==0 || planta1==0){
                    planta0=1;
                }
                if(planta2==1){
                    if(sensor2==1){
                        if(planta1==1){
                            NState=ESPERA;
                            planta2=0;
                        }else{
                            NState=ESPERA;
                            planta0=1;
                        }
                    }
                }
                if(planta1==1){
                    if(sensor1==1){
                        NState=ESPERA;
                        planta1=0;
                        planta0=1;
                    }
                }
                if(planta0==1){
                    if(sensor0==1){
                        NState=PLANTA0;
                        planta0=0;
                    }
                }
                break;
            default:
                // Planta 0 como estado por defecto
                NState=PLANTA0;
                break;
        }
    }
}

#pragma vector=PORT1_VECTOR
__interrupt void boton(void){
    if((P1IFG & BIT1) !=0){ // Actualiza boton1
        boton1=1;
        P1IFG &= ~BIT1;     // Limpia el flag
    }
    if((P1IFG & BIT2) !=0){ // Actualiza boton2
        boton2=1;
        P1IFG &= ~BIT2;     // Limpia el flag
    }
    if((P1IFG & BIT3) !=0){ // Actualiza boton3
        boton3=1;
        P1IFG &= ~BIT3;     // Limpia el flag
    }
    __bic_SR_register_on_exit(LPM0_bits);
}

// Interrupción del sensor
#pragma vector=PORT2_VECTOR
__interrupt void sensor(void){
    if((P2IFG & BIT4) !=0){ // Actualiza sensor3
        sensor3=1;
        P2IFG &= ~BIT4;     // Limpia el flag
    }
    if((P2IFG & BIT3) !=0){ // Actualiza sensor2
        sensor2=1;
        P2IFG &= ~BIT3;     // Limpia el flag
    }
    if((P2IFG & BIT2) !=0){ // Actualiza sensor1
        sensor1=1;
        P2IFG &= ~BIT2;     // Limpia el flag
    }
    if((P2IFG & BIT0) !=0){ // Actualiza sensor0
        sensor0=1;
        P2IFG &= ~BIT0;     // Limpia el flag
    }
    // CPU en modo activo
    __bic_SR_register_on_exit(LPM0_bits);
}

// Interrupción del Timer
#pragma vector=TIMER0_A0_VECTOR
__interrupt void timer(void){
    // CPU en modo activo
    __bic_SR_register_on_exit(LPM0_bits);
}
