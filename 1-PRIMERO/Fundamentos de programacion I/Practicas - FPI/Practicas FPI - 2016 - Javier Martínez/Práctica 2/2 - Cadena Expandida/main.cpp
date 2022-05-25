
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main (void){

    char cadena[100];

    printf("Ejercicio 2. Practica 2. Fundamentos de Programacion 1. \n--------------------------------------------------------------------------------\n");

    //Pedimos al usuario la cadena que queremos que se expanda
    printf("Introduzca cadena de maximo de 20 caracteres: ");
    gets(cadena);

    //En caso de superar los caracteres permitidos, le volvemos a preguntar
    while(strlen(cadena)>20)
    {printf("Error, numero de caracteres permitido excedido. Vuelve a introducir: ");
   gets(cadena);}

    //iniciamos el bucle principal y declaramos e inicializamos nuestro contador
    int ciclo=0,longitud;
    while(1){
        system("cls");

        printf("\n\n\n\n\n\n\n\n\n\n\n\n");

        //Calcula el valor total de caracteres de nuestra cadena, incluidos los espacios
        longitud=strlen(cadena)+((strlen(cadena)-1)*ciclo);

        if(longitud<=80){

            //Trataremos de centrar la cadena en lo ancho de la pantalla
            for (int centro=40-longitud/2;centro>0;centro--)
            {printf(" ");}

            //Escribimos la cadena
            for(int posicion=0;posicion<strlen(cadena);posicion++){
                {printf("%c",cadena[posicion]);}

            //Escribimos el espacio entre las letras
            for(int contador=0;contador<ciclo;contador++){ printf(" ");};
            }

        //Se repetirá el ciclo una vez más
        ciclo++;

        _sleep(250);
        }


        //si la cadena con los espacios >80, los borramos y volvemos a empezar


        else {ciclo=0;}
    }
    return(0);


}








