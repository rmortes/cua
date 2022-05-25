#include <stdio.h>

int main(void){

    //DECLARAR VARIABLES

    int veces, i, n=1, contador;

    //PEDIR UN NÚMERO AL USUARIO Y FILTRAR SÍ ES MAYOR QUE 20

    do{
        printf("Introduzca numero entero mayor que cero:"); scanf("%d",&veces);getchar();
        if(veces<=0){
            printf("Error: el numero no es mayor que cero.\n");
        }
    }while (veces<=0);

    //INICIO DEL BUCLE

    while (veces>0){

        //GUARDAR LOS INCREMENTOS DE LA VARIABLE contador EN LA VARIABLE n

        contador++;
        n=contador;
        i=0;

        //CALCULAR NÚMERO INVERSO

        while (n>0){
            i= i*10 + n%10;
            n= n/10;
        }

        //COMPROBAR SÍ EL INVERSO ES IGUAL AL NÚMERO ANTERIOR

        if(i==contador){
            printf(" %d ",i);
            veces--;
        }
    }
    printf("\n");
    return 0;
}
