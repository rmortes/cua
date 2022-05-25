#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>

#define N 35
#define M 87
int Repetir(){
    char rep[10];
    int cent=0;
    printf("Felicidades!!!\nintroduzca \"Y\" para volver a jugar:");
    scanf("%s",rep);
    getchar();
    strupr(rep);
    if(strcmp(rep,"Y")==0){
        cent=1;
    }
    return(cent);
}
void Print(char map[N][M+1]){
    //Cadena contenedora
    char img[100*40]="";
    for(int i=0;i<M+2;i++){
        strcat(img,"-");
    }
    strcat(img,"\n");
    //unir las barras laterales en cada fila de la matriz
    for(int i=0;i<N;i++){
        char aux[100];
        sprintf(aux,"|%s|\n",map[i]);
        strcat(img,aux);
    }
    for(int i=0;i<M+2;i++){
        strcat(img,"-");
    }
    strcat(img,"\n");
    system("cls");
    printf("%s",img);
    return;
}
void playerpos(char map[N][M+1],int*x,int*y){
    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            if(map[i][j]=='+'){
                *x=j;
                *y=i;
            }
        }
    }
    return;
}
//killer
void Soptima(char map[N][M+1]){
    //matriz de enteros, cada iteracion marca+1, vuelve a la pos anterior
    int cent=0;
    int matrix[N][M];
    char pared=(char)219;
    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            if(map[i][j]=='0'){
                matrix[i][j]=0;
            }
            if(map[i][j]=='+'){
                matrix[i][j]=-1;
            }
            if(map[i][j]==pared){
                matrix[i][j]=-2;
            }
            if(map[i][j]=='*'){
                matrix[i][j]=-4;
            }
            if(map[i][j]==' '){
                matrix[i][j]=-4;
            }
        }
    }
    //iterador de numero de pasos
    int itr=2;
    do{
        cent=0;
        for(int i=0;i<N;i++){
            for(int j=0;j<M;j++){
                if(matrix[i][j]==-1||matrix[i][j]==itr-1){
                    if(i<N-1&&matrix[i+1][j]==-4){
                        matrix[i+1][j]=itr;
                    }
                    if(i>0&&matrix[i-1][j]==-4){
                        matrix[i-1][j]=itr;
                    }
                    if(j<M-1&&matrix[i][j+1]==-4){
                        matrix[i][j+1]=itr;
                    }
                    if(j>0&&matrix[i][j-1]==-4){
                        matrix[i][j-1]=itr;
                    }
                    if(i<N-1&&matrix[i+1][j]==0){
                        cent=1;
                    }
                    if(i>0&&matrix[i-1][j]==0){
                        cent=1;
                    }
                    if(j<M-1&&matrix[i][j+1]==0){
                        cent=1;
                    }
                    if(j>0&&matrix[i][j-1]==0){
                        cent=1;
                    }
                }
            }
        }
        itr++;
    }while(cent==0);
    //restamos la iteracion que hizo al salir del bucle
    //buscamos la posición anterior
    itr=itr-2;
    int mov=itr;
    //cola
    do{
        for(int i=0;i<N;i++){
            for(int j=0;j<M;j++){
                cent=0;
                matrix[N-1][M-1]=-3;
                if(matrix[i][j]==-3){
                    if(i<N-1&&matrix[i+1][j]==itr){
                        matrix[i+1][j]=-3;
                        cent=1;
                    }
                    if(i>0&&matrix[i-1][j]==itr&&cent==0){
                        matrix[i-1][j]=-3;
                        cent=1;
                    }
                    if(j<M-1&&matrix[i][j+1]==itr&&cent==0){
                        matrix[i][j+1]=-3;
                        cent=1;
                    }
                    if(j>0&&matrix[i][j-1]==itr&&cent==0){
                        matrix[i][j-1]=-3;
                        cent=1;
                    }
                }
            }
        }
        itr--;
    }while(itr!=1);
    //Matriz de caracteres que será imprimida
    char muestra[N][M+1];
    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            muestra[i][j]=' ';
            if(matrix[i][j]==-1){
                muestra[i][j]='+';
            }
            if(matrix[i][j]==-2){
                muestra[i][j]=219;
            }
            if(matrix[i][j]==-3){
                muestra[i][j]='*';
            }
        }
        muestra[N-1][M-1]='0';
        muestra[i][M]='\0';
    }
    Print(muestra);
    printf("numero de movimientos hasta la meta %d",mov);
    getche();
}
int map1(char map[N][M+1],int*x,int*y){
    int cent=1;
    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            if(map[i][j]=='+'){
                map[i][j]='*';
            }
            map[*y][*x]='+';
            //condición booleana, da paso a jug2
            if(map[N-1][M-1]!='0'){
                cent=0;
            }
        }
    }
    return cent;
}
int map2(char map[N][M+1],int*x,int*y){
    int cent=1;
    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            if(map[i][j]=='+'){
                map[i][j]=' ';
            }
            map[*y][*x]='+';
            //condición booleana, victoria
            if(map[N-1][M-1]!='0'){
                cent=0;
            }
        }
    }
    return cent;
}
//obstaculos aleatorios
int obst(void){
    int obsta,aux=0;
    obsta=rand()%100;
    if(obsta<50){
        aux=1;
    }
    return aux;
}
void map20(char map[N][M+1]){
    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            if(map[i][j]==' '&&obst()==1){
                map[i][j]=219;
            }
            if(map[i][j]=='*'){
                map[i][j]=' ';
            }
        }
    }
    map[0][0]='+';
    map[N-1][M-1]='0';
    return;
}
//inicializa la matriz
void juego0(char map[N][M+1]){
    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            map[i][j]=' ';
        }
        map[i][M]='\0';
    }
    map[0][0]='+';
    map[N-1][M-1]='0';
    Print(map);
    return;
}
void mov(char map[N][M+1],int*x,int*y){
    //conversión para el condicional
    char pared=(char)219;
    char tecla=getch();
    if(tecla==-32|| tecla==0) tecla=getch();
    switch(tecla){
    //arriba
    case 72:
    case '8':
        if(*y>0&&map[(*y)-1][*x]!=pared){
            *y=(*y)-1;
        }
        break;
        //abajo
    case 80:
    case '2':
        if(*y<N-1&&map[(*y)+1][*x]!=pared){
            *y=(*y)+1;
        }
        break;
        //izq
    case 75:
    case '4':
        if(*x>0&&map[*y][(*x)-1]!=pared){
            *x=(*x)-1;
        }
        break;
        //dch
    case 77:
    case '6':
        if(*x<M-1&&map[*y][(*x)+1]!=pared){
            *x=(*x)+1;
        }
        break;
        //solve
    case 's':
        Soptima(map);
        break;
    }
    return;
}
//ruta segura
void juego1(char map[N][M+1],int*x,int*y){
    do{
        printf("jugador 1, cree la ruta segura:");
        playerpos(map,x,y);
        mov(map,x,y);
        map1(map,x,y);
        Print(map);
    }while(map1(map,x,y));
    return;
}
//inicializa el laberinto, con obstaculos
void juego20(char map[N][M+1]){
    map20(map);
    Print(map);
    return;
}
void juego2(char map[N][M+1],int*x,int*y){
    do{
        printf("Pulse s para autosolucionar:");
        playerpos(map,x,y);
        mov(map,x,y);
        map2(map,x,y);
        Print(map);
    }while(map2(map,x,y));
}

void juego(char map[N][M+1],int*x,int*y){
    juego0(map);
    juego1(map,x,y);
    juego20(map);
    juego2(map,x,y);
    return;
}

int main(void){
    //inicialización de los parametros por partida
    do{
        //coordenadas jugador
        int x=0,y=0;
        //Matriz carecteres que representa el lab
        char map[N][M+1];
        juego(map,&x,&y);
    }while(Repetir());
    return(0);
}
