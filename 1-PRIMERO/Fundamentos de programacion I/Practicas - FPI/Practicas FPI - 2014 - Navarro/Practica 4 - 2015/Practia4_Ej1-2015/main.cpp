#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <conio.h>
#include <time.h>

#define N 6

void Movimiento_nave(int vec_nave[N], int vec_alien[N], int Numeraco){
    int aux;
    //esperamos una tecla
    char tecla = getch();
    //doble código en caso de que sea un cursor
    if(tecla==-32 || tecla==0) tecla=getch();
    //en función de la tecla pulsada
    switch(tecla){
    case 72:
        for(int i=0;i<N; i++){
            if(vec_nave[i]==1){
                if(i!=0){
                    aux=i;
                    vec_nave[aux-1]=1;
                    vec_nave[aux]=0;
                }
            }
        }
    case '8':
        //ARRIBA
        break;
    case 80:
        for(int i=(N-1);i>=0; i--){

            if(vec_nave[i]==1){
                if(i!=(N-1)){
                    aux=i;
                    vec_nave[aux+1]=1;
                    vec_nave[aux]=0;
                }
            }
        }
    case '2':
        //ABAJO
        break;
    case 13:
        for(int i=0; i<N; i++){
            if(vec_nave[i]==1){
                vec_alien[i]=Numeraco;
            }
        }
        //ENTER
        break;
    }
}

int probabilidad(int aleatorio){
    int num;
    if(6< aleatorio && aleatorio<=9) num=3;
    if(3< aleatorio && aleatorio<=6) num=2;
    if(aleatorio<=3) num=1;
    return (num);
}

int Movimiento_alien(int vec_alien[N], int Niv){
    int aleatorio, num,centinela=0;
    for (int i=0; i<N; i++){
        aleatorio=rand()%(Niv+2)*2;
        num=probabilidad(aleatorio);
        vec_alien[i]= vec_alien[i]-num;
        if(vec_alien[i]==0){
            centinela=1;
        }
    }
    return(centinela);
}

void Dibujar(int vec_nave[N], int vec_alien[N]){
    //For que recorre el vector nave y tambien el del alien
    for(int i=0; i<N; i++){
        //Condicion que muestra la posicion de la nave en el vector
        if(vec_nave[i]==1){
            //Dibuja la primera ala de la nave
            printf("\\ ");
            //Recorre el vector de alien en busca del numero del vector
            //Una vez que ya ha encontrado la posicion del vector imprime espacios, tantos como valga su valor
            for(int j=0; j<vec_alien[i]; j++){
                printf(" ");
            }
            //Imprime los ojos del alien.
            printf(" o o \n");

            printf("--");
            for(int j=0; j<vec_alien[i]; j++){
                printf(" ");
            }
            printf(" |_| \n");

            printf("/ ");
            for(int j=0; j<vec_alien[i]; j++){
                printf(" ");
            }
            printf("/\\ /\\\n");

        }else{
            //Dibuja la primera ala de la nave
            printf("  ");
            //Recorre el vector de alien en busca del numero del vector
            //Una vez que ya ha encontrado la posicion del vector imprime espacios, tantos como valga su valor
            for(int j=0; j<vec_alien[i]; j++){
                printf(" ");
            }
            //Imprime los ojos del alien.
            printf(" o o \n");

            printf("  ");
            for(int j=0; j<vec_alien[i]; j++){
                printf(" ");
            }
            printf(" |_| \n");

            printf("  ");
            for(int j=0; j<vec_alien[i]; j++){
                printf(" ");
            }
            printf("/\\ /\\\n");
        }
    }
}

void jugar(int vec_nave[N], int vec_alien[N], int Numeraco, int Niv){
    int contador=1, centinela;
    do{
        printf("Número de la ronda: %d\n", contador);
        Dibujar (vec_nave, vec_alien);
        Movimiento_nave (vec_nave,vec_alien,Numeraco);
        centinela = Movimiento_alien (vec_alien, Niv);
        system("cls");
        contador++;
    }while(centinela!=1);
    printf("Ronda máxima : %d\n", contador);
    printf("\t\t\t Intentalo de nuevo\t\t\t\n");
}

void Inicio_alien(int vec_alien[N], int Numeraco){
    for (int i=0; i<N; i++){
        vec_alien[i]= Numeraco;
    }
}

void Inicio_nave(int vec_nave[N]){
    int posicion=(N/2);
    for (int i=0; i<N; i++){
        if(i == posicion){
            vec_nave[i]=1;//pintar la nave
        }else{
            vec_nave[i]=0;
        }
    }
}

int Seleccion_de_nivel(){
    int Niv;
    Niv=0;
    do{
    printf("Introduzca un numero entre (1 - 3): ");
    scanf("%d",&Niv);
    getchar();
    }while(Niv < 1 || Niv > 3);
    return (Niv);
}

int main (void){
    int Niv;
    int vec_nave[N];
    int vec_alien[N];
    int Numeraco;
    Numeraco = 50;

    Niv=Seleccion_de_nivel();
    Inicio_nave(vec_nave);
    Inicio_alien(vec_alien, Numeraco);
    jugar(vec_nave, vec_alien, Numeraco, Niv);

    return(0);
}

/*
void comandos(int vec[N]){
    int aux;
    //esperamos una tecla
    char tecla = getch();
    //doble código en caso de que sea un cursor
    if(tecla==-32 || tecla==0) tecla=getch();
    //en función de la tecla pulsada
    switch(tecla){
    case 72:
            for(int i=0;i<N; i++){
                if(vec[i]==1){
                    if(i!=0){
                    aux=i;
                    vec[aux-1]=1;
                    vec[aux]=0;
                    }
                }
            }
    case '8':
    //ARRIBA
    break;
    case 80:
        for(int i=(N-1);i>=0; i--){

                if(vec[i]==1){
                    if(i!=(N-1)){
                    aux=i;
                    vec[aux+1]=1;
                    vec[aux]=0;
                    }
                }
            }
    case '2':
    //ABAJO
    break;
    case 13:
    //ENTER
    break;
    }
}

int ponermarcianitos(int n){
    printf("   |");
    for(int j=0; j<(n); j++){
        printf(" ");
    }
    return (n);
}

int probabilidad(int aleatorio){
    int num;
    if(6< aleatorio && aleatorio<=9) num=3;
    if(3< aleatorio && aleatorio<=6) num=2;
    if(aleatorio<=3) num=1;
    return (num);
}

void Tablero(int n,int Niv, int vec[N]){
    int aleatorio;int num;
    for (int i=0; i<N; i++){
        aleatorio=rand()%(Niv+2)*2;
        num=probabilidad(aleatorio);
        n=n-num;
        if(vec[i]==0){
            printf("  ");
            n=ponermarcianitos(n);
            printf(" o o \n");
            printf("  ");
            n=ponermarcianitos(n);
            printf(" |_| \n");
            printf("  ");
            n=ponermarcianitos(n);
            printf("/\\ /\\\n");
        }
        if(vec[i]==1){
            printf("\\ ");
            n=ponermarcianitos(n);
            printf(" o o \n");
            printf("--");
            n=ponermarcianitos(n);
            printf(" |_| \n");
            printf("/ ");
            n=ponermarcianitos(n);
            printf("/\\ /\\\n");
        }
    }
}

void Inicio_Tablero(int n,int vec[N]){
    for (int i=0; i<N; i++){
        if(vec[i]==0){
            printf("  ");
            n=ponermarcianitos(n);
            printf(" o o \n");
            printf("  ");
            n=ponermarcianitos(n);
            printf(" |_| \n");
            printf("  ");
            n=ponermarcianitos(n);
            printf("/\\ /\\\n");
        }
        if(vec[i]==1){
            printf("\\ ");
            n=ponermarcianitos(n);
            printf(" o o \n");
            printf("--");
            n=ponermarcianitos(n);
            printf(" |_| \n");
            printf("/ ");
            n=ponermarcianitos(n);
            printf("/\\ /\\\n");
        }
    }
}

void Inicio_nave(int vec[N]){
    int num;
    num=4;
    //num=rand()%6;
    for(int i=(N-1); i>=0; i--){
        if(num==i){
            vec[i]=1;
        }else{
            vec[i]=0;
        }
    }
    return;
}

int seleccion_nivel(void){
    int Niv;
    Niv=0;
    do{
    printf("Introduzca un numero entre (1 - 3): ");
    scanf("%d",&Niv);
    getchar();
    }while(Niv < 1 || Niv > 3);
    return (Niv);
}

void jugar(int n,int Niv, int vec[N]){
    do{
    Tablero(n,Niv, vec);
    comandos(vec);
    system("cls");
    }while(1);
}

int main(void){
    int vec[N];
    int Niv;
    int n=45;

    Niv=seleccion_nivel();
    Inicio_Tablero(n, vec);
    Inicio_nave(vec);
    jugar(n,Niv, vec);

    return(0);
}
*/
