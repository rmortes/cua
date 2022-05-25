#include <stdio.h>
#include <string.h>

int main (){

    //Declaracion de variables y pedida de datos
    int dia, mes, ano, cuota;
    char  mesdefinitivo[20];

    printf("Introduzca fecha del prestamo (dd/mm/aaaa): ");
    scanf("%d/%d/%d",&dia,&mes,&ano);

    if (dia>30 || dia<1 || mes>12 || mes<1 || ano>2100 || ano<1900){
        printf( "Error: La fecha es incorrecta \n");

    }else{
        printf("Introduzca numero de cuotas del prestamo: ");
        scanf("%d",&cuota);
        if(cuota>1200 || cuota<1)
        {
            printf("Error: Dato incorrecto \n");
        }else{
            int total = mes-1+ano*12+cuota;
            int mescuotafinaliza= total%12;
            int anodefinitivo= total/12;

            //Acabará en año+año a sumar
            switch(mescuotafinaliza){
            case 0: strcpy( mesdefinitivo,"enero"); break;
            case 1: strcpy( mesdefinitivo,"febrero"); break;
            case 2: strcpy( mesdefinitivo,"marzo"); break;
            case 3: strcpy( mesdefinitivo,"abril"); break;
            case 4: strcpy( mesdefinitivo,"mayo"); break;
            case 5: strcpy( mesdefinitivo,"junio"); break;
            case 6: strcpy( mesdefinitivo,"julio"); break;
            case 7: strcpy( mesdefinitivo,"agosto"); break;
            case 8: strcpy( mesdefinitivo,"septiembre"); break;
            case 9: strcpy( mesdefinitivo,"octubre"); break;
            case 10: strcpy( mesdefinitivo,"noviembre"); break;
            case 11: strcpy( mesdefinitivo,"diciembre"); break;
            }


            printf("El prestamo finaliza el dia %d de %s de %d\n",dia, mesdefinitivo,anodefinitivo);
        }

    }

    return(0);
}
