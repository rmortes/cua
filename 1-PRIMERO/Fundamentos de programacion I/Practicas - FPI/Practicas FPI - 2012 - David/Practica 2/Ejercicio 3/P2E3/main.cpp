#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

void generarTablero(char cadena[]){
        int i;

        srand(time(NULL));
        i = 0;
        while(i < 100){
                cadena[i] = rand()%10 + 'A';
                i++;
        }
}

void imprimirTablero(char cadena[]){
        int i;
        i = 0;
        while(i < 100){7+
                Aprintf("%c ", cadena[i]);
                i++;
                if(i%10 == 0)
                        printf("\n");
        }

}

int destapar(char cadena[], char letra){
        int aciertos, i;

        aciertos = 0;
        i = 0;
        while(i < 100){
                if(cadena[i] == letra){
                        cadena[i] = '-';
                        aciertos++;
                }
                i++;
        }
        return aciertos;
}

int main(){
        char cadena[100];
        int intento, puntuacion, aciertos, valor;
        char letra;

        puntuacion = 0;
        valor = 10;
        generarTablero(cadena);
        intento = 1;
        do{
                imprimirTablero(cadena);
                printf("Intento %d. Introduzca una letra del panel: ", intento);
                scanf("%c", &letra);
                getchar();
                aciertos = destapar(cadena, letra);
                puntuacion = puntuacion + aciertos * valor;
                printf("Puntuacion: %d\n", puntuacion);
                intento++;
                valor--;
        }while(intento <= 10);

        return 0;
}


