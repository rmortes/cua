#include <stdio.h>

int main (void) {

    printf("Practica 1 de FP1. Ejercicio 1\n--------------------------------------\n");
    int a,c,d;
    char b;

    //Se introduce el primer operando

    printf("Introduzca operando 1:");
    scanf("%d", &a);
    getchar();

    //Se introduce el operador

    printf("Introduzca operador: (+,-,*,/ o %%):");
    scanf("%c", &b);
    getchar();

    //Si el operador es distinto de los permitidos da el primer mensaje de error

    if (b!='+' && b!='-' && b!='*' && b!='/' && b!='%')
    {printf("Error: operador no reconocido \n");}
    else

    //Si el operador es correcto, Se introduce el operando 2

    {printf("Introduzca operando 2:");
    scanf("%d", &c);
    getchar();

    //El programa realizará la operación solicitada segun los operandos y el operador introducidos

    switch (b) {

    case '+':
        d=a+c;
        printf("El resultado es: %d\n",d);
        break;


    case '-':
        d=a-c;
        printf("El resultado es: %d\n",d);
        break;


    case '*':
        d=a*c;
        printf("El resultado es: %d\n",d);
        break;


    case '/':

        //Haremos que en caso de división y resto entre 0, el programa nos de un error

        if (c==0)
        {printf("Error: El divisor no puede ser cero. \n;");

        }
        else
        {d=a/c;
         printf("El resultado es: %d\n",d);
         }
        break;




    case '%':
        if (c==0)
        {printf("Error: El divisor no puede ser cero. \n;");

        }
        else{
        d=a%c;
        printf("El resultado es: %d\n",d);
        break; }

    }

  }

}
