#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include <math.h>
//tamaño del panel

#define N 4
//función que imprime el panel de juego
void ImprimirPanel(int M[N][N]){
    int i,j;
    printf("\n--- PANEL DE JUEGO ---\n\n");
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            if(M[i][j]>=0) printf("%3d ",M[i][j]);
            else printf(" * ");
        }
        printf("\n\n");
    }
    return;
}
//función que busca el hueco con el *
//(el único número negativo del panel)
void BuscarHueco(int M[N][N], int &posi, int &posj){
    int i,j;
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            if(M[i][j]<0){
                posi=i;
                posj=j;
            }
        }
    }
    return;
}
//Funcion que realiza el movimiento
int Movimiento(int M[N][N], int m){
    int salida=0;
    int i,j;
    BuscarHueco(M,i,j);
    switch(m){
    case 0: //arriba
        if(i>0){
            M[i][j]=M[i-1][j];
            M[i-1][j]=-1;
            salida=1;
        }
        break;
    case 1: //derecha
        if(j<N-1){
            M[i][j]=M[i][j+1];
            M[i][j+1]=-1;
            salida=1;
        }

        break;
    case 2: //abajo
        if(i<N-1){
            M[i][j]=M[i+1][j];
            M[i+1][j]=-1;
            salida=1;
        }
        break;
    case 3: //izquierda
        if(j>0){
            M[i][j]=M[i][j-1];
            M[i][j-1]=-1;
            salida=1;
        }
        break;
    }
    //devolvemos 1 o 0 en función de si
    //el movimiento ha sido exitoso
    return(salida);
}
void Inicializar(int M[N][N]){
    int nivel, ncambios, i,j;
    printf("Inicializacion del panel\n");
    //nivel de juego
    printf("Nivel (1/2/3): ");
    scanf("%d",&nivel);
    ncambios=N*N*nivel;
    //inicialización en orden
    int act=1;
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            M[i][j]=act;
            act++;
        }
    }
    M[N-1][N-1]=-1; //hueco (abajo derecha)
    //generamos los movimientos aleatorios
    while(ncambios>0){
        if(Movimiento(M,rand()%4)==1){
            ncambios--;
        }
    }
    return;
}

//funcion que comprueba si el panel está solucionado
int Solucionado(int M[N][N]){
    int i,j,soluc=1,act=1;
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            if((i<N-1 || j<N-1) && M[i][j]!=act){
                soluc=0;
            }
            act++;
        }
    }
    return(soluc);
}
//funcion que gestiona el juego completo
void Juego(void){
    int M[N][N];
    Inicializar(M);
    char opc;
    do{
        system("cls");
        ImprimirPanel(M);
        printf("\nOpciones:\n");
        printf(" CURSORES: mover hueco\n");
        printf(" ESC : finalizar\n");
        printf(" R : inicializar juego\n");
        opc=getche();
        //los cursores devuelven dos caracteres
        //el primero (-32 o 0) es el panel del que
        //provienen (simple o extendido)
        if(opc==-32 || opc==0) opc=getche();
        printf("\n");
        switch(opc){
        case 27: //escape
            break;
        case 72: //arriba
            printf("ARRIBA\n");
            Movimiento(M,0);
            break;
        case 75: //izquierda
            printf("IZQUIERDA\n");
            Movimiento(M,3);
            break;
        case 77: //derecha
            printf("DERECHA\n");
            Movimiento(M,1);
            break;
        case 80: //abajo

            printf("ABAJO\n");
            Movimiento(M,2);
            break;
        case 'R':
            Inicializar(M);
            break;
        }
    }while(Solucionado(M)!=1 && opc!=27);
    if(opc==27){
        printf("Fin del juego\n");
    }else{
        system("cls");
        ImprimirPanel(M);
        printf("Felicidades, has ganado\n");
    }
    return;
}
//función principal
int main(void){
    Juego();
    getche();
    return(0);
}
