#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

#define N 9

void InicializarMatriz(int matriz[N][N]){
    int i,j;
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            matriz[i][j]=0;
        }
    }
    return;
}

void Imprimir(int matriz[N][N]){
    int i,j;

    printf("    JUEGO DEL SUDOKU\n\n");

    for(i=0;i<N;i++){
        if(i%3==0){
            for(j=0;j<25;j++)
                printf("-");
            printf("\n");
        }
        for(j=0;j<N;j++){
            if(j%3==0) printf("| ");
            if(matriz[i][j]=='0')
                printf(" ");//Es un doble espacio
            else
                printf("%d ",matriz[i][j]);
        }
        printf("|\n");
    }

    for(j=0;j<25;j++)
        printf("-");
    printf("\n\n");

    return;
}


//solicita un número entre 1 y N
int PedirNumero(int a,int b){

    int n;

    do{
        scanf("%d",&n);
        if(n<a || n>b){
            printf("Error: introduzca numero de 1 a %d :",N);
        }
    }while(n<a || n>b);

    return n;
}

//comprueba si una tirada es válida
int TiradaValida(int matriz[N][N],int i1, int j1, int valor){
    int i,j;
    int valido=1;
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            if(matriz[i][j]==valor){
                //coincide en fila o columna
                if(i==i1 || j==j1)
                    valido=0;
                //coincide en cuadrante
                if(i/3==i1/3 && j/3==j1/3)
                    valido=0;
            }
        }
    }
    return valido;
}
//Función para tirar
void TiraryComprobar(int matriz[N][N],int *contador){

    int valido=0;

    printf("Introduzca fila (1-9): ");
    int i=PedirNumero(1,9);
    i--; //Se resta uno por la numeracion de vectores

    printf("Introduzca columna (1-9): ");
    int j=PedirNumero(1,9);
    j--; //Se resta uno por la numeracion de vectores

    printf("Introduzca valor (1-9): ");
    int v=PedirNumero(1,9);

    valido=TiradaValida(matriz,i,j,v);

    if(valido==1){
        matriz[i][j]=v;
        *contador=*contador+1;
    }
    else{
        printf("Error: tirada no valida\n");
        getche();
    }

    return;
}

void Problema(void){

    int matriz[N][N],contador=0;

    InicializarMatriz(matriz);

    Imprimir(matriz);

    while(contador<N*N){

        TiraryComprobar(matriz,&contador);

        system("cls");/*Se pone aquí porque al finalizar la comprobación, si la entrada
                        no es válida, aparece un mensaje que lo advierte*/

        Imprimir(matriz);
    }

    printf("Felicidades! Has completado el sudoku!\n");
    return;
}

int main(void){

    Problema();

    getche();

    return(0);
}
