#include <iostream>
#include <vector.h>
#include <primo.h>

using namespace std;

int main(void){
    Vector<float> v1(5), v2(5), v3;
    cout << "v1 = " << v1 << endl << "v2 = " << v2 << endl;
    v3 = 4*v1 + v2*3 - v1;
    cout << "Resultado 4*v1 + v2*3 - v1 = " << v3 << endl;

    Vector<Primo> V1(5), V2(5), V3;
    cout << "V1 = " << V1 << endl << "V2 = " << V2 << endl;
    V3 = 4*V1 + V2*3 - V1;
    cout << "Resultado 4*V1 + V2*3 - V1 = " << V3 << endl;

    return 0;
}
