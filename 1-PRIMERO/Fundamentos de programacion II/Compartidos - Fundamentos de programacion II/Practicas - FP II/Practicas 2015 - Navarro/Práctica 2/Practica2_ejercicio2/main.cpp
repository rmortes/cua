#include <MatrizET.h>

int main(){
    Carta c1(3), c2(1), c3(10);
    cout << c1 << c2 << c3 << endl;
    cout << c1 * c3 << endl;

    MatrizT<double> mreal(3, 4), mreal2(3, 4);
    MatrizT<Carta> mcartas(5, 2);

    mreal = mreal2;

    cout <<  mreal + mreal2;

    cout << mreal << endl;
    cout << mcartas << endl;

    MatrizCT<Carta> mcuadrada(3), mcuadrada2(4);
    cout << mcuadrada << endl;
    cout << mcuadrada + mcuadrada2 << endl;

    cout << "matriz simetrica de cartas" << endl;
    MatrizST<Carta> msimetrica(3), msimetrica2(3);

    cout << msimetrica << endl;

    cout << msimetrica + msimetrica2 << endl;

    MatrizDT<Carta> diagonal(3), diagonal2(3);

    cout << diagonal << endl;
    cout << diagonal + diagonal2 << endl;

    MatrizET<Carta> escalar(3), escalar2(3);

    cout << escalar << endl;

    system("pause");
}
