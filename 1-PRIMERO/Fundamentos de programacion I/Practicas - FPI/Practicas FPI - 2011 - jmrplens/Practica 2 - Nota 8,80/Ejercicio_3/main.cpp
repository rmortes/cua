//Incluimos las librerias
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
int sololetras(char * cadena)
    {
         int i;
         for (i=0 ; i < strlen(cadena); i++ )
               if (cadena[i] < 'a' || cadena[i] > 'z' ) return 0;
         return 1;
    }
int main (void) {

    //Definimos las variables
    int juego, puntos1 = 0, puntos2 = 0, turno = 1, intentos, longitud, cent;
    char palabra[50], guiones[51], repeat, letra;

    do {
        //Damos valores a variables que deben ser reiniciados en cada turno
        intentos=5;
        juego=0;

        //Para que el programa ejecute un turno u otro hacemos uso de un if-else
        if (turno%2!=0) {

            //Con este do, le pedimos al usuario que introduzca la palabra, al llegar al while, si es mayor de 50, vuelve a pedirla
            do {
                printf("Introduce la palabra a adivinar Jugador 1: ");
                scanf("%s", palabra);
                fflush(stdin);
                system("cls");
            }

            while (strlen(palabra) > 50 || 0==sololetras(palabra) );


            //Con esto imprimimos tantos guiones como caracteres tenga la palabra
            longitud = strlen(palabra);
            strcpy(guiones, "-------------------------------------------------");
            guiones[longitud] = '\0';

            do {
                //Limpiamos la pantalla de lo que se va generando en cada intento o acierto
                system("cls");

                //Esta es la variable centinela que es usada para comprobar si se ha fallado con la letra
                cent = 0;
                printf("\n\n%29c Palabra: %s\n", ' ', guiones);
                printf("\nIntentos restantes: %d\n\n", intentos);

                //Aqui le pedimos al usuario que introduzca una letra para adivinar la palabra
                do {
                    printf("Introduce una letra minuscula [Jug.2]: ");
                    scanf("%c", &letra);
                    fflush(stdin);
                }

                //Si el caracter introducido no es una letra, lo pide de nuevo
                while (letra < 'a' || letra > 'z');

                //Este for comprueba posicion por posicion, de la cadena, si la letra introducida se encuentra en la cadena
                for(juego=0;juego<strlen(palabra);juego++){

                    if (palabra[juego] == letra)
                    {
                        guiones[juego] = letra;
                        cent = 1;
                    }
                }

                if (cent != 1)intentos--;
            }

            //Si no se han terminado los intentos ni se ha acertado, repite el do
            while(intentos!=0 && strcmp(guiones,palabra)!= 0);

            /*Para llegar a este if-else, debe de haberse gastado los intentos o haber adivinado la letra,
              entonces, si la palabra introducida letra a letra, es igual a la introducida en primera instancia
              imprime que se ha ganado y aumenta un punto al jugador que ha acertado*/
            if (strcmp(guiones,palabra)== 0) {
                system("cls");
                printf ("\n\n\n%30cSolucion: %s", ' ', palabra);
                printf("\n\n\n%26c HAS ACERTADO LA PALABRA!\n\n",' ');
                puntos2++;
            }
            /*En esta parte, si el jugador ha perdido, se le informa de ello, y aumenta un punto en el marcador del
            jugador que puso la palabra*/
            else {
                system("cls");
                printf("\n\n\n%27c JUGADOR 2 HAS PERDIDO",' ');
                printf("\n\n\n%29cLa palabra era: %s\n\n\n\n\n", ' ', palabra);
                puntos1++;
            }
        }

        //Aqui comienza el siguiente turno
        else{

            //Con este do, le pedimos al usuario que introduzca la palabra, al llegar al while, si es mayor de 50, vuelve a pedirla
            do {
                printf("Introduce la palabra a adivinar Jugador 2: ");
                scanf("%s", palabra);
                fflush(stdin);
                system("cls");
            }

            while (strlen(palabra) > 50 || 0==sololetras(palabra) );


            //Con esto imprimimos tantos guiones como caracteres tenga la palabra
            longitud=strlen(palabra);
            strcpy(guiones, "--------------------------------------------------");
            guiones[longitud]='\0';

            do{
                //Limpiamos la pantalla de lo que se va generando en cada intento o acierto
                system("cls");

                //Esta es la variable centinela que es usada para comprobar si se ha fallado con la letra
                cent = 0;
                printf("\n\n%29c Palabra: %s\n", ' ', guiones);
                printf("\nIntentos restantes: %d\n\n", intentos);

                //Aqui le pedimos al usuario que introduzca una letra para adivinar la palabra
                do{
                    printf("Introduce una letra minuscula [Jug.1]: ");
                    scanf("%c", &letra);
                    fflush(stdin);
                }

                //Si el caracter introducido no es una letra, lo pide de nuevo
                while (letra < 'a' || letra > 'z');

                //Este for comprueba posicion por posicion, de la cadena, si la letra introducida se encuentra en la cadena
                for(juego=0;juego<strlen(palabra);juego++){

                    if (palabra[juego]==letra) {
                        guiones[juego]=letra;
                        cent=1;
                    }
                }

                if (cent != 1)intentos--;

            }

            //Si no se han terminado los intentos ni se ha acertado, repite el do
            while(intentos!=0 && strcmp(guiones,palabra)!= 0);

            /*Para llegar a este if-else, debe de haberse gastado los intentos o haber adivinado la letra,
              entonces, si la palabra introducida letra a letra, es igual a la introducida en primera instancia
              imprime que se ha ganado y aumenta un punto al jugador que ha acertado*/
            if (strcmp(guiones,palabra)== 0){
                system("cls");
                printf ("\n\n\n%30cSolucion: %s", ' ', palabra);
                printf("\n\n\n%26c HAS ACERTADO LA PALABRA!\n\n",' ');
                puntos1++;
            }

            /*En esta parte, si el jugador ha perdido, se le informa de ello, y aumenta un punto en el marcador del
            jugador que puso la palabra*/
            else {
                system("cls");
                printf("\n\n\n%27c JUGADOR 1 HAS PERDIDO",' ');
                printf("\n\n\n%29cLa palabra era: %s\n\n\n\n\n", ' ', palabra);
                puntos2++;
            }
        }

        //Aqui pregunta si se sigue jugando o no, con las teclas "s" o "n", mayusculas o minusculas
        do{
            printf("\n%26c Seguir jugando? <S o N>: ", ' ');
            scanf("%c", &repeat);
            fflush(stdin);
        }

        while (repeat != 'S' && repeat != 's' && repeat != 'N' && repeat != 'n');

        //Sumamos uno a la variable turno, y asi ejecutar el codigo del siguiente jugador
        turno++;
        system("cls");
    }

    //Si el usuario a tecleado "s", se volvera a ejecutar el do inicial, y sera el turno siguiente
    while (repeat == 'S' || repeat == 's');

    //Si no se juega mas, se imprime en pantalla la puntuacion de los 2 jugadores.
    printf("\n\n\n\n\n\n%27cPuntuacion final: ",' ');
    printf("\n\n%25c(Jug.1) %d - %d (Jug.2)\n\n\n\n\n",' ', puntos1, puntos2);

    //A la espera de que el usuario pulse una tecla para salir del programa
    system ("pause");
    return(0);
}
