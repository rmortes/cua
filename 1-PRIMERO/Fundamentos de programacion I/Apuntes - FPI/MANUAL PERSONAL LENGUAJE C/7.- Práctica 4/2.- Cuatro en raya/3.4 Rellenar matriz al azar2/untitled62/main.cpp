#include <stdio.h>
#include<time.h>
#include<stdlib.h>

#define N 5
#define NADA 1
#define CRUZ 2
#define CIRCULO 3


void Inicializarmatriz(int matriz[N][N]){

    int i,j;

    for (i=0;i<N;i++){
        for(j=0;j<N;j++){
            matriz[i][j]=NADA;
        }
    }

    return;
}

void Imprimirmatriz(int matriz[N][N]){

    int i,j;

    for (i=0;i<N;i++){
        printf("|");
        for(j=0;j<N;j++){
            switch (matriz[i][j]) {
            case NADA: printf(" ");
                break;
            case CRUZ: printf("X");
                break;
            case CIRCULO: printf("0");
                break;
            }
        }
        printf("|\n");
    }

    return;
}

int Azar(int matriz[N][N],int jugador){

    int a,b,centinela=0;

    while(centinela==0){

        a=rand()%N;
        b=rand()%N;

        if (matriz[a][b]==NADA){
            if (jugador==CRUZ)
                matriz[a][b]=CRUZ;

            else
                matriz[a][b]=CIRCULO;

            centinela=1;
        }
    }

    return jugador;
}


int main()
{
    srand(time(NULL));

    int matriz[N][N],contador=0,jugador=CRUZ;

    Inicializarmatriz(matriz);

    Imprimirmatriz(matriz);


    while(contador<N*N){

        getchar();

        system("cls");

        Azar(matriz,jugador);

        contador++;

        Imprimirmatriz(matriz);

        if(jugador==CRUZ)
            jugador=CIRCULO;
        else
            jugador=CRUZ;

    }

    printf("\n\n");

    return 0;


}
