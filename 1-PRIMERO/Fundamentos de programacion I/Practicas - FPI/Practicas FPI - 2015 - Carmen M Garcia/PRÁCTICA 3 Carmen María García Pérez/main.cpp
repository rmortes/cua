#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int FILTRAR_NUM(int min,int max){ //usada en p1ej3, p2ej1, p2ej3
    int num;
    if(min<max){
        //pide un número comprendido entre otros dos
        do{
            scanf("%d",&num);
            getchar();
            if(num>max || num<min) printf("Error. Ese no es un numero valido.\n\nIntroduce un numero del %d al %d: ",min,max);
        }while(num>max || num<min);
    }else{
        //pide un número mayor que otro
        do{
            scanf("%d",&num);
            getchar();
            if(num<=min) printf("Error. El numero introducido no es valido.\n\nIntroduce un numero mayor que %d: ",min);
        }while(num<=min);
    }
    return num;
}

void ENTRADA_CALCULADORA (int *num1, int *num2, char *op){ //pide los num y el caracter de la p1ej1
    printf("Introduzca un numero: ");
    scanf("%d",num1);
    getchar();
    do{
        printf("Introduzca la operacion que desea realizar (+, -, *, / o %%): ");
        scanf("%c",op);
        getchar();
        if(*op!='+' && *op!='-' && *op!='*' && *op!='/' && *op!='%') printf("Error: operacion invalida.\n");
    }while(*op!='+' && *op!='-' && *op!='*' && *op!='/' && *op!='%');
    do{
        printf("Introduzca otro numero: ");
        scanf("%d",num2);
        getchar();
        if((*op=='/'  || *op=='%') && *num2==0)  printf("Error, el divisor no puede ser 0.\n");
    }while((*op=='/'  || *op=='%') && *num2==0);

    return;
}

int OPERACION (int a, int b, char c){
    int result;
    switch (c){
    case '+':
        result=a+b;
        break;
    case '-':
        result=a-b;
        break;
    case '*':
        result=a*b;
        break;
    case '/':
        result=a/b;
        break;
    case '%':
        result=a%b;
        break;
    }
    return result;
}

void P1EJ1 (void){
    printf("\n\nPractica 1 de FPI. Ejercicio 1.\n\n-------------------------------------------------------\n\n");

    int a, b;
    char c;
    ENTRADA_CALCULADORA(&a,&b,&c);

    int result=OPERACION(a,b,c);
    printf("Resultado: %d %c %d = %d\n\n",a,c,b,result);

    return;
}

void PEDIR_CADENA (char cadena[],int a){
    if(a==1){
        //pide una cadena par o impar
        do{
            printf("Introduce una cadena de 20 caracteres o menos: ");
            gets(cadena);
            if (strlen(cadena)>20 || strlen(cadena)==0) printf ("Error. ");
        }while(strlen(cadena)>20 || strlen(cadena)==0);
    }else{
        //pide una cadena par
        do{
            printf("Introduzca una cadena par de menos de 20 caracteres: ");
            gets(cadena);
            if (strlen(cadena)>20) printf("Error, la cadena no puede superar los 20 caracteres.\n\n");
            else if (strlen(cadena)==0) printf("Error, la cadena no puede estar vacia.\n\n");
            else if (strlen(cadena)%2!=0) printf("Error, la cadena no es par.\n\n");
        }while(strlen(cadena)>20 || strlen(cadena)==0 || strlen(cadena)%2!=0);
    }
    return;
}

void CENTRAR_CADENA(int longitud,char cadena[],int ciclo){
    system("cls");
    //centra la cadena
    printf("\n\n\n\n\n\n\n\n\n\n\n\n");
    for(int i=0; i<80/2 - longitud/2;i++) printf(" ");
    //imprime la cadena
    for(int posicion=0;posicion<strlen(cadena);posicion++){
        printf("%c",cadena[posicion]);
        for(int contador=0;contador<ciclo;contador++) printf(" ");
    }
    printf("\n\n\n\n\n\n\n\n");
    return;
}

void P1EJ2 (void){
    printf("\n\nPractica 1 de FP1. Ejercicio 2.\n---------------------------\n");

    char cadena[100];
    PEDIR_CADENA(cadena,1);
    CENTRAR_CADENA(strlen(cadena),cadena,0);
    _sleep(2500);
    system("cls");
    return;
}

void P1EJ3 (void){
    printf("\n\nPractica 1 de FP1. Ejercicio 3.\n--------------------------------\n");

    int sol=rand()%10+1, user, vidas=3;
    printf("Tienes 3 vidas para adivinar un numero.\n");
    do{
        printf("Introduce un numero del 1 al 10: ");
        user=FILTRAR_NUM(1,10);
        if(user==sol){
            printf("ENHORABUENA! Has acertado!\n\n");
            vidas=0;
        }else{
            vidas--;
            if(vidas>0){
                printf("Mal. El numero que estas buscando es ");
                if (user<sol) printf("mayor");
                else printf("menor");
                printf(" que %d.\nTe ",user);
                if(vidas==1) printf("queda 1 vida.");
                else printf("quedan %d vidas.",vidas);
                printf("\n\nPrueba de nuevo. ");
            }else printf("Has perdido. El numero que estabas buscando era %d.\n",sol); //cuando has perdido te dice cuál era la solución
        }
    }while(vidas!=0);

    return;
}

void INVERTIDO(int num, int *invertido){ //cálculo del invertido de un número
    while(num!=0){
        *invertido=*invertido*10+num%10;
        num=num/10;
    }
    return;
}

void P2EJ1 (void){
    printf("\n\nPractica 2 de FP1. Ejercicio 1\n\n-----------------------------------\n\n");

    printf("Introduce un numero mayor que 0: ");
    int veces=FILTRAR_NUM(0,-1);

    int capicua=0;
    while(veces>0){
        int invertido=0;
        INVERTIDO(capicua,&invertido); //invertido lo paso en puntero para modificarlo directamente, pero capicua no
        if(capicua==invertido){
            printf("%d ",invertido);
            veces--;
        }
        capicua++;
    }
    printf("\n");
    return;
}

void P2EJ2 (void){
    printf("\n\nPractica 2, ejercicio 2\n\n--------------------------------------\n\n");

    char cadena[100];
    PEDIR_CADENA(cadena,2);

    int ciclo=0,vueltas=0;
    while(vueltas<5){
        int longitud=strlen(cadena)+((strlen(cadena)-1)*ciclo);
        if(longitud<=80){
            CENTRAR_CADENA(longitud,cadena,ciclo);
            ciclo++;
            _sleep(250);
        }
        else{
            //ya ha llenado una pantalla y quitamos los espacios entre las letras
            ciclo=0;
            vueltas++;
        }
    }
    system("cls");
    return;
}

void CABALLO_ALEATORIO (char caballo1[],char caballo2[],char caballo3[],char caballo4[]){
    int avanza=rand()%4+1;
    //llenamos de espacios las cadenas de los caballos
    switch(avanza){
    case 1:
        strcat(caballo1, " ");
        break;
    case 2:
        strcat(caballo2, " ");
        break;
    case 3:
        strcat(caballo3, " ");
        break;
    case 4:
        strcat(caballo4, " ");
        break;
    }
    return;
}

void PRINT_CABALLOS (char caballo[]){
    printf("%s~__/'>\n",caballo);
    printf("%s// \\\\\n",caballo);
    printf("--------------------------------------------------------------------------------\n");
    return;
}

void P2EJ3 (void){
    printf("\n\nPractica 2 de FP1. Ejercicio 3.\n--------------------------------------\n");

    printf("Introduce el caballo por el que apuestas: ");
    int apuesta=FILTRAR_NUM(1,4);

    char cab1[80]="",cab2[80]="",cab3[80]="",cab4[80]="";
    int iteracion=0;
    while(strlen(cab1)<80-7 && strlen(cab2)<80-7 && strlen(cab3)<80-7 && strlen(cab4)<80-7){ //se ejecuta hasta que alguno llegue al final de la pantalla
        CABALLO_ALEATORIO(cab1,cab2,cab3,cab4);
        system("cls");
        printf("Carrera de caballos. Iteracion %d.\n\n",iteracion);
        iteracion++;
        PRINT_CABALLOS(cab1);
        PRINT_CABALLOS(cab2);
        PRINT_CABALLOS(cab3);
        PRINT_CABALLOS(cab4);
        _sleep(25);
    }

    int ganador;
    if (strlen(cab1)==80-7) ganador=1;
    else if (strlen(cab2)==80-7) ganador=2;
    else if (strlen(cab3)==80-7) ganador=3;
    else ganador=4;
    
    if(ganador==apuesta) printf("HAS GANADO!\n\n");
    else printf("Has perdido. Tu habias apostado por el #%d y ha ganado el #%d.\n\n",apuesta,ganador);
    
    return;
}

char OPCION (int a){
    char opc[10];
    if (a==1){ //en el caso de 4 opciones (menús de las prácticas)
        do{
            printf("Opcion: ");
            gets(opc);
            if(opc[0]!='a' && opc[0]!='b' && opc[0]!='c' && opc[0]!='d') printf("Error. Opcion introducida invalida.\n");
        }while(opc[0]!='a' && opc[0]!='b' && opc[0]!='c' && opc[0]!='d');
    }else{ //en el caso de 3 opciones (menú principal)
        do{
            printf("Opcion: ");
            gets(opc);
            if(opc[0]!='a' && opc[0]!='b' && opc[0]!='c') printf("Error. Opcion introducida invalida.\n");
        }while(opc[0]!='a' && opc[0]!='b' && opc[0]!='c');
    }
    return opc[0];
}

void PRACTICA1 (void){
    char opc;
    do{
        printf("\n\n---PRACTICA 1---\na. Ejercicio 1: Calculadora\nb. Ejercicio 2: Cadena centrada\nc. Ejercicio 3: Adivina el numero\nd. Salir\n");
        opc=OPCION(1);
        switch(opc){
        case 'a':
            P1EJ1();
            break;
        case 'b':
            P1EJ2();
            break;
        case 'c':
            P1EJ3();
            break;
        }
    }while(opc!='d');
    return;
}

void PRACTICA2 (void){
    char opc;
    do{
        printf("\n\n---PRACTICA 2---\na. Ejercicio 1: Numeros capicua\nb. Ejercicio 2: Animacion\nc. Ejercicio 3: Caballos\nd. Salir\n");
        opc=OPCION(1);
        switch(opc){
        case 'a':
            P2EJ1();
            break;
        case 'b':
            P2EJ2();
            break;
        case 'c':
            P2EJ3();
            break;
        }
    }while(opc!='d');
    return;
}

void PRINCIPAL (void){
    char opc;
    do{
        printf("--- MENU PRINCIPAL ---\na. Practica 1\nb. Practica 2\nc. Salir\n");
        opc=OPCION(0);
        if(opc=='a') PRACTICA1();
        else if(opc=='b') PRACTICA2();
        printf("\n\n");
    }while(opc!='c');
    return;
}

int main (void){
    srand(time(NULL)); //esto lo ponemos aquí para que no tener que repetirlo a lo largo del código
    PRINCIPAL();
    return 0;
}
