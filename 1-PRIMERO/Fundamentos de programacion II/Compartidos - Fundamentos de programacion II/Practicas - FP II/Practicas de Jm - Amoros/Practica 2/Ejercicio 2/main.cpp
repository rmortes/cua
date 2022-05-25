#include <iostream>
#include <time.h>
#include <iomanip>
#include <conio.h>
#include <cstdlib>
using namespace std;
template<class t>
class matrizT{
protected:
    t**m;
    int nf,nc;
public:
    matrizT(){//constructor
        m=NULL;
        nf=0;
        nc=0;
        return;
    }
    matrizT (int nf_,int nc_){//constructor con parametros
        nc=nc_;
        nf=nf_;
        m=new t*[nf];
        for(int i=0;i<nf;i++){
            m[i]=new t [nc];//reservo memoria para cada elemto de la fila
        }
        for(int i=0;i<nf;i++){
            for(int j=0;j<nc;j++){
                m[i][j]=rand()%100;//relleno aleatoriamente la matriz creada con num entre 0 y 99
            }
        }
        return;
    }
    ~matrizT(){//desctructor
        destructor();
    }
    void destructor(void){
        if(m!=NULL){
            for(int i=0;i<nf;i++){
                delete[]m[i];
            }
            delete []m;
        }
    }
    matrizT (const matrizT &origen){//constructor de copia
        nc=origen.nc;
        nf=origen.nf;
        m=new t*[nf];//repasar
        for(int i=0;i<nf;i++){
            m[i]=new int [nc];//reservo memoria para cada elemto de la fila
        }
        for(int i=0;i<nf;i++){
            for(int j=0;j<nc;j++){
                m[i][j]=origen.m[i][j];
            }
        }
        return;
    }
    matrizT operator + ( const matrizT a){//sobrecarga del operador suma
        nc=a.nc;
        nf=a.nf;
        matrizT mresultado(nf,nc);
        for(int i=0;i<nf;i++){
            for(int j=0;j<nc;j++){
                mresultado.m[i][j]=m[i][j]+a.m[i][j];
            }
        }
        return(mresultado);
    }
    matrizT operator - ( const matrizT a){//sobrecarga del operador restar
        nc=a.nc;
        nf=a.nf;
        matrizT mresultado(nf,nc);
        for(int i=0;i<nf;i++){
            for(int j=0;j<nc;j++){
                mresultado.m[i][j]=m[i][j]-a.m[i][j];
            }
        }
        return(mresultado);
    }
    friend ostream& operator <<(ostream &medio,matrizT x ){//operador de flujo de salida
        for(int i=0;i<x.nf;i++){// no me funciona bien aunke si compila
            for(int j=0;j<x.nc;j++){
                medio<<setw(7)<<x.m[i][j];
            }
            medio<<endl;
        }
        return (medio);
    }
    matrizT operator=(  matrizT a){
        if(a.nc!=nc || a.nf!=nf){//comparo las matrices
            if(m!=NULL)destructor();
            nc=a.nc;
            nf=a.nf;
            m=new t*[nf];
            for(int i=0;i<nf;i++){
                m[i]=new t [nc];//reservo memoria para cada elemto de la fila
            }
        }
        for(int i=0;i<nf;i++){
            for(int j=0;j<nc;j++){
                m[i][j]=a.m[i][j];
            }
        }
        return(*this);
    }
    matrizT operator *( matrizT a){
        matrizT mr(nf,a.nc);//multiplica A*B
        int n;
        n=0;
        if(nc==a.nf){
            for(int i=0;i<nf;i++){//recorro columnas de a
                for(int j=0;j<a.nc;j++){//recorro filas de b de la matriz resultado
                     n=0;
                    for(int c=0;c<nc;c++){
                     n=n+(m[i][c]*a.m[c][j]);
                     mr.m[i][j]=n;
                    }
                }
            }
        }else{
            cout<<"el tamaño que tiene las matrices no es valido para hacer el producto"<<endl;
        }
        return(mr);
    }
    matrizT operator +=(const matrizT &a){//sobrecarga operador +=
      (*this)+a=(*this);
        return(*this);
    }
    matrizT operator -=(const matrizT &a){//sobrecarga operador -=
      (*this)-a=(*this);
        return(*this);
    }
    matrizT operator *=(const matrizT &a){//sobrecarga operador *=
      (*this)*a=(*this);
        return(*this);
    }
    void pinta(void){
        if(nf==0|| nc==0)cout<<"Matriz Nula"<<endl;
        else{
            for(int i=0;i<nf;i++){//para pintar los marcos de las matrices
                if(i<nf)for(int r=-1;r<nc*7;r++)cout<<"-";
                if(i<nf)cout<<endl;
                for(int j=0;j<nc;j++){
                    cout<<"|"<<setw(4)<<m[i][j]<<setw(3);
                }
                cout<<"|"<<endl;
                if(i==nf-1)for(int r=-1;r<nc*7;r++)cout<<"-";
            }
            cout<<endl;
            cout<<endl;
        }
        return;
    }
    matrizT operator *(int n){//sobrecarga operador multiplicacion
        matrizT mr(nf,nc);
        for(int i=0;i<nf;i++){
          for(int j=0;j<nc;j++){
              mr.m[i][j]=n*m[i][j];
        }
      }
        return(mr);
    }
    friend matrizT operator *(int n,matrizT r){//sobrecarga operador * pasando un escalar
        matrizT mr;//
        mr=r*n;///
        return(mr);
    }
};


        int main (void){

            matrizT<int>a(3,3);

            a.pinta();

            getch();


            return(0);
        }
