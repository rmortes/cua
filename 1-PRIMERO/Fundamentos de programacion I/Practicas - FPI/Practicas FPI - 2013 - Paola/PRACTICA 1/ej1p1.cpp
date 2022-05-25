#include<conio.h>
#include<stdio.h>
#include<math.h>

int main(void){
    int a;
    printf("Introduzca un numero de loteria entre 0 y 99999:");
    scanf("%d",&a);
    getchar;
    if(a>=0 && a<=99999){
        int decenamillar=a/10000;
        int unidamillar=(a/1000)-(decenamillar*10);
        int unidades=a%10;
        int decenas=(a/10)%10;
        int centenas=(a/100)%10;
        printf("Decena de millar: %d\n",decenamillar);
        printf("Unidades de millar: %d\n",unidamillar);
        printf("Centenas: %d\n",centenas);
        printf("Decenas: %d\n",decenas);
        printf("Unidades: %d\n",unidades);

    }else{
        printf("El numero introducido no es valido\n");
    }
    getche;
    return(0);
}
