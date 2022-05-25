#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>

#define N 11 //N=nºenemigos
#define Tierra 20 //Dist.Suelo

int Repetir(){
    char rep[10];
    int cent=0;
    printf("\nPulse introduzca \"Y\" para repetir el programa:");
    scanf("%s",rep);
    getchar();
    strupr(rep);
    if(strcmp(rep,"Y")==0){
        cent=1;
    }
    return(cent);
}
int AlienMov(void){
    int mov,aux=0;
    mov=rand()%100;
    if (mov<50){
        aux=1;
    }
    return aux;
}
void AlienPos(int extra[N],int*inv){
    *inv=1;
    for(int i=0;i<N;i++){
        if(AlienMov()){
            extra[i]++;
            if(extra[i]==Tierra-1){
                *inv=0;
            }
        }
    }
    return;
}
int NavePos(int*navepos0,int extra[],int*cont){
    char tecla=getch();
    if(tecla==-32||tecla==0)tecla=getch();
    switch (tecla){
    //izq
    case 75:
    case '4':
        if(*navepos0!=0){
            *navepos0=*navepos0-1;
        }
        break;
        //dch
    case 77:
    case '6':
        if(*navepos0<N-1){
            *navepos0=*navepos0+1;
        }
        break;
        //enter
    case 13:
        extra[*navepos0]=0;
        *cont=*cont+1;
        break;
    }
    return *navepos0;
}
void Alien0(int extra[N]){
    for(int i=0;i<N;i++){
        extra[i]=0;
    }
    return;
}
void AlienPrint(char pos[],int extra[N]){
    for(int j=0;j<Tierra;j++){
        for(int i=0;i<N;i++){
            if(j==extra[i]){
                strcat(pos," =^.^= ");
            }else{
                strcat(pos,"       ");
            }
        }
        strcat(pos,"\n");
    }
    return;
}
void NavePrint(char pos[],int navepos){
    for(int i=0;i<N;i++){
        if(navepos==i){
            strcat(pos," /\\|/\\ ");
        }else{
            strcat(pos,"       ");
        }
    }
    return;
}
void Imprime(int navepos,int extra[],int *cont){
    //Cadena contenedora
    char pos [80*24] = "";
    system("cls");
    sprintf(pos,"Invasion de gatitos. Gatitos muertos:%d\n",*cont);
    for(int i=0;i<7*N;i++){
        strcat(pos,"-");
    }
    strcat(pos,"\n");
    AlienPrint(pos,extra);
    NavePrint(pos,navepos);
    strcat(pos,"\n");
    for(int i=0;i<7*N;i++){
        strcat(pos,"-");
    }
    printf("%s",pos);
    return;
}
//inicialización de la partida
void juego0(int extra[]){
    int inv=0,cont=0;
    //La nave comienza en la mitad
    int navepos0=N/2;
    //Los aliens cominzan arriba
    Alien0(extra);
    Imprime(navepos0,extra,&cont);
    do{
        AlienPos(extra,&inv);
        Imprime(NavePos(&navepos0,extra,&cont),extra,&cont);
    }while(inv);
}
int main(void){
    do{
        int extra[N];
        juego0(extra);
    }while(Repetir());
    return(0);
}
