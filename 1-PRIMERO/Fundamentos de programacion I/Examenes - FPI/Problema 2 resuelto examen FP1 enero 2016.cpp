/*Se trata de hacer un programa en el que se imprime una matriz de N*N elementos en pantalla.
En el elemento central colocamos al personaje, representado por una U. Inicializamos el resto
de la matriz a "libre" (símbolo ~) y colocamos x minas (representadas por una M, la cantidad
depende del nivel elegido por el usuario) de forma aleatoria repartidas por la matriz. El
personaje se moverá de manera aleatoria hasta que alcance una mina (muere, lo representamos
con una X) o llegue a alguno de los límites de la matriz (ganará).*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 18
#define personaje 1
#define muerto 2
#define cesped 3
#define libre 4
#define mina 5

void Movimiento (int matriz[N][N], int *iteracion, int *perdido, int *ganado){
    int persx,persy;
    for (int i=0;i<N;i++)
        for (int j=0;j<N;j++)
            if (matriz[j][i]==personaje){
                persx=j;persy=i;
                matriz[persx][persy]=libre;
            }
    int aleatorio=rand()%4;
    switch (aleatorio){
    case 0:
        if (persx<N-1){
            persx++;
            *iteracion++;
        }
        break;
    case 1:
        if (persx>0){
            persx--;
            *iteracion++;
        }
        break;
    case 2:
        if (persy<N-1){
            persy++;
            *iteracion++;
        }
        break;
    case 3:
        if (persy>0){
            persy--;
            *iteracion++;
        }
        break;
    }

    if (matriz[persx][persy]==mina){
        matriz[persx][persy]=muerto;
        *perdido=1;
    }else{
        matriz[persx][persy]=personaje;
        if (persx==N-1 || persx==0 || persy==N-1 || persy==0) *ganado=1;
    }

    return;
}

void Imprimir (int iteracion, int matriz[N][N]){
    system ("cls");
    printf(">>>Minas aleatorio<<< Iteracion %d\n------------------------",iteracion);
    for (int i=0; i<N; i++){
        printf("\n|");
        for(int j=0;j<N;j++){
            switch (matriz [j][i]){
            case cesped:
                printf("~");
                break;
            case libre:
                printf(" ");
                break;
            case mina:
                printf("M");
                break;
            case personaje:
                printf("U");
                break;
            case muerto:
                printf("X");
                break;
            }
        }
        printf("|");
    }
    return;
}

void Inicializar_Matriz(int matriz [N][N],int minas){
    for (int i=0;i<N;i++)
        for (int j=0;j<N;j++)
            matriz [j][i]=cesped;

    matriz[N/2][N/2]=personaje;

    while (minas>0){
       int a=rand()%N;
       int b=rand()%N;
        if (matriz[a][b]==cesped){
            matriz[a][b]=mina;
            minas--;
        }
    }
    return;
}

int Nivel (void){
    int nivel;
    do{
        printf("Introduzca el nivel (1-3): ");
        scanf("%d",&nivel);
        if (nivel<1 || nivel>3) printf("Error. Caracter invalido. \n");
    }while(nivel<1 || nivel>3);
    return nivel;
}

void Juego(){
    int matriz[N][N];
    int iteracion=0;
    int perdido=0, ganado=0;
    int nivel=Nivel();
    int minas=N*nivel/2;

    Inicializar_Matriz(matriz,minas);
    while(perdido==0 && ganado==0){
        Imprimir(iteracion,matriz);
        getchar();
        Movimiento(matriz,&iteracion,&perdido,&ganado);
    }
    Imprimir(iteracion,matriz);
    if(ganado==1) printf("\nHas ganado!\n");
    else printf("\nHas perdido!\n");
    return;
}


int main(void){
    srand(time(NULL));
    Juego();
    return 0;
}
