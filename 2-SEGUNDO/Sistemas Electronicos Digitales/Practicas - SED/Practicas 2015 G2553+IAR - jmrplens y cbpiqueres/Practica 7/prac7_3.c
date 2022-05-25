#include <msp430.h>
#include "LCD4bits.c"

unsigned int mem;
volatile float temperatura;

void config_screen()
{
    LCD_INI (Dos_Lineas_5x8, Derecha_NoDesplaza);   // Configuramos el msp para funcionar con el LCD
    LCD_Control (CurOFF_BliOFF);
    LCD_Control(ClearDisplay);
}
void config_ADC()
{
    // INCH_10 es el Vout de el sensor de temperatura, 3.55mv/C.
    ADC10CTL1 = INCH_10;
    // VR+ = VREF+ . 64×ADC10CLKs . Referencia activada a 1.5V
    ADC10CTL0 = SREF_1 + ADC10SHT_3 + REFON + ADC10ON;
}

int main(void)
{
    WDTCTL = WDTPW + WDTHOLD;
    DCOCTL = CALDCO_1MHZ;
    BCSCTL1 = CALBC1_1MHZ;
    config_ADC();
    config_screen();
    while(1)
    {
        // Inicio de muestreo y conversion
        ADC10CTL0 |= ENC + ADC10SC;

        // gradosCentigrados = ((Vout_sensor/1024)*Vref)-Voffset_sensor)/V_centigrado = ((ADC10MEM/1024)*1500mV)-986mV)/3.55mV
        mem = ADC10MEM;

        temperatura = (float)((mem * 1500.00)/1024.00 - 986.60)/3.55;

        // Muestra por pantalla la temperatura
        LCD_FilaColumna(1,0);
        LCD_Cadena ("Tinterna:");
        LCD_FilaColumna(1,9);
        LCD_Float (temperatura);
        LCD_FilaColumna(1,14);
        LCD_Cadena ("^C");
        // Retardo para determinar la velocidad de refresco de los datos en la pantalla. 0,5 segundos
        __delay_cycles(500000);
    }
}
