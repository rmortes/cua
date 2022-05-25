#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

int main() {
    short buf[BUFFER_SIZE];
    short M[BUFFER_SIZE/2]; // reducimos el buffer a la mitad
    int i, b, j;	

    while ((b = fread(buf, sizeof(short), BUFFER_SIZE, stdin)) != 0) {
	M[BUFFER_SIZE/2]=0; //inicializamos las muestras a cero
	j=0; // inicializamos el contador de muestas por ventana
        for (i = 0; i < b-3; i=i+4) { // leeremos cada 4 muestras la original
		M[j]=buf[i+1];  // guardamos cada dos posiciones del vector
		M[j+1]=buf[i+1]; // la misma muestra
		j=j+2; // aumentamos en dos el contador de muestras
        }
        fwrite(M, sizeof(short), BUFFER_SIZE/2, stdout);
        fflush(stdout);
    }
 
   return 0;
}
