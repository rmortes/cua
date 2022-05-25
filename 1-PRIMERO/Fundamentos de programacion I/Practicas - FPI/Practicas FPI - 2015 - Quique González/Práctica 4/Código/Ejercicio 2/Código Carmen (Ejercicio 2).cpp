#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#define N 18
#define personaje_vivo 0
#define personaje_muerto 1
#define libre_oculto 2
#define mina_oculta 3
#define libre_descubierto 4
#define mina_descubierta 5

int EleccionNivel (){
    int a;
    do{
        scanf("%d",&a);
        getchar();
        if(a<1 || a>3) printf("\nError. Nivel invalido. Introduzca nivel (1-3): ");
    }while(a<1 || a>3);
    return a;
}

void Inicializar_Matriz(int matriz[N][N],int *cantidadminas){
    for (int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            matriz[j][i]=libre_oculto; //inicializo la matriz a libre
        }
    }
    matriz[(N-1)/2][0]=personaje_vivo;

    while(*cantidadminas>0){ //coloco las minas
        int a=rand()%N, b=rand()%N;
        if(matriz[a][b]==libre_oculto){
            matriz[a][b]=mina_oculta;
            *cantidadminas=*cantidadminas-1;
        }
    }
    return;
}

void Tecla(int matriz[N][N],int *ganado,int *perdido, int *bombas){
    int persX,persY;
    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
            if (matriz[j][i]==personaje_vivo){
                persX=j;
                persY=i;
            }

    char tecla=getch();
    if(tecla==-32 || tecla==0) tecla=getch();
    switch(tecla){
    case 72: //arriba
    case '8':
        if(persY>0){// si no está arriba del todo
            matriz[persX][persY]=libre_descubierto;
            persY--;
        }
        break;
    case 80: //abajo
    case '2':
        if(persY<N-1){ //si no está abajo del todo
            matriz[persX][persY]=libre_descubierto;
            persY++;
        }
        break;
    case 75: //izquierda
    case '4':
        if(persX>0){ //si no está a la izq del todo
            matriz[persX][persY]=libre_descubierto;
            persX--;
        }
        break;
    case 77: //derecha
    case '6':
        if(persX<N-1){ //si no está a la derecha del todo
            matriz[persX][persY]=libre_descubierto;
            persX++;
        }
        break;
    case 13: //bomba descubreminas
        int yahatiradobombaaqui=1;
        if(*bombas>-1){
            for (int i=persY-2;i<=persY+2;i++) //recorremos las 24 posiciones alrededor del personaje
                for (int j=persX-2;j<=persX+2;j++){
                    if (j<0) j=0; //lo que está fuera de la pantalla no nos interesa
                    if (i<0) i=0;
                    if (matriz[j][i]==libre_oculto || matriz[j][i]==mina_oculta) yahatiradobombaaqui=0; //falso
                }
            if (yahatiradobombaaqui==0){
                if (*bombas>0){
                    for (int i=persY-2;i<=persY+2;i++) //recorremos las 24 posiciones alrededor del personaje
                        for (int j=persX-2;j<=persX+2;j++){
                            if (j<0) j=0; //lo que está fuera de la pantalla no lo vamos a tocar
                            if (i<0) i=0;
                            switch (matriz[j][i]){
                            case libre_oculto:
                                matriz[j][i]=libre_descubierto;
                                break;
                            case mina_oculta:
                                matriz[j][i]=mina_descubierta;
                                break;
                            }
                        }
                }
                *bombas=*bombas-1;
            }
        }
        break;
    }

    if(matriz[persX][persY]!=mina_oculta && matriz[persX][persY]!=mina_descubierta){ //si donde queremos poner al pers no hay mina:
        matriz[persX][persY]=personaje_vivo;  //movemos al pers
        if(persY==N-1) *ganado=1;  //si ha llegado al final ganamos
    }else{ //si donde queremos ponerlo sí hay mina muere
        matriz[persX][persY]=personaje_muerto;
        *perdido=1;
    }
    return;
}

char Volver_A_Jugar(void){
    char a[10];
    do{
        printf("\n\nQuieres volver a jugar? (S/N): ");
        gets(a);
        if (a[0]!='s' && a[0]!='S' && a[0]!='n' && a[0]!='N') printf("Error. Caracter invalido.\n");
    }while(a[0]!='s' && a[0]!='S' && a[0]!='n' && a[0]!='N');
    return a[0];
}

void Imprimir (int bombas,int matriz[N][N],int nivel){
    system("cls");
    if (bombas>-1) printf("Escapada del campo de minas. Nivel: %d. Bombas restantes: %d.\n------------------------------------------",nivel,bombas);
    else printf("Escapada del campo de minas.  Nivel: %d. NO TE QUEDAN BOMBAS!\n------------------------------------------",nivel);

    int minacercana=9;   //inicialización de la variable del personaje que indica la mina más cercana
    for (int i=0;i<N;i++) {
        printf("\n");
        for(int j=0;j<N;j++)
            switch (matriz[j][i]){
            case personaje_vivo:
                for(int minaY=0;minaY<N;minaY++)
                    for(int minaX=0;minaX<N;minaX++)
                        if(matriz[minaX][minaY]==mina_descubierta || matriz[minaX][minaY]==mina_oculta) {
                            int valorabs1,valorabs2;
                            if ((j-minaX)>0) valorabs1=j-minaX;
                            else valorabs1=(-1)*(j-minaX);
                            if ((i-minaY)>0) valorabs2=i-minaY;
                            else valorabs2=(-1)*(i-minaY);
                            if (minacercana>valorabs1+valorabs2) minacercana=valorabs1+valorabs2;
                        }
                printf("%d",minacercana);
                break;
            case personaje_muerto:
                printf("X");
                break;
            case libre_oculto:
            case mina_oculta:
                printf("~");
                break;
            case libre_descubierto:
                printf(" ");
                break;
            case mina_descubierta:
                printf("M");
                break;
            }

    }
    return;
}



void Juego (void){
    char otravez;
    int matriz[N][N];
    do{
        int ganado=0,perdido=0;
        system("cls");
        printf("Vietnam 1973. Escapada del campo de minas.\n------------------------\nIntroduzca nivel (1-3): ");
        int bombas=2;
        int nivel=EleccionNivel();
        int cantidadminas=((N*N)*nivel)/10; //cálculo de la cantidad de minas en función del nivel
        Inicializar_Matriz(matriz,&cantidadminas);

        while(ganado==0 && perdido==0){
            Imprimir(bombas,matriz,nivel);
            Tecla(matriz,&ganado,&perdido,&bombas);
        }
        Imprimir(bombas,matriz,nivel);
        otravez=Volver_A_Jugar();
    }while(otravez=='s' || otravez=='S');

    return;
}

int main (void){
    srand(time(NULL));
    Juego();
    return 0;
}
