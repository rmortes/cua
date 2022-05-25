#include <stdio.h>
//inicio del ejercio.
int main(void){
    char letra,jugar;
    int cent,min,max,cont;
    //Inicialización de algunas variables para averiguar el numero pensado.
    do{
        cent=50;
        min=1;
        max=100;
        cont=1;
        printf("Piensa un numero del 1 al 100 \n");
        //Inicio del bucle para encontrar el número.
        do{
            //Interacción con el usuario y repite el proceso en caso de que el usuario se equivoque.
            do{
                printf("Intento %d. Es mayor(M), menor(m) o igual(i) a %d ? ",cont,cent);
                scanf("%c",&letra);
                getchar();
            }while(letra!='M' && letra!='m' && letra!='i');
            //Al introducir la letra se le asigna a una variable y esta opera para acortar el límite de busca del número.
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
        //En caso de que el usuario mienta sale el mensaje por pantalla.
        if(min>max) {
            printf("Me has mentido. El numero no existe \n");
        }
        //Bucle para rectificar si se equivoca de letra.
        do{
            //Interacción con el usuario para repetir el juego o no.
            printf("Desea jugar de nuevo(s/n)? ");
            scanf("%c",&jugar);
            getchar();
        }while(jugar!='s' && jugar!='n');
    }while(jugar=='s');

    //Fin del programa.
    return 0;
}

