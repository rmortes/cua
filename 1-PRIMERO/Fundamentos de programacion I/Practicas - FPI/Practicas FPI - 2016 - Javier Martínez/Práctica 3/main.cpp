#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


//Practica 2

int caballos (void) {
    srand(time(NULL));

    //Declaramos las variables principales.

    int apuesta;

    //Las variables de cadena añadirán espacios antes de los caballos para que avancen

    char EspCab0[73]="", EspCab1[73]="", EspCab2[73]="", EspCab3[73]="";

    printf("Ejercicio 3. Practica 2. Fundamentos de Programacion 1. \n-------------------------------------------------------------------------------\n");

    //Bucle para pedir la apuesta en caso de que no se seleccione una posible

    do {printf("Introduzca su apuesta (1-4): ");
    scanf("%d", &apuesta);
    getchar();}
    while (apuesta!=1 && apuesta!=2 && apuesta !=3 && apuesta!=4);


    //Creamos un bucle for que vaya añadiendo concatenando espacios a los caballos mientras que estos no lleguen al final de la pantalla

    for (int contador=0; strlen(EspCab0)<80-7 && strlen(EspCab1)<80-7 && strlen(EspCab2)<80-7 && strlen(EspCab3)<80-7; contador++){

        int elegido = rand()%4;

        //La máquina creará un numero aleatorio del 0 al 3, el elegido, mediante un switch será el que concatene un espacio a la cadena del caballo

        switch (elegido){
            case 0:
            strcat(EspCab0," ");
            break;
            case 1:
            strcat(EspCab1," ");
            break;
            case 2:
            strcat(EspCab2," ");
            break;
            case 3:
            strcat(EspCab3," ");
            break;             }

    //se borra la pantalla, y la maquina irá haciendo avanzar aleatoriamente a los caballos. Con el contador del for , animamos la carrera mostrando los supuestos metros recorridos

    system("cls");

    printf("                        CARRERA DE CABALLOS     \n");
    printf("                        metros recorridos: %d\n\n", contador);
    printf("                  ------------------------------------                \n\n");

    printf("%s~__/'>\n",EspCab0);
    printf("%s// \\\\\n",EspCab0);

    printf("--------------------------------------------------------------------------------\n");

    printf("%s~__/'>\n",EspCab1);
    printf("%s// \\\\\n",EspCab1);

    printf("--------------------------------------------------------------------------------\n");


    printf("%s~__/'>\n",EspCab2);
    printf("%s// \\\\\n",EspCab2);

    printf("--------------------------------------------------------------------------------\n");

    printf("%s~__/'>\n",EspCab3);
    printf("%s// \\\\\n",EspCab3);

    printf("--------------------------------------------------------------------------------\n");

    _sleep(1);

    }

    //Se comprueba cual es el caballo ganador y se compara con nuestra apueseta.

    int caballo;

    if(strlen(EspCab0)==80-7){
        printf("El ganador es el caballo: 1\n");
        caballo=1;}
        else {
            if(strlen(EspCab1)==80-7){
                printf("El ganador es el caballo: 2\n");
                caballo=2;}
                else {
                    if(strlen(EspCab2)==80-7){
                        printf("El ganador es el caballo: 3\n");
                        caballo=3;}
                        else {
                            if(strlen(EspCab3)==80-7){
                                printf("El ganador es el caballo: 4\n");
                                caballo=4;}
                    }
                            }
                            }

    printf("Tu apostaste por el caballo: %d \n",apuesta);
    if(caballo==apuesta){
        printf("ENHORABUENA!! Tu caballo es el ganador!!\n\n");
    }else{
        printf("Lo siento, tu apuesta no fue la ganadora. :(  \n\n");
    }





return 0;

}

int cadenaexpansora (void){

    char cadena[100];

    printf("Ejercicio 2. Practica 2. Fundamentos de Programacion 1. \n--------------------------------------------------------------------------------\n");

    //Pedimos al usuario la cadena que queremos que se expanda
    printf("Introduzca cadena de maximo de 20 caracteres: ");
    gets(cadena);

    //En caso de superar los caracteres permitidos, le volvemos a preguntar
    while(strlen(cadena)>20)
    {printf("Error, numero de caracteres permitido excedido. Vuelve a introducir: ");
        gets(cadena);}



    //iniciamos el bucle principal y declaramos e inicializamos nuestro contador
    int ciclo=0,longitud;
    int n=0;
    while(n<5){


            system("cls");

            printf("\n\n\n\n\n\n\n\n\n\n\n\n");



            //Calcula el valor total de caracteres de nuestra cadena, incluidos los espacios
            longitud=strlen(cadena)+((strlen(cadena)-1)*ciclo);

            if(longitud<=80){

                //Trataremos de centrar la cadena en lo ancho de la pantalla
                for (int centro=40-longitud/2;centro>0;centro--)
                {printf(" ");}

                //Escribimos la cadena
                for(int posicion=0;posicion<strlen(cadena);posicion++){
                    {printf("%c",cadena[posicion]);}

                    //Escribimos el espacio entre las letras
                    for(int contador=0;contador<ciclo;contador++){ printf(" ");};
                }

                //Se repetirá el ciclo una vez más
                ciclo++;

                _sleep(250);
            }


            //si la cadena con los espacios >80, los borramos y volvemos a empezar


            else {ciclo=0;
            n++;}

    }
    return(0);


}

void calculo (int numerosamostrar){

    int inicial=1,capicua;

    while (numerosamostrar>0){
    capicua=inicial;

    int inverso=0;

    while(capicua>0)
    { inverso=inverso*10+capicua%10;
        capicua=capicua/10;

        if(inicial==inverso)
        {printf("%d  ",inverso);
            numerosamostrar--;
        }
    }
    inicial++;
}
    return ;
}
int capicua (void) {

    int numerosamostrar;

    printf("Ejercicio 1. Practica 2. Fundamentos de Programacion I. \n--------------------------------------------------------------------------------\n");

    do{printf("Introducir numero mayor que 0: "); scanf("%d", &numerosamostrar); getchar();
        if (numerosamostrar<=0)
        {printf("Error, numero menor o igual a 0. Introducir numero mayor que 0: ");}
    }

    while (numerosamostrar<=0);


    calculo(numerosamostrar);
    printf("\n");

    return(0);
}



//Practica 1

void datos (int *a){
    do{
        printf("Introduzca numero entre 0 y 10: "); scanf("%d",a); getchar();
        if (*a>10||*a<0){
            printf("Error: El numero introducido no es valido\n");
        }
    }while (*a>10||*a<0);
    return;
}
void pensador (int b){
    int a;
    for (int oportunidades=0;oportunidades<3;oportunidades++){
        datos(&a);
        if (a==b){
            printf("\nFELICIDADES, HAS ACERTADO!!!!\n");
            return;
        }else{

            if(a>b){
                printf("Lo siento, el numero introducido es mayor.\n ");
            }else{
                printf("Lo siento, el numero introducido es menor.\n ");
            }
        }}
    printf("\n HAS PERDIDO! El numero era: %d Pero no te rindas :) \n\n", b);
    return ;
}
int juego(void) {
    printf("\nPractica 1. Ejercicio 3. Fundamentos de Programacion 1. \n--------------------------------------------------------------------------------\n");

    srand(time(NULL));

    int  b = rand()%10+1;


    pensador(b);



    return 0;
}

char posicion (char *cadena){
    {printf("\n\n\n\n\n\n\n\n\n\n\n\n");

        //Se procede a hacer la resta entre la mitad de la posible longitud de pantalla y la londitud de la cadena en la mitad

        switch (40-strlen(cadena)/2) {

        case 40:
            printf("                                         ");
            break;

        case 39:
            printf("                                       ");
            break;

        case 38:
            printf("                                      ");
            break;

        case 37:
            printf("                                     ");
            break;

        case 36:
            printf("                                    ");
            break;

        case 35:
            printf("                                   ");
            break;

        case 34:
            printf("                                  ");
            break;

        case 33:
            printf("                                 ");
            break;

        case 32:
            printf("                                ");
            break;

        case 31:
            printf("                               ");
            break;

        case 30:
            printf("                              ");
            break;




        } printf("%s", cadena);
        printf("\n\n\n\n\n\n\n\n\n\ns\n\n");
}
    return 0;
}
int cadenacentral (void) {
    char (cadena) [100];


    printf("Practica 1. Ejercicio 2. Fundamentos de Programacion 1. \n--------------------------------------------------------------------------------\n");

    do{printf("Introduzca cadena par de menos de 20 caracteres: ");
        gets(cadena);

        if (strlen(cadena)>20)
        {printf("Error: El numero de caracteres es incorrecto\n"); }
        else


        {if(strlen(cadena)%2!=0)
            {printf("Error: El numero de caracteres no es par\n"); }
            else


                posicion(cadena);
        }}while(strlen(cadena)>20 || strlen(cadena)%2!=0 );
    return 0;
}

void datos (int *a, char *b, int *c){

    printf("Introduzca operando 1:"); scanf("%d", a); getchar();
    printf("Introduzca operador: (+,-,*,/ o %%):"); scanf("%c", b); getchar();
    printf("Introduzca operando 2:"); scanf("%d", c); getchar();

    return;
}
void calculo (int a, char b, int c){
    int d;
    switch (b) {

    case '+':
        d=a+c;
        printf("El resultado es: %d\n",d);
        break;
    case '-':
        d=a-c;
        printf("El resultado es: %d\n",d);
        break;
    case '*':
        d=a*c;
        printf("El resultado es: %d\n",d);
        break;
    case '/':
        if (c==0)
        {printf("Error: El divisor no puede ser cero. \n;");}
        else{
            d=a/c;
            printf("El resultado es: %d\n",d);}
        break;
    case '%':
        if (c==0)
        {printf("Error: El divisor no puede ser cero. \n;");}
        else{
            d=a%c;
            printf("El resultado es: %d\n",d);
            break; }

    }

    return;
}
void calculadora (void) {

    printf("Practica 1 de FP1. Ejercicio 1\n--------------------------------------------------------------------------------\n");
    int a,c;
    char b;

    datos(&a, &b, &c);
    calculo(a, b, c);

    return;

}

//Menu

void practica1 () {

    char practica1;

    do{

        do{
            printf("\n*** PRACTICA 1 ***\n");
            printf("a.- Ejercicio 1\n");
            printf("b.- Ejercicio 2\n");
            printf("c.- Ejercicio 3\n");
            printf("d.- Volver al menu anterior\n");
            printf("\n");
            printf("Opcion: ");
            scanf("%c", &practica1);
            getchar();}
        while(practica1!='a' && practica1!='b' && practica1!='c' && practica1!='d' );

        switch (practica1){

        case 'a':
            calculadora();
            break;
        case 'b':
            cadenacentral();
            break;
        case 'c':
            juego();
            break;
        }
    }while(practica1!='d');
    return;
}
void practica2 () {

    char practica2;

    do{

        do{
            printf("\n*** PRACTICA 2 ***\n");
            printf("a.- Ejercicio 1\n");
            printf("b.- Ejercicio 2\n");
            printf("c.- Ejercicio 3\n");
            printf("d.- Volver al menu anterior\n");
            printf("\n");
            printf("Opcion: ");
            scanf("%c", &practica2);
            getchar();}
        while(practica2!='a' && practica2!='b' && practica2!='c' && practica2!='d' );

        switch (practica2){

        case 'a':
            capicua();
            break;
        case 'b':
            cadenaexpansora();
            break;
        case 'c':
            caballos();
            break;
        }
    }while(practica2!='d');
    return ;
}
int main (void) {

    char opcion;

    do {printf("\n=== MENU PRINCIPAL ===\n\n");

        do{
            printf("a.- Practica 1\n");
            printf("b.- Practica 2\n");
            printf("c.- Salir.\n");
            printf("\n");
            printf("Opcion: ");
            scanf("%c", &opcion);
            getchar();}
        while(opcion!='a' && opcion!='b' && opcion!='c');

        switch (opcion){

        case 'a':
            practica1();

            break;
        case 'b':
            practica2();
            break;
        }
    }while(opcion!='c');
    return (0);
}
