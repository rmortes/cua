#include <stdio.h>

int main (void) {

    int numerosamostrar,inicial=1,capicua;

    printf("Ejercicio 1. Practica 2. Fundamentos de Programacion I. \n--------------------------------------------------------------------------------\n");


    //Comienza el programa pidiendo que se introduzca un número mayor a 0

    printf("Introducir numero mayor que 0: ");
    scanf("%d", &numerosamostrar);
    getchar();

    //hacemos que de error en caso de introducir un numero menor o igual a 0 y se vuelve a solicitar

    while (numerosamostrar<=0)
    { printf("Error, numero menor o igual a 0. Introducir numero mayor que 0: ");
      scanf("%d", &numerosamostrar);
      getchar();                     }

   //Creamos un bucle para los numeros a mostrar mayores que 0

    while(numerosamostrar>0)
    {
       //Declaramos la varaiable que supuestamente será capicua
        capicua=inicial;
       //Declaramos la variable desde donde se va a iniciar a contar numeros invertidos
        int inverso=0;

        //Mediante operaciones matematicas va haciendo el invertid del numero inicial

        while(capicua>0)
        { inverso=inverso*10+capicua%10;
          capicua=capicua/10;

          //Si ese invertido es igual al numero inicial, lo mostraremos

          if(inicial==inverso)
          {printf("%d  ",inverso);
          //Como ya hemos mostrado un capicua, se restara uno al numero de capicuas que queremos mostrar
           numerosamostrar--;
          }


          /* Es decir, solo se mostraran los numeros cuyo invertido sea igual al original
           *
           *  Si el inicial es 12021, su invertido sera también 12021, con lo que el numero es capicua
           * pero si el numero es 1231 el invertido seria 1321, con lo que no se mostraría la no ser capicua */


         }
        //Se le suma un numero al inicial, para seguir calculdo posibles capicuas
        inicial++;

    }

    printf("\n\n");
 return(0);
}
