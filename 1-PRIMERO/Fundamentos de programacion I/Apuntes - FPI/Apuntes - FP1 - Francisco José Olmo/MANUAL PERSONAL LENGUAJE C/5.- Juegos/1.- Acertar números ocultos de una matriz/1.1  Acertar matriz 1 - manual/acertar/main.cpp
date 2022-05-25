#include <stdio.h>
#include<stdlib.h>
#include<time.h>

#define N 3
#define ASTERISCO -1

void InicializarMatrices(int MatrizA[N][N],int MatrizB[N][N]){

    int i,j;

    for (i=0;i<N;i++){
        for (j=0;j<N;j++){
            MatrizA[i][j]=ASTERISCO;
            MatrizB[i][j]=1+rand()%(N*N);/*Si se pone N*N sin paréntesis,
                                         siempre aparecen los mismos números
                                         al azar. Se le suma 1 al principio
                                         para que no salga el 0*/


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

    return;
}

void PedirNumeroyComprobar(int MatrizA[N][N],int MatrizB[N][N],int *aciertos,int *iteracion){

    int i,j,num;

    printf("\nIntroduce un numero: ");
    scanf("%d",&num);

    system("cls");

    *iteracion=*iteracion+1;

    for (i=0;i<N;i++){
        for (j=0;j<N;j++){
            if (num==MatrizB[i][j]){
                MatrizA[i][j]=num;
                *aciertos=*aciertos+1;
            }
        }

    }
    return;
}

    int main()
    {
        srand(time(NULL));

        int MatrizA[N][N],MatrizB[N][N],aciertos=0,iteracion=0;

        InicializarMatrices(MatrizA,MatrizB);

        Imprimir(MatrizA,iteracion);

        while(aciertos<N*N){

            PedirNumeroyComprobar(MatrizA,MatrizB,&aciertos,&iteracion);

            /*El cls se ha puesto dentro de PedirNumeroyComprobar
             pero se podría haber puesto aquí en vez de allí*/

            Imprimir(MatrizA,iteracion);

        }

        printf("\n\n\t FIN \n\n");


        return 0;
    }
