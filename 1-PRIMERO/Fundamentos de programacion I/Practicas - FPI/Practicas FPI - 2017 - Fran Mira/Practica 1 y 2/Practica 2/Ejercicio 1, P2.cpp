#include <stdio.h>
int numero, primos, segunprimo, num, b, numprimo[30000], a, n, x, c,f,h=1;
int cifra[500],y;
void primo()
{
    a = c; // C primero es el numero introducido y despues va variando entre 0 hasta X
    while (a>0) // Separa los numeros en cifras 123 ---> 1, 2, 3
    {
        cifra[x]=a%10;
        a=a/10;
        x++;
    }
    for(int i=0;i<x;i++) // Suma las cifras 1,2,3 ---> 1+2+3+
    {
        segunprimo = segunprimo + cifra[i];
    }

    for(int i=1;i<(c+1);i++) // Comprueba si la suma es primo 1+2+3 = 6, 6 no es primo
    {
        if(segunprimo%i==0) // Comprueba cuantas veces el resto da 0
        {
            b++; // Variable para conocer el numero de divisiones de ese numero resultan 0, en caso de 6 ---> b = 4
        }
    }

}

int main()
{
    while (numero<1)
    {
        printf("Introduce un numero mayor a cero: ");
        scanf("%d", &numero);
        if (numero<1)
        {
            printf("Numero introducido erroneo\n");
        }
    }
    c = numero;
    primo();
    if(b!=2) // Condicion para saber si el numero es primo
    {
        printf("El numero introducido no es primo segundo\n");
        return 0;
    }
    b=0;
    c = 0;
    printf("Los primeros %d numeros primo segundos son: \n", numero);
    while(num<numero) // Bucle para imprimir todos los numeros primos segundos
    {
        // Inicializacion de variables
        segunprimo = 0;
        x = 0;
        c++; // Numero que va aumentando desde 0 hasta X para comprobar que sea primo segundo
        primo(); // Llama al bloque de funcion que comprueba que sea primo segundo


        if (b!=2) // Si la variable es diferente de 2 no es primo y se descarta ese numero
        {
            b=0;
        }
        else if (b=2) // Si la variable es 2 significa que es primo segundo
        {
            printf("%d ", c);
            b=0; // Variable a 0 para volver a comprobar
            num++; // Si num < numero se terminara el programa
        }

    }
    return 0;
}



