#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int SolicitarNumero(int nmenor, int nmayor){
    int n;
    scanf("%d",&n);
    getchar();
    if(n<nmenor || n>nmayor)
        printf("El numero es incorrecto.\n");
    return n;
}

void usurero(float r,int a,int b){
    float resultado;
    resultado=a*b*r;
    printf("Transcurridos %d",b);
    printf(" meses, sus %d",a);
    printf(" euros producen unos intereses de %.1f", resultado);
    printf(" euros." );
    return ;
}

int practica(void){
    int a;
    do{
        printf("===MENU PRINCIPAL===\n");
        printf("1.- Practica 1\n");
        printf("2.- Practica 2\n");
        printf("3.- Salir\n");
        printf("Opcion:");
        a=SolicitarNumero(1,3);
    }while(a<1 || a>3);

    if (a==3){
        printf("Fin del programa.\n");
    }

    return a;
}

int ejercicio(int num){
    int b;

    do{
        if(num==1){
            printf("*** Practica 1 ***\n");
        }
        if(num==2){
            printf("*** Practica 2 ***\n");
        }

        printf("1.- Ejercicio 1\n");
        printf("2.- Ejercicio 2\n");
        printf("3.- Ejercicio 3\n");
        printf("4.- Volver al menu\n");
        printf("Opcion:");
        b=SolicitarNumero(1,4);
    }while(b<1 || b>4);

    return b;

}
void ejerc1pract1(void){
    int a,b,c;
    do{
        printf("Numero a:");
        scanf("%d",&a);
        getchar();
        printf("Numero b:");
        scanf("%d",&b);
        getchar();
        printf("Numero c:");
        scanf("%d",&c);
        getchar();
        if(a<0 || b<0 || c<0 || a+b<c || a+c<b || c+b<a)
            printf ("El triangulo no es valido\n");
    }while(a<0 || b<0 || c<0 || a+b<c || a+c<b || c+b<a);


    if (a==b && c==a){
        printf("El triangulo es equilatero\n");
    }
    else
        if (b==a || c==a){
            printf("El triangulo es isosceles\n");
        }
        else
            printf("El triangulo es escaleno\n");

    return ;
}

void ejerc2pract1(void){
    int a,b;
    float r;
    do{
        printf("Cantidad de prestamos en euros:");
        scanf("%d",&a);
        getchar();
        printf("Tiempo en meses:");
        scanf("%d",&b);
        getchar();
        if(a<=0 || b<=0)
            printf("Los valores introducidos son incorrectos\n");
    }while(a<=0 || b<=0);

    if (a<=600){
        r=0.06;
        printf("El usurero A es el mas conveniente.\n");
        usurero(r,a,b);
    }
    if (a>600 && a<=700){
        r=0.07;
        printf("El usurero B es el mas conveniente.\n");
        usurero(r,a,b);
    }

    if (a>700 && a<4000){
        r=0.11;
        printf("El usurero B es el mas conveniente.\n");
        usurero(r,a,b);
    }

    if (a>=4000 && a<5000){
        r=0.13;
        printf("El usurero A es el mas conveniente.\n");
        usurero(r,a,b);
    }

    if (a>=5000){
        r=0.14;
        printf("El usurero B es el mas conveniente.\n");
        usurero(r,a,b);
    }

    printf("\n");
    return;
}
void ejerc3pract1(void){
    int a;
    do{
        printf("Introduzca un numero entre 1 y 100:");
        scanf("%d",&a);
        getchar();


        if (a<1 || a>100)
            printf("El numero introducido es incorrecto.");
    }while(a<1 || a>100);

    if (a==2 || a==3 || a==5 || a==7 || a==11 || a==13 || a==17 || a==19 || a==23 || a==29 || a==31 || a==37 || a==41 || a==43 || a==47 || a==53 || a==59 || a==61 || a==67 || a==71 || a==73 || a==79 || a==83 || a==89 || a==97){
        printf("El numero introducido es primo.");
    }
    else

        printf("El numero no es primo porque es divisible por los primos: ");

    if (a%2==0 && a>1 && a<100){
        printf("2 ");
    }

    if (a%3==0 && a>1 && a<100){
        printf("3 ");
    }

    if (a%5==0 && a>1 && a<100){
        printf("5 ");
    }

    if (a%7==0 && a>1 && a<100){
        printf("7 ");
    }


    if (a%11==0 && a>1 && a<100){
        printf("11 ");
    }

    if (a%13==0 && a>1 && a<100){
        printf("13 ");
    }

    if (a%17==0 && a>1 && a<100){
        printf("17 ");
    }

    if (a%19==0 && a>1 && a<100){
        printf("19 ");
    }

    if (a%23==0 && a>1 && a<100){
        printf("23 ");
    }

    if (a%29==0 && a>1 && a<100){
        printf("29 ");
    }

    if (a%31==0 && a>1 && a<100){
        printf("31 ");
    }
    if (a%37==0 && a>1 && a<100){
        printf("37 ");
    }

    if (a%41==0 && a>1 && a<100){
        printf("41 ");
    }

    if (a%43==0 && a>1 && a<100){
        printf("43 ");
    }

    if (a%47==0 && a>1 && a<100){
        printf("47 ");
    }
    printf("\n");
    return ;
}

void practica1(void){
    int d;
    do{
        d=ejercicio(1);
        if(d==1){
            ejerc1pract1();
        }
        if (d==2){
            ejerc2pract1();
        }
        if (d==3){
            ejerc3pract1();
        }

    }while(d>=1 && d<=3);


    return;

}

void ejerc1pract2(void){
    int i=112, b, d=1, n, par=0, impar=0, contador=0;

    do{
        printf("introduzca un numero mayor que cero:");
        scanf("%d",&b);
        getchar();
        if(b<=0){
            printf("error, el numero es menor o igual a cero\n");
        }
    }while(b<=0);
    printf("los %d primeros numeros parejos son: ",b);

    while (contador!=b){
        while(i/d>=1){
            n=(i/d)%10;
            d=10*d;
            if (n%2==0){
                par=n+par;
            }
            else
                impar=n+impar;
        }
        if (par==impar){
            printf("%d ",i);
            contador=contador+1;
        }
        i++;
        par=0;
        impar=0;
        d=1;
    }
    printf("\n");
    return;
}

void ejerc2pract2(void){
    srand(time(NULL));
    int i=2;
    int a,b, diferencia1, diferencia2;
    int num=rand()%1001;
    printf("Ya he elegido el numero entre 1 y 1000 \n");
    printf("Intento 1. Introduzca un numero:");
    scanf("%d",&a);
    getchar();
    if (a==num){
        printf("Felicidades, has acertado el numero en 1 intento. ");
    }
    else
        do {
        if(a<num){
            diferencia1=num-a;}
        else
            diferencia1=a-num;
        printf("Intento %d. Introduzca un numero:",i);
        scanf("%d",&b);
        if(b<num){
            diferencia2=num-b;
        }
        else
            diferencia2=b-num;
        if(diferencia2>diferencia1){
            printf("Frio, frio.\n");
        }
        if(diferencia2<diferencia1){
            printf("Caliente, caliente.\n");
        }
        if (diferencia2==diferencia1){
            printf("Templado, templado.\n");
        }
        a=b;
        i++;
    }while (b!=num);
    if (i!=2){
        printf("Felicidades, has acertado el numero en %d intentos.\n ",i-1);
    }
    return ;
}

void ejerc3pract2(){
    srand(time(NULL));
    int x, y, correcto=0,f,c, i=0, j=0, iteracion=0;
    while (correcto==0){
        system("cls");
        printf("Numero de filas del panel: ");
        scanf("%d",&f);
        getchar();
        printf("Numero de columnas del panel: ");
        scanf("%d",&c);
        getchar();
        if(5>f || 20<f || 5>c || 75<c)
            printf("Numero incorrecto de filas o columnas.\n");
        else
        {system("cls");
            correcto=1;}
    }
    while (j<=f/2 && j>=-(f-f/2-1) && i>=-c/2 && i<=c-c/2-1){
        system("cls");
        printf("Escape del laberinto iteracion %d\n",iteracion);
        for (y=f/2; y>=-(f-f/2-1); y--){
            for (x=-c/2; x<=c-c/2-1; x++){
                if (x==i && y==j)
                    printf("X");
                else
                    if (x==-c/2 ||x==c-c/2-1)
                        printf("|");
                    else
                        if (y==f/2 || y==-(f-f/2-1))
                            printf("-");
                        else
                            printf(" ");

            }
            printf("\n");
        }
        if (j==f/2 || i==c-c/2-1)
        { i++;
            j++;}
        else
            if ( j==-(f-f/2-1)||i==-c/2)
            { i--;
                j--;}
            else{


                iteracion++;
            }


        i=i+rand()%2;

        j=j+rand()%2;

        i=i-rand()%2;

        j=j-rand()%2;
    }
    printf("\n\nFin del juego. Se ha conseguido escapar en %d iteraciones.\n",
           iteracion);
    return ;
}

void practica2(void){
    int f;
    do{
        f=ejercicio(2);
        if(f==1)
            ejerc1pract2();
        if (f==2)
            ejerc2pract2();
        if (f==3)
            ejerc3pract2();


    }while(f>=1 && f<=3);
    return;
}


int main(){
    int a;
    do{
        a=practica();

        if(a==1)
            practica1();
        if(a==2)
            practica2();
    }while(a==1 || a==2);
    return 0;
}
