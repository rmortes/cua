//Fundamentos de Programacion 1. Practica 2. Ejercicio 3: Ahorcado v2.0.
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main (void){

    char palabrasecreta[50], aleatoria[50], intento[50];

    //Empezamos mostrando un encabezado a modo decorativo
    printf("Fundamentos de Programacion 1 - Practica 2/Ejercicio 3. \n");
    printf("------------------------------------------------------- \n\n");

    char si [4]="SI", res[4];
    int a;

    //Creamos un bucle para jugar todas las veces que queramos
    do{
    //Pedimos al usuario introducir la palabra a adivinar, la convertimos a mayusculas y la copiamos a una nueva cadena
    printf("Introduzca la palabra secreta: ");
    scanf("%s", palabrasecreta);
    getchar();
    strupr(palabrasecreta);
    strcpy(aleatoria, palabrasecreta);

    //Borramos la pantalla y declaramos las variables fuera de los bucles que seran necesarios para las siguientes operaciones
    system("cls");
    int oportunidades = 5, i,j;
    int longitud = strlen(aleatoria);
    int acierto=0;

    //Creamos el bucle que nos repetira las 5 oportunidades y parara en caso de acierto.
    for(i=1; i<=oportunidades && acierto!=1 ; i++){

        //Creamos el bucle que desordenara las pistas
        for(j=0; j<longitud*longitud ;j++){

            int num1 = rand()%longitud;
            int num2 = rand()%longitud;
            char aux=aleatoria[num1];
            aleatoria[num1]=aleatoria[num2];
            aleatoria[num2]=aux;
        }

        //Pedimos al usuario su que realice su intento y lo comparamos con la palabra secreta.
        printf("Intento %d de %d. ", i, oportunidades);
        printf("%s: ", aleatoria);
        scanf("%s", intento);
        strupr(intento);
        system("cls");
        int a = strcmp(intento, palabrasecreta);

        //Creamos una anidacion de condicionales para comprobar si ha acertado y parar en ese caso o seguir segun las oportunidades
        if(i==5){
            printf("Lo siento, las perdido! :(\n");
        }else{

            if(a!=0){
                printf("Lo siento, intentalo otra vez!\n");
            }else{
                printf("Enhorabuena, has acertado!\n\n");
                acierto=1;

            }
        }


    }
    system("cls");
    printf("Deseas volver a jugar? Si o No: ");
    scanf("%s", res);
    strupr(res);
    a=strcmp(res, si);
    }
    while(a==0);



    return 0;
}




