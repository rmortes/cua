#include <stdio.h>
#include <conio.h>
int main (){
    int dia,mes,anyo;
    printf("introduzca fecha dd/mm/aaaa:");
    scanf("%d/%d/%d",&dia,&mes,&anyo);

    if(dia<=0 || dia>=32 || mes<=0 || mes>=13 || anyo<=1899 || anyo>=2101){
        printf("ERROR:la fecha introducida no es correcta");
    }else{
        if (dia<=15){
            printf("primera quincena de ");
        }else{
            printf("segunda quincena de ");
        }
        switch(mes){
        case 1 :
            printf("ENERO");
            break;
        case 2 :
            printf("FEBRERO");
            break;
        case 3 :
            printf("MARZO");
            break;
        case 4 :
            printf("ABRIL");
            break;
        case 5 :
            printf("MAYO");
            break;
        case 6 :
            printf("JUNIO");
            break;
        case 7 :
            printf("JULIO");
            break;
        case 8 :
            printf("AGOSTO");
            break;
        case 9 :
            printf("SEPTIEMBRE");
            break;
        case 10 :
            printf("OCTUBRE");
            break;
        case 11 :
            printf("NOVIEBRE");
            break;
        case 12 :
            printf("DICIEMBRE");
            break;
        default :
                printf("error");
        break;

    }
        printf(" de %d", anyo);
        scanf("%d",&anyo);
    }
    getche();
    return (0);
}
