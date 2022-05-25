#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#define N 20
#define M 30

int L=1; // nivel del juego

void reset(int virus[N][M])
{
    for (int i=0;i<N;i++)
    {
        for (int j=0;j<M;j++)
        {
            virus[i][j]=0;
        }
    }
}
int virus_cerca(int virus[N][M])
{
    int hueco=0, celdas_X, celdas_Y, aux_X, aux_Y;
    for(int i=0;i<N;i++)
    {
        for (int j=0;j<M;j++)
        {
            if (virus[i][j]==55)
            {
                aux_X = j;
                aux_Y = i;

                celdas_X = j;
                celdas_Y = i-1;
                if (virus[celdas_Y][celdas_X]==77) hueco++;

                celdas_X = j-1;
                celdas_Y = i;
                if (virus[celdas_Y][celdas_X]==77) hueco++;

                celdas_X = j;
                celdas_Y = i+1;
                if (virus[celdas_Y][celdas_X]==77) hueco++;

                celdas_X = j+1;
                celdas_Y = i;
                if (virus[celdas_Y][celdas_X]==77) hueco++;
            }
        }
    }
    return hueco;
}
void convertir(int virus[N][M])
{
    int aux_X=0,aux_Y=0,probabilidad=0,porcentaje,celdas_X, celdas_Y, hueco=0;
    porcentaje=10;
    for(int i=0;i<N;i++)
    {
        for (int j=0;j<M;j++)
        {
            if (virus[i][j]==77)
            {
                aux_X=j;
                aux_Y=i;
                for(int h=0;h<3;h++)
                {
                    for(int k=0;k<3;k++)
                    {
                        celdas_X = j-1+k;
                        celdas_Y = i-1+h;
                        if (celdas_Y >=0 && celdas_Y<=19 && celdas_X>=0 && celdas_X<=29 && virus[celdas_Y][celdas_X]!=77)
                        {
                            virus[celdas_Y][celdas_X]=99;
                        }
                    }
                }
                virus[aux_Y][aux_X]=77;
            }
        }
    }
    for(int i=0;i<N;i++)
    {
        for (int j=0;j<M;j++)
        {
            if(virus[i][j]==99)
            {
                for (int h=0;h<L;h++)
                {
                    probabilidad = rand()%porcentaje;
                    if (probabilidad == 1)
                    {
                        virus[i][j]=77;
                    }
                }
            }
        }
    }

}
int* movimiento(int Y, int X)
{
    int salir=0;
    static int cursor[1];
    do
    {
        //esperamos una tecla
        char tecla = getch();
        //doble letra en Windows
        if(tecla==-32 || tecla==0){
            tecla=getch();
        }
        //doble tecla en Linux/Mac
        if(tecla==27){
            tecla=getch();
            tecla=getch();
        }
        //en función de la tecla pulsada
        switch(tecla){
        //casos arriba
        case 72: if (Y>0 && Y<=19) Y--; salir=1;
        case '8':
        case 'A':
            //acciones arriba
            //…
            break;
            //casos abajo
        case 80: if (Y>=0 && Y<19) Y++; salir=1;
        case '2':
        case 'B':
            //acciones abajo
            //…
            break;
            //casos izquierda
        case 75: if (X>0 && X<=29) X--; salir=1;
        case '4':
        case 'D':
            //acciones izquierda
            //…
            break;
            //casos derecha
        case 77: if(X>=0 && X<29) X++; salir=1;
        case '6':
        case 'C':
            //acciones derecha
            //…
            break;
        }
    }
    while(salir == 0);
    cursor[0] = X;
    cursor[1] = Y;
    return cursor;
}
void mapa(int virus[N][M])
{
    int X=M/2,Y=N/2,posicion=0, aux_X=0,aux_Y=0, camino=0, salir=0;
    int *cursor;
    do
    {
        virus[Y][X] = 55;
        posicion=0;
        system("cls");
        printf("\n ESCAPA DEL VIRUS || NIVEL %d ||\n", L);
        printf(" ");
        for(int y=0;y<M;y++)
        {
            printf("-");
        }
        printf("\n");
        // Bucle para dibujar la matriz dependiendo de su valor -----> 55=personaje 77=virus 99=virus posibilidad de convertirse
        for(int i=0;i<N;i++)
        {
            printf("|");
            for (int j=0;j<M;j++)
            {

                if (virus[i][j]==77)
                {
                    printf("X");
                }
                else if (virus[i][j] == 55)
                {
                    printf("O");
                    aux_Y=i;
                    aux_X=j;
                }
                else printf(" ");
            }
            printf("|\n");
        }
        printf(" ");
        for(int y=0;y<M;y++)
        {
            printf("-");
        }
        printf("\n");
        // Condicionante para pasar de nivel
        if (Y == 0 || Y==19 || X==0 || X==29)
        {
            L++;
            if (L>10)
            {
                printf("ENHORABUENA, HAS GANADO EL JUEGO!\n");
                L=1;
                salir = 1;
            }
            else
            {
            printf("Felicidades, has pasado el nivel %d\n", L);
            printf("Pulse una tecla para pasar al siguiente nivel");
            getch();
            salir = 1;
            }
        }
        // Condicionante y funcion para saber si se puede continuar jugando
        camino=virus_cerca(virus);
        if (camino == 4)
        {
            reset(virus);
            L=1;
            salir=1;
        }
        else if(salir ==0 )
        {

            do
            {
                virus[Y][X]=0;
                cursor = movimiento(Y, X);
                X = *cursor;
                Y = *(cursor+1);
                if (virus[Y][X] == 77)
                {
                    posicion = 1;
                    Y=aux_Y;
                    X=aux_X;
                }
                else posicion=0;
            }
            while(posicion == 1);
            convertir(virus);

        }
    }
    while (salir == 0);
}
void nivel()
{
    int rand_virus=0, rand_X, rand_Y, virus[N][M];
    reset(virus);
    rand_virus = L*2;
    for (int i=0;i<rand_virus;i++)
    {
        rand_X = rand()%29;
        rand_Y = rand()%19;
        virus[rand_Y][rand_X] = 77;
    }
    mapa(virus);
}
int main()
{
    char jugar;
    while (1)
    {
        srand(time(NULL));
        nivel();
        if (L == 1 || L>10)
        {
            do
            {
                printf("Deseas volver a jugar? s/n\n");
                scanf("%s", &jugar);
            }
            while (jugar!='s' && jugar!='n');
        }
        if (jugar == 'n') return 0;
    }
}
