#include <stdio.h>
#include<stdlib.h>
#include<time.h>

#define N 10

#define NADA 2
#define CRUZ 3

int InicializarVector(int vector[N]){

    int i,a;

    for(i=0;i<10;i++)
        vector[i]=NADA;

    a=rand()%6;
    for(i=0;i<=a;i++) //Se pone i<=a para que entre también el 0
        vector[i]=CRUZ;


    return a;
}


void Imprimir(int vector[]){

    int i;

    printf("|");
    for(i=0;i<N;i++)
        switch (vector[i]) {
        case CRUZ:printf("X");
            break;
        case NADA:printf(" ");
            break;
        }
    printf("|");
    return;
}

void Cambio(int vector[],int *a){

    vector[*a]=NADA;

    *a=*a-1;

    return;
}

int main(){

    srand(time(NULL));

    int vector[N];

    int a=InicializarVector(vector);

    Imprimir(vector);

    while(a>=0){

        getchar();
        system("cls");

        Cambio(vector,&a);

        Imprimir(vector);
    }

    printf("\n\n");

    return 0;
}

