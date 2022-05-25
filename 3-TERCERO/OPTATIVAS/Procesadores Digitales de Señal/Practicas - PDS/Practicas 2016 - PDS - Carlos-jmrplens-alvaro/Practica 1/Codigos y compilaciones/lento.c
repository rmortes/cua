#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

int main() {
    short buf[BUFFER_SIZE];
    short buf_aux[2*BUFFER_SIZE]; //inicializamos buffer mas grande
    int i, b;

    while ((b = fread(buf, sizeof(short), BUFFER_SIZE, stdin)) != 0) {
	buf_aux[2*BUFFER_SIZE]=0;// inicializamos las muestras a cero 
        for (i = 0; i < b-1; i=i+2) { // leemos cada dos muestras la original
		buf_aux[2*i]=buf[i];  // copiamos la misma cada dos posiciones
		buf_aux[(2*i)+1]=buf[i+1]; // impares con impares
		buf_aux[(2*i)+2]=buf[i];  // pares con pares 
		buf_aux[(2*i)+3]=buf[i+1];
		//guardamos por duplicado en el buffer auxiliar
        }
        fwrite(buf_aux, sizeof(short), 2*BUFFER_SIZE, stdout);
        fflush(stdout);
    }
   return 0;
}
