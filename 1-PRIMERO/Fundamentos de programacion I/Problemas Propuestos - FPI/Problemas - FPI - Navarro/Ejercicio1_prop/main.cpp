#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 15
int main(){
    int edad[N];
    int d,c,edadmedia;
    for (int i=0; i<N; i++){
        do{
        printf("Cual es su edad actual?(edades introducidas%d)\n",i);
        scanf("%d",&edad[i]);
        if(edad[i]<=0 || edad[i]>=100){
            printf("ERROR 404\n");
        }

        }while(edad[i]<=0 || edad[i]>=100);

    }
    printf("Acabas de poner todos las edades\n");
    for (int j=0; j<N; j++){
        if(d<edad[j]){
            d=edad[j];
        }if(c>edad[j]){
            c=edad[j];
        }

    }
    printf("La edad maxima de la poblacion es: %d\n",d);
    printf("La edad minima de la poblacion es: %d\n",c);
    for (int o =0; o<N; o++){
        int suma,f,k=0;
        f=edad[o];
        ;
        edadmedia=suma/N;
    }
    printf("Edad media de la poblacion: %d",edadmedia);

}
