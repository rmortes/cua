#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

int main() {
    short buf[BUFFER_SIZE];
    int i, b;

    while ((b = fread(buf, sizeof(short), BUFFER_SIZE, stdin)) != 0) {
        for (i = 0; i < b; i++) {
		if (i%2!=0){ // solo muestras pares
		 buf[i]=0 // las ponemos a cero 
		}
        }
        fwrite(buf, sizeof(short), BUFFER_SIZE, stdout);
        fflush(stdout);
    }
 
   return 0;
}
