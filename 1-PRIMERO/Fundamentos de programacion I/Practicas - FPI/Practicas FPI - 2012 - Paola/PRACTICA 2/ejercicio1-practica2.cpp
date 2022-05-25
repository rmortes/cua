#include <stdio.h>
#include<conio.h>

int main(void){
int n;

    do{
        printf("Tamanyo de la copa (1-10):",n);
        scanf("%d",&n);
        getchar();

        if(n<1|| n>10){
            printf("Error. El tamanyo no es valido.");
        }else{

            int i,j,k;


            for(i=0;i<n;i++){
                /* lado izquierdo*/

                for(j=0;j<i;j++){
                    printf(" ");
                }
                printf("\\");

                /*lado derecho*/

                for(k=0; k<2*(n-i)-1; k++){
                    printf(" ");
                }
                printf("/\n");
            }
            /*tallo*/
            for(j=0;j<n;j++){
                for (i=0;i<n;i++){
                    printf(" ");
                }
                printf("|\n");
            }
            /*base*/
            for(i=0;i<n*2+1;i++){
                printf("\-");
            }
            printf("\n");
        }

        getchar();

    }while(n<1 || n>10);


    getche();
    return(0);
}
