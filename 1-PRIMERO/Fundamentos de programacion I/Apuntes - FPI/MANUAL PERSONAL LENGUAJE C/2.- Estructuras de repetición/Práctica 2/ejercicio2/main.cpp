#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){

    srand(time(NULL));

    int contador=2,a,b, diferencia1, diferencia2;
    int num=rand()%1001;

    printf("Ya he elegido el numero entre 1 y 1000 \n");

    printf("Intento 1. Introduzca un numero: ");
    scanf("%d",&a);
    getchar();

    if (a==num){
        printf("Felicidades, has acertado el numero en 1 intento. ");
    }
    else
        do {
        if(a<num)
            diferencia1=num-a;
        else
            diferencia1=a-num;

        printf("Intento %d. Introduzca un numero: ",contador);
        scanf("%d",&b);

        if(b<num)
            diferencia2=num-b;

        else
            diferencia2=b-num;

        if(diferencia2>diferencia1)
            printf("Frio, frio.\n");

        else
            if(diferencia2<diferencia1)
                printf("Caliente, caliente.\n");

            else
                printf("Templado, templado.\n");

        a=b;//Para que el segundo número introducido pase a ser el primero
        contador++;
    }while (b!=num);

    if (contador!=2)
        printf("Felicidades, has acertado el numero en %d intentos. ",contador-1);

    printf("\n");
    return 0;
}
