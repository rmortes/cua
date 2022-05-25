#include<stdlib.h>
#include<conio.h>
#include<stdio.h>
#include<math.h>
#include<time.h>
#define N 20

void zombies(int M[N][N],int L){
    int pi,pj;
    int piz,pjz;
    //CREAMOS VARIABLE PARA CONDICIONAR EL MOVIMIENTO DEL ZOMBIE
    int zombie=0;
    //NUMERO ALEATORIO DEL 0 AL 100
    int z=rand()%101;
    //CONDICION PARA QUE SE MUEVA EL ZOMBIE
    if(z<L*10){
        zombie=1;
    }
    //SI EL ZOMBIE SE MUEVE,RECORREMOS EL PANEL Y COPIAMOS LA POSICION DEL USUARIO
    if(zombie==1){
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                if(M[i][j]==3){
                    pi=i;
                    pj=j;
                }
            }
        }
        //COPIAMOS LA POSICION DEL ZOMBIE
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                if(M[i][j]==2){
                    piz=i;
                    pjz=j;
                }
            }
        }
        //BUSCAMOS LA POSICION DEL ZOMBIE Y PASAMOS A MODIFICAR SU VALOR EN LOS CONDICIONALES
        for(int  i=0;i<N;i++){
            for(int j=0;j<N;j++){
                if(M[i][j]==2){
                    //ZOMBIE ABAJO DEL USUARIO
                    if(pi<piz){
                        //ZOMBIE A LA IZQUIERDA DEL USUARIO
                        if(pjz<pj){
                            M[i-1][j+1]=M[i][j];
                            M[i][j]=0;
                            M[i-1][j+1]=2;

                        }
                        //ZOMBIE A LA DERECHA DEL USUARIO
                        if(pj<pjz){
                            M[i-1][j-1]=M[i][j];
                            M[i][j]=0;
                            M[i-1][j-1]=2;
                        }
                    }
                    //ZOMBIE ARRIBA DEL USUARIO
                    if(piz<pi){
                        //ZOMBIE A LA IZQUIERDA DEL USUARIO
                        if(pjz<pj){
                            M[i+1][j-1]=M[i][j];
                            M[i][j]=0;
                            M[i+1][j-1]=2;
                        }
                        //ZOMBIE A LA DERECHA DEL USUARIO
                        if(pj<pjz){
                            M[i+1][j+1]=M[i][j];
                            M[i][j]=0;
                            M[i+1][j+1]=2;
                        }
                    }
                }
            }
        }
    }


    return;
}

void usuario(int M[N][N],int*estado){
    int aux[N][N];
    //HACEMOS UNA COPIA DE LA MATRIZ,PARA TRABAJAR EN LA AUXILIAR
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            aux[i][j]= M[i][j];
        }
    }
    //CREAMOS DOS VARIABLES QUE GUARDEN LA POSICION DEL USUARIO
    int pi,pj;
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            if(aux[i][j]==3){
                pi=i;
                pj=j;
            }
        }
    }
    printf("\n------------------------\nUtilize los cursores para moverse.\n");
    //CURSORES
    char tecla= getch();
    if(tecla==-32 || tecla==0){
        tecla=getch();
        switch(tecla){
        case 72:
        case '8':
            //ARRIBA
            /*SI SUBE Y COINCIDE CON UNA MINA O UN ZOMBIE,SE MUERE*/
            if(aux[pi-1][pj]==1 || aux[pi-1][pj]==2){
                //DEVUELVE EL NUEVO ESTADO,QUE ACABA EL JUEGO
                *estado=1;
            }
            //COPIA LA NUEVA POSICION Y PONE EN VACÍO LA ANTERIOR
            aux[pi-1][pj]=aux[pi][pj];
            aux[pi][pj]=0;
            break;
          case 80:
          case '2':
            //ABAJO
            if(aux[pi+1][pj]==1||aux[pi+1][pj]==2){
                *estado=1;
            }
            aux[pi+1][pj]=aux[pi][pj];
            aux[pi][pj]=0;
            break;
          case 77:
          case '6':
            //DERECHA
            if(aux[pi][pj+1]==1||aux[pi][pj+1]==2){
                *estado=1;
            }
            aux[pi][pj+1]=aux[pi][pj];
            aux[pi][pj]=0;
            break;
          case 75:
          case '4':
            //IZQUIERDA
            if(aux[pi][pj-1]==1||aux[pi][pj-1]==2){
                *estado=1;
            }
            aux[pi][pj-1]=aux[pi][pj];
            aux[pi][pj]=0;
            break;
        }
    }
    //COPIA EL PANEL AUXILIAR MODIFICADO EN EL PANEL ORIGINAL
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            M[i][j]= aux[i][j];
        }
    }
    return;
}

void imprimir(int M[N][N]){
    //BORRAMOS EL PANEL
    system("cls");
    printf(" LA CARRERA DE ZOMBIES\n----------------------\n");
    //PONEMOS LA PRIMERA LÍNEA
    for(int i=0;i<N+2;i++){
        printf("X");
    }
    printf("\n");
    //PONEMOS LA LÍNEA IZQUIERDA
    for(int j=0;j<N;j++){
        printf("X");
        //SUSTITUIMOS LOS NÚMEROS POR SUS CARÁCTERES
        for(int k=0;k<N;k++){
            switch(M[j][k]){
            case 0:
                printf(" ");
                break;
            case 1:
                printf("*");
                break;
            case 2:
                printf("Z");
                break;
            case 3:
                printf("@");
                break;
            }
        }
        //PONEMOS LA LÍNEA DERECHA
        printf("X\n");

    }
    //PONEMOS LA ÚLTIMA LÍNEA
    for(int i=0;i<N+2;i++){
        printf("X");
    }
    return;
}

void inicializar(int M[N][N]){
    int a,b;
    //RELLENAMOS EL PANEL DE CEROS(0)
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            M[i][j]=0;
        }
    }
    //RELLENAMOS LOS ZOMBIES(2)
    for(int i=0;i<N/4;i++){
        do{
            a=rand()%N;
            b=rand()%N;
        }while(M[a][b]!=0);
        M[a][b]=2;
    }
    //RELLENAMOS LAS MINAS(1)
    for(int i=0;i<N;i++){
        do{
            a=rand()%N;
            b=rand()%N;
        }while(M[a][b]!=0);
        M[a][b]=1;
    }
    //COMPROBAMOS QUE NO ESTE VACÍO
    do{
        a=rand()%N;
        b=rand()%N;
    }while(M[a][b]!=0);
    //PONEMOS AL USUARIO(3)
    M[a][b]=3;
    return;
}

int niveljuego(int nivel){
    printf("Nivel de dificultad(1 al 10):\n");
    scanf("%d",&nivel);
    getchar;
    return(nivel);
}

void carrera(){
    srand(time(NULL));
    int M[N][N];
    int L=niveljuego(L);
    int estado=0;
    inicializar(M);
    do{
        imprimir(M);
        usuario(M,&estado);
        zombies(M,L);
    }while(estado==0);
    if(estado==1){
        printf("FIN DEL JUEGO.");
    }
    return;
}

int main (void){
    carrera();
    getche;
    return 0;

}
