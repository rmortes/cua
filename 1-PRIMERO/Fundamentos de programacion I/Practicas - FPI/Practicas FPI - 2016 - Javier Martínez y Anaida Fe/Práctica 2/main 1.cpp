//Fundamentos de Programacion 1. Practica 2. Ejercicio 1: Numeros crecientes.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (void){


    //Empezamos mostrando un encabezado a modo decorativo
    printf("Fundamentos de Programacion 1 - Practica 2/Ejercicio 1. \n");
    printf("------------------------------------------------------- \n\n");

    //Pedimos al usuario el numero de numeros que quiere mostrar y comprobamos que este se pueda mostrar
    int N;
    do {
        printf("Introduzca un numero mayor que 0: ");
        scanf("%d",&N);
        if(N<=0){
            printf("Error, el numero introducido es menor que 0.\n");
        }
    }while(N<=0);



    int numero=12;
    int contador=0;

    //Creamos el bucle que ira mostrando solo el numero de numeros pedido
    while( contador< N){

    //Pasamos el numero a cadena para poder comprobar sus cifras una por una
    char numerohechocadena[50];
    sprintf(numerohechocadena, "%d", numero);
    int longitud=strlen(numerohechocadena);
    int creciente=1;


    //creamos el bucle que nos dirá si el numero es creciente o no comparando sus cifras por separado
    for(int i=0;i<longitud-1 && creciente ==1; i++){
        if(numerohechocadena[i]>=numerohechocadena[i+1])
        {creciente=0;}}

        if (creciente==1){

            printf("%d ", numero);
            contador++;
        }
        numero++;
}



return 0;

}
