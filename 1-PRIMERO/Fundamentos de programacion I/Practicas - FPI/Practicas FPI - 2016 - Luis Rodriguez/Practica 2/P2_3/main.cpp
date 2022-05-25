#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
    //Declaramos variables:
    char palabrasecreta[20], intento [20], pista [20];
    int n ,i , nintento, jugar=2, a, b, c;
    char pregunta[3];
    while(jugar==2){
        jugar=0;
        //Pedimos palabra al Jugador 1
        printf("Introduzca palabra oculta: ");
        scanf("%s",palabrasecreta);
        //Evitamos la sensibilidad entre mayusculas y minusculas
        strupr(palabrasecreta);
        //Borramos pantalla
        system ("cls");
        //Comienza el jugador 2
        //Ultima posición de la letra en la palabra secreta
        n=strlen(palabrasecreta);
        //nintento=numero de intentos; 5 son los intentos que hay (por si en el futuro se quiere modificar.)
                for(nintento=1; nintento<=5; nintento++){
            //Para dar la pista
            strcpy(pista,palabrasecreta);
            for ( i=0; i < (n*n); i++){
                a=rand()%n;
                b=rand()%n;
                c=pista[a];
                pista[a]=pista[b];
                pista[b]=c;

            }
            printf("Intento %d de 5, pista: %s palabra? ", nintento , pista);
            scanf("%s",intento);
            //Para evitar la sensibilidad dentree mayusculas y minusculas
            strupr(intento);
            //Si el intento y la palabra secreta son iguales, el jugador ha ganado
            if(strcmp(palabrasecreta,intento)==0){
                printf(" Has acertado! \n");
                printf("Deseas jugar de nuevo (s/n)? ");
                scanf("%s",pregunta);
                if(pregunta[0]== 'S' || pregunta[0]== 's'){
                    //Iniciar de nuevo el bucle del juego
                    jugar=2;
                }
                //Para acabar el bucle
                nintento=10;
            }
            if(nintento==5){
                printf("Lo siento, has consumido los intentos, la palabra era: ' %s '\n",palabrasecreta);
                       printf("Deseas jugar de nuevo (s/n)? ");
                        scanf("%s",pregunta);
                if(pregunta[0]== 'S' || pregunta[0]== 's'){
                    //Iniciar otra vez el bucle para jugar
                    jugar=2;
                }
                //Acabar el bucle de intentos
                nintento=10;
            }
        }
    }
    return(0);
}
