#include <stdio.h>
#include <string.h>

int main(void){

    printf("Practica 1, ejercicio 2\n-----------------------------------------\n");

    //DECLARAR LA CADENA

    char cadena [100];

    //PEDIR UNA CADENA PAR DE MENOS DE 20 CARACTERES AL USUARIO

    printf("Introduzca cadena par de menos de 20 caracteres:");
    gets(cadena);

    //DAR UN ERROR SI LA CADENA ES MAYOR DE 20 CARACTERES O NO ES PAR

    if (strlen(cadena)>20){
        printf("Error, la cadena es de mayor de 20 caracteres\n");
    }
    else{
        if(strlen(cadena)%2!=0){
            printf("Error, la cadena no es par\n");
        }

        //EN EL CASO EN EL QUE LA CADENA CUMPLA LAS CONDICIONES EJECUTAR EL PROGRAMA

        else{
            printf("\n\n\n\n\n\n\n\n\n\n\n\n                              ");

            switch(strlen(cadena)){

            case 20:
                break;
            case 18:
                printf(" ");
                break;
            case 16:
                printf("  ");
                break;
            case 14:
                printf("   ");
                break;
            case 12:
                printf("    ");
                break;
            case 10:
                printf("     ");
                break;
            case 8:
                printf("      ");
                break;
            case 6:
                printf("       ");
                break;
            case 4:
                printf("        ");
                break;
            case 2:
                printf("         ");
                break;
            case 0:
                printf("          ");
                break;
            }
            puts(cadena);
            printf("\n\n\n\n\n\n\n\n\n\n\n\n");
        }
    }
    return 0;
}
