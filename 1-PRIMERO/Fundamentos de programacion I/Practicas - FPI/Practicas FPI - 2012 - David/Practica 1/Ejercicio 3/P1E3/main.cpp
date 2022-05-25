#include <stdio.h>
int main(void)
{
    int a;
    int u;
    int d;
    int c;

    c=a/100;
    a=a-c*100;
    d=a/10;
    u=a-d/10;

    printf("Introduzca un valor entre 1 y 999: ");
    scanf("%d",&a);

    if(a<0 && a>999){
        printf("Error");}
    else{
        switch(c){
        case 1: if(u==0 && d==0){
                printf("Cien");}
            else{printf("ciento");}        break;
        case 2: printf("doscientos");      break;
        case 3: printf("Trescientos");     break;
        case 4: printf("Cuatrocientos");   break;
        case 5: printf("Quinientos");      break;
        case 6: printf("Seiscientos");     break;
        case 7: printf("Setecientos");     break;
        case 8: printf("Ochocientos");     break;
        case 9: printf("Novecientos");     break;
        default:                           break;
        }
        switch(d){
        case 1: switch(u){
                case 0: printf("diez"); 		break;
                case 1: printf("Once"); 		break;
                case 2: printf("Doce"); 		break;
                case 3: printf("Trece"); 		break;
                case 4: printf("catorce");	 	break;
                case 5: printf("quince"); 		break;
                default: printf("diez y %d", u); 	break;
                }  break;

        case 2: if(u==0){printf("veinte");
            }else{printf("Veinte y %d",u);}          break;

        case 3: if(u==0){printf("Treinta");
            }else{printf("Treinta y %d",u);}	     break;

        case 4: if(u==0){printf("Cuarenta");
            }else{printf("Cuarenta y %d",u);}        break;

        case 5: if(u==0){printf("Cincuenta");
            }else{printf("Cincuenta y %d",u);}       break;

        case 6: if(u==0){printf("Sesenta");
            }else{printf("Sesenta y %d",u);}         break;

        case 7: if(u==0){printf("Setenta");
            }else{printf("Setenta y %d",u);}         break;

        case 8: if(u==0){printf("Ochenta");
            }else{printf("Ochenta y %d",u);}         break;

        case 9: if(u==0){printf("Noventa");
            }else{printf("Noventa y %d",u);}         break;

        default: 				     break;
        }

        switch(u){
        case 1: printf("uno");          break;
        case 2: printf("dos");          break;
        case 3: printf("tres");         break;
        case 4: printf("cuatro");       break;
        case 5: printf("cinco");        break;
        case 6: printf("seis");         break;
        case 7: printf("siete");        break;
        case 8: printf("ocho");         break;
        case 9: printf("nueve");        break;
        default: break;
        }
    }
    getchar();
    getchar();
    return (0);
}
