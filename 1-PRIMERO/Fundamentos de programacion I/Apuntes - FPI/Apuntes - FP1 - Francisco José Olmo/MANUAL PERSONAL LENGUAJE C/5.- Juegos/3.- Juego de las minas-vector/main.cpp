#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<conio.h>

#define N 20

#define FLECHA 1
#define MINA 2
#define NADA 3
#define MUERTO 4


void InicializarVector (int vector[], int *x){
    int i;
    for(i=0;i<N;i++){
        vector[i]=NADA;

    }
    vector[*x]=FLECHA;
    vector[N-1]=MINA;

    return;
}

void Imprimir(int vector[]){
    int i;
    printf("\n\n\n");
    printf("\t");
    printf("|");
    for(i=0;i<N;i++){

        switch (vector[i]) {
        case FLECHA:
            printf("V");
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
    printf("|");
    printf("\n\n\n");
    return;
}

void MovimientoyComprobacion(int vector[],int *x, int *resultado)
{
    vector[*x]=NADA;

    //esperamos una tecla
    char tecla = getch();
    //doble letra en Windows
    if(tecla==-32 || tecla==0){
        tecla=getch();
    }

    //en función de la tecla pulsada
    switch(tecla){
    //casos izquierda
    case 75:
    case '4':*x=*x-1;
    case 'D':
        //acciones izquierda
        //…
        break;
        //casos derecha
    case 77:
    case '6':*x=*x+1;
    case 'C':
        //acciones derecha
        //…
        break;
    }

    system("cls");

    if (vector[*x]==MINA){
        vector[*x]=MUERTO;
        *resultado=1;
    }
    else
        vector[*x]=FLECHA;

    return;
}


int main(){
    int x,vector[N],resultado=0;

    x=N/2;

    InicializarVector(vector,&x);
    Imprimir(vector);

    while(vector[x]!=MUERTO && x>0){

        MovimientoyComprobacion(vector,&x,&resultado);

        Imprimir(vector);

    }

    if (resultado==0)
        printf("Has ganado");
    else
        printf("Has perdido");

    printf("\n\n\n");

    return 0;
}
