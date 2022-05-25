#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
int main(void){
    int introducido,aux,resto,invertido;
    invertido=0;
    do{
    printf("Introduzca un numero:");
    scanf("%d",&introducido);
    }while(introducido<0);
    for (int i=0; i<introducido; i++){
        aux=introducido;
        resto=aux%10;
        aux=aux/10;
        invertido=invertido*10+resto;
        printf("%d %d %d ",aux,resto,invertido);
    }

    return (0);
}
