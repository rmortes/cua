#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 18
#define VIVO 1
#define MUERTO 2
#define MALEZA 3
#define LIBRE 4
#define MINA 5

int Level (void){
    int nivel;
    do{
        printf("Introduzca el nivel (1-3): ");
        scanf("%d",&nivel);
        if (nivel<1 || nivel>3) printf("Error. Caracter invalido. \n");
    }while(nivel<1 || nivel>3);
    return nivel;
}

void Inicializar_Matriz(int M [N][N],int minas){
    for (int i=0;i<N;i++)
        for (int j=0;j<N;j++)
            M [j][i]=MALEZA;

    M[N/2][N/2]=VIVO;
    while (minas>0){
       int a=rand()%N;
       int b=rand()%N;
        if (M[a][b]==MALEZA){
            M[a][b]=MINA;
            minas--;
        }
    }
    return;
}

void Movimiento (int M[N][N], int *nmov, int *gameover, int *win){
    int X,Y;
    for (int i=0;i<N;i++)
        for (int j=0;j<N;j++)
            if (M[j][i]==VIVO){
                X=j;Y=i;
                M[X][Y]=LIBRE;
            }
    int aleatorio=rand()%4;
    switch (aleatorio){
    case 0:
        if (X<N-1){
            X++;
            *nmov=*nmov+1;
        }
        break;
    case 1:
        if (X>0){
            X--;
            *nmov=*nmov+1;
        }
        break;
    case 2:
        if (Y<N-1){
            Y++;
            *nmov=*nmov+1;
        }
        break;
    case 3:
        if (Y>0){
            Y--;
            *nmov=*nmov+1;
        }
        break;
    }

    if (M[X][Y]==MINA){
        M[X][Y]=MUERTO;
        *gameover=1;
    }else{
        M[X][Y]=VIVO;
        if (X==N-1 || X==0 || Y==N-1 || Y==0) *win=1;
    }
    return;
}

void Imprimir (int nmov, int M[N][N]){
    system ("cls");
    printf("Escapada del campo de minas\n____________________________\n>>>Minas aleatorio<<< Iteracion %d\n------------------------",nmov);
    for (int i=0; i<N; i++){
        printf("\n|");
        for(int j=0;j<N;j++){
            switch (M [j][i]){
            case MALEZA:
                printf("~");
                break;
            case LIBRE:
                printf(" ");
                break;
            case MINA:
                printf("M");
                break;
            case VIVO:
                printf("U");
                break;
            case MUERTO:
                printf("X");
                break;
            }
        }
        printf("|");
    }
    return;
}

void Escapada(){
    int M[N][N];
    int nmov=0;
    int gameover=0, win=0;
    system("cls");
    int nivel=Level();
    int minas=N*nivel/2;
    Inicializar_Matriz(M,minas);
    while(gameover==0 && win==0){
        Imprimir(nmov,M);getchar();
        Movimiento(M,&nmov,&gameover,&win);
    }
    Imprimir(nmov,M);
    if(win==1) printf("\nHas ganado!\n");
    else printf("\nHas perdido!\n");
    return;
}

int main(void){
    srand(time(NULL));
    Escapada();
    return 0;
}
