#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int numero, random, tiempofinal, num;
char z;
void juego()
{
    ////// INICIALIZACION DE VARIABLES ///////
    do // Bucle para evitar tener un 0 en el numero aleatorio
    {
    num = rand()%101; // Genera un numero aleatorio entre 1 y 100
    }
    while (num == 0);
    int tiempo = time(NULL); // Recoge los segundos en los que empieza el juego
    int intento = 1;
    int marca = 0;
    ////// FIN INICIALIZACION DE VARIABLES ///////
    printf("Adivine el numero secreto del 1 al 100\n");
    while (marca==0)
    {
        printf("Intento %d: ", intento);
        scanf("%d", &numero);
        if (numero<num) // Compara el numero introducido con el generado aleatoriamente
        {
            printf("El numero secreto es mayor\n");
            intento++;
        }
        else if (numero>num) // Compara el numero introducido con el generado aleatoriamente
        {
            printf("El numero secreto es menor\n");
            intento++;
        }
        else if (num == numero) // Compara el numero introducido con el generado aleatoriamente
        {
            tiempofinal = (time(NULL)) - tiempo; // Resta el tiempo en el que el juego termina con el guardado al empezar el juego
            printf("ACERTASTE!!!\n");
            printf("Has realizado %d intentos y has tardado %d segundos en acertar el numero", intento, tiempofinal);
            marca = 1; // Ponemos marca a 1 para salir del bucle
        }
    }
}

int main()
{
    srand(time(NULL)); // Hace que el numero aleatorio se genere en funcion del tiempo para que no hayan repeticiones
    printf("Ejercicio 3 - Practica 2\n");
    printf("---------------------\n");
    juego();
    while (1)
    {
        printf("\nDeseas jugar de nuevo (s/n)?");
        scanf("%s", &z);
        switch (z) {
        case 's':
            juego(); // Llama a la funcion 'juego' para volver a jugar
            break;
        case 'n':
            return 0; // Fin del programa
            break;
        }
    }
}
