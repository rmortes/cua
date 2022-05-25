#include <stdio.h>
#include <stdlib.h>
#include <math.h>  // Necesario para la funcion seno

#define BUFFER_SIZE 1024
#define PI 3.14159265359

int main(){
    int fs = 44100;         // Frecuencia de muestreo
    float fm =5;            // Frecuencia de modulación / duración del tremolo
    float A=2;              // Amplitud del seno que genera el tremolo
    short buf[BUFFER_SIZE];
    int i, b, j;
    float func_tremolo;
    j = 0;                  // Entero para contar el numero de muestras totales
    
    while ((b = fread(buf, sizeof(short), BUFFER_SIZE, stdin)) != 0) {
        
        for (i = 0; i < b-1; i=i+2) {
            func_tremolo= (A*sin(2*PI*fm*j/fs));// Generacion de la funcion tremolo
            /* Modificamos la amplitud de las muestras multiplicando por la funcion tremolo */
            buf[i] *= func_tremolo;             // Multiplicamos por el seno la muestra actual
            buf[i+1] *= func_tremolo;           // Multiplicamos por el seno la muestra siguiente
            j++;
        }
        fwrite(buf, sizeof(short), BUFFER_SIZE, stdout);
        fflush(stdout);
    }
    return 0;
}
