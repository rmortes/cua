#include stdio.h
#include stdlib.h
#include windows.h
#include time.h
#define numintentos 10

int main(void)
{
    srand(time(NULL));

    int intentos;
    char letra, cadena[100];
    int puntos, contador, acumulado=0;
    intentos=0;
    bool incompleto;



    for (int i=0;i100;i++){    randomizamos la cadena
        cadena[i]='A'+rand()%+10;
    }



    do{
    incompleto=false; presuponemos que el juego está completado pero cuando analicemos veremos que no
        puntos=contador=0;
        for (int i=0;i100;i++){    pintamos la cadena
            if (i%10==0 && i!=0){
                printf(n);
            }
            printf(%c,cadena[i]);
        }


        do{          le pedimos al usuario que introduzca datos
        printf (nn Introduce una letra );
        scanf (%c, &letra);
        fflush (stdin);
        }while ((letra65  letra90) && (letra97  letra122));


        for (int i=0;i100;i++){    comparamos la letra introducida y sabremos si hemos acertado

            if(cadena[i]==letra  cadena[i]==letra-32) {
                cadena[i]='-';
                contador++;
            }
            if (cadena[i]!='-'){
                incompleto=true; hemos analizado el juego y vemos que no está completado
            }
        }
        printf(n Intentos %d,intentos+1);
        printf(n aciertos %d,contador);
        puntos=contador(10-intentos);
        printf(nn puntuacion de la jugada %d,puntos);
        acumulado=acumulado+puntos;
        printf(n Acumulado %d n,acumulado);
        getchar();
        intentos++;hemos fallado restamos 1

    }while(intentosnumintentos && incompleto==true);

    printf (nn EL JUEGO HA TERMINADO MUJAJAJAJA);

    getchar();
    return (0);
}

