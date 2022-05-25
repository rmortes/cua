#include <stdio.h>
#include<stdlib.h>

#define N 10

void InicializarVector(int vector[]){

    int i;

    for(i=0;i<N;i++){

        printf("Escribe un numero: ");

        scanf("%d/n",&vector[i]);
    }

    return;
}

void Imprimir(int vector[]){

    int i;

    for(i=0;i<N;i++)

        printf(" %d ",vector[i]);

    return;
}


void PedirPosicionyComprobar(int vector[]){

    int posicion,contador,x;

    printf("\n\nEscribe la posicion: ");

    scanf("%d",&posicion);

    contador=1;

    x=1;

    while(posicion+x<N && vector[posicion]==vector[posicion+x]){

        if(vector[posicion]==vector[posicion+x]){
            x++;
            contador++;
        }
    }

    x=1;

    while(posicion-x>=0 && vector[posicion]==vector[posicion-x]){

        if(vector[posicion]==vector[posicion-x]){
            x++;
            contador++;
        }
    }


    printf("\nEn la posicion %d el numero %d se repite %d veces\n\n",posicion,vector[posicion],contador);


    return;
}


int main()
{
    int vector[N];

    InicializarVector(vector);

    system("cls");

    Imprimir(vector);

    PedirPosicionyComprobar(vector);




    return 0;
}
