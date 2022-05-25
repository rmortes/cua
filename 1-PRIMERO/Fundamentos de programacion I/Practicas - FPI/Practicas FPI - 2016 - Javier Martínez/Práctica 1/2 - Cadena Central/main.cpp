#include<stdio.h>
#include<string.h>

int main (void) {
char (cadena) [100];


    printf("Practica 1. Ejercicio 2. Fundamentos de Programacion 1. \n--------------------------------------------------------------------------------\n");

    //Se inicia el programa y pedimos al usuario introducir una cadena par de menos de 20 caracteres

    printf("Introduzca cadena par de menos de 20 caracteres: ");
    gets(cadena);

    //Abrimos una condicion para no permitir que la cadena sea mayor a 20 caracteres, en caso contrario se continua

    if (strlen(cadena)>20)
       {printf("Error: El numero de caracteres es incorrecto\n"); }
    else

        //Abrimos otra condición para no permitir que el numero de caracteres sea impar, en caso contrario se continua

       {if(strlen(cadena)%2!=0)
          {printf("Error: El numero de caracteres no es par\n"); }
        else

            //Cumplidas las condiciones, se procede a situar la cadena a 12 filas abajo del inicio del programa

    {printf("\n\n\n\n\n\n\n\n\n\n\n\n");

            //Se procede a hacer la resta entre la mitad de la posible longitud de pantalla y la londitud de la cadena en la mitad

            switch (40-strlen(cadena)/2) {

            case 40:
                printf("                                         ");
                break;

            case 39:
                printf("                                       ");
                break;

            case 38:
                printf("                                      ");
                break;

            case 37:
                printf("                                     ");
                break;

            case 36:
                printf("                                    ");
                break;

            case 35:
                printf("                                   ");
                break;

            case 34:
                printf("                                  ");
                break;

            case 33:
                printf("                                 ");
                break;

            case 32:
                printf("                                ");
                break;

            case 31:
                printf("                               ");
                break;

            case 30:
                printf("                              ");
                break;



            //Finalmente se introduce la cadena y se vuelven a introducir el resto de saltos del línea.

            } printf("%s", cadena);
        printf("\n\n\n\n\n\n\n\n\n\ns\n\n");
            }

            }


    return 0;
}
