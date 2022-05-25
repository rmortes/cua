#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define B 100
#define C 20
//funcion crear el bombo de numeros
void BOMBO(int bombo[B]){
    //vector rellenado del 1 al 100
    for(int i=0;i<99;i++){
        bombo[i]=(i+1);
    }
    //cambiamos el orden de los numeros
    for(int i=0;i<100000;i++){
        int a=rand()%99;
        int b=rand()%99;
        int aux=bombo[a];
        bombo[a]=bombo[b];
        bombo[b]=aux;
    }

    return;
}

//funcion para comprobar el carton1
void comprobar1(int carton1[C],int*acaba,int b){
    //LEER EL VECTOR PAREA VER SI SON TODO X
    for(int i=0;i<=20;i++){
        if(carton1[i]==(-1)){
            b=b+1;
        }
    }
    //final gana jugador 2
    if(b==20){
        *acaba=3;
    }
    return;
}

//funcion para comprobar el carton2
void comprobar2(int carton2[C],int*acaba,int t){
    //LEER EL VECTOR PAREA VER SI SON TODO X
    for(int i=0;i<=20;i++){
        if(carton2[i]==(-1)){
            t=t+1;
        }
    }

    //final gana jugador 2
    if(t==20){
        *acaba=2;
    }
    return;
}

//funcion imprime los cartones
void imprimir(int carton1[C],int carton2[C],int bombo[B],int pos){

    //recorro el vector de carton1 y compruebo si coincide
    for(int i=0;i<20;i++){
        if(carton1[i]==bombo[pos]){//si coincide con el valor en la posicion es una x
            carton1[i]=(-1);
        }else{
            carton1[i]=carton1[i];//si no coincide se vuelve a su valor
        }
    }
    //imprimimos el carton1
    printf("\nCARTON 1: \n");
    for(int i=1;i<=20;i++){
        if(carton1[i-1]==(-1)){
            printf("  X");
        }else{
            printf("%3d",carton1[i-1]);
        }
        if((i%5)==0){
            printf("\n");
        }
    }
    printf("\n\n");
    //recorro el vector de carton2 y compruebo si coincide
    for(int i=0;i<20;i++){
        if(carton2[i]==bombo[pos]){//si coincide con el valor en la posicion es una x
            carton2[i]=(-1);
        }else{
            carton2[i]=carton2[i];//si no coincide se vuelve a su valor
        }
    }
    //imprimimos el carton2
    printf("\nCARTON 2: \n");
    for(int i=1;i<=20;i++){
        if(carton2[i-1]==(-1)){
            printf("  X");
        }else{
            printf("%3d",carton2[i-1]);
        }
        if((i%5)==0){
            printf("\n");
        }
    }
    printf("\n\n");


    return;
}

//funcion para crear los cartones
void CARTON(int carton1[C],int carton2[C],int bombo[B]){
    //llamando a esta funcion nos sale un bombo diferente al anterior
    BOMBO(bombo);
    //me quedo con los 20 primero para rellenar
    for(int i=0;i<C;i++){
        carton1[i]=bombo[i];
    }
    //llamando a esta funcion nos sale un bombo diferente al anterior
    BOMBO(bombo);
    //me quedo con los 20 primero para rellenar
    for(int i=0;i<C;i++){
        carton2[i]=bombo[i];
    }

    return;
}

void juego(){
    srand(time(NULL));
    int carton1[C];
    int carton2[C];
    int bombo[B];
    int pos=0;
    int acaba=0;
    int t=0;
    int b=0;
    CARTON(carton1,carton2,bombo);//aqui bien porque asi me sale revuelto los numeros
    BOMBO(bombo);
    do{
        system("cls");
        printf("-----------------------------\n\n\tJUEGO DEL BINGO\n\n-----------------------------\n\n");
        printf("Bolas:");//aqui sale el vector que hemos rellenado en la función
        //imprimimos el bombo
        for(int i=0;i<pos;i++){//los numeros van saliendo cada jugada
            printf("%d",bombo[i]);
            printf(" ");
        }
        printf("\n\n");
        //imprimimos cartones
        imprimir(carton1,carton2,bombo,pos);
        pos++;//incrementamos una bola
        getche();//para la pulsacion y que saque una nueva bola
        comprobar1(carton1,&acaba,b);
        comprobar2(carton2,&acaba,t);
    }while(acaba==0);

    if(acaba==2){
        printf("Ha ganado el jugador 2");
    }
    if(acaba==3){
        printf("Ha ganado el jugador 1");
    }
    return;
}


int main(void){
    juego();
    getche();
    return(0);
}
