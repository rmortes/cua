#include <MatrizST.h>
#include <MatrizAT.h>
#include <VectorFT.h>
#include <VectorCT.h>
#include <Sucesion.h>
using namespace std;

int main(void){
    srand(time(0));
    MatrizT <float> M(3,5);
    cout<<" Matriz: "<<endl<<M<<endl;
    VectorFT<float> F(3);
    cout<<" Vector fila: "<<endl<<F<<endl;
    VectorCT<float> C(5);
    cout<<" Vector columna: "<<endl<<C<<endl;
    MatrizCT<float> R;
    R=F*M*C;
    cout<<" Vector fila*Matriz*Vector columna -> Resulta cuadrada (1x1): "<<R;
    MatrizST<float>S(3);
    cout<<" MatrizS:"<<endl<<S<<endl;
    if(S==!S) {
        cout<<" MatrizS es simetrica."<<endl<<endl;
    }else{
        cout<<" Algo ha fallado"<<endl<<endl;
    }
    MatrizA<float> A(3);
    cout<<" Matriz Antisimetrica: "<<endl<<A<<endl;
    A += !A;
    cout<<" Antisimetrica + Traspuesta = Diagonal: "<<endl<<A;
    return 0;
}

