//Se incluyen las librerias necesarias
#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>

/*Definimos las constantes, numero de filas y numero de columnas
    Gracias a ello, se puede montar una tabla de cualquier tamaño,
    manteniendo totalmente operativo el programa.
    Ademas definimos el porcentaje de poblacion como constante para
    modificarlo en cualquier momento*/

#define NFIL 20
#define NCOL 20
#define DISPERSA 10
#define NORMAL 25
#define DENSA 50
#define MASIFICADA 75

void Imprimir(int Matriz[NFIL][NCOL]){
    //Declaración de variables
    int i,j;
    //Recorremos la matriz
    for(i=0;i<NFIL;i++){
        for(j=0;j<NCOL;j++){
            //Si es 0 la celula esta muerta, por lo que se imprime un punto
            if(Matriz[i][j]==0){
                printf(". ");
            }
            //Si no, esta viva, por lo que se imprime un asterisco
            else{
                printf("* ");
            }
        }
        //Salto de linea al llegar al final de la fila
        printf("\n");
    }
}
void Duplicar(int ori[NFIL][NCOL], int dest[NFIL][NCOL]){
    //Recorremos la matriz
    for(int i=0;i<NFIL;i++)
        for(int j=0;j<NCOL;j++)
            //Copiamos la matriz origen en destino
            dest[i][j]=ori[i][j];
}
void Refrescar(int Matriz[NFIL][NCOL]){
    //Declaracion las variables
    int copiamatriz[NFIL][NCOL];
    int NUMcelulasvivas=0,i,j;
    //Copiamos la matriz en una copia auxiliar
    Duplicar(Matriz, copiamatriz);
    for(i=0;i<NFIL;i++){
        for(j=0;j<NCOL;j++){
            //Control de las celulas vecinas vivas
            if(i>0 && j>0 && Matriz[i-1][j-1]==1){
                NUMcelulasvivas++;
            }
            if(i>0 && Matriz[i-1][j]==1){
                NUMcelulasvivas++;
            }
            if(i>0 && j<NCOL && Matriz[i-1][j+1]==1){
                NUMcelulasvivas++;
            }
            if(j>0 && Matriz[i][j-1]==1){
                NUMcelulasvivas++;
            }
            if(j<NCOL && Matriz[i][j+1]==1){
                NUMcelulasvivas++;
            }
            if(i<NFIL && j>0 && Matriz[i+1][j-1]==1){
                NUMcelulasvivas++;
            }
            if(i<NFIL && Matriz[i+1][j]==1){
                NUMcelulasvivas++;
            }
            if(i<NFIL && j<NCOL && Matriz[i+1][j+1]==1){
                NUMcelulasvivas++;
            }
            //Actuamos sobre las celulas en la copia de la matriz
            if(Matriz[i][j]==1){
                //La celulas vivas con 2 o 3 celulas vivas pegadas, se mantiene vivas.
                if(NUMcelulasvivas==2 || NUMcelulasvivas==3){
                    copiamatriz[i][j]=1;
                }
                //Si no se cumple la condicion, mueren.
                else{
                    copiamatriz[i][j]=0;
                }
            }
            else{
                //Las celulas muertas con 3 celulas vivas pegadas, resucitan.
                if(NUMcelulasvivas==3){
                    copiamatriz[i][j]=1;
                }
            }
            //Ponemos a 0 el contador
            NUMcelulasvivas=0;
        }
    }
    //Devolvemos los nuevos datos a la matriz original
    Duplicar(copiamatriz, Matriz);
}
void Resucitar(int Matriz[NFIL][NCOL]){
    //Declaración de variables
    int i,j,a,b;
    do{
        printf("Introduce fila <1-%d>: ", NFIL);
        i=getche()-48;
        fflush(stdin);
    }while(i<1 || i>NFIL);
    do{
        printf("\nIntroduce columna <1-%d>: ", NCOL);
        j=getche()-48;
        fflush(stdin);
    }while(j<1 || j>NCOL);
    //Copiamos la el valor de la celula, para poder revertir el cambio
    a=Matriz[i-1][j-1];
    //Resucitamos la celula seleccionada
    Matriz[i-1][j-1]=1;
    system("cls");
    Imprimir(Matriz);
    //Preguntamos si se desea mantener la seleccion
    printf("\nCompruebe la seleccion, desea mantenerla? [s/n]");
    b=getch();
    //Limpiamos el buffer
    fflush(stdin);
    //Si no se mantiene, se devuelve el valor de la celula copiada anteriormente
    if(b=='n') Matriz[i-1][j-1]=a;
}
void Patron(int Matriz[NFIL][NCOL]){
    //Se imprime el patron "Barco" (Boat)
    //Las posiciones se interpretan: Primer numero--> Fila, Segundo numero-->Columna
    Matriz[NFIL-(NFIL/2+1)][NCOL-(NCOL/2+1)]=1; //1 Posicion (1,1) del patron
    Matriz[NFIL-(NFIL/2+1)][NCOL-(NCOL/2)]=1;   //2 Posicion (1,2) del patron
    Matriz[NFIL-(NFIL/2+1)][NCOL-(NCOL/2-1)]=0; //3 Posicion (1,3) del patron
    Matriz[NFIL-NFIL/2][NCOL-(NCOL/2+1)]=1;     //4 Posicion (2,1) del patron
    Matriz[NFIL-(NFIL/2)][NCOL-(NCOL/2)]=0;     //5 Posicion (2,2) del patron
    Matriz[NFIL-(NFIL/2)][NCOL-(NCOL/2-1)]=1;   //6 Posicion (2,3) del patron
    Matriz[NFIL-(NFIL/2-1)][NCOL-(NCOL/2+1)]=0; //7 Posicion (3,1) del patron
    Matriz[NFIL-(NFIL/2-1)][NCOL-(NCOL/2)]=1;   //8 Posicion (3,2) del patron
    Matriz[NFIL-(NFIL/2-1)][NCOL-(NCOL/2-1)]=0; //9 Posicion (3,3) del patron
}
void Juego(){
    //Declaración de variables
    int poblacion,i,j,filas,columnas,repetir,confirmar;
    int Matriz [NFIL][NCOL];
    //Menu inicial
    do{
        system("cls");
        do{
            printf("\n\tNivel de poblacion:\n");
            printf("\n\t1-Dispersa\n");
            printf("\t2-Normal\n");
            printf("\t3-Densa\n");
            printf("\t4-Masificada\n");
            poblacion=getch();
            //Limpiamos el buffer
            fflush(stdin);
            //Limpiamos pantalla
            system ("cls");
        }
        //Solo son validos los valores correspondientes a las opciones del menu
        while(!(poblacion=='1' || poblacion=='2' || poblacion=='3' || poblacion=='4'));
        //Ponemos todas las celulas muertas inicialmente
        for(i=0;i<NFIL;i++){
            for(j=0;j<NCOL;j++){
                Matriz [i][j]=0;
            }
        }
        //Aplicamos los porcentajes de poblacion sobre el total de celulas
        if(poblacion=='1'){
            poblacion=(((NFIL*NCOL)/100)*DISPERSA);
        }
        else if(poblacion=='2'){
            poblacion=(((NFIL*NCOL)/100)*NORMAL);
        }
        else if(poblacion=='3'){
            poblacion=(((NFIL*NCOL)/100)*DENSA);
        }
        else poblacion=(((NFIL*NCOL)/100)*MASIFICADA);
        //Modo aleatorio

        for(i=0;i<poblacion;i++){
            filas=rand()%20;
            columnas=rand()%20;
            //Si la celula esta muerta, la resucita
            if(Matriz [filas][columnas]==0){
                Matriz[filas][columnas]=1;
            }
            /*Si ya estaba viva se mantiene, y no lo contamos como
            una posicion añadida, asi aseguramos que se impriman el
            numero de celulas vivas seleccionado. Por ello restamos uno
            al contador*/
            else
                i--;
        }
        char letra;
        do{
            do
            {
                system("cls");
                Imprimir(Matriz);
                printf("\nPulse una tecla: \n[s] para salir \n[c] para revivir celula \n[f] para introducir forma");
                //Opciones en el juego
                letra=getch();
                //Limpiamos el buffer
                fflush(stdin);
                if(letra=='s'){
                    system("cls");
                }
                else if(letra=='f'){
                    Patron(Matriz);
                }
                else if(letra=='c'){
                    system("cls");
                    Imprimir(Matriz);
                    Resucitar(Matriz);
                }
                else{
                    Refrescar(Matriz);
                }
            }while(letra!='s');
            //Confirmacion de salida, para prevenir equivocaciones
            printf("\n\n\n\n%20cSeguro que quieres salir? [s/n]", ' ');
            confirmar=getch();
            fflush(stdin);
        }while(confirmar=='n');
        system("cls");
        //Opcion para volver a empezar, asi no hace falta salir del programa y volver a ejecutar
        printf("\n\n\n\n%20cVolver a empezar? [s/n]", ' ');
        repetir=getch();
        //Limpiamos el buffer
        fflush(stdin);
    }while(repetir=='s');
}
int main(){
    //Iniciamos el juego
    Juego();
}
