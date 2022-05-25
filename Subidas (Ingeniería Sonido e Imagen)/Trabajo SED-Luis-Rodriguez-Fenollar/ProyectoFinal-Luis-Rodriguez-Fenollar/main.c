#include <msp430.h>
#include <stdio.h>

#define ACTIVADO 3;
#define DESACTIVADO 2;
#define ALARMA 4;
#define NumMedidas 1;

volatile unsigned int ResultadodeA0[1];
float medida[1]; // para cambiar el número de medidas
char medida_cadena[16];
const char mensaje[] ="Sistema activado";
const char mensaje1[] ="Codigo de Activacion";
const char mensaje2[] ="Opcion no valida";
const char mensaje3[] ="Sistema desactivado ";
const char mensaje4[] ="¡¡¡¡ ALARMA !!!!";
const char CR[] = "\r\n";
const char temp_cpu[] ={" Temp_CPU: "};
char cadena[6];
char codigo[6]="1234";
int j=0;


char codigotecla[4];
char entrada[10];
float gradosC, Voltios;
int estado;
int PVez=0;
int fila,columna;
int vez;
int mascara_fila[4] = {0x38, 0x34, 0x2C, 0x1C}; //máscara que se utiliza para la fila
int codigos[12]= {1,2,3,4,5,6,7,8,9,10,0,15};
int tmp, tecla;
int mascara_columna[3]={1,2,4}; // máscara para la columna
int p=0;

void config_ADC();
void config_UART();
void config_timer();
void transmite(const char *str);
void ConvierteMedida(float);
void teclado();
void opcion1();
void opcion2();
void opcion3();
void opcion4();
void teclado();
void bcd_7seg(int tecla);



void main(void) {
    WDTCTL = WDTPW | WDTHOLD; // Stop watchdog timer

    //Puertos para el teclado
    // Defino los bits 3.0, 3.1 y 3.2 como entradas y el resto salidas
     P3DIR &= ~BIT0;
     P3DIR &= ~BIT1;
     P3DIR &= ~BIT2;

     // Defino los bits de salida
     P1DIR  &= BIT2+ BIT3+ BIT4+BIT5;
     P1DIR = 0x3C;

     // Defino los bits de salida del display
     P6DIR = 0xFF; // salida para colocar los segmentos del display
     P6OUT = 0x7F;

//Configuraciones
    config_timer();
    config_ADC();
    config_UART();
    __bis_SR_register(GIE); //habilita Interrupciones globales
    estado=DESACTIVADO;

    while(1){

        if(p==1){  //Variable de comprobación de transmisión de cadena
            p=0;
            //Comprobación del codigo
            if(cadena[0]==codigo[0] && cadena[1]==codigo[1] && cadena[2]==codigo[2] && cadena[3]==codigo[3]){
                estado=ACTIVADO;
            }else{
                opcion4(); //Comunica el error
                estado=DESACTIVADO;}
        }

        if(estado==2){
            __delay_cycles(500000); //tiempo para transmitir
            transmite(CR);
            transmite(mensaje1); // " Codigo de Activación "
            __delay_cycles(5000000); //tiempo para transmitir
            transmite(CR);}

        __delay_cycles(5000); //tiempo para transmitir

        if(estado==3){ //¿Activado?
            ADC12CTL0 |= ADC12SC; //  Si es así inicia la conversión, disparo por software
            __enable_interrupt();
            transmite(CR);
            transmite(temp_cpu);
            __delay_cycles(500000); //tiempo para transmitir
            transmite(medida_cadena);
            __delay_cycles(500000);

        }
        if(estado==4){//Estado : Alarma

            transmite(CR);
            transmite(mensaje4); // " Alarma "

            TA1CCR0=1000-1;       // Intervalo de reset para producir un 1K con el timer
            TA1CCR1=750-1;
            __delay_cycles(10000000);   // Retardo de 10 segundos
            TA1CCR0=0;
            TA1CCR1=0;

            while(estado==4){ //mientras que este en estado de alarma no parara
                P6OUT=0x00; // Se ilumina todo para saber cuando pulsar
                if(vez!=4){
                    teclado();
                    //vez++;
                }else { //Comprobación de las 4 pulsaciones

                    if(codigotecla[0]==1 && codigotecla[1]==0 && codigotecla[2]==0 && codigotecla[3]==0 ){
                                       estado=DESACTIVADO; //Desactivado
                                   }else{opcion4(); //Comunicamos el error
                                   }
                    vez=0; //Iniciamos la varible para nuevas pulsaciones
                }


            }
        }

    }
}


////////////////////////////////////////////////////////////////////////////
void bcd_7seg(int tecla)
{
    //Encendido de los leds en logica negativa
    switch (tecla){
    case 0: P6OUT = BIT6; break;
    case 1: P6OUT = BIT0+BIT3+BIT4+BIT5+BIT6;break;
    case 2: P6OUT = BIT2 + BIT5;break;
    case 3: P6OUT = BIT4+BIT5;break;
    case 4: P6OUT = BIT0+BIT3+BIT4+BIT7;break;
    case 5: P6OUT = BIT1+BIT4;break;
    case 6: P6OUT = BIT1;break;
    case 7: P6OUT = BIT3+BIT4+BIT5+BIT6+BIT7;break;
    case 8: P6OUT = 0x00; break;
    case 9: P6OUT = BIT3+BIT4;break;
    case 10:P6OUT = BIT3;break;
    case 15:P6OUT = BIT1+BIT2+BIT3;break;

    }

}

void teclado(){

    for (fila=0; fila < 4; fila++){
        P1OUT = mascara_fila[fila];
        __delay_cycles(500000); //tiempo para transmitir
        for (columna=0; columna<3; columna++)
            if ((P3IN & mascara_columna[columna]) == 0){
                int idx = (fila*3) + 2-columna;
                __delay_cycles(500000); //tiempo para transmitir
                tecla = codigos[idx];
                codigotecla[vez]=tecla;
                vez=vez+1;
                break;
            }
    }
    __delay_cycles(500000); //tiempo para transmitir
    bcd_7seg(tecla);
    __delay_cycles (1000000);
    P6OUT|=0x00;
}
////////////////////////////////////////////////////////////////////////////
#pragma vector=ADC12_VECTOR
__interrupt void ADC12ISR (void){
    switch(ADC12IV)
    {
    case 0: break; // Vector 0: No interrupt
    case 2: break; // Vector 2: ADC overflow
    case 4: break; // Vector 4: ADC timing overflow
    case 6: // Vector 6: ADC12IFG0
    {
        ResultadodeA0[0] = ADC12MEM0;
        medida[0]= ADC12MEM0;

        //Conversion del ADC
        Voltios = (1.5/4096.0)*medida[0];
        gradosC = (Voltios*25)/0.850;
        if(gradosC>45){estado=ALARMA;}
        ConvierteMedida(gradosC); // convierte la medida en caracteres
        break;
    }
    default: break;
    }
};
////////////////////////////////////////////////////////////////////////////
void transmite(const char *str) {
    while (*str != 0) { // Hace esto mientras  que el elemento actual recibido no sea igual al caracter nulo
        while (!(UCTXIFG & UCA0IFG)); // Mientras el bufer esté libre
        UCA0TXBUF = *str++; // Carga UCA0TXBUF con el eleme y apunta al siguiente
    }
}
////////////////////////////////////////////////////////
#pragma vector=PORT2_VECTOR
__interrupt void Port_4(void){//No haria falta ya que al modificar el estado seri si o si un 1
    if((P2IN & BIT4) == 1){  // Si se activa el sensor cambia a modo alarma
        estado=ALARMA;   }
    if((P2IN & BIT5) == 1){  // Si se activa el sensor cambia a modo alarma
        estado=ALARMA; }
    P2IFG &=~BIT4; //Boramos los flags de las interupciones
    P2IFG &=~BIT5;
}
///////////////////////////USCI A Interrupción /////////////////////////////
#pragma vector=USCI_A0_VECTOR
__interrupt void USCI_A0_ISR(void){
    switch(UCA0IV)
    {
    case 0:break; // Vector 0 - no interrupt
    case 2: // Vector 2 - RXIFG

        cadena[j++] = UCA0RXBUF;
        if (j > sizeof cadena - 1) // Guardamos hasta completar el tamaño
        {j = 0; p=1; }

        break;
    };
}
////////////////////////////////////////////////////////////////////////////
// se convierte el valor del registro ADC12MEM0 a caracteres
void ConvierteMedida(float valor)
{
    int unidades, centenas;
    unidades= (int) valor;
    centenas= (int)((valor-unidades)*100); //x100 dos decimales
    sprintf(medida_cadena, "%d.%d",unidades,centenas); // Convierte el float a una cadena de caracteres
}
////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
void opcion1(){
    estado=3;
    transmite(CR);
    transmite(mensaje); // " Sistema activado "
    __delay_cycles(50000); //tiempo para transmitir
    transmite(CR);
}
/////////////////////////////////////////////////////////////////////////////
void opcion3(){
      transmite(CR);
    transmite(mensaje3); //" Sistema desactivado "
    __delay_cycles(50000); //tiempo para transmitir
    // transmite(CR);
}
/////////////////////////////////////////////////////////////////////////////
void opcion4(){
    transmite(CR);
    transmite(mensaje2); // " Opción no válida "
    __delay_cycles(50000); //tiempo para transmitir
    transmite(CR);}
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
void config_UART(){
    // Configuración de la UART
    P3SEL = BIT3 + BIT4;                      // P3.3,4 = USCI_A0 TXD/RXD
    UCA0CTL1 |= UCSWRST;                      // **Cola la máquina de estado en RESET para programarla**
    UCA0CTL1 |= UCSSEL_2;                     // SMCLK
    UCA0BR0 = 6;                              // 1MHz 9600 (ver User's Guide)
    UCA0BR1 = 0;                              // 1MHz 9600
    UCA0MCTL = UCBRS_0 + UCBRF_13 + UCOS16;   // Modulación UCBRSx=0, UCBRFx=0 y over sampling
    UCA0CTL1 &= ~UCSWRST;                     // **Inicializa la máquina de estado USCI **
    UCA0IE |= UCRXIE;                       // Habilita la interrupción RX de USCI_A0
}


/////////////////////////////////////////////////////////////////////////////
void config_timer(){

    //INTERRUPCIÓN SENSORES
    P2DIR &= ~BIT4;             // habilitar P2.4 como entrada
     P2REN |= BIT4;              // habilitar resistencia
     P2OUT &=  ~BIT4;              // resistencia de pull-down

     P2IES = BIT4;
     P2IFG &= ~BIT4;
     P2IE = BIT4;

     P2DIR &= ~BIT5;             // habilitar P2.2 como entrada
     P2REN |= BIT5;              // habilitar resistencia
     P2OUT &=  ~BIT5;              // resistencia de pull-down
     P2IES = BIT5;
     P2IFG &= ~BIT5;
     P2IE = BIT5;


    // CONFIGURACIÓN DEL TIMER
    P2SEL |= BIT0;          // habilita el timer
    P2DIR |= BIT0;          // habilita como salida
    TA0CCTL1 = OUTMOD_7;  // modo Salida Reset/Set
    TA0CTL = TASSEL_2 + MC_1; //modo ascendente y SMCLK fuente del reloj

}
/////////////////////////////////////////////////////////////////////////////
void config_ADC(){
    // configuración ADC para medir la temperatura interna
    REFCTL0 &= ~REFMSTR; // Reset REFMSTR para control por parte del ADC12
    // Activamos el ADC, la referencia a 1,5 V y establecemos el muestreo
    ADC12CTL0 = ADC12ON+ADC12REFON+ADC12SHT0_2;
    ADC12CTL1 = ADC12SHP; //Timer de muestreo
    ADC12MCTL0 = ADC12INCH_10 + ADC12SREF_1; // A10 = Sensor temperatura
    ADC12IE = 0x01; // Habilitamos ADC12IFG.1
    __delay_cycles(100); // retardo para el establecimiento de la referencia
    ADC12CTL0 |= ADC12ENC; // Habilitación de la conversión
}
