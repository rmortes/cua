#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char frase[51];
int longi, marca = 0, tabulacion, x=0, z, caracter;
void centrar() // Funcion que centra cada linea en la pantalla
{
    for(int i=0;i<tabulacion;i++)
    {
        printf(" ");
    }
}

int main()
{
    printf("Ejercicio 2 - Practica 2\n");
    printf("------------------------\n");
    while (marca == 0) // Bucle para leer la cadena correctamente
    {
        printf("Introduzca una frase que contenga entre 10 y 50 caracteres: ");
        gets(frase); // Lee la cadena de caracteres incluyendo los espacios
        longi = strlen(frase); // Almacena el valor de longitud de la cadena leida
        if (longi<10 || longi>50) // Si la longitud de caracteres leidos esta fuera de rango salta error
        {
            printf("Error: numero de caracteres incorrecto\n");
        }
        else
        {
            marca = 1; // Cuando la cadena se ha leido correctamente, marca = 1 para salir del bucle
        }
    }
    tabulacion = (120 - longi)/2; // Resta a 120 el ancho de la cadena y lo divide entre 2 para saber donde centrar
    z = longi;
    while(1)
    {
        _sleep(70); // Hace una pausa de 70ms
        caracter=frase[0]; // Almacenamos el primer caracter de la frase
        for(int j=0;j<=(longi-1);j++) // Mueve el caracter de la derecha al caracter de la izquierda
        {
            frase[j]=frase[j+1];
        }
        frase[longi-1]=caracter;
        system("cls"); // Borra la pantalla

        for(int i=0;i<12;i++) // Generla los saltos de linea para centrar la pantalla
        {
            printf("\n");
        }
        centrar(); // Llama al bloque de funcion 'centrar'
        for(int i=0;i<longi+2;i++) // Imprime los asteriscos de arriba
        {
            printf("*");
        }
        printf("\n");
        centrar(); // Llama al bloque de funcion 'centrar'
        printf("*%s*",frase);
        printf("\n");
        centrar(); // Llama al bloque de funcion 'centrar'
        for(int i=0;i<longi+2;i++) // Imprime los asteriscos de abajo
        {
            printf("*");
        }
        printf("\n");
    }
}
