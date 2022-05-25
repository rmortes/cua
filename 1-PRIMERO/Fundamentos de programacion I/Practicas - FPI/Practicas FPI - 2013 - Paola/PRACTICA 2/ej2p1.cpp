#include<stdio.h>
#include<math.h>
#include<conio.h>

int main(void){
    int n;
    printf("Introduce un numero del 1 al 100: ");
    scanf("%d",&n);
    if(n>=1 && n<=100){
        if(n==2||n==3||n==5||n==7||n==11||n==13||n==17||n==19||n==23||n==29||n==31||n==37||n==41||n==43||n==47||n==53||n==59||n==61||n==67||n==71||n==73||n==79||n==83||n==89||n==97){
            printf("El numero es primo");
        }else{
            printf("El numero no es primo porque es divisible por los numeros primos...\n");
            if(n%2==0){
                printf("2\t");
            }if(n%3==0){
                printf("3\t");
            }if(n%5==0){
                printf("5\t");
            }if(n%7==0){
                printf("7\t");
            }if(n%11==0){
                printf("11\t");
            }if(n%13==0){
                printf("13\t");
            }if(n%17==0){
                printf("17\t");
            }if(n%19==0){
                printf("19\t");
            }if(n%23==0){
                printf("23\t");
            }if(n%29==0){
                printf("29\t");
            }if(n%31==0){
                printf("31\t");
            }if(n%37==0){
                printf("37\t");
            }if(n%41==0){
                printf("41\t");
            }if(n%43==0){
                printf("43\t");
            }if(n%47==0){
                printf("47\t");
            }if(n%53==0){
                printf("53\t");
            }if(n%59==0){
                printf("59\t");
            }if(n%61==0){
                printf("61\t");
            }if(n%67==0){
                printf("67\t");
            }if(n%71==0){
                printf("71\t");
            }if(n%73==0){
                printf("73\t");
            }if(n%79==0){
                printf("79\t");
            }if(n%83==0){
                printf("83\t");
            }if(n%89==0){
                printf("89\t");
            }if(n%97==0){
                printf("97\t");
            }

        }
    }else{
        printf("El numero no es correcto");
    }
    getche();
    return(0);
}
