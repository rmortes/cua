#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int main(void){
    char cad[70];
    int l,i;
    printf("Introduzca una frase de entre 10 y 50 caracteres:\n");
    gets(cad);//para que se puedan meter espacios
    l=strlen(cad);
    while(l<10&&l>50){
        printf("Error. Numero de caracteres incorrecto.\n");
        printf("Introduzca una frase de entre 10 y 50 caracteres:\n");
    }
    while(1){//verdad
        //mover la frase un caracter a la izquierda
        char aux=cad[0];
        for(i=0;i<l;i++){
            cad[i]=cad[i+1];
        }
        aux=cad[l-1];
        //centrar en filas
        for(i=0;i<10;i++){
            printf("\n");
        }//centrar en columnas
        for (i=0;i<40-l/2-2;i++) {
            printf(" ");
        }
        printf("o");//esquina superior izquierda
        for(i=0;i<l+2;i++){//guiones superiores
            printf("-");
        }
        printf("o");//esquina superior derecha
        printf("\n");
        for(i=0;i<40-l/2-2;i++){// l/2 para partir del centro de la frase y que haya proporcionalidad
            printf(" ");
        }
        printf("|%s|",cad);
        for(i=0;i<40-l/2-2;i++){
            printf(" ");
        }
        printf("o");//esquina inferior derecha
        for(i=0;i<l+2;i++){//guiones inferiores
            printf("-");
        }
        printf("o");
        printf("\n");
        _sleep(250);

    }

    return 0;
}
