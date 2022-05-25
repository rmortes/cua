#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/*SUPERIMPAR:
 * impar -> N/2 != par
 * compuesto por 1,3,5,7,9,... cifras(impares)
 * las cifras que forman el numero son impares
 * si sumamos las cifras del numero el resultado es un numero impar
*/
int main(void){
    printf("Practica 2 de FP1. Ejercicio1\n");
    for (int i=0;i<30;i++) {
        printf("-");
    }
    printf("\n");
    int n,i,numeroimpar=0,numero,centinela=0,totalcifras=1;
    int resultado,cifra;
    printf("Introduzca un numero entero mayor que cero.\n");scanf("%d",&n);
    while (n<=0) {
        printf("Lo siento, el numero es menor o igual que 0.\n");
        printf("Introduzca un numero mayor a cero:\n");scanf("%d",&n);
    }
    for (i=0;i<n;numeroimpar++) {
        //para que sea impar
        if (numeroimpar%2!=0){
            numero=numeroimpar;
            resultado=0;
            centinela=0;
            //
            for (totalcifras=0;numero!=0&&centinela==0;totalcifras++) {
                cifra=numero%10;
                numero=numero/10;//al hacer esta operacion le quitas una cifra al numero y la sumas al contador ya que realiza una vuelta por cifra al bucle.
                resultado=resultado+cifra;
                if(cifra%2==0){
                    centinela=1;
                }
            }
            if(totalcifras%2!=0&&resultado%2!=0&&centinela==0){
                printf("\t%d ",numeroimpar);
                printf(" ");
                i++;
            }
        }
    }
    return(0);
}
