#include <stdio.h>
int main(void)
{
    int a, b;
    char operador;

    //  En este apartado se introduce el primer dato por el teclado,
    //  el programa escanea ese valor y lo almacena.

    printf("Introduzca el primer valor:\n");
    scanf("%d",&a);
    getchar();

    //  En este apartado se introduce un car�cter matem�tico que desea
    //  utilizar, el programa escanea ese car�cter y lo almacena.
    //  En caso de no existir en la memoria del programa
    //  imprimir� "Error" cuando ejecute el switch.

    printf("Introduzca la operaci�n deseada(+ , - , * o /):\n");
    scanf("%c",&operador);
    getchar();

    //  En este apartado se introduce el segundo dato por el teclado,
    //  el programa escanea ese valor y lo almacena.

    printf("Introduzca el segundo valor:\n");
    scanf("%d",&b);
    getchar();

    //  La operaci�n switch elige que operaci�n se debe ejecutar
    //  registrando el car�cter introducido anteriormente.

    switch(operador){
        case '+': printf("Resultado:""%d",a+b);     break;
        case '-': printf("Resultado:""%d",a-b);     break;
        case '*': printf("Resultado:""%d",a*b);     break;
        case '/': printf("Resultado:""%d",a/b);     break;
    default:  printf("Error");                  break;
    }

    getchar();
    return 0;
}
