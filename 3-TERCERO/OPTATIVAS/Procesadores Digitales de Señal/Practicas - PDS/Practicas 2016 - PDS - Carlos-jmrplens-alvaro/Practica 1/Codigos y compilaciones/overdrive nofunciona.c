#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

int main() {
    short buf[BUFFER_SIZE];
    short buf_salida[BUFFER_SIZE];
    int i, b;
    while ((b = fread(buf, sizeof(short), BUFFER_SIZE, stdin)) != 0) {
        for (i = 0; i < b; i++) {
            if(buf[i]<1/3 && buf[i]>=0){
                    buf_salida[i]=2*buf[i];
                    if(buf_salida[i]>shrt_max){
                        buf_salida[i]=shrt_max;
                    }
            }else{
                    if(buf[i]<2/3 && buf[i]>=1/3){
                            buf_salida[i]=(3-((2-(3*buf[i]))*(2-(3*buf[i]))))/3;
                            if(buf_salida[i]>shrt_max){
                                buf_salida[i]=shrt_max;
                            }
                    }else{
                            if(buf[i]<=1 && buf[i]>=2/3){
                                    buf_salida[i]=1;
                            }
                    }
            }
        }
        fwrite(buf_salida, sizeof(short), BUFFER_SIZE, stdout);
        fflush(stdout);
    }

   return 0;
}
