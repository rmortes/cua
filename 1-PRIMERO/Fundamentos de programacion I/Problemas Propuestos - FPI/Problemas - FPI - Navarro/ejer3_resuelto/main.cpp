//librerías necesarias
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
//Tamaño del tablero
#define N 8
//Inicialización del tablero
void Inicializar(int T[N][N]){
    int i,j;
    //ponemos todo el tablero a 0
    //0 significa vacío y sin descubrir
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            T[i][j]=0;
        }
    }
    //colocamos las minas aleatoriamente
    int nminas=0;
    while(nminas<10){
        i=rand()%N;
        j=rand()%N;
        if(T[i][j]==0){
            //las minas las marcamos como 1
            T[i][j]=1;
            nminas++;
        }
    }
    return;
}
//impresión del tablero
void Imprimir(int T[N][N], int descubierto){
    int i,j;
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            switch(T[i][j]){
            case 0:
                printf("? ");
                break;
            case 1:
                if(descubierto==0) printf("? ");
                else printf("M ");
                break;
            case 2:
                printf("X ");
                break;
            }
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
//menu del juego
int Menu(void){
    printf("\nMenu\n");
    printf("1) Tirar\n");
    printf("2) Hacer trampa\n");
    printf("3) Terminar\n");
    int op;
    do{
        printf("Elija opcion (1-3): ");
        scanf("%d",&op);
    }while(op<1 || op>3);
    return(op);
}
//solicita un numero entre 1 y N
int PedirNumero(void){
    int num;
    do{
        scanf("%d",&num);
        if(num<1 || num>N){
            printf("error, introduzca un numero de 1 a %d :",N);
        }
    }while(num<1 || num>N);
    //restamos uno por la numeracion de los vectores
    num=num-1;
    return(num);
}
//Función para tirar
int Tirar(int T[N][N]){
    int i,j;
    printf("Introduzca fila (1-%d) ",N);
    i=PedirNumero();
    printf("Introduzca columna (1-%d) ",N);
    j=PedirNumero();
    int salida;
    if(T[i][j]==1){
        salida=1; //para que termine el bucle del menu
    }else{
        T[i][j]=2; //en caso contrario tira
        salida=0;
    }
    return(salida);
}
//función principal
void Problema(void){
    int T[N][N],resul;
    Inicializar(T);
    int terminar=0;
    while(terminar==0){
        system("cls");
        printf("JUEGO DEL BUSCAMINAS\n\n");
        Imprimir(T,0);
        int op=Menu();
        switch(op){
        case 1:
            resul=Tirar(T);
            if(resul==1){
                printf("Lo siento, has perdido\n");
                Imprimir(T,1);
                terminar=1;
            }
            break;
        case 2:
            Imprimir(T,1);
            printf("Pulse una tecla\n");
            getche();
            break;
        case 3:
            printf("Adios\n");
            terminar=1;
            break;
        }
        if(Completo(T)==1){
            printf("Felicidades, has ganado\n");
            terminar=1;
        }
    }
    return;
}
//función main
int main(void){
    Problema();
    getche();
    return(0);
}
