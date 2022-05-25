#include <stdio.h>
#include <stdlib.h>
char nombre1[30], nombre2[30];
int dd1,mm1,aaaa1,dd2,mm2,aaaa2, dias1, dias2, anyos, meses, dias;
int main()
{
    printf("********************************\n");
    printf("Practica 1 de FP1. Ejercicio 3\n");
    printf("********************************\n");
    printf("Introduzca nombre de la primera persona: ");
    scanf("%s", &nombre1);
    printf("Introduzca fecha de nacimiento de la primera persona (dd/mm/aaaa): ");
    scanf("%d/%d/%d", &dd1, &mm1, &aaaa1);
    if (dd1> 30 || dd1 <1 || mm1>12 || mm1<1 || aaaa1>2500 || aaaa1<1900) // Si alguna fecha esta fuera del rango se va a error
    {
        printf("Error. La fecha introducida no es correcta.\n");
        return 0;
    }
    printf("Introduzca nombre de la segunda persona: ");
    scanf("%s", &nombre2);
    printf("Introduzca fecha de nacimiento de la primera persona (dd/mm/aaaa): ");
    scanf("%d/%d/%d", &dd2, &mm2, &aaaa2);
    if (dd2> 30 || dd2 <1 || mm2>12 || mm2<1 || aaaa2>2500 || aaaa2<1900) // Si alguna fecha esta fuera del rango se va a error
    {
        printf("Error. La fecha introducida no es correcta.\n");
        return 0;
    }
    dias1 = dd1 + (mm1 * 30) + (((2017-aaaa1)*12)*30); // Se pasa la fecha a dias
    dias2 = dd2 + (mm2 * 30) + (((2017-aaaa2)*12)*30); // Se pasa la fecha a dias
    if (dias1 > dias2) // Se comprueba si los dias el 1ro son mayores que los del 2do
    {
        anyos = abs(aaaa1 - aaaa2); // Se resta una fecha con otra y nos quedamos con el valor absoluto
        meses = abs(mm1 - mm2); // Se resta una fecha con otra y nos quedamos con el valor absoluto
        dias = abs(dd1 - dd2); // Se resta una fecha con otra y nos quedamos con el valor absoluto
        printf("Resultado: %s es mayor que %s %d anyos %d meses y %d dias.\n", nombre1, nombre2, anyos, meses, dias);
    }
    else if (dias < dias2)
    {
        anyos = abs(aaaa1 - aaaa2); // Se resta una fecha con otra y nos quedamos con el valor absoluto
        meses = abs(mm1 - mm2); // Se resta una fecha con otra y nos quedamos con el valor absoluto
        dias = abs(dd1 - dd2); // Se resta una fecha con otra y nos quedamos con el valor absoluto
        printf("Resultado: %s es menor que %s %d anyos %d meses y %d dias.\n", nombre1, nombre2, anyos, meses, dias);
    }
    return 0;

}




