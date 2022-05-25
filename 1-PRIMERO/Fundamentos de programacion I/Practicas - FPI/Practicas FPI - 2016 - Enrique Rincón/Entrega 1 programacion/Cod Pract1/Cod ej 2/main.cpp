//Practica1 Ejercicio2
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
int main(void){
    //Definimos variables
    int dia,mes,anyo,cuota,mes2,anyo2;
    //Definimos cadenas
    char mes3[50];
    printf("Introduzca fecha de inicio de prestamo dd/mes/anyo:");
    scanf("%d/%d/%d",&dia,&mes,&anyo);
    getchar();
    //Restrigimos los valores usando el año fiscal
    if (dia>30||mes>12||anyo<1900||anyo>2100){
        printf("La fecha es incorrecta\n");
    }else{
        printf("Introducza el numero de cuotas:");
        scanf("%d",&cuota);
        getchar();
        if (cuota<0||cuota>1200){
            printf("El numero de cuotas es incorrecto\n");
        }else{
            anyo2=(anyo*12+mes-1+cuota)/12;
            mes2=(anyo*12+mes-1+cuota)%12;
            switch (mes2) {
            case 0:
                strcpy(mes3,"Enero");
                break;
            case 1:
                strcpy(mes3,"Febrero");
                break;
            case 2:
                strcpy(mes3,"Marzo");
                break;
            case 3:
                strcpy(mes3,"Abril");
                break;
            case 4:
                strcpy(mes3,"Mayo");
                break;
            case 5:
                strcpy(mes3,"Junio");
                break;
            case 6:
                strcpy(mes3,"Julio");
                break;
            case 7:
                strcpy(mes3,"Agosto");
                break;
            case 8:
                strcpy(mes3,"Septiembre");
                break;
            case 9:
                strcpy(mes3,"Octubre");
                break;
            case 10:
                strcpy(mes3,"Noviembre");
                break;
            case 11:
                strcpy(mes3,"Diciembre");
                break;
            }
            printf("El prestamo finaliza el %d de %s de %d\n",dia,mes3,anyo2);
        }
    }

    return 0;
}
