#include <iostream>
using namespace std;


using namespace std;

class Panel{
private:
    //Matriz o vector de vetores
    bool **M;
    int F,C;
public:

    //Constructor por defecto
    Panel(){
        F=0;
        C=0;
        M=NULL;
        cout<<"Contructor por defecto"<<endl;
        return;


    }

    //Constructor por parametros
    Panel(int Filas, int Columnas){
        //Cambiamos el valor de filas y columnas, por los introducidpos
        F=Filas;
        C=Columnas;
        M=NULL;
        //Creamos el panel
        if(F>0){
            M=new bool*[F];
            if(C>0){
                for(int i=0;i<F;i++){
                    M[i]=new bool[C];
                }
            }
        }
        //Ponemos todas como muertas
        if(F>0 && C>0)
            for(int i=0;i<F;i++){
                for(int j=0;j<C;j++){
                    M[i][j]=false;
                }
            }

        return;
    }

    //Constructor copia
    Panel(const Panel &p){
        //Copiamos los valores de las columnas y filas
        F=p.F;
        C=p.C;
        //Hacemos que apunte a NULL
        M=NULL;
        //Creamos el vector de vectores(la matriz)
        M=new bool *[F];
        for(int i=0;i<F;i++){
            M[i]=new bool [C];
        }

        //Copiamos el contenido de los vectores
        if(F>0 && C>0){
            if(p.M!=NULL){

                for (int i=0;i<F;i++){

                    for(int j=0;j<C;j++){
                        M[i][j]=p.M[i][j];
                    }
                }

            }
        }



        return;
    }
    //Destructor
    ~Panel(){
        //Si tiene contenido
        if(M!=NULL){
            for (int i=0;i<F;i++){
                //Borramos cada contenido(vectores) del vector principal
                delete[]M[i];

            }
            //Borramos el contenido del vector principal
            delete[]M;

        }
        return;
    }

    //Operador de igualdad
    //Constructor copia +destructor+return this
    Panel operator =(Panel p){

        F=p.F;
        C=p.C;

        M=NULL;
        M=new bool *[F];
        for(int i=0;i<F;i++){
            M[i]=new bool [C];
        }
        if(F>0 && C>0){
            if(p.M!=NULL){

                for (int i=0;i<F;i++){

                    for(int j=0;j<C;j++){
                        M[i][j]=p.M[i][j];
                    }
                }

            }
        }
        if(M!=NULL){
            for (int i=0;i<F;i++){

                delete[]M[i];

            }
            delete[]M;
        }
        return *this;
    }

    void Cuadrar(int &pi, int &pj){
        //Meter dentro del mapa (si se desborda)
        if(pi>=F){
            pi=pi%F;
        }
        if(pj>=C){
            pj=pj%C;
        }
        while(pi<0){
            pi=pi+F;
        }
        while(pj<0){
            pj=pj+C;
        }
        return;

    }

    int NVecinosVivos(int pi, int pj){
        int Ncelulasvivas=0;

        for(int i=pi-1;i<=pi+1;i++){
            for(int j=pj-1;j<=pj+1;j++){
                int ii = i, jj=j;
                Cuadrar(ii,jj);
                if(M[ii][jj]) Ncelulasvivas++;
            }
        }
        if(M[pi][pj]) Ncelulasvivas--;

        return Ncelulasvivas;
    }

    void  operator ++(int){
        Panel aux = (*this);
        int nCelulasVivas;
        //Recorre el panel
        for(int i=0;i<F;i++){
            for(int j=0;j<C;j++){
                nCelulasVivas= aux.NVecinosVivos(i,j);

                if(aux.M[i][j]){
                    //Si está viva y tiene menos de dos o mas de tres vecinas, se muere
                    if(nCelulasVivas!=2 && nCelulasVivas!=3){
                        M[i][j]=false;
                    }
                }else{
                    //Si esta muerta y tiene tres vivas revive
                    if(nCelulasVivas==3){
                        M[i][j]=true;
                    }
                }
            }
        }
        return;

    }
    bool& operator()(int a, int b){
        return M[a][b];
    }

    //    //Entrada
    //    friend istream& operator >> (istream &medio, Panel &p ){
    //        cout<< "Introduzca numero de Filas: "; medio >> p.F;
    //        cout << "Introduzca numero de columnas: "; medio>>p.C;
    //        p.M=NULL;
    //        int i,j;
    //        p.M=new bool *[p.F];
    //        for(i=0;i<p.F;i++){
    //            p.M[i]=new bool [p.C];

    //        }


    //        int cel,a,b;
    //        cout<<"Cuantas celulas vivas: "; cin>>cel;
    //        for(i=0;i<cel;i++){
    //            cout <<"Introduzca coord ";medio>>a;
    //            cout <<"Introduzca coord ";medio>>b;
    //            p.M[a][b]=true;

    //        }
    //        return(medio);
    //    }

    //Salida
    friend ostream& operator << (ostream &medio, Panel p ){
        int i, j;
        string s;
        //Recorremos el vector del eje de las y
        for(i=0;i<p.F;i++){
            for(j=0;j<p.C;j++){
                if(p.M[i][j]){
                    s+=(char)219;
                }else{
                    s+=(char)250;
                }
            }
            s+='\n';
        }
        medio<<s;
        return (medio);
    }

    bool Vacio(){
        //Suponemos que tiene algo dentro
        bool vacio=true;
        int i, j;
        for(i=0;i<F;i++){
            for(j=0;j<C;j++){
                if(M[i][j]==true){
                    //Solo cambia si algun
                    vacio=false;
                }

            }

        }
        return (vacio);
    }

    void Combinar(Panel p, int pi, int pj){
        int i, j;

        for(i=0;i<p.F;i++){
            for(j=0;j<p.C;j++){
                int ni = i+pi;
                int nj = j+pj;
                Cuadrar(ni,nj);
                M[ni][nj]=M[ni][nj] | p.M[i][j];
            }
        }

        return;
    }

};


int main(void){
    cout<<"a"<<endl;
    Panel O(1,3);
    O(0,0) = true;
    O(0,1) = true;
    O(0,2) = true;

    cout<<O<<endl<<endl;
    Panel B(3,3);
    B(0,1) = true;
    B(1,2) = true;
    B(2,0) = true;
    B(2,1) = true;
    B(2,2) = true;
    Panel P(20,70);
    cout<<P<<endl<<endl;
    P.Combinar(O,12,40);
    P.Combinar(B,11,0);


    while(!P.Vacio()){
        system("cls");
        cout<<P;
        P++;
    }
    return 0;
}


//    Panel p,m;
//    cout<<p;
//    _sleep(1500);



//    cout<<"Panel introducido: " <<endl<<m;
//    cout<<endl<<endl;
//    //system("cls");
//    p.Combinar(m,0,1);
//    cout<<"Panel cambiado: " <<endl<<p;


//    return 0;

