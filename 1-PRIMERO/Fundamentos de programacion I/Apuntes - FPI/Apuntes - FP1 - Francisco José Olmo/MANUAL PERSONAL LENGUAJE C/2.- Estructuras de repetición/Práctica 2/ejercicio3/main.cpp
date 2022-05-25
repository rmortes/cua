#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){

    srand(time(NULL));

    int x, y, correcto=0,f,c, i=0, j=0, iteracion=0;

    while (correcto==0){

        system("cls");

        printf("Numero de filas del panel: ");
        scanf("%d",&f);
        getchar();
        printf("Numero de columnas del panel: ");
        scanf("%d",&c);
        getchar();

        if(5>f || 20<f || 5>c || 75<c)
            printf("Numero incorrecto de filas o columnas.\n");
        else{
            system("cls");
            correcto=1;}
    }

    while (j<=f/2 && j>=-(f-f/2-1) && i>=-c/2 && i<=c-c/2-1){
        system("cls");

        printf("Escape del laberinto iteracion %d\n",iteracion);

        for (y=f/2; y>=-(f-f/2-1); y--){

            for (x=-c/2; x<=c-c/2-1; x++){

                if (x==i && y==j)
                    printf("X");
                else
                    if (x==-c/2 ||x==c-c/2-1)
                        printf("|");
                    else
                        if (y==f/2 || y==-(f-f/2-1))
                            printf("-");
                        else
                            printf(" ");

            }
            printf("\n");
        }

        if (j==f/2 || i==c-c/2-1){
            i++;
            j++;}
        else
            if ( j==-(f-f/2-1)||i==-c/2){
                i--;
                j--;}
            else
                iteracion++;

        i=i+rand()%2;

        j=j+rand()%2;

        i=i-rand()%2;

        j=j-rand()%2;
    }

    printf("\n\nFin del juego. Se ha conseguido escapar en %d iteraciones.\n",
           iteracion);

    return 0;
}

