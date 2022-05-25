#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

int main() {
    unsigned char buf[BUFFER_SIZE];
    int i, b;
    short muestra;

    while ((b = fread(buf, sizeof(char), BUFFER_SIZE, stdin)) != 0) {
        for (i = 0; i < b; i += 2) {
            muestra = buf[i + 1];
            muestra = muestra << 8;
            muestra = muestra | buf[i];

            /* *************************************************** *
             * Aquí se lleva a cabo el proceso                     *
             * Por ejemplo:                                        *
             *    buf[i] *= 1.5; //(pero cuidado con el overflow!) *
             * *************************************************** */

            buf[i] = (unsigned char) (0xFF & muestra);
            muestra = muestra >> 8;
            buf[i + 1] = (unsigned char) (0xFF & muestra);
        }
        fwrite(buf, sizeof(char), BUFFER_SIZE, stdout);
        fflush(stdout);
    }
 
   return 0;
}
