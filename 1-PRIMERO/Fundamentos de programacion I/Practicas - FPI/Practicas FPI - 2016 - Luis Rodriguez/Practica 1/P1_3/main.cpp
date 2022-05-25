#include <string.h>
#include <stdlib.h>
#include <stdio.h>


int main (void)
{
    char  palabrasecreta[20],  intento [20];
    int ultpospalsec; //Numero de la posicion de la ultima letra de la palabra secreta

    //Tal cual sale en el ejemplo:
    printf("Practica 1 de FP1. Ejercicio 3 \n");
    printf("------------------------------\n");

    //Pedimos la palabra:
    printf("Jugador 1, introduzca la palabra secreta: ");
    scanf("%s",palabrasecreta);

    //Pasamos a mayusculas para evitar la sensibilidad entre mayusculas y minusculas
    strupr(palabrasecreta);
    //Borramos pantalla
    system ("cls");

    //Tal cual sale en el ejemplo:
    printf("Practica 1 de FP1. Ejercicio 3 \n");
    printf("------------------------------\n");

    //Turno para el jugador dos
    //Se muestra la primera letra de la palabra secreta
    printf("Jugador 2, primer intento (pista: Empieza por letra '%c') :", palabrasecreta[0]);
    scanf("%s",intento);
    //Pasamos a mayusculas para evitar conflictos de sensibilidad entre mayusculas y minusculas
    strupr(intento);

    if (strcmp(palabrasecreta,intento)== 0){
        //Comprobamos si son iguales, pues si son iguales el jugador ha ganado
        printf("Felicidades, acertaste! \n");
    }else{
        ultpospalsec=strlen(palabrasecreta)-1;
        printf("Jugador 2, segundo intento (pista: termina por letra '%c') : ", palabrasecreta[ultpospalsec]);
        scanf("%s",intento);
        strupr(intento);
        if (strcmp(palabrasecreta,intento)== 0){
            printf("Felicidades, acertaste! \n");
         }else{
            printf("Jugador 2, tercer intento (pista: contiene '%c') : ", palabrasecreta[ultpospalsec/2]);
            scanf("%s",intento);
            strupr(intento);
            if (strcmp(palabrasecreta,intento)== 0){
            printf("Felicidades, acertaste! \n");
            }else{
                printf("Lo siento, has perdido. La palabra era %s \n",palabrasecreta );
            }
        }
    }
    return(0);
}
