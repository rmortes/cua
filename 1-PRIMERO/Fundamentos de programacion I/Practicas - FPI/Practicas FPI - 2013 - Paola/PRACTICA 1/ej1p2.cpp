#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<conio.h>

int main(void){
    printf("Ejercicio 1-Practica 2\n");
    int a;
    do{
        printf("Introduzca altura del triangulo (1-10): ",a);
        scanf("%d",&a);
        getchar();
        if(a<0 || a>10){
            printf("Error:La altura es incorrecta.\n");
        }else{
            char p;
            printf("Introduzca posicion (I-izquierda C-centro D-derecha):",p);
            scanf("%c",&p);
            getchar();
            switch(p){
            case 'i':
                //IZQUIERDA
                for(int i=0;i<a;i++){
                    for(int j=0;j<=i;j++){
                        printf("*");
                    }
                    printf("\n");
                }
                break;
            case 'd':
                //DERECHA
                for(int i=0; i<=a; i++){
                    for(int k=0;k<=a-i-1;k++){
                        printf(" ");
                    }
                    for(int j=0;j<i;j++){
                        printf("*");
                    }

                    printf("\n");
                }
                break;
            case 'c':
                //CENTRO
                for(int i=0; i<=a; i++){
                    for(int k=0;k<=a-i-1;k++){
                        printf(" ");
                    }
                    for(int j=0;j<2*i+1;j++){
                        printf("*");
                    }
                    for(int l=0;l<=a-i-1;l++){
                        printf(" ");
                    }
                    printf("\n");
                }
                break;
            }
        }

    }while(a>0 || a<11);
    getche();
    return(0);
}
