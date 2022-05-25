#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int main (void) {
    srand(time(NULL));

    //Declaramos las variables principales.

    int apuesta;

    //Las variables de cadena añadirán espacios antes de los caballos para que avancen

    char EspCab0[73]="", EspCab1[73]="", EspCab2[73]="", EspCab3[73]="";

    printf("Ejercicio 3. Practica 2. Fundamentos de Programacion 1. \n-------------------------------------------------------------------------------\n");

    //Bucle para pedir la apuesta en caso de que no se seleccione una posible

    do {printf("Introduzca su apuesta (1-4): ");
    scanf("%d", &apuesta);
    getchar();}
    while (apuesta!=1 && apuesta!=2 && apuesta !=3 && apuesta!=4);


    //Creamos un bucle for que vaya añadiendo concatenando espacios a los caballos mientras que estos no lleguen al final de la pantalla

    for (int contador=0; strlen(EspCab0)<80-7 && strlen(EspCab1)<80-7 && strlen(EspCab2)<80-7 && strlen(EspCab3)<80-7; contador++){

        int elegido = rand()%4;

        //La máquina creará un numero aleatorio del 0 al 3, el elegido, mediante un switch será el que concatene un espacio a la cadena del caballo

        switch (elegido){
            case 0:
            strcat(EspCab0," ");
            break;
            case 1:
            strcat(EspCab1," ");
            break;
            case 2:
            strcat(EspCab2," ");
            break;
            case 3:
            strcat(EspCab3," ");
            break;             }

    //se borra la pantalla, y la maquina irá haciendo avanzar aleatoriamente a los caballos. Con el contador del for , animamos la carrera mostrando los supuestos metros recorridos

    system("cls");

    printf("                        CARRERA DE CABALLOS     \n");
    printf("                        metros recorridos: %d\n\n", contador);
    printf("                  ------------------------------------                \n\n");

    printf("%s~__/'>\n",EspCab0);
    printf("%s// \\\\\n",EspCab0);

    printf("--------------------------------------------------------------------------------\n");

    printf("%s~__/'>\n",EspCab1);
    printf("%s// \\\\\n",EspCab1);

    printf("--------------------------------------------------------------------------------\n");


    printf("%s~__/'>\n",EspCab2);
    printf("%s// \\\\\n",EspCab2);

    printf("--------------------------------------------------------------------------------\n");

    printf("%s~__/'>\n",EspCab3);
    printf("%s// \\\\\n",EspCab3);

    printf("--------------------------------------------------------------------------------\n");

    _sleep(1);

    }

    //Se comprueba cual es el caballo ganador y se compara con nuestra apueseta.

    int caballo;

    if(strlen(EspCab0)==80-7){
        printf("El ganador es el caballo: 1\n");
        caballo=1;}
        else {
            if(strlen(EspCab1)==80-7){
                printf("El ganador es el caballo: 2\n");
                caballo=2;}
                else {
                    if(strlen(EspCab2)==80-7){
                        printf("El ganador es el caballo: 3\n");
                        caballo=3;}
                        else {
                            if(strlen(EspCab3)==80-7){
                                printf("El ganador es el caballo: 4\n");
                                caballo=4;}
                    }
                            }
                            }

    printf("Tu apostaste por el caballo: %d \n",apuesta);
    if(caballo==apuesta){
        printf("ENHORABUENA!! Tu caballo es el ganador!!\n\n");
    }else{
        printf("Lo siento, tu apuesta no fue la ganadora. :( ) \n\n");
    }





return 0;

}

