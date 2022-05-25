#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void P1_ejercicio_1(){
    int a;
    //Introduce un número muestra las posiciones en las que lo quieres ver.
    printf("Introduce su numero,(el numero ha de estar comprendido entre 1y3):\t");
    scanf("%d",&a);
    getchar();
    //Los casos de las posiciones de las letras.
    switch(a){
    case 1:
        printf("\nJ o r g e");
        break;
    case 2:
        printf("\nJ\n\n\to\n\n\n\t\tr\n\n\n\n\t\t\tg\n\n\n\n\n\t\t\t\te\n");
        break;
    case 3:
        printf("\nJ\no\nr\ng\ne\n\n");
        break;
    default:
        printf("\nEl numero introducido es menor o mayor a 1 y 3\n");
        break;
    }
    return;
}
void P1_ejercicio_2(){
    int dni,resto;
    char letra,introducido;
    //Aqui introduce el número y lo muestra por pantalla.
    printf("Introduzca aqui su dni:\t");
    scanf("%d-%c",&dni,&introducido);
    if(introducido>='a'&&introducido<='z'){
        introducido=introducido-'a'+'A';
        printf("Su numero introducido es %d-%c\n\n",dni,introducido);
        resto=dni%23;
    }
    //Son los casos de Error de la letra introducida.
    switch(resto){

    case 0:

        letra='T';
        printf("Su letra es: %c\n", letra);
        break;
    case 1:
        letra='R';
        printf("Su letra es: %c\n", letra);
        break;
    case 2:
        letra='W';
        printf("Su letra es: %c\n", letra);
        break;
    case 3:
        letra='A';
        printf("Su letra es: %c\n", letra);
        break;
    case 4:
        letra='G';
        printf("Su letra es: %c\n", letra);
        break;
    case 5:letra='M';
        printf("Su letra es: %c\n", letra);
        break;
    case 6:
        letra='y';
        printf("Su letra es: %c\n", letra);
        break;
    case 7:
        letra='F';
        printf("Su letra es: %c\n", letra);
        break;
    case 8:
        letra='P';
        printf("Su letra es: %c\n", letra);
        break;
    case 9:
        letra='D';
        printf("Su letra es: %c\n", letra);
        break;
    case 10:
        letra='X';
        printf("Su letra es: %c\n", letra);
        break;
    case 11:
        letra='B';
        printf("Su letra es: %c\n", letra);
        break;
    case 12:
        letra='N';
        printf("Su letra es: %c\n", letra);
        break;
    case 13:
        letra='J';
        printf("Su letra es: %c\n", letra);
        break;
    case 14:
        letra='Z';
        printf("Su letra es: %c\n", letra);
        break;
    case 15:
        letra='S';
        printf("Su letra es: %c\n", letra);
        break;
    case 16:
        letra='Q';
        printf("Su letra es: %c\n", letra);
        break;
    case 17:
        letra='V';
        printf("Su letra es: %c\n", letra);
        break;
    case 18:
        letra='H';
        printf("Su letra es: %c\n", letra);
        break;
    case 19:
        letra='L';
        printf("Su letra es: %c\n", letra);
        break;
    case 20:
        letra='C';
        printf("Su letra es: %c\n", letra);
        break;
    case 21:
        letra='K';
        printf("Su letra es: %c\n", letra);
        break;
    case 22:
        letra='E';
        printf("Su letra es: %c\n", letra);
        break;
    default:

        printf("Su letra es correcta\n");
        break;
    }
}
void P1_ejercicio_3(){
    int a,divisor;
    //Introduce el numero en una variable.
    printf("Introduzca su numero entre comprendidos entre 1 y 100:  \t");
    scanf("%d",&a);
    getchar();
    //Comprueba si mientes si esta en el rango.
    if(a<=0){
        printf("El numero introducido es menor a 1\n");
    }if(a>=101){
        printf("Su numero escrito es mayor a 100\n");
    }if(a==1){
        printf("El numero uno no esta considerado como primo \n");
    }
    //Muestra los numeros primos.
    if(a==2||a==3||a==5||a==7||a==11||a==13||a==17||a==19||a==23||a==29||a==31||a==37||a==41||a==43||a==47||a==53||a==59||a==61||a==67||a==71||a==73||a==79||a==83||a==89||a==97){
        printf("El numero es primo\nSolo es posible dividirlo entre 1 y ellos mismos\n\n");
        //Muestra los numeros divididos.
    }else{
        for(divisor=1; divisor <= a; divisor++){
            if(a%divisor==0){
                printf("El numero %d es divisible entre %d\n",a,divisor);
            }
        }
    }
}

void P2_ejercicio_1(){
    char letra,jugar;
    int cent,min,max,cont;

    do{
        cent=50;
        min=1;
        max=100;
        cont=1;
        printf("Piensa un numero del 1 al 100 \n");

        do{

            do{
                printf("Intento %d. Es mayor(M), menor(m) o igual(i) a %d ? ",cont,cent);
                scanf("%c",&letra);
                getchar();
            }while(letra!='M' && letra!='m' && letra!='i');

            switch(letra) {

            case 'M':
                min=cent+1;
                cent=(min+max)/2;
                break;

            case 'm':
                max=cent-1;
                cent=(min+max)/2;
                break;

            case 'i':
                printf("He acertado!!!\n");
                break;

            }
            cont++;
        }while(min<max && letra!='i');

        if(min>max) {
            printf("Me has mentido. El numero no existe \n");
        }
        do{
            printf("Desea jugar de nuevo(s/n)? ");
            scanf("%c",&jugar);
            getchar();
        }while(jugar!='s' && jugar!='n');
    }while(jugar=='s');
}
void P2_ejercicio_2(){
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
        //Aquí se inicia el bucle para poder ejecutar el programa.
        //Introduce una palabra y la borra en la pantalla.
        acierto=0;
        printf("Introduce la palabra: ");
        scanf("%s",palabra);
        getchar();
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
            printf("Introduce respuesta:");
            printf("intento %d de 5. %s\t",i,palabramostrar);
            scanf("%s",respuesta);
            getchar();
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
        printf("Desea jugar de nuevo(s/n)?");
        scanf("%c",&jugar);
        getchar();
    }while(jugar=='s');
}
void P2_ejercicio_3(){

}
void practica_1(){
    char introducida;
    do{
        system("cls");
        printf("---PRACTICA 1---\n");
        printf("Elige ejercicio:\n");
        printf("a.- ejercicio_1\nb.- ejercicio_2\nc.- ejercicio_3\nd.- Salir\nOpcion:\t");
        scanf("%c",&introducida);
        getchar();

        switch(introducida){
        case 'a':
            P1_ejercicio_1();
            break;
        case 'b':
            P1_ejercicio_2();
            break;
        case 'c':
            P1_ejercicio_3();
            break;
        case'd':
            break;
        default:
            printf("Letra introducida incorrecta\n");
            break;
        }
    }while( introducida != 'd');
}

void practica_2(){
    char introducida;

    do{
        system("cls");
        printf("---PRACTICA 2---\n");
        printf("Elige ejercicio:\n");
        printf("a.- ejercicio_1\nb.- ejercicio_2\nc.- ejercicio_3\nd.- Salir\nOpcion:\t");
        scanf("%c",&introducida);
        getchar();

        switch(introducida){
        case 'a':
            P2_ejercicio_1();
            break;
        case 'b':
            P2_ejercicio_2();
            break;
        case 'c':
            P2_ejercicio_3();
            break;
        case'd':
            break;
        default:
            printf("Letra introducida incorrecta\n");
            break;
        }
    }while( introducida != 'd');
}

int main(){
    char letra;
    do{
        system("cls");
        printf("***MENU PRINCIPAL***\n");
        printf("a-. Practica_1\nb-. Practica_2\nc-.Salir\nOpcion:\t");
        scanf("%c",&letra);
        getchar();

        switch(letra){
        case 'a':
            practica_1();
            break;
        case 'b':
            practica_2();
            break;
        case 'c':
            printf("Fin del programa\n");
            break;
        default:
            printf("Letra introducida erronea\n");
            break;
        }
    }while( letra != 'c');
}
