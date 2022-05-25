#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main (void) {
    srand(time(NULL));

    int a,b = rand()%10+1;




    //Comienza el programa y el programa piensa un numero del 1 al 10 aleatoriamente.

    printf("Fundamentos de Programacion I. Practica 1. Ejercicio 3\n---------------------------------------------------------\n");



    //Solicitaremos un numero del 1 al 10 al usuario

    printf("Introducir numero del 1 al 10:");
    scanf("%d", &a);
    if (a>10){
        printf("Error, el numero introducido es mayor a los permiditos.\n");}

    else {




    //Si el numero que hemos introducido es igual al numero aleatorio, se ganará el juego

    if (a==b)
       {printf("ACERTASTE!\n"); return 0; }

    else

        //Nos da los posibles errores para la primera posibilidad
        {    if (a>b)
             {printf("No acertaste: El numero introducido es mayor\n");}
             else
             {printf("No acertaste: El numero introducido es menor\n");}
         }





    //le permitimos al usuario dar una segunda oportunidad

    printf("Tienes otra oportunidad:");
    scanf("%d", &a);

    if (a==b)
       {printf("ACERTASTE!\n"); return 0; }

    else
        //Nos da los posibles errores para la segunda posibilidad
        {     if (a>b)
              {printf("No acertaste: El numero introducido es mayor\n");}
              else
              {printf("No acertaste: El numero introducido es menor\n");}
        }





    //Si el usuario aun no ha acertado, le daremos una ultima oportunidad

    printf("Ultima oportunidad, SUERTE!!:");
    scanf("%d", &a);

    if (a==b)
       {printf("ACERTASTE!\n"); }
    else
        //Nos dira que hemos perdido, y la solución
       {printf("PERDISTE! :( \nEl resultado era: %d\n", b); }

        }
        return 0;

}
