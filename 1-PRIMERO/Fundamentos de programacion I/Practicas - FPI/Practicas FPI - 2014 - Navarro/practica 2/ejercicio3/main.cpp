#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

int main(){
    int nf, nc, x, y, num;
    char jugar,coordinada;
    //Bucle de repetir el juego.
    do{
        //Coloca la pelota en una posición centrada.
        srand(time(NULL));
        nf=12;
        nc=40;
        //Muestra por pantalla la interacción con el usuario.
        printf("Introduzca el lateral por el que apuesta: Norte,Sur,Este,Oeste   [N,S,E,O]:  ");
        scanf("%c",&coordinada);
        getchar();
        if(coordinada=='n'||coordinada=='N'||coordinada=='s'||coordinada=='S'||coordinada=='e'||coordinada=='E'||coordinada=='o'||coordinada=='O'){
            do{
                for(x=0; x<nf; x++){
                    printf("\n");
                }
                for(y=0; y<nc; y++){
                    printf(" ");
                }
                printf("o\n");
                _sleep(100);
                num=rand()%4;
                switch (num) {
                case 0:
                    nf--;
                    break;
                case 1:
                    nf++;
                case 2:
                    nc--;
                    break;
                case 3:
                    nc++;
                    break;
                }

                system("cls");
            }while(x>0 && x<80 && y<80 && y>0);
            if((x==0 && coordinada == 'N') || (x==0 && coordinada == 'n')){
                printf("Has acertado\n");
            }else if((x==24 && coordinada == 'S')|| (x==24 && coordinada == 's')){
                printf("Has acertado\n");
            }else if((y==0 && coordinada == 'E') || (y==0 && coordinada == 'e')){
                printf("Has acertado\n");
            }else if((y==80 && coordinada == 'O') || (y==80 && coordinada == 'o')){
                printf("Has acertado\n");
            }else{
                printf("Has fallado. Intentelo de nuevo\n");
            }
        }
        //Llama la función. Hace posible repetir el juego.
        printf("Desea jugar de nuevo (s) Si o (n) No: ");
        scanf("%c",&jugar);
        getchar();
    }while(jugar == 's' || jugar == 'S');
}
