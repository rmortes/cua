#include<stdlib.h>
#include<stdio.h>
#include<conio.h>
#include<math.h>

int main(void){
    int d1,m1,a1,d2,m2,a2;
    printf("Introduzca la fecha de su nacimiento(dd/mm/aaaa): ");
    scanf("%d/%d/%d",&d1,&m1,&a1);
    getchar();
    printf("Introduzca la fecha actual (dd/mm/aaaa): ");
    scanf("%d/%d/%d",&d2,&m2,&a2);
    getchar();
    if(a2>a1){
        //Dias transcurridos desde el 0 hasta tu cumpleaños
        int dia1=d1+(m1*30)+(a1*360);
        //Dias transcurridos desde el 0 hasta la fecha actual
        int dia2=d2+(m2*30)+(a2*360);
        if(dia2>dia1){
            //Edad que tienes
            int dia3=(dia2-dia1);
            int anyo=(dia3/360);
            int mes=(dia3%360)/30;
            int dia= dia3%30;
            printf("Tu edad es de %d anyos, %d meses y %d dias.\n",anyo,mes,dia);

            //Meses y dias para tu cumpleaños
           int dias6=(((30-d2)+d1)%30);
            int meses;
            if(m1-m2>0){
                meses=m1-m2;
                if(d1<d2){
                    meses=(dias6/30)+(meses-1);
                }else{
                    meses=meses+(dias6/30);
                }
            }else{
                meses=12+(m1-m2);
                if(d1<d2){
                    meses=(dias6/30)+(meses-1);
                }else{//si d1>d2
                    meses=meses+(dias6/30);
                }
            }
            printf("Faltan %d meses y %d dias para tu cumpleanyos.\n",meses,dias6);

        }else{
            printf("Error.La segunda fecha debe ser mayor que la primera\n");
        }
    }else{
        printf("Error.La segunda fecha debe ser mayor que la primera\n");
    }
    getche();
    return(0);
}

