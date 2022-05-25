#include <matrizs.h>
#include <matriza.h>
#include <vectorf.h>
#include <vectorc.h>
using namespace std;
int main(void){
    srand(time(0));
    MatrizC MC(3),MC1(3),MC2,MC3;
    MatrizS MS(3);
    MatrizA MA(3),MA1(3);
    VectorC VC(3);
    VectorF VF(3);
    Matriz M(3,4);
    cout<<" Matriz: "<<endl<<M<<endl;
    VectorF F(3);
    cout<<" Vector fila: "<<endl<<F<<endl;
    VectorC C(4);
    cout<<" Vector columna: "<<endl<<C<<endl;
    MatrizC R;
    R=F*M*C;
    cout<<" Vector fila*Matriz*Vector columna -> Resulta cuadrada (1x1): "<<R<<endl;
    MatrizS S(3);
    cout<<" MatrizS:"<<endl<<S;
    if(S==!S) cout<<" MatrizS es simetrica."<<endl<<endl;
    else cout<<" Algo ha fallado"<<endl<<endl;
    MatrizA A(3);
    cout<<" Matriz Antisimetrica: "<<endl<<A<<endl;
    A += !A;
    cout<<" Antisimetrica + Traspuesta = Diagonal: "<<endl<<A;

    return 0;
}


