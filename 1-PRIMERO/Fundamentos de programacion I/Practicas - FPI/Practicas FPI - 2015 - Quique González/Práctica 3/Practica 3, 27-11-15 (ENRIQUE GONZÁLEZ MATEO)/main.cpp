#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

void Datos11(int *a, int *b,char *c){

    printf("\n\n  Practica 1, ejercicio 1\n  ---------------------------------------\n");

    printf("  Introduzca numero a:"); scanf("%d",a);getchar();
    printf("  Introduzca operacion a realizar (+,-,*,/ o %%):"); scanf("%c",c);getchar();
    printf("  Introduzca numero b:"); scanf("%d",b);getchar();

    return;
}
void Calculadora11(int a, int b,char c){
    int r;
    switch (c){

    case '+':
        r=a+b;
        printf("  El resultado es: %d\n",r);
        break;
    case '-':
        r=a-b;
        printf("  El resultado es: %d\n",r);
        break;
    case '*':
        r=a*b;
        printf("  El resultado es: %d\n",r);
        break;
    case '/':
        if (b==0){
        printf("  Error: no se puede dividir un numero entre 0\n");
        break;
        }else{
        r=a/b;
        printf("  El resultado es: %d\n",r);
        break;
        }
    case '%':
        if (b==0){
        printf("  Error: no se puede puede calcular el resto de un numero divido entre 0\n");
        break;
        }else{
        r=a%b;
        printf("  El resultado es: %d\n",r);
        break;
        }default:
        printf("  Error: eso no es ningun operando");scanf("%c",&c);getchar();
        break;
    }
    return;
}

void Datos12(char c[]){

    do{
        printf("  Introduzca cadena par de menos de 20 caracteres:"); gets(c);
        if (strlen(c)>20){
            printf("  Error, la cadena es de mayor de 20 caracteres\n");
        }else{
            if(strlen(c)%2!=0){
                printf("  Error, la cadena no es par\n");
            }
        }
    }while (strlen(c)>20 || strlen(c)%2!=0);
    return;
}
void Cadena12(char c[]){
    printf("\n\n\n\n\n\n\n\n\n\n\n\n                              ");
    switch(strlen(c)){

    case 20: break;
    case 18: printf(" "); break;
    case 16: printf("  "); break;
    case 14: printf("   "); break;
    case 12: printf("    "); break;
    case 10: printf("     "); break;
    case 8: printf("      "); break;
    case 6: printf("       "); break;
    case 4: printf("        "); break;
    case 2: printf("         "); break;
    case 0: printf("          "); break;
    }
    puts(c);
    printf("\n\n\n\n\n\n\n\n\n\n\n\n");
    _sleep(2000);
    return;
}

void Datos13(int *n){
    do{
        printf("  Introduzca numero entre 0 y 10:"); scanf("%d",n); getchar();
        if (*n>10||*n<0){
            printf("  Error: ese numero no esta entre 0 y 10\n");
        }
    }while (*n>10||*n<0);
    return;
}
void Juego13(int aleatorio){
    int n;
    for (int a=0;a<3;a++){
        Datos13(&n);
        if (n==aleatorio){
            printf("   FELICIDADES, ACERTASTE\n");
            return;
        }else{
            if(n>aleatorio){
                printf("   El numero introducido es mayor que el que buscas.\n ");
            }else{
                printf("   El numero introducido es menor que el que buscas.\n ");
            }
        }
    }
    printf("   GAME OVER: El numero es %d\n", aleatorio);
    return;
}


void Ejercicio11(){
    int a,b;
    char c;
    Datos11(&a,&b,&c);
    Calculadora11(a,b,c);
    return;
}
void Ejercicio12(){

    printf("\n  Practica 1, ejercicio 2\n  ---------------------------------------\n");
    char cadena [100];
    Datos12(cadena);
    Cadena12(cadena);
    return ;
}
void Ejercicio13(){
    printf("\n  Practica 1, ejercicio 3\n  ---------------------------------------\n");

    srand(time(NULL));
    int aleatorio=rand()%10+1;
    Juego13(aleatorio);
    return;
}



void Datos21(int *x){
    do{
        printf("Introduzca numero entero mayor que cero:"); scanf("%d",x);getchar();
        if(*x<=0){
            printf("Error: el numero no es mayor que cero.\n");
        }
    }while (*x<=0);
    return;
}
void Capicua21(int x){
    int a,i=1,b=0;
    while (x>0){
        b++;
        i=b;
        a=0;

        while (i>0){
            a= a*10 + i%10;
            i= i/10;
        }
        if(a==b){
            printf(" %d ",a);
            x--;
        }
    }
    return;
}

void Datos22(char c[]){
    printf("Introduzca cadena de menos de 20 caracteres:");gets(c);

    while (strlen(c)>20){
       printf("Error: la cadena es mayor de 20 caracteres\nIntroduzca otra cadena: ");gets(c);
    }
    while (strlen(c)==0){
       printf("Error: la cadena no puede ser de cero caracteres\nIntroduzca otra cadena: ");gets(c);
    }
    return;
}
void Extension22(char c[]){
    int extension, contador=0, centro, i, a=0;
    while (a<30){

        system("cls");

        printf("\n\n\n\n\n\n\n\n\n\n\n");

        extension=strlen(c)+((strlen(c)-1)*contador);

        if(extension<=80){
            for (centro=40-extension/2;centro>0;centro--){
                printf(" ");
            }
            for (int posicion=0;posicion<strlen(c);posicion++){
                printf("%c",c[posicion]);
                for (i=0;i<contador;i++){
                    printf(" ");
                }
            }
            contador++;
            _sleep(250);
        }else contador=0;
        a++;
    }
}

void Datos23(int *a){
    do{
        printf("  Realize su apuesta, escoja un caballo (1,2,3 o 4):"); scanf("%d", a);getchar();
        if(*a<1 || *a>4){
            printf("  Error: esa apuesta no se corresponde a ningun caballo\n");
        }
    }while(*a<1 || *a>4);
    return;
}
void Carrera23(int a){
    char caballo1[100]="", caballo2[100]="", caballo3[100]="", caballo4[100]="";
    for(int i=0;strlen(caballo1)<72 && strlen(caballo2)<72 && strlen(caballo3)<72 && strlen(caballo4)<72;i++){

        switch (rand()%4+1) {
        case 1:
            strcat(caballo1, " "); break;
        case 2:
            strcat(caballo2, " "); break;
        case 3:
            strcat(caballo3, " "); break;
        case 4:
            strcat(caballo4, " "); break;
        }

        system("cls");
        printf("  Carrera de caballos. ");
        printf("Iteracion %d\n", i);

        printf("  -----------------------------------------------------------------------------\n");
        printf("  %s~__/>\n", caballo1);
        printf("  %s// \\\\\n",caballo1);

        printf("  -----------------------------------------------------------------------------\n");
        printf("  %s~__/>\n", caballo2);
        printf("  %s// \\\\\n",caballo2);

        printf("  -----------------------------------------------------------------------------\n");
        printf("  %s~__/>\n", caballo3);
        printf("  %s// \\\\\n",caballo3);

        printf("  -----------------------------------------------------------------------------\n");
        printf("  %s~__/>\n", caballo4);
        printf("  %s// \\\\\n",caballo4);

        printf("  -----------------------------------------------------------------------------\n");
        _sleep(10); 
    }
    int vencedor;
    if (strlen(caballo1)==72) vencedor=1;
    if (strlen(caballo2)==72) vencedor=2;
    if (strlen(caballo3)==72) vencedor=3;
    if (strlen(caballo4)==72) vencedor=4;

    if (vencedor==a){
        printf("  ENHORABUENA, HAS GANADO LA APUESTA\n");
    }else printf("  Lo siento, has perdido la apuesta. Ha ganado el caballo %d \n", vencedor);
    return;
}


void Ejercicio21(){
    int veces;
    Datos21(&veces);
    Capicua21(veces);
    printf("\n");
    return;
}
void Ejercicio22(){
    char cadena[100];
    Datos22(cadena);
    Extension22(cadena);
    return;
}
void Ejercicio23(){

    srand(time(NULL));
    int apuesta;
    Datos23(&apuesta);
    Carrera23(apuesta);
    return;
}



void Practica1(){
    int a;
    do{
        printf("\n\nPRACTICA 1\n\n1:Calculadora\n2:Centrar una cadena\n3:Adivina el numero\n4:Volver al menu anterior\n\nEjercicio que desea ejecutar: ");
        scanf("%d",&a);
        getchar();

        switch (a) {
        case 1: Ejercicio11(); break;
        case 2: Ejercicio12(); break;
        case 3: Ejercicio13(); break;
        }
    }while(a!=4);
    return;
}
void Practica2(){
    int a;
    do{
        printf("\n\nPRACTICA 2\n\n1:Numeros capicuas\n2:Expande una cadena\n3:Carrera de caballos\n4:Volver al menu anterior\n\nEjercicio que desea ejecutar: ");
        scanf("%d",&a);
        getchar();

        switch (a) {
        case 1: Ejercicio21(); break;
        case 2: Ejercicio22(); break;
        case 3: Ejercicio23(); break;
        }
    }while(a!=4);
    return;
}
void MenuPrincipal(){
    int a;
    do{
        printf("\nMENU PRINCIPAL\n\n1:Practica 1\n2:Practica 2\n3:Cerrar programa\n\nEscoja la practica: ");
        scanf("%d",&a);
        getchar();

        switch (a) {
        case 1: Practica1(); break;
        case 2: Practica2(); break;

        }
    }while(a!=3);
    return;
}

int main(void){
    MenuPrincipal();
    return 0;
}
