//Fundamentos de Programación 1. Práctica 1. Ejercicio 1: Relaciones entre personas.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (void){
    
    //Empezamos mostrando un encabezado a modo decorativo
    printf("Fundamentos de Programacion 1 - Practica 1/Ejercicio 1. \n");
    printf("------------------------------------------------------- \n\n");
    
    //Declaramos las variables cadenas, para cada persona, y para cada parte de su nombre completo
    char N1 [10] , PA1 [10] , SA1 [10];
    char N2 [10] , PA2 [10] , SA2 [10];
    
    
    //Pedimos que introduzca los datos de la primera persona y los guardamos
    printf("introduce el nombre completo de la primera persona: ");
    
    scanf("%s", N1);
    scanf("%s", PA1);
    scanf("%s", SA1);
    
    strupr(N1);  strupr(PA1);  strupr(SA1);
    
    //Pedimos que introduzca los datos de la segunda persona y los guardamos
    printf("introduce el nombre completo de la segunda persona: ");
    
    scanf("%s", N2);
    scanf("%s", PA2);
    scanf("%s", SA2);
    
    strupr(N2);  strupr(PA2);  strupr(SA2);
    
    
    //comenzamos el proceso de identificacion de relación entre personas mediante condicionales
    
    int compnom = strcmp(N1, N2);
    int compa1 = strcmp(PA1, PA2);
    int compa2 = strcmp(SA1, SA2);
    int compaprimos12 = strcmp(PA1, SA2);
    int compaprimos21 = strcmp (PA2, SA1);


    //Mostraremos los nombres y apellidos de las dos personas y después su relacion
    printf("%s %s %s y %s %s %s ", N1, PA1, SA1, N2, PA2, SA2);


    //Si son la misma persona
    if (compnom==0 && compa1==0 && compa2==0){
        printf("son la misma persona.\n");
               
    }else{
        
        //Son hermanos
        if(compa1==0 && compa2==0){
            printf("%s %s %s y %s %s %s son hermanos/as.\n", N1, PA1, SA1, N2, PA2, SA2);}
        

        else{
            
            //Son primos
            if(compa1==0 || compa2==0 || compaprimos12==0 || compaprimos21==0){
                printf("%s %s %s y %s %s %s son primos/as.\n", N1, PA1, SA1, N2, PA2, SA2);}
            
            else {
                
                //Son tocayos
                if(compnom==0){
                    printf("%s %s %s y %s %s %s son tocayos/as.\n", N1, PA1, SA1, N2, PA2, SA2); }
                
                //No tienen relacion
                else {
                    printf("%s %s %s y %s %s %s no tienen relacion.\n", N1, PA1, SA1, N2, PA2, SA2);
                    
                }
                
                
            }
            
        }
    }
    
    printf("\n");
    //Finalizamos el programa
    return 0;
}
