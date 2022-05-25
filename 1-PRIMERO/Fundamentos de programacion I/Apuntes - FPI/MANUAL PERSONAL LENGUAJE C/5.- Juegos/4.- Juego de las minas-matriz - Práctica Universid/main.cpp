#include <stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

#define NFIL 20
#define NCOL 16

#define PERSONA 1
#define MINA 2
#define NADA 3
#define MUERTO 4
#define NMINAS 20


void InicializarMatriz(int matriz[NFIL][NCOL], int x, int y){

    int i,j,centinela;

    for(i=0;i<NFIL;i++){
        for(j=0;j<NCOL;j++){
            matriz[i][j]=NADA;
        }
    }

    matriz[y][x]=PERSONA;



    for (i=0;i<NMINAS;i++){

        centinela=0;

        while(centinela==0){

            int a=rand()%NFIL;
            int b=rand()%NCOL;

            if(matriz[a][b]==NADA){
                matriz[a][b]=MINA;
                centinela=1;
            }
        }
     }
    return;
}


void Imprimir(int matriz[NFIL][NCOL])
{
    for(int i=0;i<NFIL;i++){
        printf("|");
        for(int j=0;j<NCOL;j++){
            switch (matriz[i][j]) {
            case PERSONA:
                printf("U");
                break;
            case MINA:
                printf("M");
                break;
            case NADA:
                printf(" ");
                break;
            case MUERTO:
                printf("X");
                break;
            }
        }
        printf("|\n");
    }
    return;
}

void MovimientoyComprobacion(int matriz[NFIL][NCOL],int *x,int *y,int *perdido){

    getchar();

    system("cls");

    matriz[*y][*x]=NADA;

    int azar=rand()%4;
    switch (azar) {
    case 0:
        *x=*x+1;//No admite *x=*x++;
        break;
    case 1:
        *x=*x-1;
        break;
    case 2:
        *y=*y+1;
        break;
    case 3:
        *y=*y-1;
        break;
    }

    if(matriz[*y][*x]==MINA){
        matriz[*y][*x]=MUERTO;
        *perdido=1;
    }
    else
        matriz[*y][*x]=PERSONA;
    return;
}

int main()
{
    srand(time(NULL));

    int matriz[NFIL][NCOL],x,y,perdido;

    /*No se puede poner directamente el valor de x y de y en InicializarMatriz
     porque para ello necesita tener un valor asignado en la función int main*/

    y=NFIL/2;
    x=NCOL/2;

    InicializarMatriz(matriz,x,y);

    Imprimir(matriz);

    perdido=0;//Pienso que los centinelas se les debe dar valor antes del while


    //Se pone NFIL-1 y NCOL-1 porque ejemplo: si son 10 filas, van desde 0 a 9
    while(matriz[y][x]!=MUERTO && y>0 && y<NFIL-1 && x>0 && x<NCOL-1)
    {
        MovimientoyComprobacion(matriz,&x,&y,&perdido);

        Imprimir(matriz);
    }

    printf("\n\n");

    if(perdido==0)
        printf("Has ganado");
    else
        printf("Has perdido");

    printf("\n\n");

    return 0;
}
