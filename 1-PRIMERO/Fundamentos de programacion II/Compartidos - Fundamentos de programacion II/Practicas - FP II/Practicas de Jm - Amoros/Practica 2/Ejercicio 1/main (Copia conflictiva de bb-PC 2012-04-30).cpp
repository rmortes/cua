#include <iostream>
#include <time.h>
#include <iomanip>
#include <conio.h>
#include <cstdlib>
using namespace std;
class matriz{
protected:
    int **m;
    int nf,nc;
public:
    matriz(){//constructor
        m=NULL;
        nf=0;
        nc=0;
        return;
    }
    matriz (int nf_,int nc_){//constructor con parametros
        nc=nc_;
        nf=nf_;
        m=new int*[nf];
        for(int i=0;i<nf;i++){
            m[i]=new int [nc];//reservo memoria para cada elemto de la fila
        }
        for(int i=0;i<nf;i++){
            for(int j=0;j<nc;j++){
                m[i][j]=rand()%100;//relleno aleatoriamente la matriz creada con num entre 0 y 99
            }
        }
        return;
    }
    ~matriz(){//desctructor
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
    matriz (const matriz &origen){//constructor de copia
        nc=origen.nc;
        nf=origen.nf;
        m=new int*[nf];//repasar
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
    matriz operator + ( const matriz a){//sobrecarga del operador suma
        nc=a.nc;
        nf=a.nf;
        matriz mresultado(nf,nc);
        for(int i=0;i<nf;i++){
            for(int j=0;j<nc;j++){
                mresultado.m[i][j]=m[i][j]+a.m[i][j];
            }
        }
        return(mresultado);
    }
    matriz operator - ( const matriz a){//sobrecarga del operador restar
        nc=a.nc;
        nf=a.nf;
        matriz mresultado(nf,nc);
        for(int i=0;i<nf;i++){
            for(int j=0;j<nc;j++){
                mresultado.m[i][j]=m[i][j]-a.m[i][j];
            }
        }
        return(mresultado);
    }
    friend ostream& operator <<(ostream &medio,matriz x ){//operador de flujo de salida
        for(int i=0;i<x.nf;i++){// no me funciona bien aunke si compila
            for(int j=0;j<x.nc;j++){
                medio<<setw(7)<<x.m[i][j];
            }
            medio<<endl;
        }
        return (medio);
    }
    matriz operator=(  matriz a){
        if(a.nc!=nc || a.nf!=nf){//comparo las matrices
            if(m!=NULL)destructor();
            nc=a.nc;
            nf=a.nf;
            m=new int*[nf];
            for(int i=0;i<nf;i++){
                m[i]=new int [nc];//reservo memoria para cada elemto de la fila
            }
        }
        for(int i=0;i<nf;i++){
            for(int j=0;j<nc;j++){
                m[i][j]=a.m[i][j];
            }
        }
        return(*this);
    }
    matriz operator *( matriz a){
        matriz mr(nf,a.nc);//multiplica A*B
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

    matriz operator +=(const matriz &a){//sobrecarga operador +=
      (*this)+a=(*this);
        return(*this);
    }
    matriz operator -=(const matriz &a){//sobrecarga operador -=
      (*this)-a=(*this);
        return(*this);
    }
    matriz operator *=(const matriz &a){//sobrecarga operador *=
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
    matriz operator *(int n){//sobrecarga operador multiplicacion
        matriz mr(nf,nc);
        for(int i=0;i<nf;i++){
          for(int j=0;j<nc;j++){
              mr.m[i][j]=n*m[i][j];
        }
      }
        return(mr);
    }
    friend matriz operator *(int n,matriz r){//sobrecarga operador * pasando un escalar
        matriz mr;//
        mr=r*n;///
        return(mr);
    }
};
class matrizc: public matriz  {//clase matric cuadrada hereda de matriz
protected:
public:
    matrizc():matriz(){//constructor por defecto
    }
    matrizc(int t):matriz(t,t){//constructor por parametros
    }
    matrizc (matriz a):matriz(a){//constructor de conversion
    }
   /* friend  matrizc operator^ (matrizc a,int n) { //revisar  !!!!VOY POR AKIIII!!!!!!!
        //matriz identidad
        matrizc b,r;
        for(int i=0;i<a.nc;i++){
            for(int j=0;j<a.nc;j++){
                b.m[i][j]=0;//relleno
                if(i==j)b.m[i][j]=1;
            }
        }
        //a=b;
        for(int i=0;i<n;i++)r=b*a;
        return(r);
    }*/
    void  mostrar(void){
        matriz::pinta()  ;
    }
};
class matrizd :public matrizc{//clase  diagonal hereda de clase matriz cuadrada
protected:
public:
    matrizd():matrizc(){
    }
    matrizd(int t):matrizc(t){//constructor por parametros

        for(int i=0;i<t;i++){
            for(int j=0;j<t;j++){
               if(i!=j) m[i][j]=0;//relleno aleatoriamente la matriz creada con num entre 0 y 99
            }
        }


    }
    matrizd (matriz a):matrizc(a){//constructor de conversion
    }
    void mostrar (void){//metodo pintar
        matrizc::mostrar();
    }
};
class matrizp :public matrizc{//clase permutacion hereda de clase matriz cuadrada
protected:
    int t ;
public:
    matrizp(){} //constructor por defecto
    matrizp(int t):matrizc(t){//constructor por parametros
        for(int i=0;i<t;i++){//relleno una matriz con la diagonal de unos y el resto de 0
            for(int j=0;j<t;j++){
                m[i][j]=0;
                if(i==j) m[i][j]=1; //rellenamos
            }
        }
        srand(time(NULL));//aleatorio
        int v[t];//creo un vector del tamaño t
        int n,repite;//sera un aux
        int cont;//contador de veces que guardo el numero en el vector
        int aux[t][t];//matriz auxiliar para pegar el cambiazo
        repite=0;//inicio a o


        do{

            cont=0;
             for(int i=0;i<t;i++){//guardo en n un aleatorio entre 0 y 4
                 n=rand()%5;
                 if(i==0){//guardara el 1 numero almacenado en n en la 1º posicion del vector
                     v[i]=n;
                     cont++ ;
                 }
                 if(i>0){
                     for(int r=0;r<t*t;r++){
                         for(int j=0;j<cont;j++){
                             if(n==v[j]) {
                                 n=rand()%5;
                                 j=t;
                             }
                         }
                     }
                     if(n!=v[i]) {
                         v[i]=n;
                         cont++;
                     }
                 }
             }
        }while(cont!=5);//repetira mientras el contador de numero distientos no sea 5
        cout<<"aki";
                    getch();
        for(int i=0;i<t;i++){
            for(int j=0;j<t;j++){

                aux[i][j]=m[v[i]][j];//copiamos a un axiliar cambiando  el orden
            }
        }
        for(int i=0;i<t;i++){
            for(int j=0;j<t;j++){
                m[i][j]=aux[i][j];//y devolvemos a su sitio
            }
        }
        return;
    }
    void  mostrar(void){
        matriz::pinta()  ;
    }
};
int main (void){
    srand(time(NULL));
    //matriz a(3,2);
   // matrizc b(3);
   // matrizd c(3);
    matrizd a(4);


    //a.mostrar();
    // b.mostrar();
     // c.mostrar();
       a.mostrar();
    getch();
    return(0);
}
