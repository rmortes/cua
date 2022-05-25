//Declaracion de Librerias Necesarias
#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
/* Funcion para cambiar la frase */
void repetir(char frase[]){
    system("cls");
    printf("\n\n\nIntroduzca una frase: ");
    gets(frase);
    system("cls");
    return;
}
//Funcion de estadisticas
void Estadisticas(char frase[]){
    system("cls");
    int a,i,vocales,c;
    float numero,k;
    a=strlen(frase);

    printf("<--ESTADISTICAS-->");
    printf("\n\n\nCadena Actual: %s\n\n",frase);
    printf("--------------------------------------");
    printf("\nNumero de caracteres: %d",a);
    vocales=0;
    //Aqui busca si hay vocales en cada caracter, tanto mayusculas como minusculas, y aumenta en 1 la variable "vocales"
    for(i=0;i<strlen(frase);i++){
        if(frase[i]=='a' || frase[i]=='e' || frase[i]=='i' || frase[i]=='o' || frase[i]=='u' )vocales++;
        if(frase[i]=='A' || frase[i]=='E' || frase[i]=='I' || frase[i]=='O' || frase[i]=='U' )vocales++;
    }
    //Calcula el porcentaje de vocales, con una precision de dos decimales
    numero=(vocales*100.0)/a;
    printf("\n--------------------------------------");
    printf("\nVocales: %2.2f",numero);

    c=0;
    //Aqui busca caracteres que esten entre a y z, mayuculas y minusculas, y omite las vocales calculadas antes
    for(i=0;i<a;i++){
        if(frase[i]>='a' && frase[i]<='z' && frase[i]!='a' && frase[i]!='e' && frase[i]!='i' && frase[i]!='o' && frase[i]!='u')c++;
        if(frase[i]>='A' && frase[i]<='Z' && frase[i]!='A' && frase[i]!='E' && frase[i]!='I' && frase[i]!='O' && frase[i]!='U')c++;
    }
    //Calcula el porcentaje de otro caracteres alfabeticos, con una precision de dos decimales
    numero=(c*100.0)/a;
    printf("\n--------------------------------------");
    printf("\nOtros caracteres alfabeticos: %2.2f\n",numero);

    //la diferencia entre el total y las dos anteriores nos da la cantidad de otros caracteres no alfabeticos y calculamos su porcentaje
    k=(a-vocales-c)*100.0/a;
    printf("--------------------------------------");
    printf("\nCaracteres no alfabeticos: %2.2f\n",k);
    printf("--------------------------------------\n\n\n");
    system("pause");
    system("cls");
    return;
}

//Funcion para eliminar pares o impares
void EliminarPI(char frase[]){
    system("cls");
    char  nueva[100] , a;
    int l=strlen(frase),init,i,j;
    printf("<--ELIMINAR-->");
    printf("\n\n\nCadena Actual: %s\n\n",frase);
    printf("\nEliminar pares o impares <p/i>: ");
    a=getche();
    //Aqui, segun la seleccion, iniciamos la eliminacion en el primer caracter o en el segundo
    if (a=='p') init = 0;
    else init = 1;
    j=0;
    //Este for, comienza segun la seleccion en el primer o segundo caracter y copia en pasos de dos cada caracter en una nueva cadena
    for (i=init;i < l;  i = i+2)
        nueva[j++] = frase[i];
    nueva[j] = '\0';
    //Aqui copiamos la nueva cadena a la original, asi devolvemos la cadena modificada
    strcpy(frase,nueva);
    system("cls");
    return;
}
//Funcion para invertir
void Invertir(char frase[]){
    int i,l;
    char a;
    l=strlen(frase);
    //El for para cuando el valor de i es la mitad que la cantidad de caracteres de la cadena, sino volveria a dejarla como en el inicio
    for(i=0;i<l/2;i++){
        a=frase[i];
        frase[i]=frase[l-i-1];
        frase[l-i-1]=a;
    }

    system("cls");
    return;
}

//Funcion para caracteres aleatorios
void aleatorio(char frase[]){
    system("cls");
    int i;
    char a, random;
    printf("<--CARACTERES ALEATORIOS-->");
    printf("\n\n\nCadena Actual: %s\n\n",frase);
    //Seleccionamos un caracter aleatorio en un rango de 57 valores a partir del 'A'
    random='A'+rand()%57;

    printf("\nCaracter a sustituir: ");
    a=getche();
    for(i=0;i<strlen(frase);i++){
        if(frase[i]==a){ //busco el caracter en frase que sea igual a 'a'
            frase[i]=random; //y lo sustituyo por el caracter aleatorio 'b'.
        }
    }

    system("cls");
    return;
}

//Funcion que pasa todo a minusculas
void minusculas(char frase[]){
    system("cls");
    int i,l;
    l=strlen(frase);
    for(i=0;i<l;i++){
        //Pasamos por cada caracter, y si este esta en mayusculas se pasa a minusculas
        if(frase[i]>='A' && frase[i]<='Z'){
            frase[i]=frase[i]+'a'-'A';
        }
    }
    return;
}
//Funcion que pasa todo a mayusculas
void mayusculas(char frase[]){
    system("cls");
    int i,l;
    l=strlen(frase);
    for(i=0;i<l;i++){
        //Pasamos por cada caracter, y si este esta en minuculas se pasa a mayusculas
        if(frase[i]>='a' && frase[i]<='z'){
            frase[i]=frase[i]-'a'+'A';

        }
    }

    return;
}
//Funcion donde seleccionamos mayusculas o minusculas
void MayusculasMinusculas(char frase[]){
    system("cls");
    //Con la cadena "Mm" se realiza un case u otro, que se remite a una funcion para realizar lo que ha pedido el usuario
    char Mm;
    printf("<--Mayusculas&Minusculas-->");
    printf("\n\n\nCadena Actual: %s\n\n",frase);
    printf("\nMayusculas o minusculas <M/m)\n");
    Mm=getche();
    switch(Mm){
    case 'M':
        mayusculas(frase);
        break;
    case 'm':
        minusculas(frase);
        break;
        return;
    }

    return;
}
//Funcion MenuPrincipal, donde podremos elegir una opcion//
void MenuPrincipal (char frase[]){
    system("cls");
    //Declaramos la cadena "seleccion" para segun que letra realice un case u otro
    char seleccion;

    printf("\n\n\nCadena introducida: %s\n\n",frase);
    do{

        printf("\n<--MENU-->\n");
        printf("\n1) Pasar a mayusculas o a minusculas");
        printf("\n2) Cambiar caracteres aleatoriamente");
        printf("\n3) Invertir cadena");
        printf("\n4) Eliminar caracteres pares e impares");
        printf("\n5) Estadisticas");
        printf("\n6) Volver a introducir una cadena");
        printf("\n7) Salir");
        printf("\nSelecciona una opcion: ");
        fflush(stdin);
        seleccion=getche();
        printf("\n");
        switch(seleccion){
        case '1':
            MayusculasMinusculas(frase);
            printf("\n\n\nCadena Actual: %s\n\n",frase);
            break;
        case '2':
            aleatorio(frase);
            printf("\n\n\nCadena Actual: %s\n\n",frase);
            break;
        case '3':
            Invertir(frase);
            printf("\n\n\nCadena Actual: %s\n\n",frase);
            break;
        case '4':
            EliminarPI(frase);
            printf("\n\n\nCadena Actual: %s\n\n",frase);
            break;
        case '5':
            Estadisticas(frase);
            break;
        case '6':
            repetir(frase);
            printf("\n\n\nCadena Actual: %s\n\n",frase);
            break;
        case '7':
            break;
        }
    }while(seleccion!='7');
    return;
}
//Funcion para introducir cadena y llamar a menu principal//
void IntroducirCadena(){
    //Se declara la cadena "frase" y se espera a que el usuario introduzca una frase
    char frase[100];
    printf("\n\n\nIntroduzca una frase: ");
    gets(frase);
    fflush(stdin);
    MenuPrincipal(frase);
    return;
}
//Funcion principal donde llamamos a IntroducirCadena//
int main(void){
    IntroducirCadena();
    return(0);
}
