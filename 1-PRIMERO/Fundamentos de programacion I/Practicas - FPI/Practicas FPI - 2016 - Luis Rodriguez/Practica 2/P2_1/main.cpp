#include <stdio.h>
#include <stdlib.h>
#include<string.h>
int main (void)
{
    //Declaración de variables:
    int num,i,j, contador;
    char cad[25];
    //Pedimos numero mayor que 0 al usuario
    do{
        printf("Introduzca un numero mayor que cero: ");
        scanf("%d",&num);
        if(num<=0){
            printf("Error: numero incorrecto. \n");
        }
    }while(num<=0);
    printf("Los %d primeros numeros crecientes son: ",num);
    contador=0; //Iniciamos el contador a 0 debido a que no se ha mostrado ningun numero en pantalla al  inicio
            for(j=12; contador<num; j++){ //Empieza por "12" porque es el primer creciente
        //Pasamos de numero a cadena con sprintf
        sprintf(cad, "%d", j);
        //Suponemos que es creciente aunque lo comprobamos y si no lo es se lo asignamos
        int escreciente=1;
        //Hasta que se llegue a la posicion anterior a "\n", de ahi el "-1"
        for(i=0; i<strlen(cad)-1; i++){
            if(cad[i]>=cad[i+1]){
                //Asignamos que no es creciente
                escreciente=0;
            }
        }
        if(escreciente==1){
            //Sumamos uno al contador que cuenta los numeros que se muestran en pantalla
            contador=contador+1;
            //Si es creciente lo mostramos en pantalla
            printf("%d ", j);
        }
    }
    printf("\n");
    return(0);
}
