#include <stdio.h>
int main()
{
    int numero=112, a, divisor=1, n, par=0, impar=0, contador=0;

    do{
        printf("Introduzca un numero mayor que cero: ");
        scanf("%d",&a);
        getchar();
        if(a<=0){
            printf("error, el numero es menor o igual a cero\n");
        }
    }while(a<=0);

    printf("los %d primeros numeros parejos son: ",a);

    while (contador!=a){
        while(numero/divisor>=1){
            n=(numero/divisor)%10;
            divisor=10*divisor;
            if (n%2==0){
                par=n+par;
            }
            else
                impar=n+impar;
        }
        if (par==impar){
            printf("%d ",numero);
            contador=contador+1;
        }
        numero++;
        par=0;
        impar=0;
        divisor=1;
    }

    printf("\n");
    return 0;
}

