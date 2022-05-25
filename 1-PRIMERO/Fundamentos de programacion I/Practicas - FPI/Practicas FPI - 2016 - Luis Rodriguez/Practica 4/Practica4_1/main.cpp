#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <conio.h>
#define C 5
#define SUELO 7

//funcion que define la posicion de los aliens y el cañon
void init( int posalien[],int *canyon){
    //Decir que empieza desde arriba (altura(0))
    for( int i=0;i<C;i++){
        posalien[i]=0;
    }
    *canyon=C/2;

    return;
}

//funcion que imprime el juego en pantalla
void imprimir(int h,int hmax, int posalien[], int canyon, int *puntos){
    //limpiamos pantalla
    system("cls");
    //puntos acumulados
    printf("PUNTOS: %d \n", *puntos);
    //bucle que recorre verticalmente hasta la posicion del alien y lo imprime en pantalla
    for(h=0;h<hmax;h++){
        for(int i=0;i<C;i++){

            if(posalien[i]==h){
                printf(" ^o.o^ ");
            }
            else{ printf("       ");}
        }
        printf("\n" );
    }

    //bucle que imprime el cañon en su posicion
    for(int i=0;i<canyon;i++){
        printf("       ");
    }

    printf(" //|\\\\\n");
    return;
}

//funcion para controlar el movimiento de los aliens
void movalien(int posalien[],int *fin, int *contador){
    //bucle para saber si avanza para cada posicion del vector C
    int i;
    for(i=0;i<C;i++){
        //con el 50% de probabilidad
        if(rand()%2==0){
            posalien[i]++;
            //el juego acaba si el alien llega al suelo
            if(posalien[i]==SUELO){
                *fin=1;
            }
        }
    }return;
}

//funcion para mover la nave segun las teclas del cursor
void movimientoNave(int *nave, int posalien[], int *puntos){
    char tecla = getch();
    //doble código en caso de que sea un cursor
    if(tecla==-32 || tecla==0) tecla=getch();
    switch(tecla){
    case 75:
    case '4':
        //Izquierda
        if(*nave>0)
            (*nave)--;
        break;
    case 77:
    case '6':
        //Derecha
        if(*nave<C-1)
            (*nave)++;
        break;
        //disparo
    case 13:
        posalien[*nave]=0;
        *puntos=*puntos+5;
        break;
    }return;
}


int pregunta(){
    char a;
    int fin;
    printf("¿Quieres volver a jugar?");
    scanf("%c",&a);
    getchar();
    //Pasamos el carácter a mayusculas para asi evitar la sensibilidad entre mayusculas y minusculas
    if(a=='N' || a=='n'){
        //Acaba el juego
        fin=1;
    }return(fin);
}


void juego(){
    int posalien[C], nave, contador=0;
    int h=0, hmax,  puntos=0;
    hmax=7;
    init(posalien,&nave);
    int fin=0;
    do{
        //Imprimimos pantalla
        imprimir(h, hmax, posalien, nave, &puntos);
        //Decidimos si avanzan los monstruos
        movalien(posalien, &fin, &contador);
        //Caclulamos donde está la nave
        movimientoNave(&nave,posalien, &puntos);
    }while(fin==0);
    return;
}

int main(){
    int final=0;
    do{
        juego();
        final=pregunta();
    }while(final==0);

    return(0);
}
