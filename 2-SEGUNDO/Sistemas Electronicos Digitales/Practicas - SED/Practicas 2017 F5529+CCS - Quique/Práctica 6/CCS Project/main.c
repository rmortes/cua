 #include <msp430.h>
#include <MSP_Serial.h>

#define ACTIVADO 1
#define BUZZER 2
#define DESACTIVADO 3
int boton, umbral;
int NState, CState;
volatile unsigned int results[3];

void configports(){
    P1DIR &= ~BIT1;             // P1.1 como entrada
    P1REN |= BIT1;              // Resistencia pull up P1.1
    P1OUT |= BIT1;              // Resistencia pull up P1.1
    P1IES |= BIT1;              // Configuramos Interrupción
    P1IFG &= ~BIT1;
    P1IE  |= BIT1;

    P6SEL = BIT0+BIT1+BIT2;     // Enable A/D channel inputs

    P1DIR |= BIT0;              // P1.0 como salida
    P1OUT &= ~BIT0;             // Desactivamos el LED 1.0
    P4DIR |= BIT7;              // P4.7 como salida
    P4OUT &= ~BIT7;             // Desactivamos el LED 4.7

    P2DIR |= BIT5;              // Activamos el timer TA2.2
    P2SEL |= BIT5;
}

void configADC12(){
    ADC12CTL0 = ADC12ON + ADC12MSC+ADC12SHT0_2; // Turn on ADC12, set sampling time
    ADC12CTL1 = ADC12SHP + ADC12CONSEQ_1;       // Use sampling timer, single sequence
    ADC12MCTL0 = ADC12INCH_0;                   // ref+=AVcc, channel = A0
    ADC12MCTL1 = ADC12INCH_1;                   // ref+=AVcc, channel = A1
    ADC12MCTL2 = ADC12INCH_2 + ADC12EOS;        // ref+=AVcc, channel = A2
    ADC12IE = BIT2;                             // Enable ADC12IFG.2
    ADC12CTL0 |= ADC12ENC;                      // Enable conversions
}
void Compboton(){
    if(boton==1){               // Boton pulsado
        NState=ACTIVADO;
        boton=0;
    }else{
    __bis_SR_register(LPM0_bits);}
}
void StartTA1(void){
    TA1CTL = MC_1+TASSEL_1+ID_3+TACLR;          // Up Mode, ACLK/8, Clear
    TA1CCR0 = 4000;                             // Configuramos para 0.5s
    TA1CCTL0 &= ~CCIFG;
    TA1CCTL0 |= CCIE;                           // Activamos la interrupción del timer
    __bis_SR_register(LPM0_bits);               // Low power mode
    TA1CTL = MC_0;                              // Paramos el timer
}
void LEDVerde(){
    volatile int i;
    for (i=0;i<3;i++){
        P4OUT |= BIT7;
        StartTA1();
        P4OUT &= ~BIT7;
        StartTA1();
    }
    P4OUT |= BIT7;
}
void StartTA0(void){
    TA0CTL = MC_1+TASSEL_1+ID_3+TACLR;          // Up Mode, ACLK/8, Clear
    TA0CCR0 = 320;                              // Configuramos para 10 ms
    TA0CCTL0 &= ~CCIFG;
    TA0CCTL0 |= CCIE;                           // Activamos la interrupción del timer
    __bis_SR_register(LPM0_bits);               // Low power mode
    TA0CTL = MC_0;                              // Paramos el timer
}
void CompUmbral(void){
    if(umbral==1){                              // Comprobamos umbral
        NState=BUZZER;
        umbral=0;
        P4OUT &= ~BIT7;
    }
}
void LeerADC(){
    ADC12CTL0 &=  ~ADC12SC;
    ADC12CTL0 |= ADC12SC;                   // Start convn - software trigger
    __bis_SR_register(LPM4_bits + GIE);     // Enter LPM4, Enable interrupts
}
void Alarma(void){
    TA2CTL = TASSEL_2+MC_1+TACLR;           // SMCLK, upmode
    TA2CCTL2 = OUTMOD_2;                    // PWM output mode: 2

    while (boton==0){
        P1OUT |= BIT0;                      // LED rojo On
        TA2CCR0 = 3333;                     // Registro TA2CCR0
        TA2CCR2 = 1666;                     // Registro TA2CCR1
        StartTA1();                         // Esperamos 0.5 s
        P1OUT &= ~BIT0;                     // LED rojo Off
        TA2CCR0 = 1538;                     // Registro TA2CCR0
        TA2CCR2 = 769;                      // Registro TA2CCR1
        StartTA1();                          // Esperamos 0.5 s
    }
    TA2CTL = MC_0;                          // Paramos el timer
    NState=DESACTIVADO;
    boton=0;
}

int main(void) {
    int CState;
    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer
    configports();
    configADC12();
    NState=DESACTIVADO;         // Inicializamos las variables
    boton=0; umbral=0;
    __bis_SR_register(GIE);     // GIE activado
    for(;;){                    // Bucle infinito
        CState=NState;          // Nuevo estado
        switch(CState){
            case DESACTIVADO:   // Estado DESACTIVADO
                Compboton();
                LEDVerde();
                break;
            case ACTIVADO:      // Estado ACTIVADO
                StartTA0();     // 10 ms
                LeerADC();
                CompUmbral();
                break;
            case BUZZER:        // Estado BUZER
                Alarma();
                break;
            default:
                // DESACTIVADO como estado por defecto
                NState=DESACTIVADO;
                break;
        }
    }
}
// Interrupcion del boton
#pragma vector=PORT1_VECTOR
__interrupt void Boton(void){
    if((P1IFG & BIT1) !=0){ // Actualiza boton
        boton=1;
        P1IFG &= ~BIT1;     // Limpia el flag
    }
    __bic_SR_register_on_exit(LPM0_bits);
}
// Interrupción del Timer 1
#pragma vector=TIMER1_A0_VECTOR
__interrupt void timer1(void){
    // CPU en modo activo
    __bic_SR_register_on_exit(LPM0_bits);
}
// Interrupción del Timer 0
#pragma vector=TIMER0_A0_VECTOR
__interrupt void timer0(void){
    // CPU en modo activo
    __bic_SR_register_on_exit(LPM0_bits);
}
// Interrupcion ADC12
#pragma vector=ADC12_VECTOR
__interrupt void ADC12ISR (void){
    switch(__even_in_range(ADC12IV,34)){
      case  0: break;                           // Vector  0:  No interrupt
      case  2: break;                           // Vector  2:  ADC overflow
      case  4: break;                           // Vector  4:  ADC timing overflow
      case  6: break;                           // Vector  6:  ADC12IFG0
      case  8: break;                           // Vector  8:  ADC12IFG1
      case 10:                                  // Vector 10:  ADC12IFG2
          results[0] = ADC12MEM0;               // Move results, IFG is cleared
          results[1] = ADC12MEM1;               // Move results, IFG is cleared
          results[2] = ADC12MEM2;               // Move results, IFG is cleared
          if(results[0]>=2111 || results[0]<=1977){  // Comprobamos eje X
              umbral=1;
          }
          if(ADC12MEM1>=2170 || ADC12MEM1<=1880){    // Comprobamos eje Y
              umbral=1;
          }
          if(ADC12MEM2>=3000 || ADC12MEM2<=1200){    // Comprobamos eje Z
              umbral=1;
          }
          __bic_SR_register_on_exit(LPM4_bits);      // Exit active CPU
          break;
      case 12: break;                           // Vector 12:  ADC12IFG3
      case 14: break;                           // Vector 14:  ADC12IFG4
      case 16: break;                           // Vector 16:  ADC12IFG5
      case 18: break;                           // Vector 18:  ADC12IFG6
      case 20: break;                           // Vector 20:  ADC12IFG7
      case 22: break;                           // Vector 22:  ADC12IFG8
      case 24: break;                           // Vector 24:  ADC12IFG9
      case 26: break;                           // Vector 26:  ADC12IFG10
      case 28: break;                           // Vector 28:  ADC12IFG11
      case 30: break;                           // Vector 30:  ADC12IFG12
      case 32: break;                           // Vector 32:  ADC12IFG13
      case 34: break;                           // Vector 34:  ADC12IFG14
      default: break;
    }
}
