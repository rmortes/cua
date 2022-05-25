#include <stdio.h>
#include<stdlib.h>
#include<time.h>

#define N 3
#define ASTERISCO -1


void NumerosAleatorios(int vector[N*N]){

    int i,aux;

    for (i=0;i<N*N;i++){
        vector[i]=i+1;
    }
    for(int i=0;i<N*N*N*N;i++){
        int a = rand()%N*N;
        int b = rand()%N*N;
        int aux = vector[a];
        vector[a]=vector[b];
        vector[b]=aux;
    }


    return;
}

void InicializarMatrices(int MatrizA[N][N],int MatrizB[N][N]){

    int i,j;

    for (i=0;i<N;i++){
        for (j=0;j<N;j++){
            MatrizA[i][j]=ASTERISCO;
            MatrizB[i][j]=1+rand()%(N*N);
        }
    }

    return;
}

void Imprimir(int MatrizA[N][N],int iteracion){

    int i,j;

    for (i=0;i<N;i++){ //También se puede hacer con switch
        for (j=0;j<N;j++){
            if (MatrizA[i][j]==ASTERISCO)
                printf("*\t");
            else
                printf("%d\t",MatrizA[i][j]);
        }
        printf("\n");
    }

    printf("\n\nIteraciones: %d ", iteracion);
    printf("\n\n");

    printf("Numeros: ");


    return;
}

void Comprobacion(int MatrizA[N][N],int MatrizB[N][N],int vector[N*N],int *aciertos,int *iteracion,int x){

    int i,j;

    getchar();

    system("cls");

    for (i=0;i<N;i++){
        for (j=0;j<N;j++){
            if (vector[x]==MatrizB[i][j]){
                MatrizA[i][j]=vector[x];
                *aciertos=*aciertos+1;
            }
        }
    }

    *iteracion=*iteracion+1;
    return;
}

void ImprimirNumeros(int vector[N*N],int x){

    int i;

    for(i=0;i<=x;i++)
        printf(" %d ", vector[i]);

    return;
}


int main()
{
    srand(time(NULL));

    int MatrizA[N][N],MatrizB[N][N],vector[N*N],aciertos=0,iteracion=0,x;

    NumerosAleatorios(vector);

    InicializarMatrices(MatrizA,MatrizB);

    Imprimir(MatrizA,iteracion);


    for(x=0;x<N*N && aciertos<N*N;x++){

        Comprobacion(MatrizA,MatrizB,vector,&aciertos,&iteracion,x);

        Imprimir(MatrizA,iteracion);

        ImprimirNumeros(vector,x);

    }

    printf("\n\n\t FIN \n\n");


    return 0;
}
