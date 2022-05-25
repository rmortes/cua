#include <stdio.h>

int main(){

    int a,b;
    float resultado;

    printf("Cantidad de prestamos en euros: ");
    scanf("%d",&a);
    getchar();
    printf("Tiempo en meses:");
    scanf("%d",&b);
    getchar();

    if(a<=0 || b<=0){
        printf("Los valores introducidos son incorrectos");
    }

    else
        if (a<=600){
            resultado=a*b*0.06;
            printf("El usurero A es el mas conveniente.\n");
            printf("Transcurridos %d",b);
            printf(" meses, sus %d",a);
            printf(" euros producen unos intereses de %.1f", resultado);
            printf(" euros." );
        }

        else
            if (a<=700){
                resultado=a*b*0.07;
                printf("El usurero B es el mas conveniente.\n");
                printf("Transcurridos %d",b);
                printf(" meses, sus %d",a);
                printf(" euros producen unos intereses de %.1f", resultado);
                printf(" euros." );
            }
            else

                if (a<4000){
                    resultado=a*b*0.11;
                    printf("El usurero B es el mas conveniente.\n");
                    printf("Transcurridos %d",b);
                    printf(" meses, sus %d",a);
                    printf(" euros producen unos intereses de %.1f", resultado);
                    printf(" euros." );
                }
                else

                    if (a<5000){
                        resultado=a*b*0.13;
                        printf("El usurero A es el mas conveniente.\n");
                        printf("Transcurridos %d",b);
                        printf(" meses, sus %d",a);
                        printf(" euros producen unos intereses de %.1f", resultado);
                        printf(" euros." );
                    }

                    else

                    {
                        resultado=a*b*0.14;
                        printf("El usurero B es el mas conveniente.\n");
                        printf("Transcurridos %d",b);
                        printf(" meses, sus %d",a);
                        printf(" euros producen unos intereses de %.1f", resultado);
                        printf(" euros." );
                    }

    printf("\n");
    return 0;
}
