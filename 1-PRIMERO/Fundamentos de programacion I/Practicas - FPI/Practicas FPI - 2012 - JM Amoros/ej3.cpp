#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

int main (void){
    int A,i,j,intentos,aciertos,puntuacion,puntuacionf;
    char letra;
    A=intentos=aciertos=puntuacion=puntuacionf=0;
    int m[100];
    srand(time(NULL));

    printf("\tjuego de letras\n\t_______________\n\n\n");


    for( i=0;i<99;i++){
        m[i]=(rand()%9)+65;
        if((i%9)==0)printf("\n");
        printf("%c",m[i]);
    }

    do{
        printf("\n");
        printf("introduzca una letra del panel:\n");
        fflush(stdin);
        scanf("%c",&letra);
        for( i=0;i<99;i++){
            if(m[i]==letra){
                m[i]=45;
                aciertos++;
            }

        }
        puntuacion=aciertos*10;
        puntuacionf=puntuacionf+puntuacion;
        printf("%d aciertos,%d puntos conseguidos.%d acumuladoros\n",aciertos,puntuacion,puntuacionf);
        for( i=0;i<99;i++){
            if((i%9)==0)printf("\n");
            printf("%c",m[i]);
        }
        intentos++;
    }while(intentos!=10);
    printf("\n");
    printf("fin del juego");
    getch();

    return(0);
}
