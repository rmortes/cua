//Practica2 Ejercicio1
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
int main(void){
    int n,corto;
    char repetir [10];
    //Repetir programa
    do{
        //Filtro numeros permitidos
        do{
            printf("Introduzca un numero dentro del conjuto de los Naturales, que sea diferente de 0:");
            scanf("%d",&n);
            if (n<1){
                printf("Error: numero incorrecto \n");
            }
        }while(n<1);
        char numero[100];
        int a=10;
        int cont=0,finalizado=0;
        //numero de numeros imprimidos "cont"
        while(cont<n&&finalizado==0){
            sprintf(numero,"%d",a);
            int total=strlen(numero);
            corto=0;
            //verifica si un numero es creciente
            for(int b=0;b<total-1&&corto==0;b++){
                if(numero[b]>=numero[b+1]){
                    corto=1;
                }
            }
            if(corto==0){
                printf("%s ",numero);
                cont++;
                if(strcmp(numero,"123456789")==0){
                    printf("\nYa no hay mas numeros crecientes");
                    printf("\nNuemero maximo de numero crecientes:%d",cont);
                    finalizado=1;
                }
            }
            a++;

        }
        printf("\nDeseas volver a utilizar la aplicacio?Y/N:");
        scanf("%s",repetir);
        strupr(repetir);
    }while(strcmp(repetir,"N")!=0);
    return 0;
}
