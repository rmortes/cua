#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int main(void){

    //DECLARAR CADENA

    char cadena[100];

    //PEDIR CADENA AL USUARIO

    printf("Introduzca cadena de menos de 20 caracteres:");gets(cadena);

    //MOSTRAR ERROR EN EL CASO DE QUE NO SE CUMPLA LA CONDICIÓN ANTERIOR

    while (strlen(cadena)>20){
       printf("Error: la cadena es mayor de 20 caracteres\nIntroduzca otra cadena: ");gets(cadena);
    }
    while (strlen(cadena)==0){
       printf("Error: la cadena no puede ser de cero caracteres\nIntroduzca otra cadena: ");gets(cadena);
    }

    //DECLARAR VARIABLES DEL BUCLE

    int extension, contador=0, centro, i;

    //INICIO DEL BUCLE INFINITO

    while (1){

        //BORRAR EL BUCLE EN CADA ITERACIÓN

        system("cls");

        //COLOCAR LA CADENA EN EL CENTRO DE LAS 24 FILAS

        printf("\n\n\n\n\n\n\n\n\n\n\n");

        //DARLE UN VALOR A LA VARIABLE EXTENSIÓN

        extension=strlen(cadena)+((strlen(cadena)-1)*contador);

        if(extension<=80){

            //CENTRAR LA CADENA EN EL CENTRO DE LAS 80 COLUMNAS
            for (centro=40-extension/2;centro>0;centro--){
                printf(" ");
            }

            //INTRODUCIR ESPACIOS ENTRE LAS CADENAS

            for (int posicion=0;posicion<strlen(cadena);posicion++){
                printf("%c",cadena[posicion]);
                for (i=0;i<contador;i++){
                    printf(" ");
                }
            }
            contador++;
            _sleep(250);

        //CUANDO LA CADENA SUPERA LOS 80 CARACTERES PONER EL CONTADOR A O

        }else contador=0;
    }
    return(0);
}
