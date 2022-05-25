//Incluimos las librerias
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>


int main (){

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

    return(0);
}
