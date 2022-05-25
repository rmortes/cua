#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#define F 18
#define C 77
#define libre ' '
#define obstaculo '.'
#define jugador '@'

void Inicializar(char M[][C]){
    //posicion inicial
    for (int i=0;i<F;i++){
        for (int j=0;j<C;j++){
            M[i][j]=libre;
        }
    }
}
//imprimir tablero y las posiciones del jugador
void ImprimirRecuadro(char M[][C],int jugfilas,int jugcolumnas){
    for (int i=1;i<=C+2;i++) {
        printf("-");
    }
    printf("\n");
    for(int i=0;i<F;i++){
        printf("|");
        for(int j=0;j<C;j++) {
            if(i==jugfilas && j==jugcolumnas){
                printf("%c",jugador);
            }else{
                printf("%c",M[i][j]);
            }
        }
        printf("|\n");
    }
    for (int i=0;i<=C+1;i++){
        printf("-");
    }
    printf("\n");
}
void Mover(char M[F][C],int *jugfilas,int *jugcolumnas){
    //esperamos una tecla
    char tecla = getch();
    int fila, columna;
    //doble letra en Windows
    if(tecla ==-32||tecla==0){
        tecla = getch();
    }
    fila = *jugfilas;
    columna = *jugcolumnas;
    // En función de la tecla pulsada
    switch(tecla){
    //casos arriba
    case 72:
    case '8':
    case 'A':
        //acciones arriba
        fila--;
        break;
        //casos abajo
    case 80:
    case '2':
    case 'B':
        //acciones abajo
        fila++;
        break;
        //casos izquierda
    case 75:
    case '4':
    case 'D':
        //acciones izquierda
        columna--;
        break;
        //casos derecha
    case 77:
    case '6':
    case 'C':
        //acciones derecha
        columna++;
        break;
    }
    // en fila, columna esta la celda a la cual quiero ir.
    if(fila>=0 && fila<F && columna>=0 && columna<C && M[fila][columna]!=obstaculo){
        M[*jugfilas][*jugcolumnas] ='*';
        *jugfilas=fila;
        *jugcolumnas=columna;
    }
}
//sustittuir los asteriscos del jugador 1 en huecos
void MoversinAsteriscos(char M[F][C],int *jugfilas,int*jugcolumnas){
    //esperamos una tecla
    char tecla = getch();
    int fila, columna;
    //doble letra en Windows
    if(tecla ==-32||tecla==0){
        tecla = getch();
    }
    fila = *jugfilas;            // vamos a calcular la fila y la columna siguiente.
    columna = *jugcolumnas;
    // En función de la tecla pulsada
    switch(tecla){
    //casos arriba
    case 72:
    case '8':
    case 'A':
        //acciones arriba
        fila--;
        break;
        //casos abajo
    case 80:
    case '2':
    case 'B':
        //acciones abajo
        fila++;
        break;
        //casos izquierda
    case 75:
    case '4':
    case 'D':
        //acciones izquierda
        columna--;
        break;
        //casos derecha
    case 77:
    case '6':
    case 'C':
        //acciones derecha
        columna++;
        break;
    }
    if(fila>=0 && fila<F && columna>=0 && columna<C && M[fila][columna]!=obstaculo){
        M[*jugfilas][*jugcolumnas] =' ';
        *jugfilas=fila;
        *jugcolumnas=columna;
    }
}
void Obstaculosale (char M[][C]){
    int i, j, r;
    // las casillas vacias se convierten en obstaculos con una probabilidad del 70 (Obstaculo .)
    // las casillas que son * se conviernten en espacios.
    for(i = 0; i < F; i++){
        for(j = 0; j < C; j++){
            if(M[i][j] == libre){
                r =rand() % 100+1;
                if(r <= 70){
                    M[i][j] = obstaculo;
                }
            }
            else{
                M[i][j] =libre;
            }
        }
    }
}
void Ejercicio2(){

    char M[F][C];//matriz con F(filas) y C(columnas)
    int jugfilas=F/2; int jugcolumnas=C/2; char jugardenuevo;
    do{
        jugfilas=F/2;
        jugcolumnas=C/2;
        Inicializar(M);
        system("cls");
        ImprimirRecuadro(M,jugfilas,jugcolumnas);
        do{
            Mover(M,&jugfilas,&jugcolumnas);
            system("cls");
            ImprimirRecuadro(M,jugfilas,jugcolumnas);
        }while(jugfilas!=0 && jugcolumnas!=0 && jugfilas!=F-1 && jugcolumnas!=C-1);
        getchar();
        jugcolumnas=C/2;
        jugfilas=F/2;
        Obstaculosale(M);
        system("cls");
        ImprimirRecuadro(M,jugfilas,jugcolumnas);
        do{
            MoversinAsteriscos(M,&jugfilas,&jugcolumnas);
            system("cls");
            ImprimirRecuadro(M,jugfilas,jugcolumnas);
            printf("Mover con los cursores hasta llegar a alguna de las paredes\n");
        }while(jugfilas!=0 && jugcolumnas!=0 && jugfilas!=F-1 && jugcolumnas!=C-1);
        printf("Enhorabuena! Lo conseguiste.\n");
        printf("Jugar de nuevo? (s/n)");
        scanf("%s",&jugardenuevo);
        system("cls");
    }while(jugardenuevo=='s' || jugardenuevo=='S');
    return;
}
int main(void){
    Ejercicio2();
    return 0;
}































