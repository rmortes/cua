#include <MatrizE.h>

void Operacion_Matriz(int &o,int &Nf, int &Nc){
    int k=0;
    MatrizC a(Nf);MatrizC z(Nf);MatrizS s(Nf);MatrizS f(Nf);MatrizD b(Nf);MatrizD t(Nf);MatrizE e(Nf);MatrizE y(Nf);Matriz M(Nf,Nc);Matriz p(Nf,Nc);
    switch(o){
    case 1:

        cout << "Seleccione una operacion para que la ejecute la Matriz:"<< endl;
        cout << "1.- Suma\n2.- Resta\n3.- Multiplicacion\n4.- Opuesta\n"<<endl;
        cin >> k;
        cout << endl;
        switch (k) {
        case 1:

            cout<<"Suma de matrices"<<endl;
            cout << "Matriz 1\n" << M <<endl;
            cout << "Matriz 2\n" << p <<endl;
            M+=p;
            cout << "Matriz resultante\n" << M <<endl;
            break;
        case 2:

            cout<<"Resta de matrices"<<endl;
            cout << "Matriz 1\n" << M <<endl;
            cout << "Matriz 2\n" << p <<endl;
            M-=p;
            cout << "Matriz resultante\n" << M <<endl;
            break;
            break;
        case 3:

            cout<<"Multiplicacion de matrices"<<endl;
            cout << "Matriz 1\n" << M <<endl;
            cout << "Matriz 2\n" << p <<endl;
            M*=p;
            cout << "Matriz resultante\n" << M <<endl;
            break;
        case 4:

            cout<<"Matriz opuesta"<<endl;
            cout << "Matriz 1\n" << M <<endl;
            !M;
            cout << "Matriz resultante\n" << M <<endl;
            break;
        default:cout << "Error en la opción" <<endl;break;
        }
        break;
    case 2:

        cout << "Seleccione una operacion para que la ejecute la Matriz:"<< endl;
        cout << "1.- Suma\n2.- Resta\n3.- Multiplicacion\n4.- Opuesta\n5.- Traspuesta\n"<<endl;
        cin >> k;
        cout << endl;
        switch (k) {
        case 1:

            cout<<"Suma de matrices"<<endl;
            cout << "Matriz 1\n" << a <<endl;
            cout << "Matriz 2\n" << z <<endl;
            a+=z;
            cout << "Matriz resultante\n" << a <<endl;
            break;
        case 2:

            cout<<"Resta de matrices"<<endl;
            cout << "Matriz 1\n" << a <<endl;
            cout << "Matriz 2\n" << z <<endl;
            a-=z;
            cout << "Matriz resultante\n" << a <<endl;
            break;
        case 3:

            cout<<"Multiplicacion de matrices"<<endl;
            cout << "Matriz 1\n" << a <<endl;
            cout << "Matriz 2\n" << z <<endl;
            a*=z;
            cout << "Matriz resultante\n" << a <<endl;
            break;
        case 4:

            cout<<"Matriz opuesta"<<endl;
            cout << "Matriz 1\n" << a <<endl;
            !a;
            cout << "Matriz resultante\n" << a <<endl;
            break;
        case 5:

            cout<<"Matriz traspuesta"<<endl;
            cout << "Matriz 1\n" << a <<endl;
            cout << "Matriz resultante\n" << ~a <<endl;
            break;
        default:cout << "Error en la opción" <<endl;break;
        }
        break;
    case 3:

        cout << "Seleccione una operacion para que la ejecute la Matriz:"<< endl;
        cout << "1.- Suma\n2.- Resta\n3.- Multiplicacion\n4.- Opuesta\n5.- Traspuesta\n"<<endl;
        cin >> k;
        cout << endl;
        switch (k) {
        case 1:

            cout<<"Suma de matrices"<<endl;
            cout << "Matriz 1\n" << s <<endl;
            cout << "Matriz 2\n" << f <<endl;
            s+=f;
            cout << "Matriz resultante\n" << s <<endl;
            break;
        case 2:

            cout<<"Resta de matrices"<<endl;
            cout << "Matriz 1\n" << s <<endl;
            cout << "Matriz 2\n" << f <<endl;
            s-=f;
            cout << "Matriz resultante\n" << s <<endl;
            break;
        case 3:

            cout<<"Multiplicacion de matrices"<<endl;
            cout << "Matriz 1\n" << s <<endl;
            cout << "Matriz 2\n" << f <<endl;
            s*=f;
            cout << "Matriz resultante\n" << s <<endl;
            break;
        case 4:

            cout<<"Matriz opuesta"<<endl;
            cout << "Matriz 1\n" << s <<endl;
            !s;
            cout << "Matriz resultante\n" << s <<endl;
            break;
        case 5:

            cout<<"Matriz traspuesta"<<endl;
            cout << "Matriz 1\n" << s <<endl;
            cout << "Matriz resultante\n" << ~s <<endl;
            break;
        default:cout << "Error en la opción" <<endl;break;
        }
        break;
    case 4:

        cout << "Seleccione una operacion para que la ejecute la Matriz:"<< endl;
        cout << "1.- Suma\n2.- Resta\n3.- Multiplicacion\n4.- Opuesta\n5.- Traspuesta\n"<<endl;
        cin >> k;
        cout << endl;
        switch (k) {
        case 1:

            cout<<"Suma de matrices"<<endl;
            cout << "Matriz 1\n" << b <<endl;
            cout << "Matriz 2\n" << t <<endl;
            b+=t;
            cout << "Matriz resultante\n" << M <<endl;
            break;
        case 2:

            cout<<"Resta de matrices"<<endl;
            cout << "Matriz 1\n" << b <<endl;
            cout << "Matriz 2\n" << t <<endl;
            b-=t;
            cout << "Matriz resultante\n" << b <<endl;
            break;
        case 3:

            cout<<"Multiplicacion de matrices"<<endl;
            cout << "Matriz 1\n" << b <<endl;
            cout << "Matriz 2\n" << t <<endl;
            b*=t;
            cout << "Matriz resultante\n" << b <<endl;
            break;
        case 4:

            cout<<"Matriz opuesta"<<endl;
            cout << "Matriz 1\n" << b <<endl;
            !b;
            cout << "Matriz resultante\n" << b <<endl;
            break;
        case 5:

            cout<<"Matriz traspuesta"<<endl;
            cout << "Matriz 1\n" << b <<endl;
            cout << "Matriz resultante\n" << ~b <<endl;
            break;
        default:cout << "Error en la opción" <<endl;break;
        }
    case 5:

        cout << "Seleccione una operacion para que la ejecute la Matriz:"<< endl;
        cout << "1.- Suma\n2.- Resta\n3.- Multiplicacion\n4.- Opuesta\n5.- Traspuesta\n"<<endl;
        cin >> k;
        cout << endl;
        switch (k) {
        case 1:

            cout<<"Suma de matrices"<<endl;
            cout << "Matriz 1\n" << e <<endl;
            cout << "Matriz 2\n" << y <<endl;
            e+=y;
            cout << "Matriz resultante\n" << e <<endl;
            break;
        case 2:

            cout<<"Resta de matrices"<<endl;
            cout << "Matriz 1\n" << e <<endl;
            cout << "Matriz 2\n" << y <<endl;
            e-=y;
            cout << "Matriz resultante\n" << e <<endl;
            break;
        case 3:

            cout<<"Multiplicacion de matrices"<<endl;
            cout << "Matriz 1\n" << e <<endl;
            cout << "Matriz 2\n" << y <<endl;
            e*=y;
            cout << "Matriz resultante\n" << e <<endl;
            break;
        case 4:

            cout<<"Matriz opuesta"<<endl;
            cout << "Matriz 1\n" << e <<endl;
            !e;
            cout << "Matriz resultante\n" << e <<endl;
            break;
        case 5:

            cout<<"Matriz traspuesta"<<endl;
            cout << "Matriz 1\n" << e <<endl;
            cout << "Matriz resultante\n" << ~e <<endl;
            break;
        }
    }
    return;
}

void Diseno_matriz(int &o){
    int Nf,Nc,op=0;
    if(o!=1){
        cout<<"Elige el tipo de matriz que quieres:"<<endl;
        cout<<"1.- Matriz 2x2\n2.- Matriz 3x3\n3.- Matriz personalizada"<<endl;
        cin >>op;
        switch(op){
        case 1:cout<<"Matriz 2x2"<<endl;
            Nf=Nc=2;
            Operacion_Matriz(o,Nf,Nc);
            break;
        case 2:cout<<"Matriz 3x3"<<endl;
            Nf=Nc=3;
            Operacion_Matriz(o,Nf,Nc);
            break;
        case 3:
            cout<<"Matriz personalzada"<<endl;
            cout<<"Introduzca el numero de filas y de columnas"<<endl;
            cin>>Nf;
            Operacion_Matriz(o,Nf,Nc);
            break;

        default:
            cout << "Error en la opción" <<endl;
            break;
        }
    }else{
        cout<<"Elige el tipo de matriz que quieres:"<<endl;
        cout<<"1.- Matriz 2x2\n2.- Matriz 3x3\n3.- Matriz personalizada"<<endl;
        cin >>op;
        switch(op){
        case 1:cout<<"Matriz 2x2"<<endl;
            Nf=Nc=2;
            Operacion_Matriz(o,Nf,Nc);
            break;
        case 2:cout<<"Matriz 3x3"<<endl;
            Nf=Nc=3;
            Operacion_Matriz(o,Nf,Nc);
            break;
        case 3:
            cout<<"Matriz personalzada"<<endl;
            cout<<"Introduzca el numero de filas"<<endl;
            cin>>Nf;
            cout<<"Introduzca el numero de columnas"<<endl;
            cin>>Nc;
            Operacion_Matriz(o,Nf,Nc);
            break;
        default:
            cout << "Error en la opción" <<endl;
            break;
        }
    }
    return ;
}

void Seleccion_matriz(){
    int o=0;
    bool x=true;
    do{
        cout << "Seleccione una Matriz:"<< endl;
        cout << "1.- Matriz\n2.- Matriz Cuadrada\n3.- Matriz Simetrica\n4.- Matriz Diagonal\n5.- Matriz Simetrica\n6.- Salir"<<endl;
        cin >> o;
        if(o!=6){
            Diseno_matriz(o);
        }else{
            x=false;
        }
    }while(x==true);
    return;
}

int main (void){
    Seleccion_matriz();
    return(0);
}
