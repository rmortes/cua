#include <stdio.h>
#include <string.h>

/*PRÁCTICA 1, EJERCICIO 2*/

int main(void){
    /*Recoger datos Inicio*/

    char nombre[40],apellido1[40],apellido2[40];
    char nombre_[40],apellido1_[40],apellido2_[40];
    printf("Practica 1 de FP1. Ejercicio 2\n");
    printf("------------------------------\n");
    printf("Introduzca el nombre completo. Si su nombre es compuesto, separelo con un guion bajo.\n\n");
    scanf("%s",nombre);
    scanf("%s",apellido1);
    scanf("%s",apellido2);
    printf("\n");

    printf("Introduzca el segundo nombre completo. Si su nombre es compuesto, separelo con un guion bajo.\n\n");
    scanf("%s",nombre_);
    scanf("%s",apellido1_);
    scanf("%s",apellido2_);
    printf("\n");


    /*Recoger datos Fin*/
    /*Calcular y presentar datos Inicio*/
    if(strcmp(nombre,nombre_)==0 && strcmp(apellido1,apellido1_)==0 && strcmp(apellido2,apellido2_)==0){
        printf("%s %s %s y %s %s %s son la misma persona.\n",nombre,apellido1,apellido2,nombre_,apellido1_,apellido2_);

    }else{
        if(strcmp(apellido1,apellido1_)==0 && strcmp(apellido2,apellido2_)==0){
           printf("%s %s %s y %s %s %s son hermanos.\n",nombre,apellido1,apellido2,nombre_,apellido1_,apellido2_);
        }else{
            if(strcmp(apellido1,apellido1_)==0 || strcmp(apellido1,apellido2_)==0 || strcmp(apellido2,apellido2_)==0 || strcmp(apellido2,apellido1_)==0){
                printf("%s %s %s y %s %s %s son primos.\n",nombre,apellido1,apellido2,nombre_,apellido1_,apellido2_);
            }else{
                if(strcmp(nombre,nombre_)==0){
                    printf("%s %s %s y %s %s %s son tocayos.\n",nombre,apellido1,apellido2,nombre_,apellido1_,apellido2_);
                }else{
                    printf("%s %s %s y %s %s %s no tienen ninguna relacion.\n", nombre, apellido1,apellido2,nombre_,apellido1_,apellido2_);
                }
            }
      }

        /*Fin ejercicio*/
        return 0;
    }
}
