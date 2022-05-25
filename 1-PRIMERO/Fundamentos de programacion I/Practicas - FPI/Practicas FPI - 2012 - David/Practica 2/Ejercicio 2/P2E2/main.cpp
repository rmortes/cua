#include <stdio.h>
//#include <conio.h>
#include <stdlib.h>
#include <time.h>


int main(){
        int i, aciertos, a, b, resultado, puntuacion;
        int tinicio, tfin;
        char respuesta;

        do{
                printf("juego de las sumas\n");
                printf("------------------\n");
                printf("Pulse una tecla cuando este preparado...\n");
                // getche();
                srand(time(NULL)); // para cambiar la semilla.
                i = 1;
                aciertos = 0;
                tinicio = time(NULL);
                while(i <= 10){
                        a = rand()%10;
                        b = rand()%10;
                        printf("%d + %d = ", a, b);
                        scanf("%d", &resultado);
                        if(resultado == a + b){
                                printf("Correcto!\n");
                                aciertos++;
                        }
                        else{
                                printf("Error el resultado era %d\n", a + b);
                        }
                        i++;
                }
                tfin = time(NULL);
                puntuacion = aciertos*1000/(tfin-tinicio);
                printf("Has conseguido %d aciertos en %d segundos. Puntuacion %d\n", aciertos, tfin-tinicio, puntuacion);

                printf("Desea volver a jugar de nuevo?");
                getchar(); // ignora el intro del ultimo entero
                scanf("%c", &respuesta);

        }while(respuesta == 's' || respuesta == 'S');
        return 0;
}

