//Fundamentos de Programación 1. Práctica 1. Ejercicio 3: Relaciones entre personas.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main (void){

    //Empezamos mostrando un encabezado a modo decorativo
    printf("Fundamentos de Programacion 1 - Practica 1/Ejercicio 1. \n");
    printf("------------------------------------------------------- \n\n");

    char palabrasecreta[50];
    printf("Jugador 1, introduzca la palabra secreta: ");
    scanf("%s",palabrasecreta);
    getchar();
    strupr(palabrasecreta);

    system("cls");
    char intento[50];

    printf("Jugador 2. Primer intento. (Pista: Empieza por la letra: %c): ", palabrasecreta[0]);
    scanf("%s", intento);
    getchar();
    strupr(intento);
    int a = strcmp(intento,palabrasecreta);
    if(a==0){
        printf("Enhorabuena, has acertado!!\n");
    }else{


        printf("Jugador 2. Segundo intento. (Pista: Acaba por la letra: %c): ", palabrasecreta[strlen(palabrasecreta)-1]);
        scanf("%s", intento);
        getchar();
        strupr(intento);
        a = strcmp(intento,palabrasecreta);

        if(a==0){

            printf("Enhorabuena, has acertado!!\n");

        }else{

                printf("Jugador 2. Ultimo intento. (Pista: contiene la letra: %c): ", palabrasecreta[strlen(palabrasecreta)/2]);
                scanf("%s", intento);
                getchar();
                strupr(intento);
                a = strcmp(intento,palabrasecreta);

                if(a==0){

                    printf("Enhorabuena, has acertado!!\n");

                }else{
                        printf("Lo siento, has perdido :(. La palabra secreta era: %s", palabrasecreta);
                    }
                }}

  return 0;

            }









