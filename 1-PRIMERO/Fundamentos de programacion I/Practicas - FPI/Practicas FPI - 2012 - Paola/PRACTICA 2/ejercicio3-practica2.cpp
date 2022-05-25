#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<conio.h>
int main(){
    printf("JUEGO DE LAS LETRAS\n-------------------\n");
    int i,j,aci,punt,puntacu;
    char a;
    char Tab[100];
    aci=0;
    puntacu=0;
    for(i=0; i<100; i++){
        Tab [i]= rand()%10+'A';
    }
    /*for de las 10 vueltas*/
    for(j=0;j<10;j++){
        printf("PANEL ACTUAL\n");
        /*for del panel de 10x10 letras*/
        for(i=0; i<100; i++){
            printf(" %c",Tab[i]);
            if(i%10==9){
                printf(" \n");
            }
        }

        /*para sacar por pantalla el texto y que sume un intento cada vez*/
        printf("Intento %d.Introduzca una letra del panel: ",j+1);
        scanf("%c",&a);
        getchar();
        /*for para que la letra que coincide con la introducida se sustituya por un guion*/
        for(i=0; i<100; i++){
            if(Tab[i]==a){
                Tab[i]='-';
                aci=aci+1;
            }
        }
        punt=aci*(10-j);
        puntacu=puntacu+punt;
        printf("%d aciertos. %d puntos. %d puntos acumulados.\n",aci,punt,puntacu);

    }
    getche();
    return 0;
}
