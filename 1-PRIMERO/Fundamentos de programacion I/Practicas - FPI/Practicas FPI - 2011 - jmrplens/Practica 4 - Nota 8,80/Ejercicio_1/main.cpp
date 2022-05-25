#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include <time.h>

#define TAM 10



void juego(char drain[TAM], int habitaciones[TAM], int *puntos,int *full){

    // Declaración de variables
    char opcionJuego;
    int cent=0,posicion=0,num, pneto;
    float tiempo=0;
    clock_t t_fin=0, t_ini=0;
    t_ini=clock();
    do {
        // Inicialización de las variables
        int cent2=0;

        // Asigna el valor de la opcion elegida por el usuario
        opcionJuego=getch();      
        fflush(stdin);
        //Segun el valor recogido, realizara 3 tipos de acciones, desplazamiento horizontal, o drenar
        if(opcionJuego=='o' || opcionJuego=='O'){
            for(int i=0; i<TAM; i++){
                if(drain[i]=='*' && !(drain[0]==drain[i])){
                    drain[i-1]='*';
                    drain[i]=' ';
                }
            }
            cent=0;
            // Aumenta aleatoriamente el nivel de agua
            posicion=rand()%TAM;
            habitaciones[posicion]++;
        }
        else if(opcionJuego=='p' || opcionJuego=='P'){
            for(int i=0;i<TAM;i++){
                if(drain[i]=='*' && !(drain[TAM-1]==drain[i]) && cent2!=1){
                    drain[i+1]='*';
                    drain[i]=' ';
                    cent2=1;
                }
            }
            cent=0;

            // Aumenta aleatoriamente el nivel de agua
            posicion=rand()%TAM;
            habitaciones[posicion]++;
        }
        else if(opcionJuego=='q' || opcionJuego=='Q'){
            for(int i=0;i<TAM;i++){
                if(drain[i]=='*'){
                    num=habitaciones[i];
                    habitaciones[i]='0';

                    switch(num){
                    case '1':
                        *puntos=*puntos+1;
                        break;
                    case '2':
                        *puntos=*puntos+2;
                        break;
                    case '3':
                        *puntos=*puntos+3;
                        break;
                    case '4':
                        *puntos=*puntos+4;
                        break;
                    case '5':
                        *puntos=*puntos+5;
                        break;
                    }
                }
            }
            cent=0;
            // Se incrementa el nivel de agua
            posicion=rand()%TAM;
            habitaciones[posicion]++;
        }
        else{
            cent=1;
        } 
    } while(cent==1);

    system("cls");
    // Comprueba el nivel de agua
    for(int i=0;i<TAM;i++){
        if(habitaciones[i]>='6'){
            *full=1;
        }
    }
    //Si alguna habitacion esta llena, se termina el juego
    if (*full==1){
        tiempo=float(t_ini-t_fin)/1000;
        // Puntuación final del juego
        printf("\n\tPuntuacion: %d\n\n",*puntos);
        printf("\tTiempo transcurrido: %.3f segundos\n", tiempo);
        pneto=(*puntos/(tiempo*5))*60;
        printf("\tPuntuacion final: %d\n", pneto);
        getch();
    }
}
void edificio (){
    //Declaracion de variables
    char drain[TAM];
    int habitaciones[TAM], puntos=0, full=0;

    // Inicio del juego
    printf("\n\tPulsa una tecla para empezar");
    getch();
    system("cls");
    for(int i=0;i<TAM;i++){
        habitaciones[i]=rand()%4+48;
    }
    for(int i=0;i<TAM;i++){
        drain[i]=' ';
    }

    drain[TAM/2]='*';

    do{
        // Interfaz
        for(int i=0;i<TAM; i++){
            printf(" ");
            printf("%c",habitaciones[i]);
        }
        printf("\n");
        for(int i=0; i<TAM;i++){
            printf(" ");
            printf("%c", drain[i]);
        }
        printf("\n");
        printf("\nAcciones:\n");
        printf("o - Mover izquierda\n");
        printf("p - Mover derecha\n");
        printf("q - Drenar agua\n\n\n");
        printf("Puntuacion: %d\n\n",puntos);

        juego(drain, habitaciones, &puntos, &full);
    }while(full==0);
}
void repetir (){
    // Declaracion variables
    int a=0, cent;
    do{
        do{
            cent=0;
            printf("\n\tQuieres jugar de nuevo (s/n)? ");
            a=getch();
            //Limpiamos el buffer
            fflush(stdin);
            system("cls");
        }while(!(a=='s' || a=='n' || a=='S' || a=='N'));
        if (a=='s' || a=='S'){
            cent=1;
            edificio();
        }
    }while(cent==1);
}
void inicio (){

    edificio();
    repetir();
}
int main() {

    inicio();
}
