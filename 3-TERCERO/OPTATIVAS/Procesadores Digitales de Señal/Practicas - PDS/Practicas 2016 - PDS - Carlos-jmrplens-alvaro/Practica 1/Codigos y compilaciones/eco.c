#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 52400 // Mayor buffer ->mayor bloque de datos -> mayor tiempo de eco


int main() {
    short buf[BUFFER_SIZE];     // buffer de muestras
    short buf_pre[BUFFER_SIZE]; // buffer auxiliar anterior
    short buf_new[BUFFER_SIZE]; // buffer auxiliar eco
    int i, b;
    float g=0.5; // ganancia del eco
    
    
    while ((b = fread(buf, sizeof(short), BUFFER_SIZE, stdin)) != 0) {
        /* En cada bloque de datos agregamos las muestras del bloque anterior con ganancia a la mitad y
         * Almacenamos las muestras actuales reduciendo su ganancia a la mitad para agregarlas en el siguiente
         * bloque
         */
        
        for (i = 0; i < b; i++) {
            
            buf_new[i] =buf[i] + buf_pre[i]; // suma las muestras actuales con las anteriores
            
        }
        for (i = 0; i < b; i++){
            
            buf_pre[i]=g*buf[i]; // reduce la ganancia a la mitad del bloque actual y lo almacena
        }
        fwrite(buf_new, sizeof(short), BUFFER_SIZE, stdout);
        fflush(stdout);
    }
    return 0;
}
