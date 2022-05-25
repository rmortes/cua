#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

#define N 18
#define VIVO 0
#define MUERTO 1
#define NoMINA_NoVISIBLE 2
#define MINA_NoVISIBLE 3
#define NoMINA_VISIBLE 4
#define MINA_VISIBLE 5

int Nivel (){
    int n;
    do{
        scanf("%d",&n);
        getchar();
        if(n<1 || n>3) printf("\nERROR. El valor introducido no se corresponde a ningun nivel. Introduzca nivel del 1 al 3: ");
    }while(n<1 || n>3);
    return n;
}

void InicioMatriz(int M[N][N],int *nminas){
    for (int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            //inicio todo sin minas
            M[j][i]=NoMINA_NoVISIBLE;
        }
    }
    //inicio monigote
    M[(N-1)/2][0]=VIVO;
    //minas
    while(*nminas>0){
        int a=rand()%N, b=rand()%N;
        if(M[a][b]==NoMINA_NoVISIBLE){
            M[a][b]=MINA_NoVISIBLE;
            *nminas=*nminas-1;
        }
    }
    return;
}

void Movimiento(int M[N][N],int *win,int *gameover, int *bomba){
    int X,Y;//posición monigote
    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
            if (M[j][i]==VIVO){
                X=j;
                Y=i;
            }

    char mov=getch();
    if(mov==-32 || mov==0) mov=getch();
    switch(mov){
    //tecla arriba
    case 72:
    case '8':
        if(Y>0){//para comprobar que no esté al principio
            M[X][Y]=NoMINA_VISIBLE;
            Y--;
        }
        break;
    //tecla abajo
    case 80:
    case '2':
        if(Y<N-1){ //para comprobar que no esté abajo del todo
            M[X][Y]=NoMINA_VISIBLE;
            Y++;
        }
        break;
    //telca izquierda
    case 75:
    case '4':
        if(X>0){ //para comprobar que no esté a la izquierda del todo
            M[X][Y]=NoMINA_VISIBLE;
            X--;
        }
        break;
    //tecla derecha
    case 77:
    case '6':
        if(X<N-1){ //para comprobar que no esté a la derecha del todo
            M[X][Y]=NoMINA_VISIBLE;
            X++;
        }
        break;
    //intro (bomba)
    case 13:
        int c=1;
        if(*bomba>-1){
            // 24 posiciones alrededor del monigote
            for (int i=Y-2;i<=Y+2;i++)
                for (int j=X-2;j<=X+2;j++){
                    if (j<0) j=0;
                    if (i<0) i=0;
                    if (M[j][i]==NoMINA_NoVISIBLE || M[j][i]==MINA_NoVISIBLE) c=0;
                }
            if (c==0){
                if (*bomba>0){
                    // 24 posiciones alrededor del monigote
                    for (int i=Y-2;i<=Y+2;i++)
                        for (int j=X-2;j<=X+2;j++){
                            if (j<0) j=0;
                            if (i<0) i=0;
                            switch (M[j][i]){
                            case NoMINA_NoVISIBLE:
                                M[j][i]=NoMINA_VISIBLE;
                                break;
                            case MINA_NoVISIBLE:
                                M[j][i]=MINA_VISIBLE;
                                break;
                            }
                        }
                }
                *bomba=*bomba-1;
            }
        }
        break;
    }
    //if donde el personaje se va a mover no hay mina lo movemos
    if(M[X][Y]!=MINA_NoVISIBLE && M[X][Y]!=MINA_VISIBLE){
        M[X][Y]=VIVO;
        //if ha llegado al final win
        if(Y==N-1) *win=1;
    //if donde queremos ponerlo hay mina, gameover
    }else{
        M[X][Y]=MUERTO;
        *gameover=1;
    }
    return;
}

char Again(void){
    char a[10];
    do{
        printf("\n\nTe echas otra? SI=S, NO=N: ");;
        gets(a);
        if (a[0]!='s' && a[0]!='S' && a[0]!='n' && a[0]!='N') printf("ERROR\n");
    }while(a[0]!='s' && a[0]!='S' && a[0]!='n' && a[0]!='N');
    return a[0];
}

void Print (int bomba,int M[N][N],int level){
    system("cls");
    if (bomba>-1) printf("Escapada del campo de minas. Nivel: %d. Bombas restantes: %d.\n------------------------------------------",level,bomba);
    else printf("Escapada del campo de minas.  Nivel: %d. NO TE QUEDAN BOMBAS!\n------------------------------------------",level);
    //mina más próxima
    int prox=9;
    for (int i=0;i<N;i++) {
        printf("\n");
        for(int j=0;j<N;j++)
            switch (M[j][i]){
            case VIVO:
                for(int mY=0;mY<N;mY++)
                    for(int mX=0;mX<N;mX++)
                        if(M[mX][mY]==MINA_VISIBLE || M[mX][mY]==MINA_NoVISIBLE) {
                            int v1,v2;
                            if ((j-mX)>0) v1=j-mX;
                            else v1=(-1)*(j-mX);
                            if ((i-mY)>0) v2=i-mY;
                            else v2=(-1)*(i-mY);
                            if (prox>v1+v2) prox=v1+v2;
                        }
                printf("%d",prox);
                break;
            case MUERTO:
                printf("X");
                break;
            case NoMINA_NoVISIBLE:
            case MINA_NoVISIBLE:
                printf("~");
                break;
            case NoMINA_VISIBLE:
                printf(" ");
                break;
            case MINA_VISIBLE:
                printf("M");
                break;
            }

    }
    return;
}

void EscapadaDelCampo (void){
    char otra;
    int M[N][N];
    do{
        int win=0,gameover=0;
        system("cls");
        printf("Vietnam 1973. Escapada del campo de minas.\n------------------------\nIntroduzca nivel (1-3): ");
        int bomba=2;
        int level=Nivel();
        //numero de minas según nivel
        int nminas=((N*N)*level)/10;
        InicioMatriz(M,&nminas);

        while(win==0 && gameover==0){
            Print(bomba,M,level);
            Movimiento(M,&win,&gameover,&bomba);
        }
        Print(bomba,M,level);
        otra=Again();
    }while(otra=='s' || otra=='S');

    return;
}

int main (void){
    srand(time(NULL));
    EscapadaDelCampo();
    return 0;
}
