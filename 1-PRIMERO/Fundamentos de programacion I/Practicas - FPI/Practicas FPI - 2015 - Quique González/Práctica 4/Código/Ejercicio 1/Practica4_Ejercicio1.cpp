#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>

#define N 6

int Level(){
    int level;
    do{//Filtramos el nivel que introduce el usuario
        printf("Introduzca nivel del 1 al 3: "); scanf("%d",&level); getchar();
        if (level<1 || level>3){
            printf("Error. Ese nivel no se corresponde a ninguno de los indicados");
        }
    }while(level<1 || level>3);
    return level;//Devolvemos el nivel introducido
}

int Cursores(){
    int c;
    //esperamos una tecla
    char tecla = getch();
    //doble código en caso de que sea un cursor
    if(tecla==-32 || tecla==0) tecla=getch();
    //en función de la tecla pulsada
    switch(tecla){
    case 72:
    case '8':
        c=-1;
        //ARRIBA
        break;
    case 80:
    case '2':
        c=1;
        //ABAJO
        break;
    case 13:
        c=0;
        //ENTER
        break;
    }
    return c;
}

void Dibujar (int canion, int aliens[], int puntos){//Creamos la función que se encargue de dibujar el cañon y los aliens
    int longitud;

    system("cls");//Borramos pantalla para que no se acomulen las animaciones
    printf("Invasion alienigena\n---------------------\nPuntuacion: %d\n", puntos);
    for (int i=0;i<N;i++){//Recorremos las tres partes que tienen tanto el cañon como lo los alienigenas
        for(int j=0;j<3;j++){
            if(i==canion){
                longitud=aliens[i]-2;
                if (j==0){
                    printf("\\ ");
                }else{
                    if(j==1){
                      printf("==");
                    }else{
                        printf("/ ");
                    }
                }
            }else{
                longitud=aliens[i];
            }
            for (int y=0;y<longitud;y++) printf(" ");

            if (j==0){
                printf(" o o\n");
            }else{
                if(j==1){
                  printf(" |_|\n");
                }else{
                    printf("/\\ /\\ \n");
                }
            }
        }
    }
    return;
}

char Menu(){//Introducimos un menú que se activará cuando el usuario haya perdido
    char a[100];
    do{//Filtramos la opción escogida
        printf("\n MENU\n------\nVolver a jugar: a\nSalir del juego: b\n\n");
        printf("Introduzca opcion a o b: "); gets(a);
        if (a[0]!='a' && a[0]!='b') printf("Error. Caracter invalido.\n");
    }while(a[0]!='a' && a[0]!='b');
    return a[0];
}

void Canion_vs_Aliens(void){

    char opcion;

    do{//Bucle que finalizará cuando el usuario introduzca una b en el menú
        int level, aliens[N], canion=N/2, puntos=0, gameover=0,i;

            system("cls");
            printf("Invasion alienigena\n---------------------\n");
            level= Level();

            for (i=0;i<N;i++){//Inicializamos cada alien a 80
                aliens[i]=80;
            }


            Dibujar(canion,aliens,puntos);//Invocamos la función Dibujar

            do{//Bucle hasta que un alien llegue a la parte izquierda de la pantalla
                int cursor=Cursores(), i;
                if((cursor==1 && canion!=N-1) || ((cursor==-1) && canion!=0) || cursor==0){
                    for(i=0;i<N;i++){
                        aliens[i]=aliens[i]-(rand()%(level+2)*2);
                    }
                    if((cursor==1 && canion!=N-1) || (cursor==-1 && canion!=0)){
                        canion=canion+cursor;
                    }else{
                        if (cursor==0){
                            aliens[canion]=80;
                            puntos++;
                        }
                    }
                    for (int i=0;i<N;i++){
                        if (aliens[i]<=0){//Cambiar el valor de gameover para que finalice el juego
                            gameover=1;
                        }
                    }

                    Dibujar(canion,aliens, puntos);
                }

            }while (gameover==0);

            printf("Partida finalizada. Has consegido %d puntos. \n", puntos);
            opcion=Menu();//Invocar el menú

    }while(opcion=='a');

    return;
}

int main(void){

    srand(time(NULL));
    Canion_vs_Aliens();//Invocamos la función que ejecuta el juego


    return 0;
}
