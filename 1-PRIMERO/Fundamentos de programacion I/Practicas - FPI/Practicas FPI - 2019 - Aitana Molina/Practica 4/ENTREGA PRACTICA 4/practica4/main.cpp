#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define N 6
//inicializar vector
void Inicializar(int T[], int R[]){
    for(int i=0;i<N;i++){
        T[i]=R[i]=0;
    }
    return;
}
//crear carriles
void separacionguiones(char pantalla[]){
    for(int i=0;i<80;i++){
        strcat(pantalla,"-");
    }
    strcat(pantalla,"\n");
    return;
}
void imprimirt(int T[]){
    char pantalla[80*24+100]="";//crear una cadena que englobe toda la pantalla
    printf("Carrera de trineos.\n");
    separacionguiones(pantalla);
    for(int i=0;i<N;i++){//bucle para imprimir
        for(int j=0;j<T[i];j++){
            strcat( pantalla," ");
        }
        char aux[50];
        sprintf(aux,"T%d---\\\n",i+1);
        strcat(pantalla,aux);
        for(int j=0;j<T[i];j++){
            strcat( pantalla," ");
        }
        strcat( pantalla,"<o> <o>\n");
        separacionguiones(pantalla);
    }
    system("cls");
    printf("%s",pantalla);
    return;
}
void Ranking(int R[N]){

    printf("\tEl orden de llegada es:\n");
    for(int i=0;i<N;i++){
        printf("\tT%d\n",R[i]+1);
    }
    return;
}
void Mover(int T[], int *ganadores, int R[]){
    int n;
    do{
        n=rand()%N;
    }while(T[n]==73);
    T[n]++;
    if(T[n]==73){
        R[*ganadores]=n;
        *ganadores = *ganadores + 1;
    }
    return;
}
void Practica4(){
    int T[N],R[N],L[N];
    char volverajugar;
    do{
    Inicializar(T,R);
    int ganadores=0;
    while(ganadores<N){
        imprimirt(T);
        Mover(T,&ganadores,R);
    }
    imprimirt(T);
    Ranking(R);
    printf("Jugar de nuevo?(s/n)\n");
    scanf("%s",&volverajugar);
    }while(volverajugar=='s'||volverajugar=='S');

    return;
}
int main(void){
    srand(time(NULL));
    Practica4();
    return 0;
}
/*Aitana Molina Garcia Sarrió Roldán Bañó Pascual Gonzalez Jerez*/


