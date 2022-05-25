#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

int main() {
    short buf[BUFFER_SIZE];
    int i, b;

    while ((b = fread(buf, sizeof(short), BUFFER_SIZE, stdin)) != 0) {
        for (i = 0; i < b; i++) {
            /* *************************************************** *
             * Aquí se lleva a cabo el proceso                     *
             * Por ejemplo:                                        *
             *    buf[i] *= 1.5; //(pero cuidado con el overflow!) *
             * *************************************************** */
        }
        fwrite(buf, sizeof(short), BUFFER_SIZE, stdout);
        fflush(stdout);
    }
 
   return 0;
}
