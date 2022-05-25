#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

#define N 10

//Funcion que selecciona el nivel de dificultad
int nivel(){
    int n;
    //Bucle que se repite si el numero no es correcto
    do{
        printf ("Seleccione su nivel de dificultad entre (1 y 10):");
        scanf("%d",&n);
    }while(n>10 || n<1);
    return n;
}

//Funcion movimiento robot
int Movimiento_robot(int vec_agua[N], int pos){
    //esperamos una tecla
    char tecla = getch();
    //doble código en caso de que sea un cursor
    if(tecla==-32 || tecla==0) tecla=getch();
    //en función de la tecla pulsada
    switch(tecla){
    case 72:
    case '8':
        //ARRIBA
        if(pos>0) pos--;
        break;
    case 80:
    case '2':
        //ABAJO
        if(pos<N-1) pos++;
        break;
    case 13:
        //INTRO
        vec_agua[pos]=0;
        break;
    }
    return pos;
}

//Pone agua en las habitaciones
int rellenar_agua(int level, int vec_agua[N]){
    int aux,L;
    //Centinela para para el juego.
    int cent=0;
    L=level;
    do{
        aux=rand()%N;
        if(vec_agua[aux]!=N)vec_agua[aux]= vec_agua[aux]+1;
        else cent=1;
        L--;
    }while(L==0);
    return cent;
}

//Crea el agua por habitación
void crea_agua(int vec_agua[N]){
    for(int i=0;i<N;i++){
        vec_agua[i]=rand()%(N/2);
    }
    return ;
}

//Funcion que crea el robot
int inic_robot(void){
    int pos = rand()%N;
    return pos;
}

//Funcion tablero
void tablero(int vec_agua[N],int contador, int robot){
    system("cls");
    printf("El juego del robot bombero\n---------------------------\nRondas conseguidas: %d\n",contador);
    for (int i=0; i<N; i++){
        if(robot==i) printf("R");
        else printf(" ");
        printf("|");
        for (int j=0; j<vec_agua[i]; j++){
            printf("~");
        }
        for (int j=0; j<N-vec_agua[i]; j++){
            printf(" ");
        }
        printf("|\n");
    }
    printf("\nCursores: (Arriba/Abajo)Para mover y ENTER para drenar agua\n");
    return;
}

//Funcion juego, aqui se inicializan algunas variables.
void juego(int level, int vec_agua[N], int robot){
    int cent=0;
    int contador=0;
    do{
        tablero(vec_agua,contador,robot);
        robot = Movimiento_robot(vec_agua,robot);
        cent=rellenar_agua(level,vec_agua);
        contador++;
    }while(cent==0);
    printf("\n\n  ~  ~  ----> LOSER <----  ~  ~  \n\n");
}

//Inicio juego.
void Iniciojuego(){
    int vec_agua[N];
    int level;
    printf("--------JUEGO DEL ROBOT BOMBERO--------\n");
    level=nivel();
    crea_agua(vec_agua);
    int robot = inic_robot();
    juego(level,vec_agua,robot);
    return;
}

//Funcion principal
int main(){
    srand(time(NULL));
    Iniciojuego();
    return (0);
}
