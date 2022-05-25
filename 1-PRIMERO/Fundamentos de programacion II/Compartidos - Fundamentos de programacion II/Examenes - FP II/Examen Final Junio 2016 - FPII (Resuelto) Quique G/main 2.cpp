#include <iostream>
#include <time.h>
#include <stdlib.h>

using namespace std;

//Clase Principal//
template <class T>
class Vector{
protected:
    T *vector;
    int tamanyo;
public:    Vector(){//Por defecto
        tamanyo = 0;
        vector = NULL;
    }
    Vector(int cantidad){//Por parametros
        tamanyo = cantidad;
        vector = new T[tamanyo];
        for(int i=0; i<tamanyo; i++) vector[i] = (rand()%100)/10.0;
    }
    Vector(const Vector &original){//copia
        Copiar(original);
    }
    ~Vector(){
        Limpiar();
    }

    //Métodos generales
    void Copiar(const Vector &original){
        tamanyo = original.tamanyo;
        vector = new T[tamanyo];
        for(int i = 0; i<tamanyo; i++) vector[i] = original.vector[i];
        return;
    }
    void Limpiar(){
        tamanyo = 0;
        if(vector) delete []vector;
        return;
    }
    virtual void Comprobar(){

    }

    Vector operator =(Vector asignado){
        Limpiar();
        Copiar(asignado);
        Comprobar();
        return *this;
    }


    friend Vector operator +(Vector a, Vector b){
        Vector resultado(a.tamanyo);
        if(a.tamanyo==b.tamanyo){
            for(int i=0; i<a.tamanyo; i++) resultado.vector[i] = a.vector[i] + b.vector[i];
        }else resultado.Limpiar();
        return resultado;
    }
    friend Vector operator -(Vector a, Vector b){
        Vector resultado(a.tamanyo);
        if(a.tamanyo==b.tamanyo){
            for(int i=0; i<a.tamanyo; i++) resultado.vector[i] = a.vector[i] - b.vector[i];
        }else resultado.Limpiar();
        return resultado;
    }

    friend Vector operator *(Vector a, int b){
        Vector resultado(a.tamanyo);
        for(int i=0; i<a.tamanyo; i++) resultado.vector[i]=a.vector[i]*b;
        return resultado;
    }
    friend Vector operator *(int b, Vector a){
        return a*b;
    }
    friend bool operator ==(Vector a,Vector b){
        bool igualdad = true;
        if(a.tamanyo==b.tamanyo){
            for(int i=0;i<a.tamanyo;i++){
                if(a.vector[i]!=b.vector[i]) igualdad = false;
            }
        }else{
            igualdad = false;
        }
        return igualdad;

    }
    friend ostream& operator <<(ostream &mostrar, Vector pasado){
        for(int i=0; i<pasado.tamanyo; i++) mostrar << pasado.vector[i] << " ";
        mostrar << endl;
        return mostrar;
    }

};

//Clase Vector Creciente//
template <class T>
class VectorC:public Vector<T>{
public:
    VectorC():Vector<T>(){

    }
    VectorC(int cantidad):Vector<T>(cantidad){
        Vector<T>::vector[0]=((rand()%100)/10.0);
        for(int i=1; i<Vector<T>::tamanyo; i++){
            Vector<T>::vector[i]= Vector<T>::vector[i-1]+((rand()%100)/10.0);
        }
        Comprobar();
    }
    VectorC(const Vector<T> &original):Vector<T>(original){

    }
    void Comprobar(){
        for(int i=1; i<Vector<T>::tamanyo; i++){
            if(Vector<T>::vector[i]<=Vector<T>::vector[i-1]){
                if(Vector<T>::vector[i] != 0) Vector<T>::Limpiar();
            }
            return;
        }
    }
};

//Clase Vector Decreciente//
template <class T>
class VectorD:public Vector<T>{
public:
    VectorD():Vector<T>(){

    }
    VectorD(int cantidad):Vector<T>(cantidad){
        Vector<T>::vector[0]=((rand()%100)/10.0);
        for(int i=1; i<Vector<T>::tamanyo; i++){
            Vector<T>::vector[i]= Vector<T>::vector[i-1]-((rand()%100)/10.0);
        }
        Comprobar();
    }
    VectorD(const Vector<T> &original):Vector<T>(original){

    }
    void Comprobar(){
        for(int i=1; i<Vector<T>::tamanyo; i++){
            if(Vector<T>::vector[i]>=Vector<T>::vector[i-1]){
                if(Vector<T>::vector[i] != 0) Vector<T>::Limpiar();
            }
            return;
        }
    }
};

//Clase Vector Gruyer//
template <class T>
class VectorG:public Vector<T>{
public:
    VectorG():Vector<T>(){

    }
    VectorG(int cantidad):Vector<T>(cantidad){
        for(int i=0; i<Vector<T>::tamanyo; i++){
            if(i%2==0) Vector<T>::vector[i] = 0;
        }
        Comprobar();
    }
    VectorG(const Vector<T> &original):Vector<T>(original){

    }
    void Comprobar(){
        for(int i=0; i<Vector<T>::tamanyo; i++){
            if(i%2==0){
                if(Vector<T>::vector[i] != 0) Vector<T>::Limpiar();
            }
            return;
        }
    }
};

//Clase Vector Simetrico//
template <class T>
class VectorS:public Vector<T>{
public:
    VectorS():Vector<T>(){

    }
    VectorS(int cantidad):Vector<T>(cantidad){
        for(int i=0;i<(Vector<T>::tamanyo)/2;i++){
            Vector<T>::vector[i]= ((rand()%100)/10.0);
            Vector<T>::vector[(Vector<T>::tamanyo-1)-i]=Vector<T>::vector[i];
        }
        Comprobar();


    }
    VectorS(const Vector<T> &original):Vector<T>(original){

    }
    void Comprobar(){
        for(int i=0;i<(Vector<T>::tamanyo)/2;i++){
            if(Vector<T>::vector[(Vector<T>::tamanyo-1)-i]!=Vector<T>::vector[i]) Vector<T>::Limpiar();
        }
        return;
    }
};

//Clase Vector Par//
template <class T>
class VectorPa:public Vector<T>{
public:
    VectorPa():Vector<T>(){

    }
    VectorPa(int cantidad):Vector<T>(cantidad){
        for(int i=0;i<(Vector<T>::tamanyo);i++){
            Vector<T>::vector[i]= ((rand()%100)/10.0);
            Vector<T>::vector[i]=Vector<T>::vector[i]*2;
        }
        Comprobar();


    }
    VectorPa(const Vector<T> &original):Vector<T>(original){

    }
    void Comprobar(){
        for(int i=0;i<(Vector<T>::tamanyo)/2;i++){
            if(Vector<T>::vector[i]%2 != 0) Vector<T>::Limpiar();
        }
        return;
    }

};





int main(void){
    srand(time(NULL));
    VectorD<int> a(5);
    VectorC<int> b(5);
    VectorG<int> c(5);
    VectorS<int> d(5);
    VectorPa<int> e(5);









    return 0;

}
