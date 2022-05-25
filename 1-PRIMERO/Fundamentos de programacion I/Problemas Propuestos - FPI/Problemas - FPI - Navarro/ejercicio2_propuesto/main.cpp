//Ejercicio 4
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>
#define N 2
#define M 2

int Funcion_multiplicacion(int v1[N],int v2[M],int m[N][M]){
    int resul,R[M];
    for(int i=0; i<N; i++){
        for( int j=0; j<M; j++){
            R[i]+=v1[i]*m[i][j];
        }
    }
    for (int j=0; j<N; j++){
        resul+=R[j]*v2[j];
    }
return resul;
}

int main (){
    int v1[N],v2[M],m[N][M];
    int resul;
    for(int i=0; i<N; i++){
        v1[i]=rand()%101;
        printf("%d",v1[i]);
    }printf("\n");
    for (int j=0; j<M; j++){
        v2[j]=rand()%101;
        printf("\n");
        printf("%d",v2[j]);
    }printf("\n");
    for(int i=0; i<N; i++){
        for (int j=0; j<M; j++){
            m[i][j]=rand()%101;

            printf("%d",m[i][j]);
        }printf("\n");
    }printf("\n");


    resul=Funcion_multiplicacion(v1,v2,m);
    printf("Resultado de la operacion: %d\n",resul);
    return resul;

}

