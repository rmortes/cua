#include <time.h>
#include <conio.h>
#include<stdio.h>
#include <string.h>
#include <stdlib.h>


int main(void){
    srand(time(NULL));
    //definimos las variables
    int a;
    int tirada=0;
    char posicion[11]="0123456789";
    char visual[11]="??????????";
    char oculto[11]="__________";
    printf("Ejercicio 2-Practica 2\n----------------------\n");

    do{//Filtrar el numero de minas
        printf("Introduzca el numero de minas(1-3): ");
        scanf("%d",&a);
        getchar();
        if(a<1 || a>3){
            printf("Error.\n");
        }
    }while(a<1 || a>3);

    int p;
    for(int i=1;i<=a;i++){//rellenamos de minas
        do{
            p=rand()%10;
        }while(oculto[p]=='M');
        oculto[p]='M';
    }
    printf("\n\n");

    //imprimimos el juego
    printf("Posicion: ");
    for(int i=0;i<10;i++){
        printf("%c ",posicion[i]);
    }
    printf("\n");

    printf("Casilla : ");
    for(int i=0;i<10;i++){
        printf("%c ",visual[i]);
    }
    printf("\n");

    int parar=0;//variable centinela
    while(parar==0){//centinela
        int t;//variable de tirada
        do{
            printf("\nIntroduzca casilla (0-9): ");
            scanf("%d",&t); getchar();
            if(t<0 || t>9){
                printf("Error.\n");
            }
        }while(t<0||t>9);

        int distmin=10;
        for(int i=0; i<10; i++){
            if(oculto[i]=='M'){
                int d=t-i;
                if(d<0){
                    d=(-d);
                }
                if(d<distmin){
                    distmin=d;
                }
            }
        }
        if(distmin==0){//Ha encontrado una mina
            visual[t]='M';
            //imprimimos el panel
            printf("Posicion: ");
            for(int i=0;i<10;i++){
                printf("%c ",posicion[i]);
            }
            printf("\n");

            printf("Casilla : ");
            for(int i=0;i<10;i++){
                printf("%c ",visual[i]);
            }
            printf("\n\n");

            parar=1;
        }else{
            visual[t]=distmin+'0';

            //imprimimos el panel
            printf("Posicion: ");
            for(int i=0;i<10;i++){
                printf("%c ",posicion[i]);
            }
            printf("\n");

            printf("Casilla : ");
            for(int i=0;i<10;i++){
                printf("%c ",visual[i]);
            }
            printf("\n");

            tirada++;
            if(tirada==(10-a)){
                parar=2;
            }
        }

    }//del while

    if(parar==1){
        printf("HAS PERDIDO.LO SIENTO! :( \n");
    }
    if(parar==2){
        printf("HAS GANADO.ENHORABUENA! :) \n");
    }
    getche();
    return(0);
}
