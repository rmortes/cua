#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#define N 7

//Funcion de las teclas
int Comandos(int matriz[N][N]){
    //esperamos una tecla
    char tecla = getch();
    //doble código en caso de que sea un cursor
    if(tecla==-32 || tecla==0) tecla=getch();
    //recorre la matriz en busca del humano.
    int a,b;
    int h=1;
    for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
            if(matriz[i][j]==1){
                //asigna la posicion a las variables.
                a=i;
                b=j;
            }
        }
    }
    //en función de la tecla pulsada
    switch(tecla){
    case 72:
    case '8':
        if(a>0){
            if(matriz[a-1][b]==2){
                h=0;
            }
            matriz[a-1][b]=1;
            matriz[a][b]=0;
        }

    //ARRIBA
    break;
    case 80:
    case '2':
        if(a<N-1){
            if(matriz[a+1][b]==2){
                h=0;
            }
            matriz[a+1][b]=1;
            matriz[a][b]=0;
        }
    //ABAJO
    break;
    case 75:
    case '4':
        if(b>0){
            if(matriz[a][b-1]==2){
                h=0;
            }
            matriz[a][b-1]=1;
            matriz[a][b]=0;
        }
    //IZQUIERDA
    break;
    case 77:
    case '6':
        if(b<N-1){
            if(matriz[a][b+1]==2){
                h=0;
            }
            matriz[a][b+1]=1;
            matriz[a][b]=0;
        }
    //DERECHA
    break;
    case 13:
    //ENTER
    break;
    }
    return(h);
}
//Funcion que inicia al soldado.
void pj(int matriz[N][N]){
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            if(j==(N/2) && i==0){
                matriz[i][j]=1;
            }else{
                matriz[i][j]=0;
            }
        }
    }
}

int distmina(int matriz[N][N]){
    int x,y;
    int d,absx,absy;
    int mx,my;
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            if(matriz[i][j]==1){
                x=i;y=j;
            }
            if(matriz[i][j]==2){
                mx=i;my=j;
            }
        }
    }

    if((x-mx)<0){
        absx=-(x-mx);
    }else{
        absx=(x-mx);
    }
    if((y-my)<0){
        absy=-(y-my);
    }else{
        absy=(y-my);
    }
    d=absx+absy;
    return(d);
}

//Funcion que pinta el tablero.
void tablero(int matriz[N][N]){
    int distancia;
    distancia=distmina(matriz);
    for (int i=0; i<N; i++){
        printf("|");
        for(int j=0; j<N; j++){
            if(matriz[i][j]==1){
                printf("%d",distancia);
            }else{
                printf("~");
            }
        }
        printf("|\n");
    }
}

//Funcion que genera minas aleatoriamente.
void mina(int matriz[N][N],int Niv){
    int iaux=0;
    int jaux=0;
    int contador=0;
    srand(time(NULL));
    //Bucle que genera minas segun el nivel de dificultad.
    do{
        //Coordenadas elegidas al azar.        
        iaux=rand()%N;
        jaux=rand()%N;
        //Bucle que recorre la matriz.
        for (int i=0; i<N; i++){
            for(int j=0; j<N; j++){
                //Condición que se encarga de ver si esta ocupada la posicion.
                if(i==iaux && j==jaux && matriz[i][j]!=1 && matriz[i][j]!=2){
                    //Asigna la mina en la matriz.
                    matriz[i][j]=2;
                    //Cuenta las minas puestas.
                    contador ++;
                }
            }
        }
    }while (contador == (((10*Niv)*(N*N))/100));
}


//Función que selecciona el nivel de dificultad.
int Nivel(){
    int Niv;
    Niv=0;
    //Bucle de intentos en caso de que no se haya introducido bien el numero.
    do{
    printf("Introduzca un numero entre (1 - 3): ");
    scanf("%d",&Niv);
    getchar();
    }while(Niv < 1 || Niv > 3);
    return (Niv);
}



int main (void){
    int matriz[N][N];
    int Niv;
    int hum;
    Niv=Nivel();
    pj(matriz);
    mina(matriz,Niv);
    do{
        system("cls");
        tablero (matriz);
        hum=Comandos(matriz);

    }while(hum==1);
}


