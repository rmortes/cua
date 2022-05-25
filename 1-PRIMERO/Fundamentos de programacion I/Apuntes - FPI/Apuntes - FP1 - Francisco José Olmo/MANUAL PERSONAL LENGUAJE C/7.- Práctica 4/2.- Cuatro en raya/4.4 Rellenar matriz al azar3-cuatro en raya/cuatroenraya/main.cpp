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



void Cambio(int matriz[N][N],int jugador,int *iteracion,int *f,int *c){

    int centinela=0;

    while(centinela==0){

        *f=rand()%N;
        *c=rand()%N;

        if (matriz[*f][*c]==NADA){
            if (jugador==CRUZ)
                matriz[*f][*c]=CRUZ;

            else
                matriz[*f][*c]=CIRCULO;

            centinela=1;
        }
    }

    *iteracion=*iteracion+1;

    return;
}

void Comprobacion(int matriz[N][N],int *contador,int f,int c,int valor){

    int a=0,b=0,x=0,y=0;

    switch (valor) {
    case 1:
        a=1;
        break;
    case 2:
        b=1;
        break;
    }

    *contador=1;
    x=a; y=b;

    while((c+x<N && c+x>=0 && f+y<N && f+y>=0) && matriz[f][c]==matriz[f+y][c+x]){
        x=x+a;
        y=y+b;
        *contador=*contador+1;
    }

    a=-a;
    b=-b;
    x=a; y=b;

    while((c+x<N && c+x>=0 && f+y<N && f+y>=0) && matriz[f][c]==matriz[f+y][c+x]){
        x=x+a;
        y=y+b;
        *contador=*contador+1;
    }
    return;
}



int main()
{
    srand(time(NULL));

    int matriz[N][N],iteracion=0,jugador=CRUZ,contador1=1,contador2=1,f=0,c=0;

    Inicializarmatriz(matriz);

    Imprimirmatriz(matriz);


    while(iteracion<N*N && contador1<4 && contador2<4){

        getchar();

        system("cls");

        Cambio(matriz,jugador,&iteracion,&f,&c);

        // Horizontal=1  Vertical=2
        Comprobacion(matriz,&contador1,f,c,1);

        Comprobacion(matriz,&contador2,f,c,2);

        Imprimirmatriz(matriz);

        if(jugador==CRUZ)
            jugador=CIRCULO;
        else
            jugador=CRUZ;

    }

    //Se pone > porque pueden ser 5 en raya

    if (contador1>=4 || contador2>=4){

        printf("\n\n");

        //El jugador se pone al contrario porque se cambia al final del while
        printf("El juego ha terminado: ganan  ");

        if (jugador==CIRCULO)
            printf("las cruces\n");
        else
            printf("los circulos \n");
    }
    else
        printf("El juego ha terminado");


    printf("\n\n");

    return 0;

}
