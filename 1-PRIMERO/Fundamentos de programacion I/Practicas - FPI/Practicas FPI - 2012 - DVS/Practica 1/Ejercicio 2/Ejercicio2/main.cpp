
#include <stdio.h>

int main(void)
{
    int dd, mm, aaaa;
    printf("Introduce una fecha en formato dd/mm/aaaa:\n");
    scanf("%d/%d/%d", &dd, &mm, &aaaa);
    getchar();

    if(dd<1 && dd>31 && mm<1 && mm>12 && aaaa<1900 && aaaa>2100){
        printf("Error");
    }else{
        if(dd>1 && dd<15){
            printf("Primera quincena de ");}
        else{
            printf("Segunda quincena de ");}

        switch(mm){
        case 1: printf("Enero de ");        break;
        case 2: printf("Febrero de ");      break;
        case 3: printf("Marzo de ");        break;
        case 4: printf("Abril de ");        break;
        case 5: printf("Mayo de ");         break;
        case 6: printf("Junio de ");        break;
        case 7: printf("Julio de ");        break;
        case 8: printf("Agosto de ");       break;
        case 9: printf("Septiembre de ");   break;
        case 10: printf("Octubre de ");     break;
        case 11: printf("Noviembre de ");   break;
        default: printf("Diciembre de ");   break;
                  }
        printf("%d",aaaa);
         }
    getchar();
    getchar();
    return 0;
}
