#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#define N 6

int Nivel (){
    int nivel;
    do{
        printf("\nIntroduzca nivel (1-3): ");
        scanf("%d",&nivel);
        getchar();
        if(nivel<1 || nivel>3) printf("Error. Nivel invalido.\n");
    }while(nivel<1 || nivel>3);
    return nivel;
}

void Tecla(int *movimiento){
    char pulsado=getch();
    if(pulsado==-32 || pulsado==0) pulsado=getch();
    switch(pulsado){
    case 72: //arriba
    case '8':
        *movimiento=-1;
        break;
    case 80: //abajo
    case '2':
        *movimiento=1;
        break;
    case 13: //disparar
        *movimiento=0;
        break;
    default:
        *movimiento=2; //se ha pulsado una tecla no válida
        break;
    }
    return;
}

void Imprimir (int ubicnave, int aliens[], int puntuacion, int nivel){
    system("cls");
    int espacios;
    printf("Invasion extraterrestre. Nivel: %d. Puntuacion actual: %d\n----------------------------------------\n",nivel,puntuacion);

    for (int i=0; i<N; i++){ //cambiamos de alien
        for(int j=0;j<3;j++){ //cambiamos de línea de cada alien
            if (i==ubicnave){ //si este alien está en la misma línea que la nave imprimimos la nave también y los espacios son 2 menos
                espacios=aliens[i]-2;
                if(j==0) printf("\\ ");
                else if (j==1) printf("==");
                else printf("/ ");
            }else espacios=aliens[i];

            for (int x=0;x<espacios;x++) printf(" ");

            if (j==0) printf (" o o \n");
            else if (j==1) printf (" |_| \n");
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

void Juego (void){
    char again;

    do{ //mientras que se quiera seguir jugando

        int puntuacion=0, nave, aliens [N];

        if (N%2==0) /*N es par*/ nave=N/2-1; //por estética, para que, puestos que no puede quedar en el centro, quede más arriba que abajo
        else /*N impar*/ nave=N/2;

        int fin=0; //cuando algún bicho llegue a la tierra será =1

        system("cls");
        printf("Invasion extraterrestre.\n----------------------");
        int nivel=Nivel();
        for (int i=0;i<N;i++) aliens[i]=74; //inicializa todos los espacios de los aliens

        Imprimir(nave,aliens,puntuacion,nivel);

        do{ //mientras que no se haya perdido
            int movimiento;
            Tecla(&movimiento);
            if((movimiento==1 && nave!=N-1) || ((movimiento==-1) && nave!=0) || movimiento==0){ //si la tecla es válida
                for (int i=0;i<N;i++) aliens[i]=aliens[i]-rand()%(((nivel+2)*2)+1);  //acercamos a los aliens hacia la tierra (es +1 porque al usar el resto si no el alien nunca se movería el máximo)

                if((movimiento==1 && nave!=N-1) || (movimiento==-1) && nave!=0) nave=nave+movimiento; //movimiento de la nave
                else if (movimiento==0){ //disparo
                    aliens[nave]=74;
                    puntuacion++;
                }

                for (int i=0;i<N;i++) if (aliens[i]<=0) fin=1; //si algún alien ha llegado al límite el juego acaba

                Imprimir(nave,aliens,puntuacion,nivel);
            }

        }while(fin==0);

        printf("La partida ha terminado con %d puntos.\n",puntuacion);

        again=Volver_A_Jugar();
    }while(again=='s' || again=='S');

    return;
}

int main (void){
    srand(time(NULL));
    Juego();
    return 0;
}
