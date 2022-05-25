#include <stdio.h>
float nota1, nota2, nota3, nota4, parcial, final, teoria, practicas, total, media;
int cont_notas; // Variable que se incrementa en cada lectura correcta de cada calificacion
void leernotas()
{
    printf("Calificacion practica 1: ");
    scanf("%f", &nota1);
    if (nota1 <0 || nota1 > 10) // Si se introduce una calificacion fuera del rango--> 'ERROR'
    {
        printf("Ha introducido una calificacion erronea\n");
        return;
    }
    cont_notas++; // Si la calificacion ha sido leida correctamente "cont_notas +1"
    printf("Calificacion practica 2: ");
    scanf("%f", &nota2);
    if (nota1 <0 || nota2 > 10) // Si se introduce una calificacion fuera del rango--> 'ERROR'
    {
        printf("Ha introducido una calificacion erronea\n");
        return;
    }
    cont_notas++; // Si la calificacion ha sido leida correctamente "cont_notas +1"
    printf("Calificacion practica 3: ");
    scanf("%f", &nota3);
    if (nota1 <0 || nota3 > 10) // Si se introduce una calificacion fuera del rango--> 'ERROR'
    {
        printf("Ha introducido una calificacion erronea\n");
        return;
    }
    cont_notas++; // Si la calificacion ha sido leida correctamente "cont_notas +1"
    printf("Calificacion practica 4: ");
    scanf("%f", &nota4);
    if (nota1 <0 || nota4 > 10) // Si se introduce una calificacion fuera del rango--> 'ERROR'
    {
        printf("Ha introducido una calificacion erronea\n");
        return;
    }
    cont_notas++; // Si la calificacion ha sido leida correctamente "cont_notas +1"
    printf("Calificacion examen parcial: ");
    scanf("%f", &parcial);
    if (nota1 <0 || parcial > 10) // Si se introduce una calificacion fuera del rango--> 'ERROR'
    {
        printf("Ha introducido una calificacion erronea\n");
        return;
    }
    cont_notas++; // Si la calificacion ha sido leida correctamente "cont_notas +1"
    printf("Calificacion examen final: ");
    scanf("%f", &final);
    if (nota1 <0 || final > 10) // Si se introduce una calificacion fuera del rango--> 'ERROR'
    {
        printf("Ha introducido una calificacion erronea\n");
        return;
    }
    cont_notas++; // Si la calificacion ha sido leida correctamente "cont_notas +1"
}
void calculonotas()
{
    //// MEDIA TEORIA /////
    teoria = parcial / 3; // Calcula 1/3 de la nota parcial
    teoria = teoria + ((final / 3)*2); // Añade 2/3 a 1/2 de la nota parcial calculada anteriormente
    //// FIN MEDIA TEORIA /////
    //// MEDIA PRACTICAS /////
    practicas = (nota1 + nota2 + nota3 + nota4) / 4;
    //// FIN MEDIA PRACTICAS /////
    //// NOTA FINAL /////
    if (teoria >=4 && practicas >= 4)
    {
        total = (final*1.4-final)+(parcial*1.2-parcial)+(practicas*1.4-practicas);
    }
    else
    {
        printf("La nota de teoria es inferior a 4, no se puede hacer media\n");
        if (teoria < parcial) // Se pone como nota final la minima entre teoria-parcial
        {
            total = teoria;
        }
        else
        {
            total = parcial;
        }
    }
    //// FIN NOTA FINAL /////
}
int main()
{
    printf("Practica 1 de FP1. Ejercicio 2\n");
    printf("---------------------------------\n");
    leernotas(); // Funcion que recoge los valores de las calificaciones
    if (cont_notas==6) // Si se ha leido correctamente las calificaciones se sigue ejecutando el codigo
    {
        printf("Calificaciones finales:\n");
        calculonotas(); // Funcion que hace las operaciones de cada calificacion
        printf("Teoria: %.2f", teoria);
        printf(" Practicas: %.2f", practicas);
        printf(" Final: %.2f\n", total);
        //// RANGOS DE APROBADO-SUSPENSO ////
        if (final < 5.00) // Si la nota es menor de 5 se mostrara SUSPENSO
        {
            printf("SUSPENSO\n");
        }
        else if (final >= 5.00 && final < 7.00) // Entre 5-7 se mostrará APROBADO
        {
            printf("APROBADO\n");
        }
        else if(final >= 7.00 && final < 9.00) // Entre 7-9 se mostrará NOTABLE
        {
            printf("NOTABLE\n");
        }
        else if (final >= 9.00 && final == 10) // Entre 9-10 se mostrará SOBRESALIENTE
        {
            printf("SOBRESALIENTE\n");
        }
        //// FIN RANGOS DE APROBADO-SUSPENSO ////
    }
}


