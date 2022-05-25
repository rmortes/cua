#include <iostream>
#include <Panel.h>
#include <Barra.h>
#include <Columna.h>
#include <BarcoH.h>
#include <BarcoV.h>
#include <BarcoD.h>
using namespace std;

int main(){
    Panel P(24,80);
    P.Combinar(Barra(3),6,20);
    P.Combinar(Barra(3),6,60);
    P.Combinar(Columna(3),16,20);
    P.Combinar(Columna(3),16,60);
    P.Combinar(BarcoV(),1,40);
    P.Combinar(BarcoH(),10,40);
    int it=0;
    while(!P.Vacio()){
    system("cls");
    cout<<"Juego de la vida. Iteracion "<<it<<endl<<P;
    P++;
    it++;
    }
    return 0;
}
