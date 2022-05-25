//Practica1 Ejercicio1
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int main(void){
    //Establecemos las siguientes cadenas
    char Nombre1[30],Apellido11[30],Apellido12[30];
    char Nombre2[30],Apellido21[30],Apellido22[30];
    //Pasamos los datos a mayusculas
    printf("Introduzca un nombre completo,si su nombre es compuesto utilice \"_\":");
    scanf("%s",Nombre1);
    getchar();
    strupr(Nombre1);
    scanf("%s",Apellido11);
    getchar();
    strupr(Apellido11);
    scanf("%s",Apellido12);
    getchar();
    strupr(Apellido12);
    printf("Introduzca un segundo nombre completo:");
    scanf("%s",Nombre2);
    getchar();
    strupr(Nombre2);
    scanf("%s",Apellido21);
    getchar();
    strupr(Apellido21);
    scanf("%s",Apellido22);
    getchar();
    strupr(Apellido22);
    //Comparamos las parejas de datos
    int comp1 = strcmp(Nombre1,Nombre2);
    int comp2 = strcmp(Apellido11,Apellido21);
    int comp3 = strcmp(Apellido12,Apellido22);
    int comp4 = strcmp(Apellido11,Apellido22);
    int comp5 = strcmp(Apellido12,Apellido21);
    //Establecemos las condiciones para cada posible resultado
    if(comp1==0 && comp2==0 && comp3==0){
        printf("Resultado:%s %s %s y %s %s %s son la misma persona\n",Nombre1,Apellido11,Apellido12,Nombre2,Apellido21,Apellido22);
    }else{
        if(comp1!=0 && comp2==0 && comp3==0){
            printf("Resultado:%s %s %s y %s %s %s son hermanos\n",Nombre1,Apellido11,Apellido12,Nombre2,Apellido21,Apellido22);
        }else{
            if(comp2==0 || comp3==0 || comp4==0 || comp5==0){
                printf("Resultado:%s %s %s y %s %s %s son primos\n",Nombre1,Apellido11,Apellido12,Nombre2,Apellido21,Apellido22);
            }else{
                if(comp1==0){
                    printf("Resultado:%s %s %s y %s %s %s son tocayos\n",Nombre1,Apellido11,Apellido12,Nombre2,Apellido21,Apellido22);
                }else{
                    printf("Resultado:%s %s %s y %s %s %s no poseen relacion\n",Nombre1,Apellido11,Apellido12,Nombre2,Apellido21,Apellido22);
                }
            }
        }
    }

    return 0;
}
