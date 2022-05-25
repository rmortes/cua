#include <stdio.h>

int main(void){
    int a;
    //Introduce el numero en una variable.
    printf("Introduzca su numero entre comprendidos entre 1 y 100:  \t");
    scanf("%d",&a);
    //Comprueba si mientes si esta en el rango.
    if(a<=0){
        printf("El numero introducido es menor a 1\n");
    }if(a>=101){
        printf("Su numero escrito es mayor a 100\n");
    }if(a==1){
        printf("El numero uno no esta considerado como primo \n");
    }
    //Muestra los numeros primos.
    if(a==2||a==3||a==5||a==7||a==11||a==13||a==17||a==19||a==23||a==29||a==31||a==37||a==41||a==43||a==47||a==53||a==59||a==61||a==67||a==71||a==73||a==79||a==83||a==89||a==97){
        printf("El numero es primo\nSolo es posible dividirlo entre 1 y ellos mismos\n\n");
    }
    //Muestra los numeros divididos.
    if(a==4){
        printf("Los divisores de este numero son:\t2\n\n");
    }
    if(a==9){
        printf("Los divisores de este numero son:\t3\n\n");
    }
    if(a==6){
        printf("Sus divisores:\t2 y 3\n\n");
    }
    if(a==8){
        printf("Los divisores de este numero son:\t2 y 4\n\n");
    }
    if(a==10){
        printf("Sus divisores:\t 2 y 5 \n\n");
    }
    if(a==12){
        printf("Sus divisores:\t2, 3, 4 y 6\n\n");
    }
    if(a==14){
        printf("Sus divisores:\t2 y 7\n\n");
    }
    if(a==15){
        printf("Sus divisores:\t3 y 5\n\n");
    }
    if(a==16){
        printf("Sus divisores:\t2, 4 y 8\n\n");
    }
    if(a==18){
        printf("Sus divisores:\t2, 3, 6 y 9\n\n");
    }
    if(a==20){
        printf("Sus divisores:\t2, 4, 5 y 10\n\n");
    }
    if(a==21){
        printf("Sus divisores:\t3 y 7\n\n");
    }
    if(a==22){
        printf("Sus divisores:\t2 y 11\n\n");
    }
    if(a==24){
        printf("Sus divisores:\t2, 3, 4, 6, 8 y 12\n\n");
    }
    if(a==25){
        printf("Sus divisores:\t 5 \n\n");
    }
    if(a==26){
        printf("Sus divisores:\t2 y 13\n\n");
    }
    if(a==27){
        printf("Sus divisores:\t3 y 9\n\n");
    }
    if(a==28){
        printf("Sus divisores:\t2, 4, 7 y 14\n\n");
    }
    if(a==30){
        printf("Sus divisores:\t2, 3, 5, 6, 10 y 15\n\n");
    }
    if(a==32){
        printf("Sus divisores:\t2, 4, 8 y 16\n\n");
    }
    if(a==33){
        printf("Sus divisores:\t3 y 11\n\n");
    }
    if(a==34){
        printf("Sus divisores:\t2 y 17\n\n");
    }
    if(a==35){
        printf("Sus divisores:\t5 y 7\n\n");
    }
    if(a==36){
        printf("Sus divisores:\t2, 4, 6, 9 y 18\n\n");
    }
    if(a==38){
        printf("Sus divisores:\t2 y 19\n\n");
    }
    if(a==39){
        printf("Sus divisores:\t3 y 13\n\n");
    }
    if(a==40){
        printf("Sus divisores:\t2, 4, 5, 8, 10 y 20\n\n");
    }
    if(a==42){
        printf("Sus divisores:\t2, 6, 7 y 21\n\n");
    }
    if(a==44){
        printf("Sus divisores:\t2, 4, 11 y 22\n\n");
    }
    if(a==45){
        printf("Sus divisores:\t3, 5, 9 y 15\n\n");
    }
    if(a==46){
        printf("Sus divisores:\t2 y 23\n\n");
    }
    if(a==48){
        printf("Sus divisores:\t2, 3, 4, 6, 8, 12, 16 y 24\n\n");
    }
    if(a==49){
        printf("Sus divisores:\t 7 \n\n");
    }
    if(a==50){
        printf("Sus divisores:\t2, 5, 10 y 25\n\n");
    }
    if(a==51){
        printf("Sus divisores:\t13 y 17\n\n");
    }
    if(a==52){
        printf("Sus divisores:\t2, 4, 13 y 26\n\n");
    }
    if(a==54){
        printf("Sus divisores:\t2, 3, 6, 9, 18 y 27\n\n");
    }
    if(a==55){
        printf("Sus divisores:\t5 y 11\n\n");
    }
    if(a==56){
        printf("Sus divisores:\t2, 4, 7, 8, 14 y 28\n\n");
    }
    if(a==58){
        printf("Sus divisores:\t2 y 29\n\n");
    }
    if(a==60){
        printf("Sus divisores:\t2, 3, 4, 5, 6, 10, 15, 20 y 30\n\n");
    }
    if(a==62){
        printf("Sus divisores:\t2 y 31\n\n");
    }
    if(a==63){
        printf("Sus divisores:\t3, 7, 9 y 21\n\n");
    }
    if(a==64){
        printf("Sus divisores:\t2, 4, 8, 16 y 32\n\n");
    }
    if(a==65){
        printf("Sus divisores:\t5 y 13\n\n");
    }
    if(a==66){
        printf("Sus divisores:\t2, 3, 6, 11, 22 y 33\n\n");
    }
    if(a==68){
        printf("Sus divisores:\t2, 4, 17 y 24\n\n");
    }
    if(a==69){
        printf("Sus divisores:\t3 y 23\n\n");
    }
    if(a==70){
        printf("Sus divisores:\t2, 5, 7, 10, 14 y 35\n\n");
    }
    if(a==72){
        printf("Sus divisores:\t2, 3, 4, 6, 8, 9, 12, 18, 24 y 36\n\n");
    }
    if(a==74){
        printf("Sus divisores:\t2 y 37\n\n");
    }
    if(a==75){
        printf("Sus divisores:\t5 y 15\n\n");
    }
    if(a==76){
        printf("Sus divisores:\t2, 4, 19 y 38\n\n");
    }
    if(a==77){
        printf("Sus divisores:\t7 y 11\n\n");
    }
    if(a==78){
        printf("Sus divisores:\t2, 3, 6, 13, 26 y 39\n\n");
    }
    if(a==80){
        printf("Sus divisores:\t2, 4, 5, 8, 10, 16, 20 y 40\n\n");
    }
    if(a==81){
        printf("Sus divisores:\t3, 9 y 27\n\n");
    }
    if(a==82){
        printf("Sus divisores:\t2 y 41\n\n");
    }
    if(a==84){
        printf("Sus divisores:\t2, 4, 21 y 42\n\n");
    }
    if(a==85){
        printf("Sus divisores:\t5 y 17\n\n");
    }
    if(a==86){
        printf("Sus divisores:\t2 y 43\n\n");
    }
    if(a==87){
        printf("Sus divisores:\t3 y 29\n\n");
    }
    if(a==88){
        printf("Sus divisores:\t2, 4, 8, 11, 22 y 44\n\n");
    }
    if(a==90){
        printf("Sus divisores:\t2, 3, 5, 6, 9, 10, 15, 18, 30 y 45\n\n");
    }
    if(a==91){
        printf("Sus divisores:\t7 y 13\n\n");
    }
    if(a==92){
        printf("Sus divisores:\t2 y 46\n\n");
    }
    if(a==93){
        printf("Sus divisores:\t3 y 31\n\n");
    }
    if(a==94){
        printf("Sus divisores:\t2 y 47\n\n");
    }
    if(a==95){
        printf("Sus divisores:\t5 y 19\n\n");
    }
    if(a==96){
        printf("Sus divisores:\t2, 3, 4, 6, 8, 12, 16, 24, 32 y 48\n\n");
    }
    if(a==98){
        printf("Sus divisores:\t2, 7, 14 y 49\n\n");
    }
    if(a==99){
        printf("Sus divisores:\t3, 9, 11 y 33\n\n");
    }
    if(a==100){
        printf("Sus divisores:\t2, 4, 5, 10, 20, 25 y 50\n\n");
    }
    return(0);
}
