#include <stdio.h>
#include<stdlib.h>
#include<time.h>

#define N 10

#define NADA 2
#define CRUZ 3

void Imprimir(int vector[]){

    int i;

printf("|");
for(i=0;i<N;i++)
    switch (vector[i]) {
    case CRUZ:printf("X");
         break;
    case NADA:printf(" ");
         break;
    }
printf("|");
return;
}


int main(){

srand(time(NULL));

int vector[10],i,a;


for(i=0;i<10;i++)
    vector[i]=NADA;


a=rand()%6;
for(i=0;i<=a;i++) //Se pone i<=a para que entre también el 0
    vector[i]=CRUZ;

Imprimir(vector);

while(a>=0){

getchar();
system("cls");

vector[a]=NADA;

a--;

Imprimir(vector);

}

printf("\n\n");

return 0;
}

