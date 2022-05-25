#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
int main(void){ //Definir datos
    int l,i,centinela=0,mitad,aleatorio;
    char palabra1[68]/*secreta*/,pista[68];
    char palabra2[68];
    char jugardenuevo;
    do{
        srand(time(NULL));//para sacar numeros aleatorios diferentes
        printf("Practica 2 de FP1. Ejercicio 3\n");
        printf("------------------------------\n");
        printf("Jugador 1, introduzca la palabra secreta:\n");
        scanf("%s",palabra1);
        getchar();
        l=strlen(palabra1);
        system("cls");
        printf("Practica 2 de FP1. Ejercicio 3\n");
        printf("------------------------------\n");
        //Blucle para repetir los 5 intentos

        for(i=0;i<6&&(centinela==0);i++){
            strcpy(pista,palabra1);//copia el contenido de palabra1 en palabra2
            if(l%2==0){//si l es par
                for(mitad=0;mitad<=l/2;mitad++){//variable nueva para sacar la mitad de asteriscos
                    aleatorio = rand()%l;
                    pista[aleatorio]='*';
                }
            }else{//si l es impar
                for(mitad=0;mitad<=(l/2)+1;mitad++){//variable nueva para sacar la mitad de asteriscos +1
                    aleatorio = rand()%l;
                    pista[aleatorio]='*';
                }
            }
            printf("Jugador 2, intento %d de 5, pista: %s, introduzca palabra: \n",i,pista);
            scanf("%s",palabra2);
            getchar();
            system("cls");
            printf("Practica 2 de FP1. Ejercicio 3\n");
            printf("------------------------------\n");
            if(strcmp(palabra1,palabra2)==0){
                printf("Felicidades! Acertaste.\n");
                centinela=1;
            }else{
                centinela=0;
            }
        }if(strcmp(palabra1,palabra2)!=0){
            printf("Lo siento, perdiste, la palabra era '%s'\n",palabra1);
        }
        do{
            printf("Jugar de nuevo? (s/n)");
            scanf("%s",&jugardenuevo);
        }while(jugardenuevo!='s' && jugardenuevo!='S' && jugardenuevo!='n' && jugardenuevo!='N');

    }while(jugardenuevo=='s'||jugardenuevo=='S');

    return 0;
}

