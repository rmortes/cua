//Incluimos la librerias
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>


int main(void){

    //Definimos las variables que vamos a necesitar
    int i, i2, num;

    //Pedimos al usuario que introduzca un numero
    printf("Introduce numero de filas <5-10>:");
    scanf("%d", &num);

    //Si el numero introducido no esta en el rango de valores definidos, se solicita de nuevo un numero
    while(num<5 || num>10){
        printf("Numero no valido, vuelva a escribir: \n");
        scanf("%d", &num);
    }

    /*Usando esta instruccion, repetimos el codigo tantas veces como el numero elegido,
      haciendo que salte al siguiente bloque al incrementar en cada repeticion otra variable,
      que al comparar con el numero introducido, si esta variable en menor o igual, se sigue ejecutando.*/
    for(i=1;i<=num;i++){
        //Este apartado en concreto, imprime asteriscos incrementando en 1 en cada repeticion.
        for(i2=1;i2<=i;i2++){
            printf("*");
        }
        //Con esta linea, hacemos el salto de linea, para seguir imprimiendo en una nueva fila
        printf("\n");
    }
    //Aqui hacemos la inversa de la anterior instruccion for
    for(i=num;i>=0;i--){
        for(i2=0;i2<i;i2++){
            printf("*");
        }
        //Y de nuevo saltos de linea
        printf("\n");
    }

    //El programa espera a que el usuario pulse una tecla para cerrar
    system ("pause");
    return 0;
 }
