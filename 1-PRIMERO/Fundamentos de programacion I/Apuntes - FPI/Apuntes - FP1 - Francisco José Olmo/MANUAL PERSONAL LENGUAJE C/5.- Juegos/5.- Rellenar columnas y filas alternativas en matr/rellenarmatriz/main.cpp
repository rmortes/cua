#include <stdio.h>
#include<stdlib.h>
#include<time.h>

#define N 10

#define NADA 2
#define CRUZ 3
#define CIRCULO 4

void InicializarMatriz(int matriz[N][N],int fil[N],int col[N])
{
    int i,j;

    for (i=0;i<N;i++)
        fil[i]=9;

    for (i=0;i<N;i++)
        col[i]=0;

    for (i=0;i<N;i++){
        for(j=0;j<N;j++){
            matriz[i][j]=NADA;
        }
    }
    return;
}

void CambioColumna(int matriz[N][N],int fil[N],int columna){

    matriz[fil[columna]][columna]=CRUZ;

    fil[columna]--;

    return;
}

void CambioFila(int matriz[N][N],int col[N],int fila){

    matriz[fila][col[fila]]=CIRCULO;

    col[fila]++;

    return;
}

void Imprimir(int matriz[N][N])
{
    int i,j;

    for (i=0;i<N+2;i++){
        printf("-");}
    printf("\n");

    for (i=0;i<N;i++){
        printf("|");

        for(j=0;j<N;j++){
            switch (matriz[i][j]) {
            case NADA:printf(" ");
                break;
            case CRUZ:printf("X");
                break;
            case CIRCULO:printf("O");
                break;
            }
        }
        printf("|\n");
    }

    for (i=0;i<N+2;i++){
        printf("-");}
    printf("\n");

    return;
}


int main()
{
    int matriz[N][N],fil[N],col[N],fila,columna;

    InicializarMatriz(matriz,fil,col);

    Imprimir(matriz);

    do
    {
        printf ("Elige una columna: ");
        scanf("%d",&columna);

        system("cls");

        CambioColumna(matriz,fil,columna);

        Imprimir(matriz);

        if(fil[columna]>0) //Para que cuando sea 0 pase por directamente por el while
        {
            printf ("Elige una fila: ");
            scanf("%d",&fila);

            system("cls");

            CambioFila(matriz,col,fila);

            Imprimir(matriz);
        }

    }while (fil[columna]>=0 && col[fila]<=9);

    return 0;
}
