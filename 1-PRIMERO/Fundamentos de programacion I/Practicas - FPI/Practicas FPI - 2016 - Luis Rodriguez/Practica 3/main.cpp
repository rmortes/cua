#include  <stdio.h>
#include  <string.h>
#include <math.h>
#include <stdlib.h>


#define F 20 // Sera la x
#define C 10 // Sera la y

#define Casilla_Vacia 0
#define Casilla_Negra 1
#define Asterisco 2
#define Salida   3
#define Jugador   4

void Pantalla(int M[][C]){

    //Limpiamos la pantalla para que no se vean las repeticiones del bucle

        system("cls");

        printf("Jugador 1:\n");

        //Linea Superior delimitante

       printf("|"); for(int i=0;i<F;i++) {printf("-");}   printf("|\n");

        //Impresion de Pantalla

        for(int j=0;j<C;j++){
            printf("|");
            for(int i=0;i<F;i++){
                switch (M[i][j]) {
                case Casilla_Vacia: printf(" "); break;
                case Casilla_Negra: printf("%c",126); break;
                case Asterisco:     printf("*");break;
                case Salida:        printf("0");break;
                case Jugador:       printf("+");break;
                }
            }
            printf("|\n");
        }

        //Linea Inferior delimitante

        printf("|");for(int i=0;i<F;i++){ printf("-");}   printf("|\n");
    return;}


int main(){
//Declaracion de las variables

int a=0;
int b=0;
int Matriz[F][C];

//Inicializar
for(int j=0;j<C;j++){
    for(int i=0;i<F;i++){
        Matriz[i][j]=Casilla_Vacia;
    }
}

Matriz[a][b]=Jugador;
Matriz[F-1][C-1]=Salida;

//Se repitira hasta que el Asterisco llegue a la casilla de salida

do{

//Limpiamos la pantalla para que no se vean las repeticiones del bucle

    system("cls");

    printf("Jugador 1:\n");

    //Linea Superior delimitante

   printf("|"); for(int i=0;i<F;i++) {printf("-");}   printf("|\n");

    //Impresion de Pantalla

    for(int j=0;j<C;j++){
        printf("|");
        for(int i=0;i<F;i++){
            switch (Matriz[i][j]) {
            case Casilla_Vacia: printf(" "); break;
            case Casilla_Negra: printf("%c",126); break;
            case Asterisco:     printf("*");break;
            case Salida:        printf("0");break;
            case Jugador:       printf("+");break;
            }
        }
        printf("|\n");
    }




    //Linea Inferior delimitante

    printf("|");for(int i=0;i<F;i++){ printf("-");}   printf("|\n");

    //Introducimos una tecla para el movimiento del Jugador

    char tecla=getchar();
    if(tecla==-32 || tecla==0) {tecla=getchar();}

    //Movimiento segun la tecla pulsada donde dejara el rastro de por donde a pasado el jugador

    switch(tecla){

    case 65: case 97:  if((a-1)>0){ Matriz[a][b]=Asterisco; a=a-1; Matriz[a][b]=Jugador;}  break;   //IZQUIERDA (A o a)
    case 68: case 100: if((a+1)<F){ Matriz[a][b]=Asterisco; a=a+1; Matriz[a][b]=Jugador;}  break;  //DERECHA (D,d)
    case 87: case 119: if((b-1)>0){ Matriz[a][b]=Asterisco; b=b-1; Matriz[a][b]=Jugador;}  break;  //ARRIBA (W,w)
    case 83: case 115: if((b+1)<C){ Matriz[a][b]=Asterisco; b=b+1; Matriz[a][b]=Jugador;}  break;   //ABAJO (S,s)
    }


}while(Matriz[a][b]!=Matriz[F-1][C-1]);

//Buscamos los asteriscos para pasarlos a blanco y los demas con una probablididad de 50% se pasaran a negro

for(int j=0;j<C;j++){
    for(int i=0;i<F;i++){
        if(Matriz[i][j]==Asterisco ){
            Matriz[i][j]=Casilla_Vacia;
        }else{
            if(Matriz[i][j]==Casilla_Vacia){
                Matriz[i][j]={Matriz[i][j]+rand()%2};
            }  }}}

    //Posicionamiento de jugador y la salida
a=0;b=0;
    Matriz[a][b]=Jugador;
    Matriz[F-1][C-1]=Salida;

    //Pantalla del segundo jugador

    do{

    system("cls");

    printf("Jugador 2:\n");

        //Linea Superior delimitante

       printf("|"); for(int i=0;i<F;i++) {printf("-");}   printf("|\n");

        //Impresion de Pantalla

        for(int j=0;j<C;j++){ printf("|");
            for(int i=0;i<F;i++){
                switch (Matriz[i][j]) {
                case Casilla_Vacia: printf(" "); break;
                case Casilla_Negra: printf("%c",126); break;
                case Asterisco:     printf("*");break;
                case Salida:        printf("0");break;
                case Jugador:       printf("+");break;
                default:break;
          }
            }printf("|\n");}

        //Linea Inferior delimitante

        printf("|");for(int i=0;i<F;i++){ printf("-");}   printf("|\n");

        //Introducimos una tecla para el movimiento del asterisco

        char tecla=getchar();
        if(tecla==-32 || tecla==0) {tecla=getchar();}

        //Movimiento segun la tecla pulsada

        switch(tecla){

        case 65: case 97:  if(Matriz[a-1][b]!=Casilla_Negra){if((a-1)>=0){Matriz[a][b]=Asterisco; a=a-1; Matriz[a][b]=Jugador;}}  break;//IZQUIERDA (A o a)
        case 68: case 100: if(Matriz[a+1][b]!=Casilla_Negra){if((a+1)<F){Matriz[a][b]=Asterisco; a=a+1; Matriz[a][b]=Jugador;}}  break;  //DERECHA (D,d)
        case 87: case 119: if(Matriz[a][b-1]!=Casilla_Negra){if((b-1)>=0){ Matriz[a][b]=Asterisco; b=b-1; Matriz[a][b]=Jugador;}} break;  //ARRIBA (W,w)
        case 83: case 115: if(Matriz[a][b+1]!=Casilla_Negra){if((b+1)<=C){ Matriz[a][b]=Asterisco; b=b+1; Matriz[a][b]=Jugador;}} break;  //ABAJO (S,s)

        }
    }while(Matriz[a][b]!=Matriz[F-1][C-1]);


    return 0;}
