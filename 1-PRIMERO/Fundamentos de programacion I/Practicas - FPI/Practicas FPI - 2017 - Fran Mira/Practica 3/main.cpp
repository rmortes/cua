#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
// Recoger numero entero
int pedir_num(int rango1, int rango2)
{
    int num;
    scanf("%d",&num);
    while(num<rango1 || num>rango2)
    {
        printf("ERROR. El numero introducido esta fuera del rango.\n");
        printf("Introduzca un numero valido: ");
        scanf("%d",&num);
    }
    return num;
}
// Recoge una cadena y obtiene su longitud
int pedir_cadena (char cadena[],int rango1 ,int rango2){
    int long_cadena;
    fflush(stdin);
    gets(cadena);
    long_cadena =strlen(cadena);
    if(long_cadena<rango1 || long_cadena>rango2){
        printf("ERROR. El cadena introducida esta fuera del rango.\n");
        printf("Introduzca una cadena valida: ");
        pedir_cadena(cadena,rango1,rango2);
    }
    return long_cadena;
}
//// INICIO Practica 1 - Ejercicio 1 ////
void p1_ejer1(void)
{
    //Pedir numero
    int num;
    printf("Introduzca un numero de loteria (0-99999):\n");
    num = pedir_num(0,99999);
    //Descomponer e imprimir numero en cifras
    if(num % 10!=0) printf("Unidades: %d\n", num % 10);
    num /= 10;
    if(num % 10 != 0) printf("Decenas: %d\n", num % 10);
    num /= 10;
    if(num % 10 != 0) printf("Centenas: %d\n", num % 10);
    num /= 10;
    if(num % 10 != 0) printf("Unidades de millar: %d\n", num % 10);
    num /=10;
    if(num % 10 != 0) printf("Decenas de millar: %d\n", num % 10);
}
//// FIN Practica 1 - Ejercicio 1 ////
// Recoger numero real
float pedir_num_decimal(int rango1, int rango2){
    float num;
    scanf("%f", &num);
    while(num<rango1 || num>rango2)
    {
        printf("ERROR. El numero introducido esta fuera del rango.\n");
        printf("Introduzca un numero valido: ");
        scanf("%f", &num);
    }
    return num;
}
//// INICIO Practica 1 - Ejercicio 2 ////
//Imprimir calificaciones dependiendo de la nota final
void imprimir_calificaciones(float nota,float nota_practica,float nota_teoria)
{
    printf("Calificaciones finales:\n");
    printf("Teoria: %.2f ",nota_teoria);
    printf("Practica: %.2f ",nota_practica);
    printf("Final: %.2f ",nota);
    if(nota<5)printf("\nSuspenso\n");
    if(5<nota && nota<7)printf("\nAprobado\n");
    if(7<nota && nota<9)printf("\nNotable\n");
    if(9<nota)printf("\nSobresaliente\n");
}
void p1_ejer2(void)
{
    float p1,p2,p3,p4,ep,ef,nota_final,nota_practica,nota_teoria;
    printf("Introduzca nota de la practica 1:");
    p1=pedir_num_decimal(0,10);
    printf("Introduzca nota de la practica 2:");
    p2=pedir_num_decimal(0,10);
    printf("Introduzca nota de la practica 3:");
    p3=pedir_num_decimal(0,10);
    printf("Introduzca nota de la practica 4:");
    p4=pedir_num_decimal(0,10);
    printf("Introduzca nota del examen parcial:");
    ep=pedir_num_decimal(0,10);
    printf("Introduzca nota del examen final:");
    ef=pedir_num_decimal(0,10);
    nota_teoria= ep/3+2*ef/3;
    nota_practica=(p1+p2+p3+p4)/4;
    if ((p1+p2+p3+p4)/4>4)
    {
        if(ep/3+2*ef/3>4)
        {
            nota_final=nota_practica*0.4+ep*0.2/3+ef*0.8/3;
            imprimir_calificaciones(nota_final,nota_practica,nota_teoria);
        }
        else
        {
            if(ep>4 && ef<5)
            {
                nota_final=nota_practica*0.4+ep*0.2/3;
                imprimir_calificaciones(nota_final,nota_practica,nota_teoria);
            }
            else
            {
                nota_final=nota_practica*0.4+ef*0.8/3;
                imprimir_calificaciones(nota_final,nota_practica,nota_teoria);
            }
        }
    }
    else
    {
        nota_final=0.2*ep/3+0.8*ef/3;
        imprimir_calificaciones(nota_final,nota_practica,nota_teoria);
    }
}
//// FIN Practica 1 - Ejercicio 2 ////
//// INICIO Practica 1 - Ejercicio 3 ////
void p1_ejer3(void)
{
    int d1,m1,a1,d2,m2,a2,edad1_en_dias,edad2_en_dias,a_total,m_total,d_total;
    char nombre1[30],nombre2[30];
    printf("Introduzca nombre de la primera persona:");
    pedir_cadena(nombre1,0,50);
    do
    {
        printf("Introducir fecha de nacimiento de la primera persona (dd/mm/aaaa):");
        scanf("%d/%d/%d",&d1,&m1,&a1);
    }
    while(d1>30|| m1>12 || a1>2500 || a1<1900);
    printf("Introduzca nombre de la segunda persona:");
    pedir_cadena(nombre2,0,50);
    do
    {
        printf("Introducir fecha de nacimiento de la segunda persona (dd/mm/aaaa):");
        scanf("%d/%d/%d",&d2,&m2,&a2);
    }
    while(d2>30|| m2>12 || a2>2500 || a2<1900);
    // Pasa edades a días
    edad1_en_dias= a1*360+m1*30+d1;
    edad2_en_dias= a2*360+m2*30+d2;
    // Compara edades y determinar al mayor y la diferencia de edades
    if (edad1_en_dias<=edad2_en_dias)
    {
        a_total=(edad2_en_dias-edad1_en_dias)/360;
        m_total=((edad2_en_dias-edad1_en_dias)%360)/12;
        d_total=(edad2_en_dias-edad1_en_dias)%4320/30;
        printf("Resultado: %s es mayor que %s por %d anyos %d meses y %d dias.\n",nombre1,nombre2,a_total,m_total,d_total);
    }
    else
    {
        a_total=(edad1_en_dias-edad2_en_dias)/360;
        m_total=((edad1_en_dias-edad2_en_dias)%360)/12;
        d_total=(edad1_en_dias-edad2_en_dias)%4320/30;
        printf("Resultado: %s es menor que %s por %d anyos %d meses y %d dias.\n",nombre1,nombre2,a_total,m_total,d_total);
    }
}
//// FIN Practica 1 - Ejercicio 3 ////

//// INICIO Practica 2 - Ejercicio 1 ////
void p2_ejer1(void)
{
    bool primo;
    int num_intro,i,j,primo_sec,cont_primos=0,num=2,divisor_n;
    printf("Introduzca un numero mayor a 0: ");
    num_intro= pedir_num(1,1000);
    printf("Los %d primeros numeros primos segundos son: ",num_intro);
    while(cont_primos<num_intro)
    {
        primo=true;
        primo_sec=0;
        j=1;
        //Separar las cifras.
        while(j<(num*10))
        {
            divisor_n=(num/j)%10;
            primo_sec=primo_sec+divisor_n;
            j*=10;
        }
        //Encontrar numeros primos segundos.
        for(i=2; i<primo_sec;i++)
        {
            if(primo_sec%i==0)
            {
                primo=false;
            }
        }
        if(primo_sec==1)
        {
            primo=false;
        }
        //Imprimir numeros primos segundos.
        if(primo)
        {
            printf("%d ",num);
            cont_primos++;
        }
        num++;
    }
    printf("\n");
}
//// FIN Practica 2 - Ejercicio 1 ////
//// INICIO Practica 2 - Ejercicio 2 ////
// Inicio de centrado de la cadena.
void centrar_en_anchura(int long_cadena){
    int i,cantidad_de_esp;
    cantidad_de_esp= (120-(long_cadena+2))/2;
    for(i=0;i<cantidad_de_esp;i++){
        printf(" ");
    }
}
void centrar_en_altura(void){
    int i;
    for(i=0;i<10;i++){
        printf("\n");
    }
}
// Fin de centrado de la cadena.
// Creación de asteriscos.
void asteriscos(int long_cadena)
{
    int i;
    printf("\n");
    centrar_en_anchura(long_cadena);
    for(i=0;i<long_cadena+2;i++){
        printf("*");
    }
    printf("\n");
}
void p2_ejer2(void)
{
    int i,long_cadena, tiempo= time(NULL),tiempo_f;
    char cadena[50],ult_letra;
    //Solicitar cadena al usuario.
    printf("Introduzca una cadena entre 10 y 50 caracteres:\n");
    long_cadena= pedir_cadena(cadena,10,50);
    //Impresión de la cadena.
    while((tiempo_f-tiempo)<=10)
    {
        centrar_en_altura();
        asteriscos(long_cadena);
        centrar_en_anchura(long_cadena);
        printf("*%s*",cadena);
        asteriscos(long_cadena);
        centrar_en_altura();
        // Rotación
        ult_letra=cadena[0];
        for(int j=0;j<=(long_cadena-1);j++)
        {
            cadena[j]=cadena[j+1];
        }
        cadena[long_cadena-1]=ult_letra;
        _sleep(70);
        system("cls");
        tiempo_f= time(NULL);
    }
}
//// FIN Practica 2 - Ejercicio 2 ////
//// INICIO Practica 2 - Ejercicio 3 ////
void p2_ejer3(void)
{
    char juega[1];
    juega[0]='s';
    while(juega[0]=='s')
    {
        time((NULL));
        int n_intentos=0, num_secreto= rand()%100+1, tiempo=time(NULL), num_introducido=0,tiempo2;
        printf("Adivine el numero secreto del 1 al 100\n");
        //Inicio de juego.
        while(num_secreto!=num_introducido)
        {
            n_intentos++;
            printf("Intento %d: ", n_intentos);
            scanf("%d",&num_introducido);
            if(num_introducido<num_secreto)printf("El numero secreto es mayor.\n");
            if(num_introducido>num_secreto)printf("El numero secreto es menor.\n");
        }
        tiempo2=time(NULL);
        tiempo=tiempo2-tiempo;
        //Fin de juego.
        printf("ACERTASTE!!!\n");
        printf("Has realizado %d intentos y has tardado %d segundos en adivinar el numero.\n",n_intentos, tiempo);
        printf("Desea seguir jugando(s/n)?");
        scanf("%s",juega);
    }
}
//// FIN Practica 2 - Ejercicio 3 ////
int submenu1(void)
{
    int opcion2=0;
    printf("*** PRACTICA 1 ***\n");
    printf("1.- Ejercicio 1\n");
    printf("2.- Ejercicio 2\n");
    printf("3.- Ejercicio 3\n");
    printf("4.- Volver al menu anterior\n");
    printf("Opcion: ");
    scanf("%d", &opcion2);
    return opcion2;
}
int submenu2(void)
{
    int opcion3;
    printf("*** PRACTICA 2 ***\n");
    printf("1.- Ejercicio 1\n");
    printf("2.- Ejercicio 2\n");
    printf("3.- Ejercicio 3\n");
    printf("4.- Volver al menu anterior\n");
    printf("Opcion: ");
    scanf("%d", &opcion3);
    return opcion3;
}
int menu_principal(void)
{
    int opcion1;
    printf("--- MENU PRINCIPAL ---\n");
    printf("1.- PRACTICA 1\n");
    printf("2.- PRACTICA 2\n");
    printf("3.- Salir\n");
    printf("Opcion: ");
    scanf("%d", &opcion1);
    return opcion1;
}
int main()
{
    int opcion1=0, opcion2, opcion3, marca=0;
    while(opcion1<3)
    {
        if (marca == 0)
        {
            opcion1 = menu_principal();
        }
        switch (opcion1)
        {
        // PRACTICA 1
        case 1:
            marca = 1;

            opcion2 = submenu1();
            switch (opcion2)
            {
            case 1:
                p1_ejer1();
                break;
            case 2:
                p1_ejer2();
                break;
            case 3:
                p1_ejer3();
                break;
            case 4:
                marca = 0;
                break;
            }
            break;
            // PRACTICA 2
        case 2:
            marca = 1;

            opcion3 = submenu2();
            switch (opcion3)
            {
            case 1:
                p2_ejer1();
                break;
            case 2:
                p2_ejer2();
                break;
            case 3:
                p2_ejer3();
                break;
            case 4:
                marca = 0;
                break;
            }
            break;
        case 3:
            return 0;
            break;
        }

    }
}
