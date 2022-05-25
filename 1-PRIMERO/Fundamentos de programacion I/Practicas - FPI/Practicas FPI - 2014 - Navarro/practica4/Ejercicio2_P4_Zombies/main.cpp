#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10
#define M 30

//Funcion que genera el nivel de dificultad
int dificultad(){
    int n;
    printf("--->  LA CARRERA DE ZOMBIS  <---\n");
    //Bucle que repite en caso de ser erroneo el número introducido
    do{
        //Le pregunta al usuario el nivel y se lo asigna a una variable.
        printf("Ponga el nivel de dificultad deseado ( 1 y 10 ): ");
        scanf("%d",&n);
    }while (n < 1 || n > 10);
    return n;
}

//Funcion que inicia el tablero y le asigna a toda la matriz 0
void iniciar_tablero(int Matriz[N][M]){
    int i, j;
    for (i=0; i<N; i++){
        for (j=0; j<M; j++){
            Matriz[i][j]=0;
        }
    }
    return ;
}

//Funcion del movimiento humano
int movimiento_humano(int h,int *m, int Matriz[N][M]){
    //esperamos una tecla
    char tecla = getch();
    //doble código en caso de que sea un cursor
    if(tecla==-32 || tecla==0) tecla=getch();

    //posicion
    int a,b;
    for (int i=0; i<N; i++){
        for (int j=0; j<M; j++){
            if(Matriz[i][j]==2){
                a=i;
                b=j;
            }
        }
    }


    //en función de la tecla pulsada
    switch(tecla){
    case 72:
    case '8':
        //Mueve a arriba el humano
        if(a>0){
            if(Matriz[a-1][b]!= 3 && Matriz[a-1][b]!= 1){
                Matriz[a-1][b]=2;
                Matriz[a][b]=0;
                //Destruye la mina y el humano
            }else if (Matriz[a-1][b] == 3){
                Matriz[a-1][b] = 0;
                Matriz[a][b]=0;
                (*m)--;
                h--;
                //El zombi se come al humano
            }else if (Matriz[a-1][b] == 1){
                Matriz[a][b] = 0;
                h--;
            }
        }
        //ARRIBA
        break;
    case 80:
    case '2':
        //Mueve a abajo el humano
        if(a<N-1){
            if(Matriz[a+1][b]!= 3 && Matriz[a+1][b]!= 1){
                Matriz[a+1][b]=2;
                Matriz[a][b]=0;
            //Destruye la mina y el humano
            }else if (Matriz[a+1][b] == 3){
                Matriz[a+1][b] = 0;
                Matriz[a][b]=0;
                (*m)--;
                h--;
                //El zombi se come al humano
            }else if (Matriz[a+1][b] == 1){
                Matriz[a][b] = 0;
                h--;
            }
        }
        //ABAJO
        break;
    case 75:
    case '4':
        //Mueve a la izquierda el humano
        if(b>0){
            if(Matriz[a][b-1]!= 3 && Matriz[a][b-1]!= 1){
                Matriz[a][b-1]=2;
                Matriz[a][b]=0;
                //Destruye la mina y el humano
            }else if (Matriz[a][b-1] == 3){
                Matriz[a][b-1] = 0;
                Matriz[a][b]=0;
                (*m)--;
                h--;
                //El zombi se come al humano
            }else if (Matriz[a][b-1] == 1){
                Matriz[a][b] = 0;
                h--;
            }
        }
        //IZQUIERDA
        break;
    case 77:
    case '6':
        //Mueve a la derecha el humano
        if(b<M-1){
            if(Matriz[a][b+1]!= 3 && Matriz[a][b+1]!= 1 ){
                Matriz[a][b+1]=2;
                Matriz[a][b]=0;
                //Destruye la mina y el humano
            }else if (Matriz[a][b+1] == 3){
                Matriz[a][b+1] = 0;
                Matriz[a][b]=0;
                (*m)--;
                h--;
                //El zombi se come al humano
            }else if (Matriz[a][b+1] == 1){
                Matriz[a][b] = 0;
                h--;
            }
        }
        //DERECHA
        break;
    }
    return h;
}

//Funcion que genera el movimiento de los zombis
int movimiento_zombis(int L,int *h, int Matriz[N][M]){
    int i,j,a,b,ah,bh,a1,b1;
    int aux, z;
    z=0;
    //Hace dos bucles para recorrer la matriz.
    for (i=0; i<N; i++){
        for (j=0; j<M; j++){
            //Localiza la posición del humano.
            if (Matriz[i][j] == 2){
                ah=i;
                bh=j;
            }
        }
    }
    //Volvemos a recorrer la matriz en busca de zombis.
    for (i=0;i<N;i++){
        for(j=0; j<M; j++){
            //Busca al zombi
            if (Matriz[i][j]==1){
                //genera un numero aleatorio del 0 al 100
                aux=rand()%101;
                //Si el número es menor que L(dificultad) * (un numero del 0 al 9) se movera el zombi.
                if (aux<(L*10)){
                    //Asigna a las variables la posicion del zombi
                    a=a1=i;
                    b=b1=j;
                    //Busca el lugar en el que se encuentra el humano y se mueve hacia él.
                    if (a<ah){
                        a1=a+1;
                    }
                    if (a>ah){
                        a1=a-1;
                    }
                    if (b>bh) {
                        b1=b-1;
                    }
                    if (b<bh) {
                        b1=b+1;
                    }

                    Matriz[a][b]=0;
                    if(Matriz[a1][b1]==0){
                        Matriz[a1][b1]=4;
                    }else if(Matriz[a1][b1]==3){
                        Matriz[a1][b1]=0;
                    }else if(Matriz[a1][b1]==1 ||Matriz[a1][b1]==4){
                        Matriz[a1][b1]=4;
                    }else if(Matriz[a1][b1]==2){
                        Matriz[a1][b1]=4;
                        (*h)--;
                    }
                }
            }
        }
    }
    //Recorre otra vez la matriz en busca del numero 4
    for(i=0;i<N;i++){
        for(j=0;j<M;j++){
            //Una vez lo encuentra le asigna el numero correspondiente al zombi.
            if (Matriz[i][j]==4){
                Matriz[i][j]=1;
            }
        }
    }
    z=0;
    for(i=0;i<N;i++){
        for(j=0;j<M;j++){
            //Una vez lo encuentra le asigna el numero correspondiente al zombi.
            if (Matriz[i][j]==1){
                z++;
            }
        }
    }

    return z;
}

//Funccion que crea las minas.
int generar_minas(int Matriz[N][M]){
    int f,g;
    int m=0;
    //Hace el tantas veces como minas hagan falta
    do{
        //Genera una posicion aleatoria
        f=rand()%N;
        g=rand()%M;
        //Comprueba que en la posicion no haya nada
        if (Matriz[f][g]==0){
            //Asigna a la matriz que hay una mina
            Matriz[f][g]=3;
            //Le suma uno a minas creadas
            m++;
        }
    }while(m <(((N*M)*10)/100));
    //Devuelve el valor de cantidades de minas que hay.
    return m;
}

//Funcion que crea el humano.
int generar_humanos(int Matriz[N][M]){
    int h=0;
    int f,g;
    //Hace este bucle tantas veces como sea necesario.
    do{
        //Genera una posicion aleatoria en la cual poner el humano
        f=rand()%N;
        g=rand()%M;
        //Busca si la casilla esta vacia
        if (Matriz[f][g]==0){
            //Le asigna la casilla al humano
            Matriz[f][g]=2;
            h++;
        }
    }while (h < 1);
    return h;

}

//Funcion quecrea zombis
int generar_zombis(int Matriz[N][M]){
    int z=0;
    int f,g;
    //El bucle se crea hasta que no esten el tope de zombis indicado
    do{
        //Genera una posicion aleatoria
        f=rand()%N;
        g=rand()%M;
        //Busca si en la casilla correspondiente esta vacia, le asigna la posicion, y suma 1 al número de zombis creados
        if (Matriz[f][g]==0){
            Matriz[f][g]=1;
            z++;
        }
    }while (z < (((N*M)*2)/100));
    return z;
}

//Función para representar el tablero
void tablero( int z,int m, int h,int Matriz[N][M]){
    int i,j;
    printf("--->  LA CARRERA DE ZOMBIS  <---\n");
    printf("\n");
    //Limita el margen de la pantalla
    for (j=0; j<M+2; j++){
        printf("-");
    }
    //Da un salto de linea para no dibujar en la linea
    printf("\n");
    for (i=0; i<N; i++){
        //Pone los limites laterales de la matriz
        printf("|");
        //Dibuja los zombies,humanos y minas que hay en la matriz
        for(j=0; j<M; j++){
            if (Matriz[i][j]==0) printf(" ");
            if (Matriz[i][j]==1) printf ("Z");
            if (Matriz[i][j]==2) printf ("H");
            if (Matriz[i][j]==3) printf ("*");
        }
        printf("|\n");
    }
    //Limita el borde inferior de la matriz
    for (j=0; j<M+2; j++){
        printf("-");
    }
    printf("\n");
    //Muestra por pantalla el número de zombies, minas y humanos en juego.
    printf ("Numero de participantes:\n Zombies:  %d\t Personas:  %d\t Minas:  %d\n", z,h,m);
    return ;
}

//Inicia el juego
void juego(){
    //Crea las variables y les asigna un valor
    int z=0,h=0,m=0,L;
    int Matriz[N][M];
    //Se le asigna el nivel de dificultad asignado por el usuario
    L=dificultad();
    srand(time(NULL));
    //Lama a su resectiva función
    iniciar_tablero(Matriz);
    z=generar_zombis(Matriz);
    h=generar_humanos(Matriz);
    m=generar_minas(Matriz);
    //Bucle para poder jugar inefinidamente hasta que se acabe el juego
    do{
        system("cls");
        tablero(z,m,h,Matriz);
        h=movimiento_humano(h,&m,Matriz);
        z=movimiento_zombis(L,&h,Matriz);
    }while(h!=0 && z!=0);
    //system("cls");
    tablero(z,m,h,Matriz);
    if (h==0){
        printf("\n-----> GAME OVER <-----\n");
    }
    if (z==0){
        printf("\n-----> WINNER <-----\n");
    }
    return ;
}

//Función principal del juego.
int main(void){
    juego();
    return 0;
}
