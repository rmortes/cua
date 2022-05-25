//Incluimos las librerias
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

/* Este es el programa completo. Con el,
se realizan la serie de funciones propuestas
en el ejercicio 1, de la practica 1*/

int main(void){

/* 1. Aqui definimos los datos y que tipo de
    valores van a manejar. En este caso tenemos 3
    datos, que pueden contener numeros enteros*/

    int NUMERO1, NUMERO2, NUMERO3;

    system("cls");

/* 2. En este segundo punto, imprimimos dos preguntas,
    sobre los valores de dos numeros enteros, y estos
    se guardan en 2 de los datos definidos, y la suma
    de estos se guarda en el tercer dato*/

    printf("Primer numero: ");
    scanf("%d", &NUMERO1);
    printf("Segundo numero: ");
    scanf("%d", &NUMERO2);
    NUMERO3=NUMERO1+NUMERO2;

    system("cls");

/* 3. Ahora valoramos el resultado, manejando
    el valor del dato para saber si es par o no.
    Bajo estas condiciones, el siguiente bloque if
    hara una funcion u otra segun sea par o no el
    resultado de la suma. */

    if((NUMERO3/2)*2==NUMERO3){
        printf("\n\n\n\n%18c***********************************************\n", ' ');
        printf("%18c*  Bienvenido a Fundamentos de programacion 1 *\n", ' ');
        printf("%18c*\t\tCurso 2011-2012        \t\t*\n", ' ');
        printf("%18c***********************************************\n", ' ');
        printf("%38c%d + %d = %d", ' ',NUMERO1,NUMERO2,NUMERO3);

    }else{
        printf("***********************************************\n");
        printf("*  Bienvenido a Fundamentos de programacion 1 *\n");
        printf("*");
        printf("%14cCurso 2011-2012", ' ');
        printf("%16c*\n", ' ');
        printf("***********************************************\n");
        printf("%20c%d + %d = %d", ' ',NUMERO1,NUMERO2,NUMERO3);

    }

/* 4. Finaliza el programa, se debe hacer
    pulsar en alguna tecla para cerrar. */

    getche();
       return (0);

}
