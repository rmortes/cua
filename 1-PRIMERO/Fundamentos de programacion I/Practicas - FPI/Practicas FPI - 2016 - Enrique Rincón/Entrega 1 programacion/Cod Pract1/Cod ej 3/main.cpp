//Practica1 Ejercio3
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main(void){
    //Cadenas
    char palabra[50],palabra1[50];
    //Variables
    int cadena;
    printf("Jugador1, introduzca la palabra secreta:");
    scanf("%s",palabra);
    getchar();
    strupr(palabra);
    system("cls");
    printf("Jugador2, primer intento (pista, la palabra empieza por\'%c'):",palabra[0]);
    scanf("%s",palabra1);
    getchar();
    strupr(palabra1);
    cadena=strlen(palabra);
    if(strcmp(palabra,palabra1)==0){
        printf("Felicidades, acertaste :3\n");
    }else{
        printf("jugador2, segundo intento(pista, la palabra termina por\'%c'):",palabra[cadena-1]);
        scanf("%s",palabra1);
        getchar();
        strupr(palabra1);
        if(strcmp(palabra,palabra1)==0){
            printf("Felicidades, acertaste :3\n");
        }else{
            printf("jugador2, tercer intento(pista, la letra central de la palabra es \'%c'):",palabra[cadena/2]);
            scanf("%s",palabra1);
            getchar();
            strupr(palabra1);
            if(strcmp(palabra,palabra1)==0){
                printf("Felicidades, acertaste :3\n");
            }else{
                printf("Lo sentimos, perdiste, la palabra era \"%s\"\n",palabra);
            }
        }
    }

    return 0;
}
