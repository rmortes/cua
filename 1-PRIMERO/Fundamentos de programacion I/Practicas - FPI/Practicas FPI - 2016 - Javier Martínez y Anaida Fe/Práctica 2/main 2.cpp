//Fundamentos de Programacion 1. Practica 2. Ejercicio 2: Círculo
#include<stdio.h>
#include<stdlib.h>

int main (void){

    //Decalramos las variables con las que nuestro bucles irán contando.
    int ancho, alto, radio;

    while (1){

        //Primer bucle para no sobrepasar el radio, cuando este termine, empezaremos de 0, así que borraremos la pantalla
        for(radio=1; radio<12; radio++){
            system("cls");

            //Segundo bucle para no sobrepasar el alto del CMD
            for(alto=1; alto<24;alto++){

                //Tercer bucle para no pasar de los 80 de ancho del CMD
                for(ancho=1; ancho<80; ancho++){

                    //Ecuación de una circunferencia centrada en la mitad de la pantalla según los datos introducidos en el CMD
                    if(((ancho-40)*(ancho-40))+((alto-12)*(alto-12))>radio*radio){
                        printf(" ");
                    }else{
                            printf("*");}
                        }
                printf("\n");
                    }
                }
            }






    return 0;
}
