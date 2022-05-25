#include <msp430.h>

/*
 * main.c
 */
void setup(){       //Activamos los pines de los light
    P1DIR |=0x40;   //Activamos P1.6
    P3DIR |=0x1F;   //Activamos los pins de P3
    P6DIR |=0x60;   //Activamos los pins de P6

    P2DIR &= ~0x02; //Activamos P2.0
    P2REN |= 0x02;  //Resistencia PullUp
    P2OUT |= 0x02;  //Activamos la resistencia
}

void OFF(){ //Negamos todas los registros para apagarlos
    P1OUT &= ~0x40;   //Negamos P1.6
    P3OUT &= ~0x1F;   //Negamos los pins de P3
    P6OUT &= ~0x60;   //Negamos los pins de P6
}

void ON(char light){ //Encendemos los LEDs
    //Comprobamos que la máscara actual coincide con la máscara de cada LED
    if((light & 0x80)!=0){ //LED D8
        P3OUT |= 0x01;
    }
    if((light & 0x40)!=0){ //LED D7
        P3OUT |= 0x02;
    }
    if((light & 0x20)!=0){ //LED D6
        P3OUT |= 0x04;
    }
    if((light & 0x10)!=0){ //LED D5
        P6OUT |= 0x40;
    }
    if((light & 0x08)!=0){ //LED D4
        P1OUT |= 0x40;
    }
    if((light & 0x04)!=0){ //LED D3
        P3OUT |= 0x08;
    }
    if((light & 0x02)!=0){ //LED D2
        P3OUT |= 0x10;
    }
    if((light & 0x01)!=0){ //LED D1
        P6OUT |= 0x20;
    }
}

void delay(){ //Hacemos un delay de 0.5 segundos
    int j;
    for (j=500;j>0;j--){
        _delay_cycles(1000);
    }
}

void blink(){ //Función para el parpadeo
    int i;
    OFF(); //Apagamos los LEDs
    delay(); //Retardo 0.5 segundos
    for(i=0;i<10;i++){ //Bucle de 10 vueltas
        ON(0xFF); //Encendemos todos los LEDs
        delay(); //Retardo 0.5 segundos
        OFF(); //Apagamos todos los LEDs
        delay(); //Retardo 0.5 segundos
    }
}

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer
    setup();
    char DES[8]={0x80,0xC0,0xE0,0xF0,0xF8,0xFC,0xFE,0xFF}; //Cadena con la máscara de cada LED de D8 a D1
    char ASC[8]={0x01,0x03,0x07,0x0F,0x1F,0x3F,0x7F,0xFF}; //Cadena con la máscara de cada LED de D1 a D8
    int i,j;
    OFF(); //Apagamos los LEDs
    while(1){
        for(i=0;i<8;i++){ //Bucle para recorrer las cadenas de las máscaras
            ON(DES[i]); //Encendemos el LED correspondiente
            delay(); //Retardo 0.5 segundos
            if((P2IN & 0x02)==0){ //Comprobamos si el botón S1 está pulsado
                int k;
                j=k=0;
                while(j<8 && k==0){ //Encendemos el resto de LEDs ascendientemente
                    char sum;
                    sum= DES[i] | ASC[j]; //Sumamos las mascaras de todos los LEDs encendidos
                    ON(sum);
                    delay(); //Retardo 0.5 segundos
                    if(sum == 0xff){ //Comprobamos si están todos los LEDs encendidos
                        blink(); //Parpadeo
                        k=1; //Terminamos bucle while
                    }
                    j++;
                }
                ON(DES[i]); //Encendemos los LEDs que estaban encendidos antes de pulsar S1
                delay(); //Retardo 0.5 segundos
            }
        }
        OFF(); //Apagamos todos los LEDs
        delay(); //Retardo 0.5 segundos
    }
}
