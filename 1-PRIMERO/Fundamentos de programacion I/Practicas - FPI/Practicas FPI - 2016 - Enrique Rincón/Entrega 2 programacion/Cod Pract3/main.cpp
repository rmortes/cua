#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<conio.h>
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
void Continua(void){
    printf("\nError, opcion incorrecta, pulse intro para continuar\n");
    getche();
    return;
}
int Filtradom(int b){
    int n;
    do{
        scanf("%d",&n);
        getchar();
        if(n<b){
            printf("Error, datos incorrectos,introduzcalos de nuevo:");
        }
    }while(n<b);
    return n;
}
int Filtrado(int b,int c){
    int a;
    do{
        scanf("%d",&a);
        getchar();
        if(a<b||a>c){
            printf("Error, datos incorrectos,introduzcalos de nuevo:");
        }
    }while(a<b||a>c);
    return a;
}
int FechaCorrecta(int*dia,int*mes,int*anyo,int a, int b){
    int salida;
    if(*dia<1||*dia>30||*mes<1||*mes>12||*anyo<a||*anyo>b){
        salida=1;
    }else{
        salida=0;
    }
    return salida;
}
void Filtradofechas(int*dia,int*mes,int*anyo,int a,int b){
    do{
        scanf("%d/%d/%d",dia,mes,anyo);
        getchar();
        if(FechaCorrecta(dia,mes,anyo,a,b)){
            printf("La fecha es incorrecta, introduzcala de nuevo:");
        }
    }while(FechaCorrecta(dia,mes,anyo,a,b));
    return;
}
void Cad(char a[]){
    scanf("%s",a);
    getchar();
    strupr(a);
    return;
}
void Nent(char a[],char b[],char c[]){
    Cad(a);
    Cad(b);
    Cad(c);
    return;
}
void Condparentesco(int comp1,int comp2,int comp3,int comp4,int comp5, char Nombre1[],char Nombre2[],char Apellido11[],char Apellido21[],char Apellido12[],char Apellido22[]){
    if(comp1==0 && comp2==0 && comp3==0){
        printf("Resultado:%s %s %s y %s %s %s son la misma persona\n",Nombre1,Apellido11,Apellido12,Nombre2,Apellido21,Apellido22);
    }else{
        if(comp1!=0 && comp2==0 && comp3==0){
            printf("Resultado:%s %s %s y %s %s %s son hermanos\n",Nombre1,Apellido11,Apellido12,Nombre2,Apellido21,Apellido22);
        }else{
            if(comp2==0 || comp3==0 || comp4==0 || comp5==0){
                printf("Resultado:%s %s %s y %s %s %s son primos\n",Nombre1,Apellido11,Apellido12,Nombre2,Apellido21,Apellido22);
            }else{
                if(comp1==0){
                    printf("Resultado:%s %s %s y %s %s %s son tocayos\n",Nombre1,Apellido11,Apellido12,Nombre2,Apellido21,Apellido22);
                }else{
                    printf("Resultado:%s %s %s y %s %s %s no poseen relacion\n",Nombre1,Apellido11,Apellido12,Nombre2,Apellido21,Apellido22);
                }
            }
        }
    }
    return;
}
void Cmparaparentesco(char a[],char b[],char c[],char d[],char e[],char f[]){
    int comp1 = strcmp(a,b);
    int comp2 = strcmp(c,d);
    int comp3 = strcmp(e,f);
    int comp4 = strcmp(c,f);
    int comp5 = strcmp(e,d);
    Condparentesco(comp1,comp2,comp3,comp4,comp5,a,b,c,d,e,f);
    return;
}
void Palsecreta(char palabra[]){
    system("cls");
    printf("jugador1, introduzca la palabra secreta:");
    Cad(palabra);
    system("cls");
    return;
}
int Acierto(char palabra[]){
    int cent=0;
    char palabra1[50];
    Cad(palabra1);
    if(strcmp(palabra,palabra1)==0){
        printf("Felicidades, has ganado\n");
        cent=1;
    }
    return cent;
}
int Crecientes(char numero[],int total){
    int corto=0;
    for(int b=0;b<total-1&&corto==0;b++){
        if(numero[b]>=numero[b+1]){
            corto=1;
        }
    }
    return corto;
}
int DistanciaCuadrada(int x, int y, int x1, int y1){
    int dcuadrada=(y-y1)*(y-y1)+(x-x1)*(x-x1);
    return dcuadrada;
}
void Circunsferencia(int R){
    char bolita [2000];
    //variable "a" controla la posición dentro de "bolita"
    int a=0;
    //sistema de cordenadas, y=columnas x=filas
    for(int y=0;y<24;y++){
        for(int x=0;x<80;x++){
            if(DistanciaCuadrada(x,y,40,12)<=R*R){
                bolita[a]='*';
                a++;
            }else{
                bolita[a]=' ';
                a++;
            }
        }
        bolita[a]='\n';
        a++;
    }
    bolita[a]='\0';
    printf("%s",bolita);
    return;
}
void Animacion(void){
    for(int R=0;R<12;R++){
        Circunsferencia(R);
        _sleep(150);
        system("cls");
    }
    return;
}
void Swap(char*a,char*b){
    char aux=*a;
    *a=*b;
    *b=aux;
    return;
}
void Desordena(char cad[],int n,int veces){
    for(int i=0;i<veces;i++){
        int r1=rand()%n;
        int r2=rand()%n;
        Swap(&cad[r1],&cad[r2]);
    }
    return;
}

void Ej11(void){
    do{
        system("cls");
        //Establecemos las siguientes cadenas
        char Nombre1[30],Apellido11[30],Apellido12[30];
        char Nombre2[30],Apellido21[30],Apellido22[30];
        printf("Introduzca un nombre completo,si es compuesto utilice \"_\"\ny si tiene solo un apellido ponga \".\" en el lugar del segundo:");
        Nent(Nombre1,Apellido11,Apellido12);
        printf("Introduzca un segundo nombre completo:");
        Nent(Nombre2,Apellido21,Apellido22);
        //Comparamos los dos nombres y su relativa relacion
        Cmparaparentesco(Nombre1,Nombre2,Apellido11,Apellido21,Apellido12,Apellido22);
    }while(Repetir());
    return;
}
void Ej12(void){
    //Definimos variables
    int dia,mes,anyo,cuota,mes2,anyo2;
    //Definimos cadenas
    char mes3[50];
    do{
        system("cls");
        printf("Introduzca fecha de inicio de prestamo dd/mes/anyo:");
        Filtradofechas(&dia,&mes,&anyo,1900,2100);
        printf("Introducza el numero de cuotas:");
        cuota=Filtrado(1,1200);
        //Calculo de fecha final
        anyo2=(anyo*12+mes-1+cuota)/12;
        mes2=(anyo*12+mes-1+cuota)%12;
        switch (mes2) {
        case 0: strcpy(mes3,"Enero"); break;
        case 1: strcpy(mes3,"Febrero"); break;
        case 2: strcpy(mes3,"Marzo"); break;
        case 3: strcpy(mes3,"Abril"); break;
        case 4: strcpy(mes3,"Mayo"); break;
        case 5: strcpy(mes3,"Junio"); break;
        case 6: strcpy(mes3,"Julio"); break;
        case 7: strcpy(mes3,"Agosto"); break;
        case 8: strcpy(mes3,"Septiembre"); break;
        case 9: strcpy(mes3,"Octubre"); break;
        case 10: strcpy(mes3,"Noviembre"); break;
        case 11: strcpy(mes3,"Diciembre"); break;
        }
        printf("El prestamo finaliza el %d de %s de %d\n",dia,mes3,anyo2);
    }while(Repetir());
    return;
}
void Ej13(void){
    do{
        //Cadena
        char palabra[50];
        Palsecreta(palabra);
        //cent para salir del bucle
        int corta=0;
        //Distintos intentos
        for(int i=1;i<4&&corta==0;i++){
            switch(i){
            case 1:
                printf("Jugador2, primer intento, pista:la palabra comienza por:%c:",palabra[0]);
                break;
            case 2:
                printf("Jugador2, segundo intento, pista:la palabra termina por:%c:",palabra[strlen(palabra)-1]);
                break;
            case 3:
                printf("Jugador2, ultimo intento, pista:la letra central es:%c:",palabra[strlen(palabra)/2]);
                break;
            }
            corta=Acierto(palabra);
        }
        if(corta==0){
            printf("lo sentimos, has perdido, la palabra era \"%s\"\n",palabra);
        }
    }while(Repetir());
    return;
}
void Ej21(void){
    int n;
    do{
        system("cls");
        printf("Introduzca un numero dentro del conjuto de los Naturales, que sea diferente de 0:");
        n=Filtradom(1);
        char numero[100];
        int a=10;
        int cont=0,finalizado=0;
        //numero de numeros imprimidos "cont"
        while(cont<n&&finalizado==0){
            sprintf(numero,"%d",a);
            int total=strlen(numero);
            //verifica si un numero es creciente
            if(Crecientes(numero,total)==0){
                printf(" %s",numero);
                cont++;
                //num max de crecientes
                if(strcmp(numero,"123456789")==0){
                    printf("\nYa no hay mas numeros crecientes");
                    printf("\nNuemero maximo de numero crecientes:%d\n",cont);
                    finalizado=1;
                }
            }
            a++;
        }
    }while(Repetir());
    return;
}
void Ej22(void){
    do{
        for(int i=0;i<10;i++){
            Animacion();
        }
    }while(Repetir());
    return;
}
void Ej23(void){
    //Cadenas
    char palabra[50],desordenada[50];
    do{
        Palsecreta(palabra);
        strcpy(desordenada,palabra);
        int n=strlen(palabra);
        //Variable "corta", corta el bucle si se gana
        int corta = 0;
        //Da hasta 5 intententos para acertar
        for(int i=1;i<6&&corta==0;i++){
            //Desordena n*n la cadena "desordenada"
            Desordena(desordenada,n,n*n+1);
            printf("jugador 2, intento %d de 5, pista: %s, su propuesta de palabra:",i,desordenada);
            corta=Acierto(palabra);
        }
        if(corta==0){
            printf("Has perdido, la palabra secreta era %s\n",palabra);
        }
    }while(Repetir());
    return ;
}
void Practica2(void){
    char c;
    do{
        system("cls");
        printf("\nMENU PRACTICA 2\n\na.-Ej 1\nb.-Ej 2\nc.-Ej 3\nd.-Menu principal\n\nopcion:");
        scanf("%c",&c);
        getchar();
        switch(c){
        case 'a':
        case 'A':
            Ej21();
            break;
        case 'b':
        case 'B':
            Ej22();
            break;
        case 'c':
        case 'C':
            Ej23();
            break;
        case 'd':
        case 'D':
            break;
        default:
            Continua();
            break;
        }
    }while(c!='d');
    return;
}
void Practica1(void){
    char c;
    do{
        system("cls");
        printf("\nMENU PRACTICA 1\n\na.-Ej 1\nb.-Ej 2\nc.-Ej 3\nd.-Menu principal\n\nopcion:");
        scanf("%c",&c);
        getchar();
        switch(c){
        case 'a':
        case 'A':
            Ej11();
            break;
        case 'b':
        case 'B':
            Ej12();
            break;
        case 'c':
        case 'C':
            Ej13();
            break;
        case 'd':
        case 'D':
            break;
        default:
            Continua();
            break;
        }
    }while(c!='d');
    return;
}
void Menuppal(void){
    char c;
    do{
        system("cls");
        printf("\nMENU PRINCIPAL\n\na.-Practica 1\nb.-Practica 2\nc.-Finalizar\n\nopcion:");
        scanf("%c",&c);
        getchar();
        switch(c){
        case 'a':
        case 'A':
            Practica1();
            break;
        case 'b':
        case 'B':
            Practica2();
            break;
        case 'c':
        case 'C':
            break;
        default:
            Continua();
            break;
        }
    }while(c!='c');
    return;
}
int main(void){
    Menuppal();
    system("cls");
    return (0);
}
