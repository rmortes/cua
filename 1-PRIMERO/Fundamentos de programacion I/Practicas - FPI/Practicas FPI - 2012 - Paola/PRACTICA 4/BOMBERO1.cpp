#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#define N 10

int juego(int H[N],int posicion,int*dificultad){
    if(*dificultad==0){
        printf("Elige un nivel de dificultad\n");
        scanf("%d",&*dificultad);
        getchar;
    }
        printf("Utiliza arriba/abajo para moverte y ENTER para drenar");
    //CURSORES
        char tecla= getch();
        if(tecla==-32 || tecla==0){
            tecla=getch();
            switch(tecla){
            case 72:
            case '8':
                //ARRIBA
                posicion=posicion-1;
                break;
              case 80:
              case '2':
                //ABAJO
                posicion=posicion+1;
                break;
              case 13:
                //INTRO
                H[posicion]=0;
                break;
            }
        }
    for(int i=0;i<(*dificultad);i++){
        int l=rand()%N;
        H[l]=(H[l]+1);
    }
    return(posicion);
}

int pos(int H[N],int posicion){
    posicion=rand()%10;
    for(int j=0;j<N;j++){
        H[j]=rand()%N/2;
    }
    return(posicion);
}

void imprimir(int H[N],int posicion){
    system("cls");
    printf("JUEGO DEL ROBOT BOMBERO\n-------------------\n");
    for(int i=0;i<N;i++){
            if (posicion==i){
                printf("R");
            }else{
                printf(" ");
            }
            printf("|");
            for(int j=0;j<H[i];j++){
                printf("@");
            }
            for(int l=0;l<N-H[i];l++){
                printf(" ");
            }
            printf("|\n");
        }
    return;
}

int comprobar(int H[N],int acaba){
    for(int i=0;i<N;i++){
        if(H[i]==10){
            acaba=1;
        }
    }
    return(acaba) ;
}

void bombero(){
    int H[N];
    int posicion;
    int dificultad=0;
    int acaba=0;
    srand(time(NULL));
    posicion=pos(H,posicion);
    do{
        imprimir(H,posicion);
        posicion=juego(H,posicion,&dificultad);
        imprimir(H,posicion);
        acaba=comprobar(H,acaba);
    }while(acaba==0);
    printf("EL JUEGO HA TERMINADO");
return;
}

int main (void){
    bombero();
    getche();
    return 0;

}
