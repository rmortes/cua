//Librerias necesarias //
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

//Funcion del ejercicio 3 de la paractica 2
int sololetras(char * cadena){
    int i;
    for (i=0 ; i < strlen(cadena); i++ )
        if (cadena[i] < 'a' || cadena[i] > 'z' ) return 0;
    return 1;
}
void E3P2(void) {

    //Definimos las variables
    int juego, puntos1 = 0, puntos2 = 0, turno = 1, intentos, longitud, cent;
    char palabra[50], guiones[51], repeat, letra;

    do {
        //Damos valores a variables que deben ser reiniciados en cada turno
        intentos=5;
        juego=0;

        //Para que el programa ejecute un turno u otro hacemos uso de un if-else
        if (turno%2!=0) {

            //Con este do, le pedimos al usuario que introduzca la palabra, al llegar al while, si es mayor de 50, vuelve a pedirla
            do {
                printf("Introduce la palabra a adivinar Jugador 1: ");
                scanf("%s", palabra);
                fflush(stdin);
                system("cls");
            }

            while (strlen(palabra) > 50 || 0==sololetras(palabra) );


            //Con esto imprimimos tantos guiones como caracteres tenga la palabra
            longitud = strlen(palabra);
            strcpy(guiones, "-------------------------------------------------");
            guiones[longitud] = '\0';

            do {
                //Limpiamos la pantalla de lo que se va generando en cada intento o acierto
                system("cls");

                //Esta es la variable centinela que es usada para comprobar si se ha fallado con la letra
                cent = 0;
                printf("\n\n%29c Palabra: %s\n", ' ', guiones);
                printf("\nIntentos restantes: %d\n\n", intentos);

                //Aqui le pedimos al usuario que introduzca una letra para adivinar la palabra
                do {
                    printf("Introduce una letra minuscula [Jug.2]: ");
                    scanf("%c", &letra);
                    fflush(stdin);
                }

                //Si el caracter introducido no es una letra, lo pide de nuevo
                while (letra < 'a' || letra > 'z');

                //Este for comprueba posicion por posicion, de la cadena, si la letra introducida se encuentra en la cadena
                for(juego=0;juego<strlen(palabra);juego++){

                    if (palabra[juego] == letra)
                    {
                        guiones[juego] = letra;
                        cent = 1;
                    }
                }

                if (cent != 1)intentos--;
            }

            //Si no se han terminado los intentos ni se ha acertado, repite el do
            while(intentos!=0 && strcmp(guiones,palabra)!= 0);

            /*Para llegar a este if-else, debe de haberse gastado los intentos o haber adivinado la letra,
                  entonces, si la palabra introducida letra a letra, es igual a la introducida en primera instancia
                  imprime que se ha ganado y aumenta un punto al jugador que ha acertado*/
            if (strcmp(guiones,palabra)== 0) {
                system("cls");
                printf ("\n\n\n%30cSolucion: %s", ' ', palabra);
                printf("\n\n\n%26c HAS ACERTADO LA PALABRA!\n\n",' ');
                puntos2++;
            }
            /*En esta parte, si el jugador ha perdido, se le informa de ello, y aumenta un punto en el marcador del
                jugador que puso la palabra*/
            else {
                system("cls");
                printf("\n\n\n%27c JUGADOR 2 HAS PERDIDO",' ');
                printf("\n\n\n%29cLa palabra era: %s\n\n\n\n\n", ' ', palabra);
                puntos1++;
            }
        }

        //Aqui comienza el siguiente turno
        else{

            //Con este do, le pedimos al usuario que introduzca la palabra, al llegar al while, si es mayor de 50, vuelve a pedirla
            do {
                printf("Introduce la palabra a adivinar Jugador 2: ");
                scanf("%s", palabra);
                fflush(stdin);
                system("cls");
            }

            while (strlen(palabra) > 50 || 0==sololetras(palabra) );


            //Con esto imprimimos tantos guiones como caracteres tenga la palabra
            longitud=strlen(palabra);
            strcpy(guiones, "--------------------------------------------------");
            guiones[longitud]='\0';

            do{
                //Limpiamos la pantalla de lo que se va generando en cada intento o acierto
                system("cls");

                //Esta es la variable centinela que es usada para comprobar si se ha fallado con la letra
                cent = 0;
                printf("\n\n%29c Palabra: %s\n", ' ', guiones);
                printf("\nIntentos restantes: %d\n\n", intentos);

                //Aqui le pedimos al usuario que introduzca una letra para adivinar la palabra
                do{
                    printf("Introduce una letra minuscula [Jug.1]: ");
                    scanf("%c", &letra);
                    fflush(stdin);
                }

                //Si el caracter introducido no es una letra, lo pide de nuevo
                while (letra < 'a' || letra > 'z');

                //Este for comprueba posicion por posicion, de la cadena, si la letra introducida se encuentra en la cadena
                for(juego=0;juego<strlen(palabra);juego++){

                    if (palabra[juego]==letra) {
                        guiones[juego]=letra;
                        cent=1;
                    }
                }

                if (cent != 1)intentos--;

            }

            //Si no se han terminado los intentos ni se ha acertado, repite el do
            while(intentos!=0 && strcmp(guiones,palabra)!= 0);

            /*Para llegar a este if-else, debe de haberse gastado los intentos o haber adivinado la letra,
                  entonces, si la palabra introducida letra a letra, es igual a la introducida en primera instancia
                  imprime que se ha ganado y aumenta un punto al jugador que ha acertado*/
            if (strcmp(guiones,palabra)== 0){
                system("cls");
                printf ("\n\n\n%30cSolucion: %s", ' ', palabra);
                printf("\n\n\n%26c HAS ACERTADO LA PALABRA!\n\n",' ');
                puntos1++;
            }

            /*En esta parte, si el jugador ha perdido, se le informa de ello, y aumenta un punto en el marcador del
                jugador que puso la palabra*/
            else {
                system("cls");
                printf("\n\n\n%27c JUGADOR 1 HAS PERDIDO",' ');
                printf("\n\n\n%29cLa palabra era: %s\n\n\n\n\n", ' ', palabra);
                puntos2++;
            }
        }

        //Aqui pregunta si se sigue jugando o no, con las teclas "s" o "n", mayusculas o minusculas
        do{
            printf("\n%26c Seguir jugando? <S o N>: ", ' ');
            scanf("%c", &repeat);
            fflush(stdin);
        }

        while (repeat != 'S' && repeat != 's' && repeat != 'N' && repeat != 'n');

        //Sumamos uno a la variable turno, y asi ejecutar el codigo del siguiente jugador
        turno++;
        system("cls");
    }

    //Si el usuario a tecleado "s", se volvera a ejecutar el do inicial, y sera el turno siguiente
    while (repeat == 'S' || repeat == 's');

    //Si no se juega mas, se imprime en pantalla la puntuacion de los 2 jugadores.
    printf("\n\n\n\n\n\n%27cPuntuacion final: ",' ');
    printf("\n\n%25c(Jug.1) %d - %d (Jug.2)\n\n\n\n\n",' ', puntos1, puntos2);

    //A la espera de que el usuario pulse una tecla para salir del programa
    system ("pause");
    return;
}

//Funcion del ejercicio 2 de la paractica 2
void E2P2(void){
    //Definimos las variables que vamos a utilizar
    int dia=0, i, dianum, numes;
    char diainicial, reload;
    bool prt;

    //Con esta instruccion, ejecutamos una primera vez, y al final, si se cumple la condicion se repite de nuevo
    do{

        /*Le damos valor falso al booleano por si se ejecuta 2 o mas veces el codigo, asi los if de abajo
        funcionaran de nuevo desde el principio*/
        prt=false;

        //Le pedimos al usuario que introduzca el numero de mes
        printf("Introduce un mes <1-12>: ");
        scanf("%d", &numes);
        fflush(stdin);

        //Si el numero de mes introducido excede del rango establecido, se vuelve a solicitar hasta que sea valido
        while(numes<1 || numes>12){
            printf("El mes no es valido, escriba otro <1-12>: ");
            scanf("%d", &numes);
            fflush(stdin);
        }
        //Se solicita al usuario que introduzca un dia, usando la inicial
        printf("Introduce dia (minusculas tambien son aceptadas) <L-M-X-J-V-S-D>: ");
        scanf("%c", &diainicial);
        fflush(stdin);


        /*Si la inicial introducida no coincide con los valores establecidos, se solicita de nuevo,
        el codigo debajo de estas lineas, ha sido dividido en lineas para facilitar la lectura*/
        while(diainicial!='L' && diainicial!='M' && diainicial!='X' && diainicial!='J'
              && diainicial!='V' && diainicial!='S' && diainicial!='D' && diainicial!='l'
              && diainicial!='m' && diainicial!='x' && diainicial!='j' && diainicial!='v'
              && diainicial!='s' && diainicial!='d'){
            printf("Dia incorrecto, recuerde <L-M-X-J-V-S-D> Tambien minusculas: ");
            scanf("%c", &diainicial);
            fflush(stdin);
        }
        //Aqui damos valor numerico a la letra introducida y lo asignamos a una variable
        if(diainicial=='L' || diainicial=='l')dianum=1;
        else if(diainicial=='M' || diainicial=='m')dianum=2;
        else if(diainicial=='X' || diainicial=='x')dianum=3;
        else if(diainicial=='J' || diainicial=='j')dianum=4;
        else if(diainicial=='V' || diainicial=='v')dianum=5;
        else if(diainicial=='S' || diainicial=='s')dianum=6;
        else if(diainicial=='D' || diainicial=='d')dianum=7;

        //Aqui, segun el dato que tiene la variable numes, se imprimira un nombre de mes concreto
        switch (numes) {

        case 1:
            printf("\n\nEnero\n");
            break;

        case 2:
            printf("\n\nFebrero\n");
            break;

        case 3:
            printf("\n\nMarzo\n");
            break;

        case 4:
            printf("\n\nAbril\n");
            break;

        case 5:
            printf("\nMayo\n");
            break;

        case 6:
            printf("\n\nJunio\n");
            break;

        case 7:
            printf("\n\nJulio\n");
            break;

        case 8:
            printf("\n\nAgosto\n");
            break;

        case 9:
            printf("\n\nSeptiembre\n");
            break;

        case 10:
            printf("\n\nOctubre\n");
            break;

        case 11:
            printf("\n\nNoviembre\n");
            break;

        case 12:
            printf("\n\nDiciembre\n");
            break;
        }

        //Despues del nombre de mes, se imprime las iniciales de los dias
        printf("  L  M  X  J  V  S  D\n");

        //Usamos esta intruccion de incremento para imprimir los numeros del calendario, cuando i sea mayor de 31, ya no se ejecuta.
        for(i=1; i<=31; i++){
            dia++;

            /*imprimimos tantos espacios como sean necesario para comenzar a imprimir numeros en el dia de la semana elegido
            si la variable dia es distinta de la variable dianum y el dato booleano es falso*/
            if(dia!=dianum && prt==false){
                printf("   ");
                i--;
            }
            //Imprime el dia numero 1 debajo del dia de la semana elegido por el usuario despues de 3 huecos y asi sucesivamente
            else if (dia==dianum && prt==false){
                printf("%3d", i);
                prt=true;
            }
            /*El dato booleano ha sido cambiado a verdadero, por lo que las dos intrucciones anteriores
            ya no se ejecutan, y se imprime el siguiente numero tres huecos despues de donde se quedo la impresion*/
            else {
                printf("%3d", i);
            }
            //Con esta parte, realizamos un salto de linea al llegar al domingo, para seguir debajo con los numeros
            if(dia==7 || i==31){
                printf("\n");
                dia=0;
            }

        }
        //Le preguntamos al usuario si quiere reanudar el programa
        printf("\n\nOtra vez? <s-n>: ");
        scanf("%c", &reload);
        fflush(stdin);
        system("cls");

    }
    //Si la variable reload contiene 's' se repite la instruccion do
    while(reload=='s');

    return;
}

//Funcion del ejercicio 1 de la paractica 2
void E1P2(void){
    //Definimos las variables que vamos a necesitar
    int i, i2, num;

    //Pedimos al usuario que introduzca un numero
    printf("Introduce numero de filas <5-10>:");
    scanf("%d", &num);

    //Si el numero introducido no esta en el rango de valores definidos, se solicita de nuevo un numero
    while(num<5 || num>10){
        printf("Numero no valido, vuelva a escribir: \n");
        scanf("%d", &num);
    }

    /*Usando esta instruccion, repetimos el codigo tantas veces como el numero elegido,
      haciendo que salte al siguiente bloque al incrementar en cada repeticion otra variable,
      que al comparar con el numero introducido, si esta variable en menor o igual, se sigue ejecutando.*/
    for(i=1;i<=num;i++){
        //Este apartado en concreto, imprime asteriscos incrementando en 1 en cada repeticion.
        for(i2=1;i2<=i;i2++){
            printf("*");
        }
        //Con esta linea, hacemos el salto de linea, para seguir imprimiendo en una nueva fila
        printf("\n");
    }
    //Aqui hacemos la inversa de la anterior instruccion for
    for(i=num;i>=0;i--){
        for(i2=0;i2<i;i2++){
            printf("*");
        }
        //Y de nuevo saltos de linea
        printf("\n");
    }

    //El programa espera a que el usuario pulse una tecla para cerrar
    system ("pause");
    return;
}

//Funcion del ejercicio 3 de la paractica 1
void E3P1(void){
    //Definimos las variables
    int a;

    //Pedimos al usuario que introduzca un valor y este sera asignado a la variable definida
    printf ("Introduce nota: ");
    scanf ("%d", &a);

    //Con esta instruccion conseguimos distintas respuestas definidas a valores concretos
    switch (a){
        //Definimos que debe ejecutar segun el valor de la variable
    case 0:
        printf ("Tu nota es: SUSPENSO \n\n");
        break;
    case 1:
        printf ("Tu nota es: SUSPENSO \n\n");
        break;
    case 2:
        printf ("Tu nota es: SUSPENSO \n\n");
        break;
    case 3:
        printf ("Tu nota es: SUSPENSO \n\n");
        break;
    case 4:
        printf ("Tu nota es: SUSPENSO \n\n");
        break;
    case 5:
        printf ("Tu nota es: APROBADO \n\n");
        break;
    case 6:
        printf ("Tu nota es: APROBADO \n\n");
        break;
    case 7:
        printf ("Tu nota es: NOTABLE \n\n");
        break;
    case 8:
        printf ("Tu nota es: NOTABLE \n\n");
        break;
    case 9:
        printf ("Tu nota es: SOBRESALIENTE \n\n");
        break;
    case 10:
        printf ("Tu nota es: MATRICULA DE HONOR \n\n");
        break;
    }
    //El programa se pausa y espera a que el usuario presione una tecla para finalizar
    system ("pause");

    return;
}

//Funcion del ejercicio 2 de la paractica 1
void E2P1(void){
    //Definimos las variables
    int valor, a, b, c, d, e, f, p ;

    //Esperamos a que el usuario introduzca un numero para ser descompuesto
    printf ("Introduce numero (Maximo 6 cifras): \n");
    scanf ("%d", &valor);

    //Si el valor del numero introducido es mayor o igual a 1.000.000, el programa solicita de nuevo un numero
    while (valor > 999999){
        printf ("Numero no valido, vuelva a escribir (Recuerde: Maximo 6 cifras): \n");
        scanf ("%d", &valor);
    }
    //Cuando el valor del numero es menor de 1.000.000, se procede a su descomposicion, jugando con operaciones matematicas de numeros enteros, omitiendo decimales.
    if(valor>=1){

        f= valor/100000;
        if(f>=1) printf ("Centenas de millar: %d\n", f);
        p= valor - (valor /100000 * 100000);
        if(f>=1) printf ("Quedan por procesar: %d\n", p);


        e= p/10000;
        if(e>=1) printf ("Decenas de millar: %d\n", e);
        p= valor - (valor /10000 * 10000);
        if(e>=1) printf ("Quedan por procesar: %d\n", p);

        d= p/1000;
        if(d>=1) printf ("Unidades de millar: %d\n", d);
        p= valor - (valor /1000 * 1000);
        if(d>=1) printf ("Quedan por procesar: %d\n", p);

        c= p/100;
        if(c>=1) printf ("Centenas: %d\n", c);
        p= valor - (valor /100 * 100);
        if(c>=100) printf ("Quedan por procesar: %d\n", p);


        b= p/10;
        if(b>=1) printf ("Decenas: %d\n", b);
        p= valor - (valor /10 * 10);
        if(b>=1) printf ("Quedan por procesar: %d\n", p);

        a= valor;
        a= a - (valor /10 * 10);
        if(a>=1)
            printf ("Unidades: %d\n", a);
    }else{
        printf ("\nNingun valor\n\n\n");
    }


    //Espera a que el usuario pulse una tecla
    system ("pause");

    return;

}

//Funcion del ejercicio 1 de la paractica 1
void E1P1(void){
    /* 1. Aqui definimos los datos y que tipo de
        valores van a manejar. En este caso tenemos 3
        datos, que pueden contener numeros enteros*/

    int NUMERO1, NUMERO2, NUMERO3;

    system("cls");

    /* 2. En este segundo punto, imprimimos dos preguntas,
        sobre los valores de dos numeros enteros, y estos
        se guardan en 2 de los datos definidos, y la suma
        de estos se guarda en el tercer dato*/

    printf("Primer numero: ");
    scanf("%d", &NUMERO1);
    printf("Segundo numero: ");
    scanf("%d", &NUMERO2);
    NUMERO3=NUMERO1+NUMERO2;

    system("cls");

    /* 3. Ahora valoramos el resultado, manejando
        el valor del dato para saber si es par o no.
        Bajo estas condiciones, el siguiente bloque if
        hara una funcion u otra segun sea par o no el
        resultado de la suma. */

    if((NUMERO3/2)*2==NUMERO3){
        printf("\n\n\n\n%18c***********************************************\n", ' ');
        printf("%18c*  Bienvenido a Fundamentos de programacion 1 *\n", ' ');
        printf("%18c*\t\tCurso 2011-2012        \t\t*\n", ' ');
        printf("%18c***********************************************\n", ' ');
        printf("%38c%d + %d = %d", ' ',NUMERO1,NUMERO2,NUMERO3);

    }else{
        printf("***********************************************\n");
        printf("*  Bienvenido a Fundamentos de programacion 1 *\n");
        printf("*");
        printf("%14cCurso 2011-2012", ' ');
        printf("%16c*\n", ' ');
        printf("***********************************************\n");
        printf("%20c%d + %d = %d", ' ',NUMERO1,NUMERO2,NUMERO3);

    }

    /* 4. Finaliza el programa, se debe hacer
        pulsar en alguna tecla para cerrar. */

    getche();
    return;

}

//Menu de la practica 2
void P2(void){
    char a;

    do{
        system("cls");
        printf("<--MENU EJERCICIOS-->\n");
        printf("\na) Ejercicio 1\n");
        printf("b) Ejercicio 2\n");
        printf("c) Ejercicio 3\n");
        printf("d) Volver al menu anterior\n");
        printf("\n[Elige una opcion]");
        a=getche();
        printf("\n");
        system("cls");
        if(a=='a')E1P2();
        if(a=='b')E2P2();
        if(a=='c')E3P2();

        //Si se pulsa una tecla distinta de d, sigue pidiendo una letra
    }while(a!='d');
    return;
}

//Menu de la practica 1
void P1(void){
    char a;


    do{
        system("cls");
        printf("<--MENU EJERCICIOS-->\n");
        printf("\na) Ejercicio 1\n");
        printf("b) Ejercicio 2\n");
        printf("c) Ejercicio 3\n");
        printf("d) Volver al menu anterior\n");
        printf("\n[Elige una opcion]");
        a=getche();
        printf("\n");
        system("cls");
        if(a=='a')E1P1();
        if(a=='b')E2P1();
        if(a=='c')E3P1();

        //Si se pulsa una tecla distinta de d, sigue pidiendo una letra
    }while(a!='d');
    return;
}

//Menu principal
void Menu(void){
    char a;
    /* Bucle para que solo se salga del menu cuando nosotros queramos*/
    do{
        system ("cls");
        printf("<--MENU PRINCIPAL-->\n");
        printf("\na) Practica 1\n");
        printf("b) Practica 2\n");
        printf("c) Salir\n");
        printf("\n[Elige una opcion]");
        a=getche();
        printf("\n");
        if(a=='a')P1();
        if(a=='b')P2();

        //Si se pulsa una tecla distinta de c, sigue pidiendo una letra
    }while(a!='c');
    return;
}

//Inicio programa
int main(void){
    Menu();
    return(0);
}
