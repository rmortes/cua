/*PRÁCTICA 1, EJERCICIO 3*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void){

    /*Recoger datos Inicio*/
    //JUGADOR 1

    char palabra1[70];
    char palabra2[70];
    int l,a;
    printf("Practica 1 de FP1. Ejercicio 3\n");
    printf("------------------------------\n");
    printf("Jugador 1, introduzca su palabra secreta: ");
    scanf("%s", palabra1);
    getchar();
    system("cls");
    printf("Practica 1 de FP1. Ejercicio 3\n");
    printf("------------------------------\n");
    //JUGADOR 2
    l=strlen(palabra1); //Sirve para devolver el mismo numero de caracteres que se definen.
    printf("La palabra tiene %d letras.\n\n",l);
    a = rand()%(l);
    printf("Jugador 2, primer intento (pista: en la posicion %d esta la letra %c): ",a+1,palabra1[a]);
    scanf("%s",palabra2);
    getchar();
    if(strcmp(palabra2,palabra1)==0){
        printf("Felicidades! Acertaste.\n");
    }else{
        a = rand()%l;
        printf("Jugador 2, segundo intento (pista: en la posicion %d esta la letra %c): ",a+1,palabra1[a]);
        scanf("%s",palabra2);
        getchar();
        if(strcmp(palabra2,palabra1)==0){
            printf("Felicidades! Acertaste.\n");
        }else{
            int a=rand()%l;
            printf("Jugador 2, tercer intento (pista: en la posicion %d esta la letra %c): ",a+1,palabra1[a]);
            scanf("%s",palabra2);
            getchar();
            if(strcmp(palabra2,palabra1)==0){
                printf("Felicidades! Acertaste.\n");
            }else{
                int a=rand()%l;
                printf("Jugador 2, ultimo intento (pista: en la posicion %d esta la letra %c): ",a+1,palabra1[a]);
                scanf("%s",palabra2);
                getchar();
                if(strcmp(palabra2,palabra1)==0){
                    printf("Felicidades! Acertaste.\n");
                }else{
                    printf("Lo siento, ha agotado todos los intentos la palabra era '%s'.\n",palabra1);
                }
            }
        }
    }
    return 0;
}
