//Practica2 Ejercicio3
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
int main(void){
    //Cadenas
    char palabra[50],desordenada[50],respuesta[50],repetir[50];
    do{
        system("cls");
        printf("jugador1, introduzca la palabra secreta:");
        scanf("%s",palabra);
        strupr(palabra);
        int n=strlen(palabra);
        strcpy(desordenada,palabra);
        system("cls");
        //Variable "corta", corta el bucle si se gana
        int corta = 0;
        //Da hasta 5 intententos para acertar
        for(int i=1;i<6&&corta==0;i++){
            //Desordena n*n veces la palabra
            for(int j=0;j<n*n+1;j++){
                int r1=rand()%n;
                int r2=rand()%n;
                //Guardamos el caracter de la posicion r1
                char aux = desordenada[r1];
                //Intercambiamos los caracteres de r1 y r2
                desordenada[r1] = desordenada[r2];
                desordenada[r2] = aux;
            }
            printf("jugador 2, intento %d de 5, pista: %s, su propuesta de palabra:",i,desordenada);
            scanf("%s",respuesta);
            strupr(respuesta);
            if(strcmp(palabra,respuesta)==0){
                printf("Felicidades, has ganado!!\n");
                corta=1;
            }
        }
        if(corta==0){
            printf("Has perdido, la palabra secreta era %s\n",palabra);
        }
        //volver a jugar
        printf("Deseas volver a jugar?Y/N:");
        scanf("%s",repetir);
        strupr(repetir);
    }while(strcmp(repetir,"N")!=0);
    return 0;
}
