//Incluimos las librerias
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

int main(void){
    //Definimos las variables
    int a;

    //Pedimos al usuario que introduzca un valor y este sera asignado a la variable definida
    printf ("Introduce nota: ");
    scanf ("%d", &a);

    //Con esta instruccion conseguimos distintas respuestas definidas a valores concretos
    switch (a){
    //Definimos que debe ejecutar segun el valor de la variable
    case 0:
        printf ("Tu nota es: SUSPENSO \n\n");
        break;
    case 1:
        printf ("Tu nota es: SUSPENSO \n\n");
        break;
    case 2:
        printf ("Tu nota es: SUSPENSO \n\n");
        break;
    case 3:
        printf ("Tu nota es: SUSPENSO \n\n");
        break;
    case 4:
        printf ("Tu nota es: SUSPENSO \n\n");
        break;
    case 5:
        printf ("Tu nota es: APROBADO \n\n");
        break;
    case 6:
        printf ("Tu nota es: APROBADO \n\n");
        break;
    case 7:
        printf ("Tu nota es: NOTABLE \n\n");
        break;
    case 8:
        printf ("Tu nota es: NOTABLE \n\n");
        break;
    case 9:
        printf ("Tu nota es: SOBRESALIENTE \n\n");
        break;
    case 10:
        printf ("Tu nota es: MATRICULA DE HONOR \n\n");
        break;
    }
    //El programa se pausa y espera a que el usuario presione una tecla para finalizar
    system ("pause");

    return 0;
   }
