#include <iostream>
#include <math.h>
#include <triangulo.h>
#include <complejo.h>

int main(){

    Triangulo<Complejo> a(5), b(5),c;

    c=a*b;
    a*=b;
    cout<< "Triangulo c: "<<endl <<c <<endl << "*"<<endl<< "Triangulo b: "<<endl <<a;

    cout<<"El triangulo de la multiplicación es: "<< endl << c <<endl;



    return 0;
}
