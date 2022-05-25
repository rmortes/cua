#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main()
{
    //Declaración de variables y puesta en marcha
    int i,j,r;
    while(1){
        //Ponemos el maximo radio posible
        for(r=1;r<12;r++){
            //Recorremos filas
            for (i=0;i<24;i++){
                //Recorremos columnas
                for (j=0;j<80;j++){
                    if((i-12)*(i-12)+(j-40)*(j-40)<(r*r)){
                        //Si está dentro del radio se coloca un asterisco
                        printf("*");
                    }else{
                        printf(" "); //Si no está dentro del radio se coloca un espacio
                    }
                }
                printf("\n"); //Acabamos la fila
            }
            _sleep(150);
            system("cls");
        }
    }
}
