//Practica2 Ejercicio2
#include<stdio.h>
#include<stdlib.h>
#include<stralign.h>
int main(void){
    printf("*\n*");
    while(1){
        for(int R=0;R<12;R++){
            //cadena que contiende las circunsferencias
            char bolita [2000];
            //variable "a" controla la posición dentro de "bolita"
            int a=0;
            //sistema de cordenadas, y=columnas x=filas
            for(int y=0;y<24;y++){
                for(int x=0;x<80;x++){
                    //Ecuación del area de una circunsferencia
                    if(((y-12)*(y-12))+((x-40)*(x-40))<=R*R){
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
            //Retraso de 150ms
            _sleep(150);
            system("cls");
        }
    }
    return 0;
}
