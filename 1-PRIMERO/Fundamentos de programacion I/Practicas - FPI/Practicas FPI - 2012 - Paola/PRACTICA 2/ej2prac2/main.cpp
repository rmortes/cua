MANUUU

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include <conio.h>

int main(){
    //Se ponen las variables y la función para que sea aleatorio
    srand(time(NULL));
    int i, op1, op2, ans, aciertos, tiempo_inic, tiempo_fin, durac, puntuacion;
    char preg;
    do{
        printf("Juego de las diez sumas\n-----------------------\nPulse intro cuando este preparado");
        getchar();
        //Se inicializa el tiempo y los aciertos
        tiempo_inic = time(NULL);
        aciertos = 0;
        //Bucle para las diez preguntas aleatorias
        for(i=0; i <= 9; i++){
            op1 = rand()%10;
            op2 = rand()%10;
            printf("%d + %d = ", op1, op2);
            scanf("%d", &ans);
            getchar();
            //Se evalua si es correcta
            if(ans == (op1 + op2)){
                aciertos++;
                printf("Correcto!\n");
            }
            else{
                printf("Error, el resultado era %d\n", op1+op2);
            }
        }
        //Se pone el tiempo final y la duración
        tiempo_fin = time(NULL);
        durac = tiempo_fin- tiempo_inic;
        //Se evalúa la puntuación y se muestan los datos por pantalla
        puntuacion = (aciertos*1000)/durac;
        printf("Has conseguido %d aciertos en %d segundos. Puntuacion %d\n", aciertos, durac, puntuacion);
        //Pregunta se se quiere jugar otra vez
        printf("Desea jugar de nuevo? (s,n)");
        scanf("%s", &preg);
        getchar();
    }while(preg == 's');
    //getche();
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){

    int i;
    char p;
    srand(time(NULL));
    do{
        printf("Juego de las diez sumas\n-----------------------\n\nPulse intro para empezar...");
        getchar();
        int tiempo_inic = time(NULL);
        int aciertos = 0;
        for(i=0; i<= 9; i++){
            int a = rand()%10;
            int b = rand()%10;
            int solucion;
            printf("%d + %d = ",a,b);
            scanf("%d", &solucion);
            getchar();
            if(solucion == (a + b)){
                aciertos++;
                printf("Correcto!\n");
            }
            else{
                printf("Error.El resultado era %d.\n",a+b);
            }
        }
        int tiempo_fin = time(NULL);
        int tiempototal = tiempo_fin- tiempo_inic;
        int puntuacion = (aciertos*1000)/tiempototal;
        printf("Has conseguido %d aciertos en %d segundos. Puntuacion %d\n", aciertos, tiempototal, puntuacion);
        printf("Quiere jugar de nuevo? (s,n)");
        scanf("%s", &p);
        getchar();
    }while(p=='s');
    return 0;
}