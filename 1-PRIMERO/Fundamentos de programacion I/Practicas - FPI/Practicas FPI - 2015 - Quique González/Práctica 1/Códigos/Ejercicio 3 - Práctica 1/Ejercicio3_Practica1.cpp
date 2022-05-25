//INTRODUCIR LIBRERIAS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//DECLARAR LA FUNCIÓN PRINCIPAL

int main(void){

    printf("Practica 1, ejercicio 3\n-----------------------------------------\n");

    //PARA QUE CADA VEZ QUE EL PROGRAMA ARRANQUE ESCOJA UNA SEMILLA DE NUMEROS ALEATORIOS DISTINTA

    srand(time(NULL));

    //DECLARAMOS LAS VARIABLES CON LAS QUE VAMOS A TRABAJAR

    int n, aleatorio=rand()%10+1;

    //PEDIMOS UN NÚMERO AL USUARIO

    printf("Introduzca numero entre 0 y 10:"); scanf("%d",&n); getchar();

    //ENVIAR UN MENSAJE DE ERROR SÍ EL NÚMERO NO CUMPLE LAS CONDICIONES INICIALES

    if (n>10|| n<0){
        printf("Error: ese numero no esta entre 0 y 10");
    }

    //INICIAR LAS TRES OPORTUNIDADES DEL USUARIO PARA ACERTAR EL NÚMERO

    else{

        //OPORTUNIDAD 1

        if (n==aleatorio){
            printf("FELICIDADES, ACERTASTE\n");
        }else{

            //OPORTUNIDAD 2

            if(n>aleatorio){
                printf("El numero introducido es mayor que el que buscas.\nIntroduzca otro numero: ");
            }else{
                printf("El numero introducido es menor que el que buscas.\nIntroduzca otro numero: ");
            }
        }scanf("%d",&n);getchar();

        if (n==aleatorio){
            printf("FELICIDADES, ACERTASTE\n");
        }else{

            //OPORTUNIDAD 3

            if(n>aleatorio){
                printf("El numero introducido es mayor que el que buscas.\nIntroduzca otro numero:");
            }else{
                printf("El numero introducido es menor que el que buscas.\nIntroduzca otro numero:");
            }
        }scanf("%d",&n);getchar();

        if (n==aleatorio){
            printf("FELICIDADES, ACERTASTE\n");
        }
        else{

            //EN EL CASO QUE NO ACIERTE EL USUARIO REVELAR EL NÚMERO

            printf("GAME OVER: El numero es %d \n\n\n\n\n GAME OVER, PAQUETE \n", aleatorio);
        }
    }
    return 0;
}
