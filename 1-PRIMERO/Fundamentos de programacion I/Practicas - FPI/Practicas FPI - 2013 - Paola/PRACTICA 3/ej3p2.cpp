#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<conio.h>

int main(void){
    int a;
    printf("Ejercicio 3-Practica 2\n");
    do{
        printf("Introduzca el caracol por el que apuesta(1-4):");
        scanf("%d",&a);
        getchar();
    }while(a<1 || a>4);
    //inicializamos
    int pos1=0;
    int pos2=0;
    int pos3=0;
    int pos4=0;
    do{
        system("cls");
        int c=rand()%4;
        switch(c){
        case 0:
            //caracol1
            if((rand()%100)>=20){//se mueve
                if((rand()%100)>=30){//hacia delante
                    pos1++;
                }else if(pos1>0){//hacia atras
                    pos1--;
                }
            }
            break;
        case 1:
            //caracol2
            if(rand()%100>=20){//se mueve
                if(rand()%100>=30){//hacia delante
                    pos2++;
                }else if(pos2>0){//hacia atras
                    pos2--;
                }
            }
            break;
        case 2:
            //caracol3
            if(rand()%100>=20){//se mueve
                if(rand()%100>=30){//hacia delante
                    pos3++;
                }else if(pos3>0){
                    pos3--;
                }
            }
            break;
        case 3:
            //caracol4
            if(rand()%100>=20){//se mueve
                if(rand()%100>=30){//hacia delante
                    pos4++;
                }else if(pos4>0){
                    pos4--;
                }
            }
            break;
        }
        //imprimimos caracol1
        for(int i=0;i<pos1;i++){ //espacios de delante
            printf(" ");
        }
        printf("@v");
        for(int i=pos1;i<35;i++){//espacios de detras
            printf(" ");
        }
        printf("M\n");
        //imprimimo caracol2
        for(int i=0;i<pos2;i++){//espacios de delante
            printf(" ");
        }
        printf("@v");
        for(int i=pos2;i<35;i++){//espacios de detras
            printf(" ");
        }
        printf("E\n");
        //imprimimos caracol 3
        for(int i=0;i<pos3;i++){//espacios de delante
            printf(" ");
        }
        printf("@v");
        for(int i=pos3;i<35;i++){//espacios de detras
            printf(" ");
        }
        printf("T\n");
        //imprimimos caracol 4
        for(int i=0;i<pos4;i++){//espacios de delante
            printf(" ");
        }
        printf("@v");
        for(int i=pos4;i<35;i++){//espacios de detras
            printf(" ");
        }
        printf("A\n");
    }while(pos1<35 && pos2<35 && pos3<35 && pos4<35);

    if(((a==1) && (pos1==35)) || ((a==2) && (pos2==35)) || ((a==3) && (pos3==35)) || ((a==4) && (pos4==35))){
        printf("Enhorabuena.Has ganado!!");
    }else if(pos1==35){
        printf("Lo sentimos.El caracol ganador ha sido el 1");
    }else if(pos2==35){
        printf("Lo sentimos.El caracol ganador ha sido el 2");
    }else if(pos3==35){
        printf("Lo sentimos.El caracol ganador ha sido el 3");
    }else if(pos4==35){
        printf("Lo sentimos.El caracol ganador ha sido el 4");
    }
    getche();
    return(0);
}
