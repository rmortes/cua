/* REALIZADO POR JOSE M.R. PLENS */
unsigned int mem;
volatile float temperatura;
static char cadena_temp[16];

void config_ADC()
{
    // INCH_10 es el Vout de el sensor de temperatura, 3.55mv/C.
    ADC10CTL1 = INCH_10;
    // VR+ = VREF+ . 64?ADC10CLKs . Referencia activada a 1.5V
    ADC10CTL0 = SREF_1 + ADC10SHT_3 + REFON + ADC10ON;
}
void temp(){
  
 ADC10CTL0 |= ENC + ADC10SC;

        // gradosCentigrados = ((Vout_sensor/1024)*Vref)-Voffset_sensor)/V_centigrado = ((ADC10MEM/1024)*1500mV)-986mV)/3.55mV
        mem = ADC10MEM;

        temperatura = (float)((mem * 1500.00)/1024.00 - 986.60)/3.55;
        sprintf(cadena_temp, "%.2f", temperatura); // Convierte el float a una cadena de caracteres
       
}