#include <stdio.h>

int main(){
        int linea, i, n, espacios;

        do{
                printf("n:");
                scanf("%d", &n);
        }while(n <= 0 || n >= 10);

        linea = 1;
        espacios = 2*n-1;
        while(linea <= n){
                i = 1;
                while(i <= linea - 1){
                        printf(" ");
                        i++;
                }
                printf("\\");
                i = 1;
                while(i <= espacios){
                        printf(" ");
                        i++;
                }
                linea++;
                espacios = espacios - 2;
                printf("/\n");
        }

        linea = 1;
        while(linea <= n){
                i = 1;
                while(i <= n){
                        printf(" ");
                        i++;
                }
                printf("|\n");
                linea++;
        }
        i = 1;
        while(i <= 2*n+1){
                printf("-");
                i++;
        }
        printf("\n");
        return 0;
}
