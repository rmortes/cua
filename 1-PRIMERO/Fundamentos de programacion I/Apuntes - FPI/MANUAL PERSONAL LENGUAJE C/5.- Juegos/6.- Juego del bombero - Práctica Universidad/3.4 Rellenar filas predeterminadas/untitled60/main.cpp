#include <stdio.h>
#include<stdlib.h>
#include<time.h>

#define NFIL 10
#define NCOL 20
#define NADA 2
#define CRUZ 3


void InicializarMatriz(int matriz[NFIL][NCOL],int col[NCOL])
{
    int i,j,k;

    for (i=0;i<NFIL;i++){
        for(j=0;j<NCOL;j++){
            matriz[i][j]=NADA;
        }
    }

    for(i=0;i<NFIL;i++){
        col[i]=rand()%10;
        for(k=0;k<=col[i];k++){    //Se pone k<=a para que también coja la columna 0,
            matriz[i][k]=CRUZ;  //y de esta forma cuando a=0 funcione el bucle for
        }
    }

    return;
}

void Imprimir(int matriz[NFIL][NCOL])
{
    int i,j;

    for (i=0;i<NFIL;i++){
        printf("|");
        for(j=0;j<NCOL;j++){
            switch (matriz[i][j]) {
            case NADA:printf(" ");
                break;
            case CRUZ:printf("X");
                break;
            }
        }
        printf("|\n");
    }

    return;
}

void Cambio(int matriz[NFIL][NCOL],int col[NCOL],int fila){

    col[fila]++;

    matriz[fila][col[fila]]=CRUZ;

    return;
}

int main()
{
    srand(time(NULL));

    int matriz[NFIL][NCOL],col[NCOL],fila;

    InicializarMatriz(matriz,col);
    Imprimir(matriz);

    do{
        printf ("Elige una fila: ");
        scanf("%d",&fila);

        system("cls");

        Cambio(matriz,col,fila);

        Imprimir(matriz);

    }while (col[fila]<NCOL-1);

    return 0;
}

