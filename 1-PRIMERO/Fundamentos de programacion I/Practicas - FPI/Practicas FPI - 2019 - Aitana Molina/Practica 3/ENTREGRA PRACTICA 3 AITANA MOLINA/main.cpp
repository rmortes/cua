#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
void ejercicio1_1(){
    system("cls");
    int dias,semanas,meses,anyos;
    /*Coger datos Inicio*/
    printf("EJERCICIO 1 PRACTICA 1\n");
    printf("=======================\n");
    printf("Introduzca la edad del bebe en semanas:\n");
    scanf("%d",&semanas);
    getchar();

    /*Coger datos Fin*/
    if(semanas==0){
        printf("El bebe acaba de nacer.\n");
    }
    if(semanas<-40){
        printf("ERROR, las semanas no pueden ser menores a -40.\n");
    }else{
        if(semanas>=-40 && semanas<0){
            dias=(-1)*semanas*7;
            anyos=dias/360;
            meses = (dias - anyos*360)/30;
            dias = dias - anyos*360 - meses*30;
            printf("Al bebe le faltan:\n");
        }/*calcular Datos Inicio*/
        if(semanas>0){
            dias=semanas*7;
            anyos=dias/360;
            meses = (dias - anyos*360)/30;
            dias = dias - anyos*360 - meses*30;
            printf("El bebe tiene:\n");
        }
        if(anyos>1){
            printf("%d anyos\n",anyos);
        }else{
            if (anyos==1){
                printf("%d anyo\n",anyos);
            }
        }
        if(meses>1){
            printf("%d meses\n",meses);
        }else{
            if (meses==1){
                printf("%d mes\n",meses);
            }
        }
        if(dias>0){
            printf("%d dias\n",dias);
        }else{
            if (dias==1){
                printf("%d dia\n",dias);
            }
        }
    }
    system("pause");
    return;
}
void personas(char nom[],char ap1[], char ap2[],char nom_[],char ap1_[],char ap2_[]){
    printf("%s %s %s y %s %s %s ",nom,ap1,ap2,nom_,ap1_,ap2_);
    return;
}
void pedirdatos(char n[],char a1[],char a2[]){
    printf("Introduzca el nombre completo. Si su nombre es compuesto, separelo con un guion bajo.\n\n");
    scanf("%s",n);
    scanf("%s",a1);
    scanf("%s",a2);
    getchar();
    return;
}
void pedirdatos2(char n_[],char a1_[],char a2_[]){
    printf("Introduzca el segundo nombre completo. Si su nombre es compuesto, separelo con un guion bajo.\n\n");
    scanf("%s",n_);
    scanf("%s",a1_);
    scanf("%s",a2_);
    getchar();
    return;
}
void ejercicio2_1(){
    system("cls");
    char nombre[40],apellido1[40],apellido2[40];
    char nombre_[40],apellido1_[40],apellido2_[40];
    //persona 1
    printf("EJERCICIO 2 PRACTICA 1\n");
    printf("=======================\n");
    pedirdatos(nombre,apellido1,apellido2);
    printf("\n");
    //persona 2
    pedirdatos2(nombre_,apellido1_,apellido2_);
    printf("\n");

    //Recoger datos Fin
    //Calcular y presentar datos Inicio
    if(strcmp(nombre,nombre_)==0&&strcmp(apellido1,apellido1_)==0&&strcmp(apellido2,apellido2_)==0){
        personas(nombre,apellido1,apellido2,nombre_,apellido1_,apellido2_);
        printf(" son la misma persona.\n");
    }else{
        if(strcmp(apellido1,apellido1_)==0&&strcmp(apellido2,apellido2_)==0){
            personas(nombre,apellido1,apellido2,nombre_,apellido1_,apellido2_);
            printf(" son hermanos.\n");
        }else{
            if(strcmp(apellido1,apellido1_)==0||strcmp(apellido1,apellido2_)==0||strcmp(apellido2,apellido2_)==0||strcmp(apellido2,apellido1_)==0){
                personas(nombre,apellido1,apellido2,nombre_,apellido1_,apellido2_);
                printf(" son primos.\n");
            }else{
                if(strcmp(nombre,nombre_)==0){
                    personas(nombre,apellido1,apellido2,nombre_,apellido1_,apellido2_);
                    printf(" son tocayos.\n");
                }else{
                    personas(nombre,apellido1,apellido2,nombre_,apellido1_,apellido2_);
                    printf(" no tienen ninguna relacion.\n\n");
                }
            }
        }
    }
    //Fin ejercicios
    system("pause");
    return;
}
void intentos(int centinela, char palabra2[],char palabra1[],int i,int l,int pista){
    for(i=1;i<5&&(centinela==0);i++){
        strcpy(palabra2, palabra1);//copia el contenido de palabra1 en palabra2
        int a=rand()%l;
        pista=i+1;
        printf("Intento %d de 4.",i);
        printf("(pista: en la posicion %d esta la letra %c).\n",a+1,palabra1[a]);
        scanf("%s",palabra2);
        getchar();
        system("cls");
        if(strcmp(palabra1,palabra2)==0){
            printf("Felicidades! Acertaste.\n");
            centinela=1;
        }else{
            centinela=0;
        }
    }
    return;
}
void ejercicio3_1(){
    system("cls");
    //Definir datos
    int l,i,centinela=0,pista;
    char palabra1[68];/*secreta*/
    char palabra2[68];
    printf("EJERCICIO 3 PRACTICA 1\n");
    printf("=======================\n");
    printf("Jugador 1, introduzca la palabra secreta:\n");
    scanf("%s",&palabra1);
    getchar();
    l=strlen(palabra1);
    system("cls");
    printf("Jugador2.\n\nLa palabra tiene %d letras.\n\n",l);
    //Blucle para repetir los 5 intentos
    intentos(centinela,palabra2,palabra1,i,l,pista);
    if(strcmp(palabra1,palabra2)!=0){
        printf("Lo siento, perdiste, la palabra era '%s'.\n",palabra1);
    }
    system("pause");
    return;
}
void ejercicio1_2(){
    system("cls");
    int n,i,numeroimpar=0,numero,centinela=0,totalcifras=1;
    int resultado,cifra;
    printf("EJERCICIO 1 PRACTICA 2\n");
    printf("=======================\n");
    printf("\tIntroduzca un numero entero mayor que cero.\n");
    scanf("%d",&n);
    getchar();
    while(n<=0){
        printf("Lo siento, el numero es menor o igual que 0.\n");
        printf("Introduzca un numero mayor a cero:\n");
        scanf("%d",&n);
        getchar();
    }
    for(i=0;i<n;numeroimpar++){
        if (numeroimpar%2!=0){
            numero=numeroimpar;
            resultado=0;
            centinela=0;
            for (totalcifras=0;numero!=0&&centinela==0;totalcifras++) {
                cifra=numero%10;
                numero=numero/10;//al hacer esta operacion le quitas una cifra al numero y la sumas al contador ya que realiza una vuelta por cifra al bucle.
                resultado=resultado+cifra;
                if(cifra%2==0){
                    centinela=1;
                }
            }
            if(totalcifras%2!=0&&resultado%2!=0&&centinela==0){
                printf("%d ",numeroimpar);
                i++;
            }
        }
    }printf("\n");
    system("pause");
    return;
}
void tabulacion(int ahora){//ejercicio2_2
    for(int i=0;i<ahora;i++){
        printf(" ");
    }
    return;
}
void guiones(int nveces){//ejercicio2_2
    printf("o");
    for(int i=0;i<nveces;i++){
        printf("-");
    }
    printf("o");
    return;
}
void animar(char cad[],int l){//ejercicio2_2
    for(int i=0;i<l-1;i++){
        cad[i]=cad[i+1];
    }
    return;
}
void ejercicio2_2(){
    system("cls");
    int l,i;
    char cad[100];
    printf("EJERCICIO 2 PRACTICA 2\n");
    printf("=======================\n");
    printf("\nIntroduzca una frase que contenga entre 10 y 50 caracteres:\n");
    gets(cad);
    l=strlen(cad);//pasa el valor de cad(cadena)a l(entero)

    while(l<10||l>50){//error si la frase es menor a 10 o mayor a 50
        printf("Error. Numero incorrecto de caracteres.\n");
        printf("Introduzca una frase que contenga entre 10 y 50 caracteres:\n");
        gets(cad);
        l=strlen(cad);
        system("cls");
    }
    int t=time(NULL);
    while((time(NULL)-t)<5){//desplazar la frase un caracter
        system("cls");
        //situar en el centro de la pantalla, parte vertical
        for(i=0;i<10;i++){
            printf("\n");
        }
        tabulacion(' ');//lleva al centro de la pantalla
        guiones(l+2);//imprime o y guiones superiores
        printf("\n");//baja a la siguiente fila
        tabulacion(' ');//lleva al centro de la pantalla
        printf("| %s |\n",cad);//imprime cadena
        char aux=cad[0];
        animar(cad,l);
        cad[l-1]=aux;
        tabulacion(' ');//lleva al centro de la pantalla
        guiones(l+2);//imprime o y guiones superiores
        printf("\n");//baja a la siguiente fila
        _sleep(250);
    }
    system("pause");
    return;
}
void asteriscospar(int mitad,int l,int aleatorio,char pista[]){
    for(mitad=0;mitad<=l/2;mitad++){//variable nueva para sacar la mitad de asteriscos
        aleatorio = rand()%l;
        pista[aleatorio]='*';
    }
    return;
}
void asteriscosimpar (int mitad,int l,int aleatorio,char pista[]){
    for(mitad=0;mitad<=(l/2)+1;mitad++){//variable nueva para sacar la mitad de asteriscos +1
        aleatorio = rand()%l;
        pista[aleatorio]='*';
    }
    return;
}
void ejercicio3_2(){
    system("cls");
    //Definir datos
    int l,i,centinela=0,mitad,aleatorio;
    char palabra1[68]/*secreta*/,pista[68];
    char palabra2[68];
    srand(time(NULL));//para sacar numeros aleatorios diferentes
    printf("EJERCICIO 3 PRACTICA 2\n");
    printf("=======================\n");
    printf("Jugador 1, introduzca la palabra secreta:\n");
    scanf("%s",&palabra1);
    getchar();
    l=strlen(palabra1);
    system("cls");
    //Blucle para repetir los 5 intentos
    for(i=0;i<6&&(centinela==0);i++){
        strcpy(pista, palabra1);//copia el contenido de palabra1 en palabra2
        if(l%2==0){//si l es par
            asteriscospar(mitad,l,aleatorio,pista);
        }else{//si l es impar
            asteriscosimpar(mitad,l,aleatorio,pista);
        }
        printf("Intento %d de 5:%s\n",i,pista);
        scanf("%s",palabra2);
        getchar();
        system("cls");
        if(strcmp(palabra1,palabra2)==0){
            printf("Felicidades! Acertaste.\n");
            centinela=1;
        }else{
            centinela=0;
        }
    }if(strcmp(palabra1,palabra2)!=0){
        printf("Lo siento, perdiste, la palabra era %s\n",palabra1);
    }
    system("pause");
    return;
}
void menupractica1(){
    int opcion;
    do{
        system("cls");
        printf("***MENU PRACTICA 1***\n");
        printf("1.-ejercicio1_1\n");
        printf("2.-ejercicio2_1\n");
        printf("3.-ejercicio3_1\n");
        printf("4.-volver al menu principal\n");
        scanf("%d",&opcion);
        getchar();

        switch(opcion){
        case 1:ejercicio1_1();
            break;
        case 2:ejercicio2_1();
            break;
        case 3:ejercicio3_1();
            break;
        }
    }while(opcion>0&&opcion<4);
    return;
}
void menupractica2(){
    int opcion;
    do{
        system("cls");
        printf("***MENU PRACTICA 2***\n");
        printf("1.-ejercicio1_2\n");
        printf("2.-ejercicio2_2\n");
        printf("3.-ejercicio3_2\n");
        printf("4.-volver al menu principal\n");
        scanf("%d",&opcion);
        getchar();

        switch(opcion){
        case 1:ejercicio1_2();
            break;
        case 2:ejercicio2_2();
            break;
        case 3:ejercicio3_2();
            break;
        }
    }while(opcion!=4);
    return;
}
void menuprincipal(){
    int opcion;//almacenan resultados en la operacion
    do{
        system("cls");
        printf("***MENU PRINCIPAL***\n");
        printf("1.-Menu practica 1.\n");
        printf("2.-Menu practica 2.\n");
        printf("3.-Salir.\n");

        scanf("%d",&opcion);
        getchar();
        switch(opcion){
        case 1:menupractica1();
            break;
        case 2:menupractica2();
            break;
        }
    }while(opcion!=3);
    return;//no se devuleve ningun valor a menuprincipal
}
int main (void){
    menuprincipal();
    return 0;
}


