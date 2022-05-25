//Incluimos las librerias
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>

int main (void) {

    //Definimos las variables
    int i=5, j=0, puntosJug1 = 0, puntosJug2 = 0, turno = 1, medidaCad, centinela;
    char palabra[50], cadena[51];
    char jugar, letra;

    do {

        //Para que el programa ejecute un turno u otro hacemos uso de un if-else
        if (turno%2!=0) {

            //Con este do, le pedimos al usuario que introduzca la palabra, al llegar al while, si es mayor de 50, vuelve a pedirla
            do {
                printf("Introduce la palabra a adivinar Jugador 1: ");
                scanf("%s", palabra);
                fflush(stdin);
                system("cls");
            }

            while (strlen(palabra) > 50);

            //Con esto imprimimos tantos guiones como caracteres tenga la palabra
            medidaCad = strlen(palabra);
            strcpy(cadena, "-------------------------------------------------");
            cadena[medidaCad] = '\0';

            do {
                //Esta es la variable centinela que es usada para comprobar si se ha fallado con la letra
                centinela = 0;
                printf("\n\nPalabra: %s\n\n", cadena);
                printf("Intentos restantes: %d\n\n", i);

                //Aqui le pedimos al usuario que introduzca una letra para adivinar la palabra
                do {
                    printf("Introduce una letra minuscula (Jug.2): ");
                    scanf("%c", &letra);
                    fflush(stdin);
                }

                //Si el caracter introducido no es una letra, lo pide de nuevo
                while (letra < 'a' || letra > 'z');

                //Este for comprueba posicion por posicion, de la cadena, si la letra introducida se encuentra en la cadena
                for(j=0;j<strlen(palabra);j++){

                    if (palabra[j]==letra)
                    {
                        cadena[j]=letra;
                        centinela = 1;
                    }
                }

                if (centinela != 1)i--;
            }

            //Si no se han terminado los intentos ni se ha acertado, repite el do
            while(i!=0 && strcmp(cadena,palabra)!= 0);

            /*Para llegar a este if-else, debe de haberse gastado los intentos o haber adivinado la letra,
              entonces, si la palabra introducida letra a letra, es igual a la introducida en primera instancia
              imprime que se ha ganado y aumenta un punto al jugador que ha acertado*/
            if (strcmp(cadena,palabra)== 0) {
                system("cls");
                printf ("Has acertado, la palabra era: %s\n", palabra);
                puntosJug2++;
            }
            /*En esta parte, si el jugador ha perdido, se le informa de ello, y aumenta un punto en el marcador del
            jugador que puso la palabra*/
            else {
                system("cls");
                printf("Has perdido, la palabra era: %s",palabra);
                puntosJug1++;
            }
        }

        //Aqui comienza el siguiente turno
        else{
            centinela = 0;
            //Con este do, le pedimos al usuario que introduzca la palabra, al llegar al while, si es mayor de 50, vuelve a pedirla
            do {
                printf("Introduce la palabra a adivinar Jugador 2: ");
                scanf("%s", palabra);
                fflush(stdin);
                system("cls");
            }

            while (strlen(palabra) > 50);

            //Con esto imprimimos tantos guiones como caracteres tenga la palabra
            medidaCad = strlen(palabra);
            strcpy(cadena, "-------------------------------------------------");
            cadena[medidaCad] = '\0';

            do{
                //Esta es la variable centinela que es usada para comprobar si se ha fallado con la letra
                centinela = 0;
                printf("\n\nPalabra: %s\n", cadena);
                printf("Intentos restantes: %d\n\n", i);

                //Aqui le pedimos al usuario que introduzca una letra para adivinar la palabra
                do{
                    printf("Introduce una letra minuscula [Jug.1]: ");
                    scanf("%c", &letra);
                    fflush(stdin);
                }

                //Si el caracter introducido no es una letra, lo pide de nuevo
                while (letra < 'a' || letra > 'z');

                //Este for comprueba posicion por posicion, de la cadena, si la letra introducida se encuentra en la cadena
                for(j=0;j<strlen(palabra);j++){

                    if (palabra[j]==letra) {
                        cadena[j]=letra;
                        centinela=1;
                    }
                }

                if (centinela != 1)i--;
                printf("\n\n");

            }

            //Si no se han terminado los intentos ni se ha acertado, repite el do
            while(i!=0 && strcmp(cadena,palabra)!= 0);

            /*Para llegar a este if-else, debe de haberse gastado los intentos o haber adivinado la letra,
              entonces, si la palabra introducida letra a letra, es igual a la introducida en primera instancia
              imprime que se ha ganado y aumenta un punto al jugador que ha acertado*/
            if (strcmp(cadena,palabra)== 0){
                system("cls");
                printf ("Has acertado, la palabra era: %s", palabra);
                puntosJug1++;
            }

            /*En esta parte, si el jugador ha perdido, se le informa de ello, y aumenta un punto en el marcador del
            jugador que puso la palabra*/
            else {
                system("cls");
                printf("Has perdido, la palabra era: %s",palabra);
                puntosJug2++;
            }
        }

        //Aqui pregunta si se sigue jugando o no, con las teclas "s" o "n", mayusculas o minusculas
        do{
            printf("Quereis jugar mas partidas? <S o N>: ");
            scanf("%c", &jugar);
            fflush(stdin);
        }

       while (jugar != 'S' && jugar != 'N');

        //Sumamos uno a la variable turno, y asi ejecutar el codigo del siguiente jugador
        turno++;
        system("cls");
        //inicializamos las variables
        i=5;
        j=0;
    }

    //Si el usuario a tecleado "s", se volvera a ejecutar el do inicial, y sera el turno siguiente
    while (jugar == 'S' || jugar == 's');

    //Si no se juega mas, se imprime en pantalla la puntuacion de los 2 jugadores.
    printf("Puntuacion final: (Jug.1) %d - %d (Jug.2)", puntosJug1, puntosJug2);

    //A la espera de que el usuario pulse una tecla para salir del programa
    system ("pause");
    return(0);
}
