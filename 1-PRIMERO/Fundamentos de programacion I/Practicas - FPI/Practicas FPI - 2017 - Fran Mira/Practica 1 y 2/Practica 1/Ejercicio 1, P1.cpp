#include <stdio.h>
int numero_loteria, unidades, decenas, centenas, umillar, dmillar, cmillar, x;
void clasificar_numeros()
{
    unidades = numero_loteria % 10; // Calcula el resto del numero entre 10 y el resultado serán las unidades
    x = numero_loteria - unidades; // Resta al numero de loteria las unidades
    x = x % 100; // Calcula el resto del numero entre 100
    decenas = x / 10; // Divide el resto obtenido entre 10 para tener las decenas
    x = numero_loteria - decenas; // Resta las decenas al numero de la loteria
    x= x % 1000; // Calcula el resto pero ahora entre 1000
    centenas = x/100; // Divide el resto obtenido entre 100 para obtener las centenas finalmente
    x = numero_loteria - centenas; // Resta al numero de loteria las centenas
    x = x % 10000; // Saca el resto ahora dividiendo entre 10000
    umillar = x / 1000; // Divide el resto entre 1000 para obtener las unidades de millar
    x = numero_loteria - umillar; // Resta al numero de loteria las unidades de millar
    x = x % 100000; // Saca el resto dividiendo entre 100000
    dmillar = x / 10000; // Divide el resto entre 10000 para obtener las centenas de millar
}
void imprimir_resultados()
{
    if (unidades>0) // Si las unidades son mayor de 0 las muestra por pantalla
    {
        printf("Unidades: %d\n", unidades);
    }
    if (decenas>0) // Si las decenas son mayor de 0 las muestra por pantalla
    {
        printf("Decenas: %d\n", decenas);
    }
    if (centenas>0) // Si las centenas son mayor de 0 las muestra por pantalla
    {
        printf("Centenas: %d\n", centenas);
    }
    if (umillar > 0) // Si las unidades de millar son mayor de 0 las muestra por pantalla
    {
        printf("Unidades de millar: %d\n", umillar);
    }
    if (dmillar > 0) // Si las centenas de millar son mayor de 0 las muestra por pantalla
    {
        printf("Decenas de millar: %d\n", dmillar);
    }
}
int main()
{
    printf("\n\tPractica 1 de FP1. Ejercicio 1\n");
    printf("-----------------------------------------------\n\n");
    printf("Introduzca su numero de loteria (0-99999): ");
    scanf("%d",&numero_loteria);
    if (numero_loteria > 99999 || numero_loteria < 0) // Si el numero leido es mayor que '99999' o menor que '0' ---> error
    {
        printf("Numero introducido fuera de rango \n");
        return 0; // Se termina el programa
    }
    else
    {
        clasificar_numeros(); // Llamamos a la funcion que clasifica los digitos en unidades, decenas, etc...
        imprimir_resultados(); // Llamamos a la funcion que imprime
    }
    return 0; // Se termina el programa
}









