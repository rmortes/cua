#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<math.h>
#include<time.h>
#define N 10

int NIVEL(){
    int nivel;
    do{//filtramos el nivel
        printf("Introduce nivel de dificultad(1-3):");
        scanf("%d",&nivel);
        getchar();
    }while(nivel<1 || nivel>3);
    return(nivel);
}

void iniciar(int M[N][N],int nivel){
    int a,b;
    //rellenamos la matriz de 0,que son galletas
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            M[i][j]=0;
        }
    }
    //ponemos los obstaculos
    for(int i=1;i<=nivel*10;i++){
        do{
            a=rand()%N;
            b=rand()%N;
        }while(M[a][b]!=0);
        M[a][b]=1;
    }

    //ponemos la X
    do{
        a=rand()%N;
        b=rand()%N;
    }while(M[a][b]!=0);
    M[a][b]=2;
    return;
}


int mover(int M[N][N],int centinela,int nivel,int*puntos){
    int posi,posj;
    for(int i=0;i<N;i++){//guarda la posicion del usuario
        for(int j=0;j<N;j++){
            if(M[i][j]==2){
                posi=i;
                posj=j;
            }
        }
    }
    char tecla= getch();
    if(tecla==-32 || tecla==0){
        do{
            tecla=getch();
            switch(tecla){
            case 72:
            case '8':
                //ARRIBA
                if(posi>0 && M[posi-1][posj]==0){//si es una galleta
                    M[posi-1][posj]=2;//ponemos la X ahi
                    M[posi][posj]=3;
                    (*puntos)=(*puntos)+1;
                }
                break;
            case 80:
            case '2':
                //ABAJO
                if(posi<9 && M[posi+1][posj]==0){//si es una galleta
                    M[posi+1][posj]=2;//ponemos la X ahi
                    M[posi][posj]=3;
                    (*puntos)=(*puntos)+1;

                }
                break;
            case 77:
            case '6':
                //DERECHA
                if(posj<9 && M[posi][posj+1]==0){//si es una galleta
                    M[posi][posj+1]=2;//ponemos la X ahi
                    M[posi][posj]=3;
                    (*puntos)=(*puntos)+1;

                }
                break;
            case 75:
            case '4':
                //IZQUIERDA
                if(posj>0 && M[posi][posj-1]==0){//si es una galleta
                    M[posi][posj-1]=2;//ponemos la X ahi
                    M[posi][posj]=3;
                    (*puntos)=(*puntos)+1;

                }
                break;

            }
        }while(tecla=='s' || tecla=='i');
    }
    if(tecla=='s' ){
        centinela=1;
    }
    if(tecla=='i'){
        iniciar(M,nivel);
    }
    //COMPROBACION
    //si es un obstaculo o un guion ,en los cuatro movimientos, se queda ahi y finaliza
    if((M[posi-1][posj]==1 || M[posi-1][posj]==3) || posi<=0){//ARRIBA
        if(M[posi+1][posj]==1 || M[posi+1][posj]==3 || posi>=9){//ABAJO
            if(M[posi][posj-1]==1 || M[posi][posj-1]==3 || posj<=0){//IZQUIERDA
                if(M[posi][posj+1]==1 || M[posi][posj+1]==3 || posj>=9){//DERECHA
                    M[posi][posj]=2;
                    centinela=1;
                }
            }
        }
    }

    return(centinela);
}


void imprimir(int M[N][N]){

    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            switch(M[i][j]){
            case 0:
                printf(" .");
                break;
            case 1:
                printf(" *");
                break;
            case 2:
                printf(" X");
                break;
            case 3:
                printf(" -");
                break;
            }
        }
        printf("\n");
    }

    return;
}

void gusanos(){
    srand(time(NULL));
    int M[N][N];
    int centinela=0;
    int nivel=NIVEL();
    int puntos=0;
    iniciar(M,nivel);
    do{
        system("cls");//borramos el panel
        printf("------------------\n\n JUEGO DEL GUSANO\n\n------------------\n");
        imprimir(M);
        printf("PUNTOS:%d\n\n",puntos);
        printf("\nCONTROLES:\n");
        printf("-cursores para mover el gusano\n i para iniciar de nuevo el panel \n s para salir del programa.\n");
        centinela=mover(M,centinela,nivel,&puntos);
    }while(centinela==0);

    if(centinela==1){
        printf("\n\nFIN DEL JUEGO.");
    }

    return;
}


int main(void){
    gusanos();
    getche();
    return(0);
}
