//Incluimos las librerias
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

int main(void){

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

    return 0;

}
