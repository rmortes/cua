
#include <stdio.h>
int main(void)
{
    int a;
    char operador;
    int b;

    printf("Introduczca el primer valor:\n");
    scanf("%d",&a);
    getchar();

    printf("Introduzca la operacion deseada(+,-,* o /):\n");
    scanf("%c",&operador);
    getchar();

    printf("Introduzca el segundo valor:\n");
    scanf("%d",&b);
    getchar();

    switch(operador){
    case '+': printf("Resultado:""%d",a+b);    break;
    case '-': printf("Resultado:""%d",a-b);    break;
    case '*': printf("Resultado:""%d",a*b);    break;
    case '/': printf("Resultado:""%d",a/b);    break;
    default: printf("Error");                  break;
    }

    getchar();
    return 0;
}
