//Una posible solución sería:
//librerías necesarias
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
//tamaño del tablero
#define N 9
//Inicialización del tablero
void Inicializar(int T[N][N]){
    int i,j;
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            T[i][j]=0;
        }
    }
    return;
}
//impresión del tablero
void Imprimir(int T[N][N]){
    int i,j;
    for(i=0;i<N;i++){
        if(i!=0 && i%3==0){
            for(j=0;j<21;j++) printf("-");
            printf("\n");
        }
        for(j=0;j<N;j++){
            if(j!=0 && j%3==0) printf("| ");
            if(T[i][j]=='0') printf(" ");
            else printf("%d ",T[i][j]);
        }
        printf("\n");
    }
    return;
}
//responde si el tablero está o no completo
int Completo(int T[N][N]){
    int i,j;
    int completo=1;
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            if(T[i][j]==0) completo=0;
        }
    }
    return(completo);
}
//solicita un número entre 1 y N
int PedirNumero(void){
    int n;
    do{
        scanf("%d",&n);
        if(N<1 || n>N){
            printf("Error: introduzca numero de 1 a %d :",N);
        }
    }while(n<1 || n>N);
    return(n);
}
//comprueba si una tirada es válida
int TiradaValida(int T[N][N],int i1, int j1, int valor){
    int i,j;
    int valido=1;
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            if(T[i][j]==valor){
                //coincide en fila o columna
                if(i==i1 || j==j1) valido=0;
                //coincide en cuadrante
                if(i/3==i1/3 && j/3==j1/3) valido=0;
            }
        }
    }
    return(valido);
}
//Función para tirar
void Tirar(int T[N][N]){
    //solicitiamos fila, columna y valor
    printf("Introduzca fila (1-9): ");
    int i=PedirNumero();
    i--; //se resta uno por la numeracion de vectores
    printf("Introduzca columna (1-9): ");
    int j=PedirNumero();
    j--; //se resta uno por la numeracion de vectores
    printf("Introduzca valor (1-9): ");
    int v=PedirNumero();
    if(TiradaValida(T,i,j,v)==1){
        T[i][j]=v;
    }else{
        printf("Error: tirada no valida\n");
        getche();
    }
    return;
}
//función principal
void Problema(void){
    int T[N][N];
    Inicializar(T);
    while(Completo(T)==0){
        system("cls");
        printf("JUEGO DEL SUDOKU\n\n");
        Imprimir(T);
        printf("\n");
        Tirar(T);
    }
    printf("Felicidades! Has completado el sudoku!\n");
    return;
}
//función main
int main(void){
    Problema();
    getche();
    return(0);
}
