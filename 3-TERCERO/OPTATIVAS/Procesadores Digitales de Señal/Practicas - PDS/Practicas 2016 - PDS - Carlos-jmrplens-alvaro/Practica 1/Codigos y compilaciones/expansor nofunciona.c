#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

int main() {
    short buf[BUFFER_SIZE];
    short bufexpansor[BUFFER_SIZE];
    int threshold=2;// valor maximo que puede tomar la señal
    float v=0.2; // tiempo de ataque
    int i, b;

    while ((b = fread(buf, sizeof(short), BUFFER_SIZE, stdin)) != 0) {
        for (i = 0; i < b; i++) {

            if (threshold>buf[i] && buf[i]>-threshold){
                    bufexpansor[i]=v*buf[i];
            }
        }
        fwrite(bufexpansor, sizeof(short), BUFFER_SIZE, stdout);
        fflush(stdout);
    }
   return 0;
}
