#include <stdio.h>

int main(void) {
    int dni, resto;
    char letra, introducido;

    //Aqui introduce el número y la letra del dni.
    printf("Introduce el DNI: ");
    scanf("%d-%c",&dni,&introducido);

    //En este "if" transforma la letra de minuscula a mayuscula
    if(introducido>='a'&&introducido<='z'){
        introducido=introducido-'a'+'A';
    }
    //Ejecuta la operación para hallar el valor con la letra correspondiente
    resto=dni%23;
    //Son las letras correspondientes al dni.
    switch(resto){
    case 0:
        letra='T';
        break;
    case 1:
        letra='R';
        break;
    case 2:
        letra='W';
        break;
    case 3:
        letra='A';
        break;
    case 4:
        letra='G';
        break;
    case 5:
        letra='M';
        break;
    case 6:
        letra='y';
        break;
    case 7:
        letra='F';
        break;
    case 8:
        letra='P';
        break;
    case 9:
        letra='D';
        break;
    case 10:
        letra='X';
        break;
    case 11:
        letra='B';
        break;
    case 12:
        letra='N';
        break;
    case 13:
        letra='J';
        break;
    case 14:
        letra='Z';
        break;
    case 15:
        letra='S';
        break;
    case 16:
        letra='Q';
        break;
    case 17:
        letra='V';
        break;
    case 18:
        letra='H';
        break;
    case 19:
        letra='L';
        break;
    case 20:
        letra='C';
        break;
    case 21:
        letra='K';
        break;
    case 22:
        letra='E';
        break;
    }
    //Comprueba si su letra introducida con la correspondiente son iguales.
    if(introducido == letra){
        printf("Su letra es correcta\n");
    }else{
        printf("Su letra era erronea\n");
        printf("Su letra es: %c\n", letra);
    }

    return (0);
}
