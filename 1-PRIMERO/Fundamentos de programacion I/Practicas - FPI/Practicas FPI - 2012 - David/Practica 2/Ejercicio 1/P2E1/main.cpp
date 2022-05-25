#include <stdio.h>
int main()
{
    /////////
    //CALIZ//
    /////////

    int medida, vertical, horizontal, base, limite, linea, i;
    printf("Introduzca una medida (1-10)\n");
    scanf("%d", &medida);
    printf("\n");
    limite = 2 * medida - 1;
    linea = 1;
    while(linea<=medida){
        i = 1;
        while(i<=linea - 1){
            printf(" ");
            i ++;
        }
        printf("\\");
        i = 1;
        while(i<=limite){
            printf(" ");
            i++;
        }
        printf("/\n");
        linea++;
        limite=limite-2;
    }
    ////////////////////////////
    //MEDIDA DEL TRONCO Y BASE//
    ////////////////////////////

    vertical = 1;
    base = 2 * medida + 1;
    while(vertical<=medida){
        horizontal = 1;
        while(horizontal<=medida){
            printf(" ");
            horizontal ++;
        }
        printf("|\n");
        vertical ++;
    }

    limite = 1;
    while(limite <= base){
        printf("_");
        limite ++;
    }
    getchar();
    getchar();
    return 0;
}
