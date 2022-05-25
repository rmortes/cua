#include <stdio.h>
#include<stdlib.h>
#include<time.h>

#define N 9
#define ASTERISCO -1


void NumerosAleatorios(int vector[], int tam){

    int i,aux;

    for (i=0;i<tam;i++){
        vector[i]=i+1;
    }
    for(int i=0;i<tam*tam;i++){
        int a = rand()%tam;
        int b = rand()%tam;
        int aux = vector[a];
        vector[a]=vector[b];
        vector[b]=aux;
    }

    return;
}


void Imprimir(int Tablero[],int Bolas[],int tam,int centinela,int x,int iteracion){

    int i;

    for (i=0;i<tam;i++){ //También se puede hacer con switch
        if (Tablero[i]==ASTERISCO)
            printf("*\t");
        else
            printf("%d\t",Tablero[i]);

        if((i+1)%3==0)
            printf("\n");
    }
    printf("\n");


    printf("Iteraciones: %d ", iteracion);
    printf("\n\n");

    printf("Numeros/Bolas: ");

    if (centinela==1){

        int i;

        for(i=0;i<=x;i++)
            printf(" %d ", Bolas[i]);
    }


    return;
}

void Comprobacion(int Tablero[],int Bolas[],int tam,int *aciertos,int *iteracion,int x){

    int i;

    getchar();

    system("cls");

    for (i=0;i<tam;i++){
        if (Bolas[x]==Tablero[i]){
            Tablero[i]=ASTERISCO;
            *aciertos=*aciertos+1;
        }
    }

    *iteracion=*iteracion+1;

    return;
}


int main()
{
    srand(time(NULL));

    int Tablero[2*N],Bolas[2*N],aciertos=0,iteracion=0,x;

    //Esta dos funcines hacen de inicialización del vector(Tablero) y vector(Bolas)
    NumerosAleatorios(Tablero,2*N);

    NumerosAleatorios(Bolas,2*N);


    Imprimir(Tablero,Bolas,N,0,x,iteracion);


    for(x=0;x<2*N && aciertos<N;x++){

        Comprobacion(Tablero,Bolas,N,&aciertos,&iteracion,x);

        Imprimir(Tablero,Bolas,N,1,x,iteracion);
    }

    printf("\n\n\t FIN \n\n");


    return 0;
}
