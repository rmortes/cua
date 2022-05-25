#include <stdio.h>

int main(void){

    //DECLARACIÓN DE VARIABLES

    int a,b,r;
    char c;

    printf("Practica 1, ejercicio 1\n-----------------------------------------\n");

    //PEDIR AL USUARIO UN NUMERO "A", "B" Y UN OPERANDO. DAR ERROR EN EL CASO DE QUE SE INTRODUZCA UN OPERANDO QUE NO EXISTA

    printf("Introduzca numero a:"); scanf("%d",&a);getchar();
    printf("Introduzca operacion a realizar (+,-,*,/ o %%):\t"); scanf("%c",&c);getchar();
    printf("Introduzca numero b:"); scanf("%d",&b);getchar();

    //REALIZAR UNA OPERACIÓN UTILIZANDO UNA ESTRUCTURA DE DECISIÓN MÚLTIPLE SEGÚN EL OPERANDO QUE INTRODUZCA EL USUARIO

    switch (c){

    case '+':
        r=a+b;
        printf("El resultado es: %d\n",r);
        break;
    case '-':
        r=a-b;
        printf("El resultado es: %d\n",r);
        break;
    case '*':
        r=a*b;
        printf("El resultado es: %d\n",r);
        break;
    case '/':
        if (b==0){

        //EN EL CASO EN EL QUE SE DIVIDA POR 0 DAR UN CASO DE ERROR

        printf("Error: no se puede dividir un numero entre 0\n");
        break;
        }
        else{
        r=a/b;
        printf("El resultado es: %d\n",r);
        break;
        }
    case '%':
        if (b==0){

        //EN EL CASO EN EL QUE SE DIVIDA POR 0 DAR UN CASO DE ERROR

        printf("Error: no se puede puede calcular el resto de un numero divido entre 0\n");
        break;
        }
        else{
        r=a%b;
        printf("El resultado es: %d\n",r);
        break;
        }
    default:
        printf("Error: eso no es ningun operando");scanf("%c",&c);
        break;
    }

    return 0;
}
