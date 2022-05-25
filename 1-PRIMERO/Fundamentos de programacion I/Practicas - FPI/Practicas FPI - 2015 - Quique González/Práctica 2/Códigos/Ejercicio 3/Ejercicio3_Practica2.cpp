#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int main(void){

    //PARA QUE CADA VEZ QUE EL PROGRAMA INICIE ESCOJA UNA SERIE DE NÚMERO ALEATORIOS DISTINTOS

    srand(time(NULL));

    //DECLARAMOS VARIABLES Y CADENAS

    int apuesta;
    char caballo1[100]="", caballo2[100]="", caballo3[100]="", caballo4[100]="";

    //PEDIMOS UNA APUESTA AL USUARIO Y FILTRAMOS SÍ CUMPLE LAS CONDICIONES

    do{
        printf("Realize su apuesta, escoja un caballo (1,2,3 o 4):"); scanf("%d", &apuesta);getchar();
        if(apuesta<1 || apuesta>4){
            printf("Error: esa apuesta no se corresponde a ningun caballo\n");
        }
    }while(apuesta<1 || apuesta>4);

    //INICIAMOS EL BUCLE

    for(int i=0;strlen(caballo1)<73 && strlen(caballo2)<73 && strlen(caballo3)<73 && strlen(caballo4)<73;i++){

        //ESCOJEMOS UN NÚMERO ALEATORIO PARA QUE CUANDO SE CORRESPODA CON UNO DE LOS CABALLOS IMPRIMA UN ESPACIO DETRÁS SUYO

        switch (rand()%4+1) {
        case 1:
            strcat(caballo1, " "); break;
        case 2:
            strcat(caballo2, " "); break;
        case 3:
            strcat(caballo3, " "); break;
        case 4:
            strcat(caballo4, " "); break;
        }

        //PARA QUE EN CADA INTERACCIÓN SE BORRE LA PANTALLA

        system("cls");

        //IMPRIMIMOS LA CARRERA

        printf("Carrera de caballos. ");

        //CONTADOR DE ITERACIONES

        printf("Iteracion %d\n", i);

        printf("-------------------------------------------------------------------------------\n");
        printf("%s~__/>\n", caballo1);
        printf("%s// \\\n",caballo1);

        printf("-------------------------------------------------------------------------------\n");
        printf("%s~__/>\n", caballo2);
        printf("%s// \\\n",caballo2);

        printf("-------------------------------------------------------------------------------\n");
        printf("%s~__/>\n", caballo3);
        printf("%s// \\\n",caballo3);

        printf("-------------------------------------------------------------------------------\n");
        printf("%s~__/>\n", caballo4);
        printf("%s// \\\n",caballo4);

        printf("-------------------------------------------------------------------------------\n");

        _sleep(10);
    }

    //DECLARAMOS LA VARIABLE

    int vencedor;

    //ASIGNAMOS UN NÚMERO AL CABALLO QUE LLEGUE AL FINAL DE LA PANTALLA

    if (strlen(caballo1)==73) vencedor=1;
    if (strlen(caballo2)==73) vencedor=2;
    if (strlen(caballo3)==73) vencedor=3;
    if (strlen(caballo4)==73) vencedor=4;

    //FELICITAMOS AL USUARIO SÍ GANA

    if (vencedor==apuesta){
        printf("ENHORABUENA, HAS GANADO LA APUESTA\n");
    }else printf("Lo siento, has perdido la apuesta. Ha ganado el caballo %d \n", vencedor);
    return 0;
}
