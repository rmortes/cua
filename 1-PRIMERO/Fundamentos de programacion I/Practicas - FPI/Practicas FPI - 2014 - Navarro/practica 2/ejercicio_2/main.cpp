#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Inicio del juego.
int main() {
    char jugar;
    int i,j;
    int cont=0;
    int aocultar=0;
    int tam=0;
    char palabra[30]="";
    char respuesta[30];
    int tamresp=0;
    int acierto;

    do{
            //Introduce una palabra y la borra en la pantalla.
            acierto=0;
            printf("Introduce la palabra: ");
            scanf("%s",palabra);
            system("cls");

            tam=strlen(palabra);
            //Mide la longitud de la cadena y coloca su valor en un entero.
            aocultar=strlen(palabra)*0.75;

            char palabraoculta[tam];
            char palabramostrar[tam];
            strcpy(palabraoculta,palabra);
            //Se inicia el bucle de los intentos para adivinarla.
            for(i=1;i<=5&&acierto==0;i++) {
                //Copia la cadena en otra variable.
                strcpy(palabramostrar,palabraoculta);
                while(cont < aocultar) {
                    int posicion=0;
                    posicion=(rand()%tam);
                    if(palabramostrar[posicion]!='*'){
                        palabramostrar[posicion]='*';
                    }
                    cont++;
                }
                cont=0;
                //Pide al usuario una respuesta.
                printf("Introduce respuesta:");
                printf("intento %d de 5. %s\t",i,palabramostrar);
                scanf("%s",respuesta);
                tamresp=strlen(respuesta);
                //Caso en el que ganas el juego.
                if(tamresp==tamresp){
                    for(j=0;j<tam;j++){
                        if(palabraoculta[j]==respuesta[j]){
                            if(j==tam-1){
                                printf("Has acertado \n");
                                acierto=1;
                            }
                        }
                    }
                }
            }
            //Pregunta al usuario si desea jugar de nuevo al juego.
            printf("Desea jugar de nuevo(s/n)?");
            scanf("%s",&jugar);
            getchar();
    }while(jugar=='s');

    return 0;
}
