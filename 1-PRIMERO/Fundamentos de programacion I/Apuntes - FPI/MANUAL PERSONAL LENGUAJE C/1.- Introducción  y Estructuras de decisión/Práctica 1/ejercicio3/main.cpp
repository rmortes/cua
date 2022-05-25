#include <stdio.h>

int main(){

    int a;

    printf("Introduzca un numero entre 1 y 100: ");
    scanf("%d",&a);
    getchar();


    if (a<1 || a>100){
        printf("El numero introducido es incorrecto.");
    }
    else
        if (a==2 || a==3 || a==5 || a==7 || a==11 || a==13 || a==17 || a==19 || a==23 || a==29 || a==31 || a==37 || a==41 || a==43 || a==47 || a==53 || a==59 || a==61 || a==67 || a==71 || a==73 || a==79 || a==83 || a==89 || a==97){
            printf("El numero introducido es primo.");
        }
        else{
            printf("El numero no es primo porque es divisible por los primos: ");

            if (a%2==0){
                printf("2 ");
            }

            if (a%3==0){
                printf("3 ");
            }

            if (a%5==0){
                printf("5 ");
            }

            if (a%7==0){
                printf("7 ");
            }


            if (a%11==0){
                printf("11 ");
            }

            if (a%13==0){
                printf("13 ");
            }

            if (a%17==0){
                printf("17 ");
            }

            if (a%19==0){
                printf("19 ");
            }

            if (a%23==0){
                printf("23 ");
            }

            if (a%29==0){
                printf("29 ");
            }

            if (a%31==0){
                printf("31 ");
            }
            if (a%37==0){
                printf("37 ");
            }

            if (a%41==0){
                printf("41 ");
            }

            if (a%43==0){
                printf("43 ");
            }

            if (a%47==0){
                printf("47 ");
            }
        }

    printf("\n");
    return 0;
}

