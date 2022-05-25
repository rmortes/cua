#include <stdio.h>

int main(void){
    int a;
    //Introduce un número muestra las posiciones en las que lo quieres ver.
    printf("Introduce su numero,(el numero ha de estar comprendido entre 1y3):\t");
    scanf("%d",&a);
    getchar();
    if(a>0 && a<4){
        //Los casos de las posiciones de las letras.
        switch(a){
        case 1:
            printf("\nJ o r g e\n");
            break;
        case 2:
            printf("\nJ\n o\n  r\n   g\n    e\n");
            break;
        case 3:
            printf("\nJ\no\nr\ng\ne\n\n");
            break;
        }
    }else{
        printf("Error al introducir el numero\n");
    }
    return 0;
}
