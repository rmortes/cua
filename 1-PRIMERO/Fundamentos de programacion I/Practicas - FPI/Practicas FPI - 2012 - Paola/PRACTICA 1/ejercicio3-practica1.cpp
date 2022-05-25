#include<stdio.h>
#include<conio.h>
int main (void){

    printf("\n------------\nLEER NUMERO\n------------\n");
    int u,d,c,n;
    printf("introduzca un numero entre 1 y 999:");
    scanf("%d",&n );
    c=n/100;
    d=(n/10)%10;
    u=n%10;

    if(1>n || 999<n){
        printf("ERROR");
    }else{

        switch (c){

        case 0:
            break;
        case 1:
            if(d==0 && u==0){
                printf("CIEN ");
            }else{
                printf("CIENTO ");
            }
            break;

        case 2:
            printf("DOSCIENTOS  ");
            break;
        case 3:
            printf("TRESCIENTOS  ");
            break;
        case 4:
            printf("CUATROCIENTOS  ");
            break;
        case 5:
            printf("QUINIENTOS  ");
            break;
        case 6:
            printf("SEISCIENTOS  ");
            break;
        case 7:
            printf("SETECIENTOS  ");
            break;
        case 8:
            printf("OCHOCIENTOS  ");
            break;
        case 9:
            printf("NOVECIENTOS  ");
            break;
        }
        switch (d){
        case 0:
            break;
        case 1:
            if(u<=5){
                switch (u){
                case 1:
                    printf("ONCE");
                    break;
                case 2:
                    printf("DOCE");
                    break;
                case 3:
                    printf("TRECE");
                    break;
                case 4:
                    printf("CATORCE");
                    break;
                case 5:
                    printf("QUINCE");
                    break;
                }
            }else{
               printf("DIEZ ");
            }
            break;

        case 2:
            printf("VEINTE ");
            break;
        case 3:
            printf("TREINTA ");
            break;
        case 4:
            printf("CUARENTA ");
            break;
        case 5:
            printf("CINCUENTA ");
            break;
        case 6:
            printf("SESENTA ");
            break;
        case 7:
            printf("SETENTA ");
            break;
        case 8:
            printf("OCHENTA ");
            break;
        case 9:
            printf("NOVENTA ");
            break;
        }
        if (!(u==0) && !(d==1 && u<=5)){
            printf (" Y ");

            switch(u){
            case 1:
                printf("UNO");
                break;
            case 2:
                printf("DOS");
                break;
            case 3:
                printf("TRES");
                break;
            case 4:
                printf("CUATRO");
                break;
            case 5:
                printf("CINCO");
                break;
            case 6:
                printf("SEIS");
                break;
            case 7:
                printf("SIETE");
                break;
            case 8:
                printf("OCHO");
                break;
            case 9:
                printf("NUEVE");
                break;
            }
        }
    }
    getche();
    return(0);
}
