#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#define N 5

int Nivel (){
    int nivel;
    do{
        scanf("%d",&nivel);
        getchar();
        if(nivel<1 || nivel>3) printf("\nError. Nivel invalido. Introduzca nivel (1-3): ");
    }while(nivel<1 || nivel>3);
    return nivel;
}

int Tecla(){
    int n;
    char tecla=getch();
    if(tecla==-32 || tecla==0) tecla=getch();
    switch(tecla){
    case 72: //arriba
    case '8':
        n=-1;
        break;
    case 80: //abajo
    case '2':
        n=1;
        break;
    case 13: //disparar
        n=0;
        break;
    }
    return n;
}

void Imprimir (int ubicnave, int aliens[], int puntuacion){
    system("cls");
    int espacios;
    printf("Invasion extraterrestre. Puntuacion actual: %d\n----------------------------------------\n",puntuacion);
    for (int i=0; i<N; i++){
        for(int y=0;y<3;y++){
            if (i==ubicnave){
                espacios=aliens[i]-2;
                if(y==0) printf("\\ ");
                else if (y==1) printf("==");
                else printf("/ ");
            }else espacios=aliens[i];

            for (int x=0;x<espacios;x++) printf(" ");

            if (y==0) printf (" o o \n");
            else if (y==1) printf (" |_| \n");
            else printf ("/\\ /\\\n");
        }
    }
    return;
}

char Volver_A_Jugar(void){
    char a[10];
    do{
        printf("Quieres volver a jugar? (S/N): ");
        gets(a);
        if (a[0]!='s' && a[0]!='S' && a[0]!='n' && a[0]!='N') printf("Error. Caracter invalido.\n");
    }while(a[0]!='s' && a[0]!='S' && a[0]!='n' && a[0]!='N');
    return a[0];
}

void juego (void){
    char again;

    do{
        int puntuacion=0, nave=N/2, aliens [N];
        int fin=0; //para saber cuando ha llegado algún bicho a la tierra

        system("cls");
        printf("Invasion extraterrestre.\n----------------------\nIntroduzca nivel (1-3): ");
        int nivel=Nivel();
        for (int i=0;i<N;i++) aliens[i]=74; //inicializa todos los espacios de los aliens

        Imprimir(nave,aliens,puntuacion);

        do{ //mientras que no se haya perdido
            int tecla=Tecla();
            if((tecla==1 && nave!=N-1) || ((tecla==-1) && nave!=0) || tecla==0){
                for (int i=0;i<N;i++) aliens[i]=aliens[i]-rand()%(((nivel+2)*2)+1);

                if((tecla==1 && nave!=N-1) || (tecla==-1) && nave!=0) nave=nave+tecla; //movimiento
                else if (tecla==0){//disparo
                    aliens[nave]=74;
                    puntuacion++;
                }

                for (int i=0;i<N;i++) if (aliens[i]<=0) fin=1;

                Imprimir(nave,aliens,puntuacion);
            }

        }while(fin==0);

        printf("La partida ha terminado con %d puntos.\n",puntuacion);

        again=Volver_A_Jugar();
    }while(again=='s' || again=='S');

    return;
}
int main (void){
    srand(time(NULL));
    juego();
    return 0;
}
