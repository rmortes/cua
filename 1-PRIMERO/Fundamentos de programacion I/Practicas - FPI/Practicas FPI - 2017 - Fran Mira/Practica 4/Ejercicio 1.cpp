#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#define N 10
// Prototipos


int comprobar(int habitaciones[N])
{
    int comprobacion=0, fin_juego=0;
    for(int i=0;i<N;i++)
    {
        comprobacion=habitaciones[i];
        if (comprobacion==N)
        {
            fin_juego = 1;  
        }
    }
    return fin_juego;
}

int puntuacion(int puntos)
{
    printf("\t\t\t\t\t\t-------------------\n");
    printf ("\t\t\t\t\t\t|JUEGO DEL BOMBERO|\n");
    printf("\t\t\t\t\t\t-------------------\n\n");
    printf("\t\t\t\t\t\tPuntuacion actual: %d\n", puntos);
}

int movimiento(int num_hab)
{
    int aux=num_hab, salir=0;
    do
    {
        salir=0;
        //esperamos una tecla
        char tecla = getch();
        //doble letra en Windows
        if(tecla==-32 || tecla==0){
            tecla=getch();
        }
        //en función de la tecla pulsada
        switch(tecla){
        // caso enter
        case 13: salir=1;
            break;
            //casos arriba
        case 72: if (num_hab>0 && num_hab<10)num_hab--;
        case '8':
        case 'A':
            //acciones arriba
            //…
            break;
            //casos abajo
        case 80:  if (num_hab>=0 && num_hab<9)num_hab++;
        case '2':
        case 'B':
            //acciones abajo
            //…
            break;
        }
    }
    while(num_hab == aux && salir==0);
    return num_hab;
}
int solicitar()
{
    int L=0;
    printf ("Introduzca el nivel de juego entre 1 y %d que desea: ", N);
    scanf("%d", &L);
    do
    {
        if (L < 1 || L > N)
        {
            printf("Nivel introducido fuera de rango, vuelva a intentarlo: ");
            fflush(stdin);
            scanf("%d", &L);
        }
    }
    while(L < 1 || L > N);
    return L;
}
int mapa_final(int num_hab, int habitaciones[N])
{
    int aux = 0, num_fuego=0, sin_fuego=0, aux1=0, puntos=0, variable=0, nivel_juego=0, comprobacion=0;
    nivel_juego = solicitar();
    while(1)
    {
        system("cls");
        puntuacion(puntos);
        for (int i=0;i<N;i++)
        {
            if (i==num_hab) printf("B|"); else printf(" |");
            aux=0;
            num_fuego = habitaciones[i];
            for (int j=0;j<num_fuego;j++)
            {
                printf("~");
                aux++;
            }
            sin_fuego=N-aux;
            for (int x=0;x<sin_fuego;x++)
            {
                printf(" ");
            }
            printf("|\n");
        }
        aux1 = num_hab;
        printf("Cursores <arriba/abajo> para mover o ENTER para apagar una habitacion\n");
        if (comprobacion==1)
        {
            printf("El juego ha terminado con una puntuacion de: %d\n", puntos);
            return 0;
        }
        num_hab = movimiento(num_hab);
        if (num_hab == aux1)
        {
            puntos = puntos+habitaciones[num_hab];
            habitaciones[num_hab]=0;
        }
        for (int i=0;i<nivel_juego;i++)
        {
            variable = rand()%11;
            habitaciones[variable] = habitaciones[variable]+1;
        }
        comprobacion=comprobar(habitaciones);

    }
}
int fuego()
{
    int num_fuego;
    num_fuego = rand()%(N/2)+1;
    return num_fuego;
}
int mapa_juego(int num_hab)
{
    int num_fuego=0, aux=0;
    int habitaciones[N];
    num_hab = rand()%11;
    for (int i=0;i<N;i++)
    {
        num_fuego = fuego();
        aux=0;
        for (int j=0;j<num_fuego;j++)
        {
            aux++;
        }
        habitaciones[i] = aux;
    }
    mapa_final(num_hab, habitaciones);
}

int juego()
{
    int L=0, direccion=0, nivel_juego, num_hab=0;

    mapa_juego(num_hab);
}
int main()
{
    srand(time(NULL));
    juego();
}
