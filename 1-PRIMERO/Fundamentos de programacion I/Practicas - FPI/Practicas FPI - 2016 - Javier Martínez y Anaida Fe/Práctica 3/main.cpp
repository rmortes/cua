#include <stdio.h>
#include<stdlib.h>
#include<string.h>

//FUNCIONES EJERCICIO 1_3 y 2_3
//Mostrar palabra secreta
void Mostrar(char palabrasecreta[]){
    printf("La palabra secreta era: %s\n", palabrasecreta);
    return;
}
//Pedir palabra secreta
void Secreta(char palabrasecreta[]){
    //Pedimos al usuario introducir la palabra a adivinar, la convertimos a mayusculas y la copiamos a una nueva cadena

    printf("Introduzca la palabra secreta: ");
    scanf("%s", palabrasecreta);
    getchar();
    strupr(palabrasecreta);
    return;
}
//Comprobar si se ha acertado
int Comprobacion(int a, int b, int c, char palabrasecreta[]){

    //Creamos una anidacion de condicionales para comprobar si ha acertado y parar en ese caso o seguir segun las oportunidades
    int  acierto=0;
    if(a==0){
        printf("Enhorabuena, has acertado!\n\n");
        acierto=1;
    }else{
        if(b==c){
            printf("Lo siento, has perdido! :(\n");
            Mostrar(palabrasecreta);
        }else{
            printf("Lo siento, intentalo otra vez!\n");
        }
    }return(acierto);
}

//FUNCIONES EJERCICIO2_1
int FiltradoNumero(void){
    int N;
    do {
        printf("Introduzca un numero mayor que 0: ");
        scanf("%d",&N);
        getchar();
        if(N<=0){
            printf("Error, el numero introducido es menor que 0.\n");
        }
    }while(N<=0);
    return (N);
}
void BucleCreciente (int N){
    int numero=12;
    int contador=0;

    //Creamos el bucle que ira mostrando solo el numero de numeros pedido
    while( contador< N){
        //Pasamos el numero a cadena para poder comprobar sus cifras una por una
        char numerohechocadena[50];
        sprintf(numerohechocadena, "%d", numero);
        int longitud=strlen(numerohechocadena);
        int creciente=1;

        //creamos el bucle que nos dirá si el numero es creciente o no comparando sus cifras por separado
        for(int i=0;i<longitud-1 && creciente ==1; i++){
            if(numerohechocadena[i]>=numerohechocadena[i+1])
            {creciente=0;}
        }
        if (creciente==1){
            printf("%d ", numero);
            contador++;
        }
        numero++;
    }
    return;
}

//FUNCIONES EJERCICIO1_1
//Pedir nombres
void Nombres(char N1[],char PA1[],char SA1[],char N2[],char PA2[],char SA2[]){

    //Pedimos que introduzca los datos de la primera persona y los guardamos
    printf("Introduce el nombre completo de la primera persona: ");
    scanf("%s", N1);
    scanf("%s", PA1);
    scanf("%s", SA1);
    getchar();

    //Pedimos que introduzca los datos de la segunda persona y los guardamos
    printf("Introduce el nombre completo de la segunda persona: ");

    scanf("%s", N2);
    scanf("%s", PA2);
    scanf("%s", SA2);
    getchar();

    return;
}
int Comparaciones(char a[],char b[]){
    //Comenzamos el proceso de identificacion de relación entre personas mediante condicionales
    strupr(a);
    strupr(b);
    int compa=strcmp(a, b);

    return (compa);
}
void MostrarRelacion(int compnom,int compa1,int compa2,int compaprimos12,int compaprimos21){

    //Si son la misma persona
    if (compnom==0 && compa1==0 && compa2==0){
        printf("son la misma persona.\n");
    }else{
        //Son hermanos
        if(compa1==0 && compa2==0){
            printf("son hermanos/as.\n");
        }else{

            //Son primos
            if(compa1==0 || compa2==0 || compaprimos12==0 || compaprimos21==0){
                printf("son primos/as.\n");
            }else{
                //Son tocayos
                if(compnom==0){
                    printf("son tocayos/as.\n");
                }else{
                    //No tienen relacion
                    printf("no tienen relacion.\n");
                }
            }
        }
    }

    return;
}


//FUNCIONES EJERCICIO1_2
void PedirFecha(int *dia,int *mes,int *ano){

    //Pedimos al usuario la fecha en la que pidio el prestamo


    printf("Introduzca la fecha de concesion del prestamo(dd/mm/aaaa): ");
    scanf("%d/%d/%d",dia, mes, ano);
    getchar();




}
void PedirCuotas(int *cuotas){


    printf("Introduzca el numero de cuotas (meses)del prestamo: ");
    scanf("%d",cuotas);
    getchar();

}
void FechaFinal(int *dia, int*mesfuturo, int*anofuturo){

    //Mostramos el resultado: Fecha de finalizacion del prestamo
    //Con el Switch haremos que muestre el mes de forma alfabética
    printf("El prestamo finaliza el: %d de ",*dia);


    switch(*mesfuturo){

    case 0:  printf("enero");
        break;
    case 1:  printf("febrero");
        break;
    case 2:  printf("marzo");
        break;
    case 3:  printf("abril");
        break;
    case 4:  printf("mayo");
        break;
    case 5:  printf("junio");
        break;
    case 6:  printf("julio");
        break;
    case 7:  printf("agosto");
        break;
    case 8:  printf("septiembre");
        break;
    case 9:  printf("octubre");
        break;
    case 10:  printf("noviembre");
        break;
    case 11:  printf("diciembre");
        break;
    }

    //mostramos el año
    printf(" de %d\n\n", *anofuturo);




    return ;
}
void FiltradoFecha(int *dia, int *mes, int *ano){
    int di;
    do{
        PedirFecha(&*dia, &*mes, &*ano);

        //filtramos los datos introducidos
        if (*dia>30 || *dia<1){
            printf("Error, el dia introducido no es correcto.\n");
        }else{
            if(*mes<1 || *mes>12){
                printf("Error, el mes introducido no es correcto.\n");
            }else{
                if(*ano<1900 || *ano>2100){
                    printf("Error, el anio introducido no es correcto.\n");
                }
            }
        }
    }while(*dia>30 || *dia<1 || *mes<1 || *mes>12 || *ano<1900 || *ano>2100);
    di=*dia+1;
    printf("%d",di);
    return;
}

//Practica 2
void Ejercicio2_3(void){
    char palabrasecreta[50], aleatoria[50], intento[50];


    system("cls");
    //Empezamos mostrando un encabezado a modo decorativo
    printf("------------------------------------------------------- \n\n");
    printf("FP 1 - Practica 2/Ejercicio 3. \n");
    printf("------------------------------------------------------- \n\n");
    char si [4]="SI", res[4];
    int a;
    //Creamos un bucle para jugar todas las veces que queramos
    do{
        Secreta(palabrasecreta);
        strcpy(aleatoria, palabrasecreta);

        //Borramos la pantalla y declaramos las variables fuera de los bucles que seran necesarios para las siguientes operaciones
        system("cls");
        int oportunidades = 5, i,j;
        int longitud = strlen(aleatoria);
        int acierto=0;
        //Creamos el bucle que nos repetira las 5 oportunidades y parara en caso de acierto.
        for(i=1; i<=oportunidades && acierto!=1 ; i++){
            //Creamos el bucle que desordenara las pistas
            for(j=0; j<longitud*longitud ;j++){

                int num1 = rand()%longitud;
                int num2 = rand()%longitud;
                char aux=aleatoria[num1];
                aleatoria[num1]=aleatoria[num2];
                aleatoria[num2]=aux;
            }

            //Pedimos al usuario su que realice su intento y lo comparamos con la palabra secreta.
            printf("Intento %d de %d. ", i, oportunidades);
            printf("%s: ", aleatoria);
            scanf("%s", intento);
            getchar();
            strupr(intento);
            system("cls");
            int a = strcmp(intento, palabrasecreta);

            acierto=Comprobacion(a,i,oportunidades,palabrasecreta);

        }
        printf("Deseas volver a jugar? Si o No: ");
        scanf("%s", res);
        getchar();
        strupr(res);
        a=strcmp(res, si);
    }
    while(a==0);
    return;
}

void Ejercicio2_2(void){
    //Decalramos las variables con las que nuestro bucles irán contando.
    int ancho, alto, radio;

    for(int i=0;i<10;i++){
        system("cls");
        char c[1945]; //1920 + 24 + 1 (\n)
        //Primer bucle para no sobrepasar el radio, cuando este termine, empezaremos de 0, así que borraremos la pantalla
        for(radio=1; radio<12; radio++){
            system("cls");
            int cont=0;

            //Segundo bucle para no sobrepasar el alto del CMD
            for(alto=1; alto<24;alto++){

                //Tercer bucle para no pasar de los 80 de ancho del CMD
                for(ancho=1; ancho<80; ancho++){

                    //Ecuación de una circunferencia centrada en la mitad de la pantalla según los datos introducidos en el CMD
                    if(((ancho-40)*(ancho-40))+((alto-12)*(alto-12))>radio*radio){
                        c[cont]=' ';
                        cont++;;
                    }else{
                        c[cont]='*';
                        cont++;
                    }
                }
                c[cont]='\n';
                cont++;
            }c[cont]='\0';
            printf("%s\n",c);
            _sleep(150);
        }
    }
    return;
}

void Ejercicio2_1(void){

    system("cls");

    //Empezamos mostrando un encabezado a modo decorativo
    printf("------------------------------------------------------- \n\n");
    printf("FP 1 - Practica 2/Ejercicio 1. \n");
    printf("------------------------------------------------------- \n\n");

    //Pedimos al usuario el numero de numeros que quiere mostrar y comprobamos que este se pueda mostrar
    int N;
    N=FiltradoNumero();
    int numero=12;
    int contador=0;

    BucleCreciente(N);
    printf("\n\n");
    return;
}

//Practica 1
void Ejercicio1_3(void){

    system("cls");

    //Empezamos mostrando un encabezado a modo decorativo
    printf("------------------------------------------------------- \n\n");
    printf("FP 1 - Practica 1/Ejercicio 1. \n");
    printf("------------------------------------------------------- \n\n");

    char palabrasecreta[50];
    Secreta(palabrasecreta);

    system("cls");
    char intento[50];
    int j=0;
    for (int i=1; j==0 && i<4; i++){
        int intentos=3;
        printf("Jugador 2. Intento %d de %d. ",i, intentos);
        switch(i){
        case(1): printf("(Pista: Empieza por la letra: %c): ", palabrasecreta[0]);
            break;
        case(2): printf("(Pista: Acaba por la letra: %c): ", palabrasecreta[strlen(palabrasecreta)-1]);
            break;
        case(3): printf("(Pista: contiene la letra: %c): ", palabrasecreta[strlen(palabrasecreta)/2]);
            break;
        }
        scanf("%s", intento);
        getchar();
        strupr(intento);
        int comp=strcmp(palabrasecreta,intento);
        j=Comprobacion(comp,i,intentos,palabrasecreta);

    }


    return;
}

void Ejercicio1_2(void){

    system("cls");

    //Empezamos mostrando un encabezado a modo decorativo
    printf("------------------------------------------------------- \n\n");
    printf("FP 1 - Practica 1/Ejercicio 2. \n");
    printf("------------------------------------------------------- \n\n");


    //Pedimos al usuario la fecha en la que pidio el prestamo
    int dia, mes, ano, anomes, mesactual;

    FiltradoFecha(&dia, &mes, &ano);
    printf("%d",dia);


    //Convertimos los años a meses, y los sumamos al mes introducido
    anomes = ano*12;
    mesactual = mes-1+anomes;



    //Pedimos al usuario el numero de cuotas de su prestamo
    int cuotas, mesfinal, anofuturo, mesfuturo;
    PedirCuotas(&cuotas);


    //Filtramos los datos obtenidos
    if(cuotas<1 || cuotas>1200){
        printf("Error, el numero de cuotas introducido no es correcto\n");

    }else{


        //Calculamos segun las cuotas cual será el mes de finalizacion del prestamo
        mesfinal=mesactual+cuotas;

        //Pasamos de años a meses
        anofuturo=mesfinal/12;
        mesfuturo=mesfinal%12;

        FechaFinal(&dia, &mesfuturo, &anofuturo);


    }//Finalizamos el ejercicio
    return;
}

void Ejercicio1_1(void){

    system("cls");

    //Empezamos mostrando un encabezado a modo decorativo
    printf("------------------------------------------------------- \n\n");
    printf("FP 1 - Practica 1/Ejercicio 1. \n");
    printf("------------------------------------------------------- \n\n");

    //Declaramos las variables cadenas, para cada persona, y para cada parte de su nombre completo
    char N1 [10] , PA1 [20] , SA1 [20];
    char N2 [10] , PA2 [20] , SA2 [20];

    //Pedimos los nombres al usuario
    Nombres(N1,PA1,SA1,N2,PA2,SA2);


    //Comenzamos el proceso de identificacion de relación entre personas mediante condicionales
    int compnom = Comparaciones(N1,N2);
    int compa1 = Comparaciones(PA1, PA2);
    int compa2 = Comparaciones(SA1, SA2);
    int compaprimos12 = Comparaciones(PA1, SA2);
    int compaprimos21 = Comparaciones (PA2, SA1);

    //Mostramos el resultado
    printf("%s %s %s y %s %s %s ",N1,PA1,SA1,N2,PA2,SA2);
    MostrarRelacion(compnom, compa1, compa2, compaprimos12, compaprimos21);
    printf("\n");

    //Finalizamos el ejercicio
    return;
}


//Menus
void Practica2(void){
    char opc[50];
    system("cls");
    do{
        printf("=MENU PRACTICA 2=\na.- Ejercicio 1\nb.- Ejercicio 2\nc.- Ejercicio 3\nd.- Salir\nOpcion: \n");
        scanf("%s",opc);
        getchar();

        switch (opc[0]) {
        case 'a':
            Ejercicio2_1();
            break;
        case 'b':
            Ejercicio2_2();
            break;
        case 'c':
            Ejercicio2_3();
            break;
        }
    }while(opc[0]!='d');
    return;
}

void Practica1(void){
    char opc[50];
    system("cls");
    do{
        printf("=MENU PRACTICA 1=\na.- Ejercicio 1\nb.- Ejercicio 2\nc.- Ejercicio 3\nd.- Salir\nOpcion: ");
        scanf("%s",opc);
        getchar();

        switch (opc[0]) {
        case 'a':
            Ejercicio1_1();
            break;
        case 'b':
            Ejercicio1_2();
            break;
        case 'c':
            Ejercicio1_3();
            break;
        }
    }while(opc[0]!='d');
    return;
}

void Menu(void){
    char opc[50];

    do{

        printf("=MENU PRINCIPAL=\na.- Practica 1\nb.- Practica 2\nc.- Salir\nOpcion: ");
        scanf("%s",opc);
        getchar();

        switch (opc[0]) {
        case 'a':
            Practica1();
            break;
        case 'b':
            Practica2();
            break;
        }
    }while(opc[0]!='c');
    return;
}

int main (void){
    Menu();

    return(0);
}
