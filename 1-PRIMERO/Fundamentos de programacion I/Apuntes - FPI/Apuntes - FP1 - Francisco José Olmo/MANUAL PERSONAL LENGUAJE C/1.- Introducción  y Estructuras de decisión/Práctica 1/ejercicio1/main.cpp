#include <stdio.h>

int main(){
    int a,b,c;

    printf("Ejercicio 1 Practica 1\n");
    printf("----------------------\n");

    printf("Longitud del primer lado: ");
    scanf("%d",&a);
    getchar();
    printf("Longitud del segundo lado: ");
    scanf("%d",&b);
    getchar();
    printf("Longitud del tercer lado: ");
    scanf("%d",&c);
    getchar();

    if(a<0 || b<0 || c<0 || a+b<c || a+c<b || c+b<a){
        printf ("Las longitudes no se corresponden con un triangulo valido");
    }

    else
        if (a==b && c==a){
            printf("El triangulo es equilatero");
        }
        else
            if (b==a || c==a || b==c){
                printf("El triangulo es isosceles");
            }
            else
                printf("El triangulo es escaleno");

    printf("\n");
    return 0;

}

