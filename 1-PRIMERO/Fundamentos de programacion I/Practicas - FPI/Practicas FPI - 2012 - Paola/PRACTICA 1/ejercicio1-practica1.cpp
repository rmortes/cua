#include<stdio.h>
#include<conio.h>
#include<math.h>
int main (void){
    int a,b,c;
    char o;
    printf("-------------\nCALCULADORA\n-------------\n");
    printf("introduzca primer operando:");
    scanf("%d",&a);
    getchar();
    printf("introduzca operacion (+,-,* o /):");
    scanf("%c",&o);
    getchar();
    printf("introduzca seegunda operando:");
    scanf("%d",&b);
    getchar();


    switch(o){
    case '+':
        printf("RESULTADO %d",c=a+b);
        scanf("%d",&c);
        break;
    case  '-':
        printf("RESULTADO %d",c=a-b);
        scanf("%d",&c);
        break;
    case '*':
        printf("RESULTADO %d",c=a*b);
        scanf("%d",&c);
        break;
    case '/':
        if(b==0){
            printf("error:no es posible");
        }else{
            printf("resultado %d", &c);
        }
        break;
    default:
        printf("error:el carácter no es válido");
        break;
    }

    getche();
    return(0);
}
