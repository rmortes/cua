#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024
#define MAX 3           // Nivel para maximizar
int main() {
    short buf[BUFFER_SIZE];
    int i, b;
    while ((b = fread(buf, sizeof(short), BUFFER_SIZE, stdin)) != 0) {
        for (i = 0; i < b; i++) {
     /* Primero comprueba si la ganancia de la muestra crearia overflow al amplificarla,
     * si al aumentar diese overflow asigna el valor maximo o minimo segun si la muestra
     * es positiva o negativa. Si no va a generar overflow se le aplica el aumento
     *
     * Si el valor de la muestra es negativa y menor al valor del overdrive dividido
     * por el valor de amplificacion, se generaria overdrive por lo que se le asigna
     * el valor maximo negativo. Para el caso de muestras positivas se realiza el mismo
     * proceso pero con valores positivos.
     */
            if(buf[i]<-32767/MAX){
                buf[i]=-32767;
            }else if(buf[i]>32767/MAX){
                buf[i]=32767;
            }
            else  buf[i] *= MAX;
        }
        fwrite(buf, sizeof(short), BUFFER_SIZE, stdout);
        fflush(stdout);
    }

    return 0;
}
