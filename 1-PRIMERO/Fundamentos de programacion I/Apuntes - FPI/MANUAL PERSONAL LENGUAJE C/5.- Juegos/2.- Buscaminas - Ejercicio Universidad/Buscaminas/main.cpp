#include <stdio.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>

#define N 8

#define PUNTO 1
#define MINA 2
#define CRUZ 3
#define NUMEROMINAS 10

void InicializarMatrizA(int MatrizA[N][N]){

    int i,j;

    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            MatrizA[i][j]=PUNTO;
        }
    }

    return;
}

void InicializarMatrizB(int MatrizB[N][N]){

    int i,j,a,b;

    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            MatrizB[i][j]=PUNTO;
        }
    }


    for(i=0;i<NUMEROMINAS;i++){

        int centinela=0;/*El centinela se debe poner aquí  y no al principio
                          de la función, porque si no cogería solo una mina*/

        while(centinela==0){

            a=rand()%N;
            b=rand()%N;

            if (MatrizB[a][b]==PUNTO){
                MatrizB[a][b]=MINA;
                centinela=1;
            }
        }
    }

    return;
}

void ImprimirMatriz(int Matriz[N][N]){

    int i,j;

    printf("  JUEGO  DEL BUSCAMINAS\n\n");

    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            switch (Matriz[i][j]) {
            case PUNTO:
                printf(". ");//Se deja un espacio para que se imprima más ancho
                break;
            case MINA:
                printf("M ");//Se deja un espacio para que se imprima más ancho
                break;

            case CRUZ:
                printf("X ");//Se deja un espacio para que se imprima más ancho
                break;
            }
        }
        printf("\n");
    }

    printf("\n\n");


    return;
}


int NumeroCorrecto(int num,int menor,int mayor){

    do{
        if(num<menor || num>mayor){

            printf("Numero erroneo. Elige otra vez:  ");

            scanf("%d",&num);
        }

    }while(num<menor || num>mayor);

    return num;
}

void Tirar(int MatrizA[N][N], int MatrizB[N][N],int *contador,int *perdido){

    int fila,columna,num,elegido;

    ImprimirMatriz(MatrizA);

    do{
        elegido=0;

        printf("\nIntroduce una fila de 1 a %d: ",N);
        scanf("%d",&num);

        fila=NumeroCorrecto(num,1,N);
        fila--;//Para que coincida con la fila de la matriz en el programa

        printf("\nIntroduce una columna de 1 a %d: ",N);
        scanf("%d",&num);

        columna=NumeroCorrecto(num,1,N);
        columna--;//Para que coincida con la columna de la matriz en el programa

        system("cls");

        switch (MatrizB[fila][columna]) {
        case PUNTO:{
            MatrizB[fila][columna]=CRUZ;
            MatrizA[fila][columna]=CRUZ;
            *contador=*contador+1;
        }
            break;
        case MINA:{
            MatrizA[fila][columna]=MINA;
            *perdido=1;
        }
            break;
        case CRUZ:{
            system("cls");
            ImprimirMatriz(MatrizA);
            printf("Lo has elegido anteriormente\n");
            elegido=1;
        }
        }
    }while(elegido==1);

    return;
}


void Ayuda(int MatrizA[N][N], int MatrizB[N][N]){

    ImprimirMatriz(MatrizA);

    ImprimirMatriz(MatrizB);

    getche();/*En este caso no coge el getchar. La librería
               del getche() es conio.h*/

    system("cls");

    return;
}


int Menu(int MatrizA[N][N], int MatrizB[N][N],int *contador,int *perdido){

    int num,opcion;

    printf("1.- Tirar\n");
    printf("2.- Ayuda\n");
    printf("3.- Salir\n");
    printf("       Elige opcion(1-3):  ");

    scanf("%d",&num);

    opcion=NumeroCorrecto(num,1,3);


    if(opcion==1){
        system("cls");

        // Hay que poner forzosamente &* a las variables contador y perdido
        Tirar(MatrizA,MatrizB,&*contador,&*perdido);
    }

    if (opcion==2){
        system("cls");
        Ayuda(MatrizA,MatrizB);
    }

    return opcion;
}

int main()
{
    srand(time(NULL));

    /*Se deben crear aquí las variables contador=0 y perdido=0
     porque si se crean después dentro de una función, cuando se vuelva
     a pasar por dicha función pondrá otra vez los dos valores a 0*/

    int MatrizA[N][N],MatrizB[N][N],opcion,contador=0,perdido=0;

    InicializarMatrizA(MatrizA);

    InicializarMatrizB(MatrizB);


    do{
        ImprimirMatriz(MatrizA);/*Se emplea la misma función para imprimir
                                 la MatrizA y MatrizB*/


        opcion=Menu(MatrizA,MatrizB,&contador,&perdido);

    }while(opcion<3 && perdido!=1 && contador!=(N*N-NUMEROMINAS));


    if(opcion==3){
        printf("\n");
        printf("Te has salido del juego");
    }

    if(perdido==1){
        ImprimirMatriz(MatrizA);
        printf("Has perdido");
    }

    if(contador==(N*N-NUMEROMINAS)){
        ImprimirMatriz(MatrizA);
        printf("Has ganado");
    }

    printf("\n\n");


    return 0;
}
