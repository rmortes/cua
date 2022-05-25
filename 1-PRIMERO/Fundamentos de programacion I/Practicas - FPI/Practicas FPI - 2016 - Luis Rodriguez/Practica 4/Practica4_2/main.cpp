#include  <stdio.h>
#include  <string.h>
#include  <math.h>
#include  <stdlib.h>
#include  <time.h>


#define F 20 // Sera la x
#define C 10 // Sera la y

#define Casilla_Vacia 0
#define Casilla_Negra 1
#define Asterisco 2
#define Salida   3
#define Jugador   4

void InversionMatriz(int M[][C]){

    //Buscamos los asteriscos para pasarlos a blanco y los demas con una probablididad de 50% se pasaran a negro

    for(int j=0;j<C;j++){
        for(int i=0;i<F;i++){
            if(M[i][j]==Asterisco ){
                M[i][j]=Casilla_Vacia;
            }else{
                if(M[i][j]==Casilla_Vacia){
                    M[i][j]={M[i][j]+rand()%2};
                }  }}}

    return;
}
void Tecla(int M[][C],int *x,int *y){

    //Introducimos una tecla para el movimiento del asterisco

    char tecla=getchar();
    if(tecla==-32 || tecla==0) {tecla=getchar();}

    //Movimiento segun la tecla pulsada

    switch(tecla){

    case 65: case 97:  if(M[*x-1][*y]!=Casilla_Negra){if((*x-1)>=0){M[*x][*y]=Asterisco; *x=*x-1;  M[*x][*y]=Jugador;}}  break;//IZQUIERDA (A o a)
    case 68: case 100: if(M[*x+1][*y]!=Casilla_Negra){if((*x+1)<F){M[*x][*y]=Asterisco; *x=*x+1;   M[*x][*y]=Jugador;}}   break;  //DERECHA (D,d)
    case 87: case 119: if(M[*x][*y-1]!=Casilla_Negra){if((*y-1)>=0){ M[*x][*y]=Asterisco; *y=*y-1; M[*x][*y]=Jugador;}} break;  //ARRIBA (W,w)
    case 83: case 115: if(M[*x][*y+1]!=Casilla_Negra){if((*y+1)<=C){ M[*x][*y]=Asterisco; *y=*y+1; M[*x][*y]=Jugador;}} break;  //ABAJO (S,s)

    }
}

void Dibujar(int M[][C],int n){

    //Limpiamos la pantalla para que no se vean las repeticiones del bucle

        system("cls");

        printf("Jugador %d:\n",n);

        //Linea Superior delimitante

       printf("|"); for(int i=0;i<F;i++) {printf("-");}   printf("|\n");

        //Impresion de Pantalla

        for(int j=0;j<C;j++){
            printf("|");
            for(int i=0;i<F;i++){
                switch (M[i][j]) {
                case Casilla_Vacia: printf(" "); break;
                case Casilla_Negra: printf("%c",219); break;
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
void Juego(){

        //Declaracion de las variables

        int a=0;
        int b=0;
        int Matriz[F][C];

        //Inicializar toda la matriz a 0

        for(int j=0;j<C;j++){
            for(int i=0;i<F;i++){
                Matriz[i][j]=Casilla_Vacia;
            }
        }
        a=0;b=0;
        Matriz[a][b]=Jugador;
        Matriz[F-1][C-1]=Salida;


        do{
            Dibujar(Matriz,1);
            Tecla(Matriz,&a,&b);}

        while(Matriz[a][b]!=Matriz[F-1][C-1]);


       InversionMatriz(Matriz);
       a=0;b=0;
       Matriz[a][b]=Jugador;
       Matriz[F-1][C-1]=Salida;

        do{
            Dibujar(Matriz,2);
            Tecla(Matriz,&a,&b);}

        while(Matriz[a][b]!=Matriz[F-1][C-1]);

        system("cls");

char respuesta='S';


 system("cls");
    printf("¿Quieres volver a jugar? (s/n)\n");
    scanf("%s",&respuesta);getchar();





        if(respuesta=='s'|| respuesta=='S'){ Juego();}else {return;}



}


int main()
{
Juego();
    return 0;
}
