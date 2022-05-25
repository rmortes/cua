#include<fstream>
#include <iostream>

using namespace std;

class Producto{

private:
    string nombre;
    int cantidad;
public:

    friend ostream& operator <<(ostream &medio, Producto objProductoout){
        cout<<"Nombre del producto: ";
        medio<<objProductoout.nombre<<endl;
        cout<<"Cantidad: ";
        medio<<objProductoout.cantidad<<endl;
        return(medio);
    }
    friend istream& operator >>(istream &medio, Producto &producto ){
        cout<<"Nombre del producto: "<<endl;
        medio>>producto.nombre;
        cout<<"Cantidad: "<<endl;
        medio>>producto.cantidad;
        return(medio);
    }
    int getCantidad(){
        return(cantidad);
    }
    void setCantidad(int CanNueva){
        cantidad=CanNueva;
    }

    string getnombreProducto(){
        return(nombre);
    }
    void grabar(ofstream &f){
        f<<nombre<<endl;
        f<<cantidad<<endl;
    }
    void cargar(ifstream &f){
        f>>nombre;
        f>>cantidad;
    }
};
class Tienda{
private:
    string nombre;
    Producto *productos;
    int tam;

    void copiarmemoria(const Tienda &origen){
        nombre = origen.nombre;
        tam=origen.tam;
        if(tam!=0){
            productos=new Producto[tam];
            for(int i=0;i<tam;i++){
                productos[i]=origen.productos[i];
            }
        }else{
            productos=NULL;
        }
        return;
    }

    void borrarmemoria(){
        if(productos!=NULL){
            delete []productos;
        }
        return;
    }
public:
    Tienda(){
        tam=0;
        productos=NULL;
        return;
    }
    Tienda(const Tienda &origen){
        copiarmemoria(origen);
    }
    Tienda operator=(Tienda origen){
        borrarmemoria();
        copiarmemoria(origen);
        return *this;
    }
    ~Tienda(){
        borrarmemoria();
    }
    void grabar(ofstream &f){
        f<<nombre<<endl;
        f<<tam<<endl;
        for(int i=0;i<tam;i++){
            productos[i].grabar(f);
        }
        return;
    }
    void cargar(ifstream &f){
        f>>nombre;
        f>>tam;
        productos=new Producto[tam];
        for(int i=0;i<tam;i++){
            productos[i].cargar(f);
        }
    }
    void ModificarProducto(void){
        Producto producto;
        cin>>producto;
        bool existe=false;
        for(int i=0;i<tam;i++){
            if(producto.getnombreProducto()==productos[i].getnombreProducto()){

                existe=true;
            }
        }
        if(!existe){
            Producto *aux=new Producto[tam+1];
            for(int i=0;i<tam;i++){
                aux[i]=productos[i];
            }
            aux[tam] = producto;
            if(productos!=NULL) delete[] productos;
            productos=aux;
            tam++;
        }else{
            producto.setCantidad(producto.getCantidad());
        }
    }
    friend istream& operator >>(istream &medio, Tienda &T ){
        cout<<"Nombre de la Tienda: "<<endl;
        medio>>T.nombre;
        return(medio);
    }
    friend ostream& operator <<(ostream &medio, Tienda T ){
        cout<<"Nomre de la Tienda: "<<endl;
        medio<<T.nombre<<endl;
        cout<<"Numero de productos en la tienda: "<<T.getNumProdTienda()<<endl;
        cout<<"Stock:"<<endl;
        for(int i=0;i<T.tam;i++){
            cout<<T.productos[i]<<endl;
        }
        return(medio);
    }

    void BuscarProducto(string NombreProducto,int &cent){
        int i;
        int detect=-1;
        for( i=0;i<tam;i++){
            if(NombreProducto==productos[i].getnombreProducto()){
                detect=i;
                cent++;
            }
        }
        if(detect!=-1){
            if(cent==1){
                cout<<productos[detect];
                cout<<"Este producto esta en : "<<endl;
            }
            cout<<nombre<<endl;
        }
    }
    void OrdenarProductos(){
        Producto aux;
        int i,j;
        for( i=0;i<tam;i++){
            for( j=0;j<tam-1;j++){
                if(productos[j].getnombreProducto()>productos[j+1].getnombreProducto()){
                    aux=productos[j];
                    productos[j]=productos[j+1];
                    productos[j+1]=aux;
                }
            }
        }
        return;
    }
    int getNumProdTienda(){
        return(tam);
    }
    string getnombreTienda(){
        return(nombre);
    }
};
class Asociacion{
private:
    string nombre;
    Tienda *tiendas;
    int tam;

    void copiarmemoria(const Asociacion &a){
        tam=a.tam;
        if(tam!=0){
            tiendas=new Tienda[tam];
            for(int i=0;i<tam;i++){
                tiendas[i]=a.tiendas[i];
            }
        }else{
            tiendas=NULL;
        }
        return;
    }

    void borrarmemoria(){
        if (tiendas!=NULL){
            delete []tiendas;
        }
    }

public:
    Asociacion(){
        tam=0;
        tiendas=NULL;
        return;
    }
    Asociacion(const Asociacion &origen){
        copiarmemoria(origen);
    }

    Asociacion operator=(Asociacion origen){
        borrarmemoria();
        copiarmemoria(origen);
        return *this;
    }
    ~Asociacion(){
        borrarmemoria();
    }

    void grabar(){
        ofstream f("salida.txt");
        f<<tam<<endl;
        for(int i=0;i<tam;i++){
            tiendas[i].grabar(f);
        }
        f.close();
        return;
    }
    void cargar(){
        ifstream f ("salida.txt");
        f>>tam;
        tiendas=new Tienda[tam];
        for(int i=0;i<tam;i++){
            tiendas[i].cargar(f);
        }
        f.close();
    }
    friend istream& operator >>(istream &medio, Asociacion &A ){
        Tienda objT;

        bool existe=false;

        cin>>objT;
        for(int i=0;i<A.tam;i++){
            if(objT.getnombreTienda()==A.tiendas[i].getnombreTienda()){
             A.tiendas[i].ModificarProducto();
                      existe=true;
            }
        }
        if(!existe){
            Tienda *vaux=new Tienda[A.tam+1];
            for(int i=0;i<A.tam;i++){
                vaux[i]=A.tiendas[i];
            }
            vaux[A.tam]=objT;
            vaux[A.tam].ModificarProducto();
            delete[] A.tiendas;
            A.tiendas=vaux;
            A.tam++;
        }
        return(medio);
    }
    friend ostream& operator <<(ostream &medio, Asociacion A){
        Tienda tienda;
        cout<<"Numero de Tiendas: "<<A.tam<<endl;
        for(int i=0;i<A.tam;i++){
            medio<<A.tiendas[i];
        }
        return(medio);
    }

    void BuscarProducto2(void){
        string NombredelProducto;
        int cent=0;
        cout<<"Introduce nombre del Producto: "<<endl;
        cin>>NombredelProducto;
        for(int i=0;i<tam;i++){
            tiendas[i].BuscarProducto(NombredelProducto,cent);
        }
    }
    void OrdenarTiendayProd(){
        Tienda orden;
        Tienda aux;
        int i,j;
        for( i=0;i<tam;i++){
            for( j=0;j<tam-1;j++){
                if(tiendas[j].getnombreTienda()>tiendas[j+1].getnombreTienda()){
                    aux=tiendas[j];
                    tiendas[j]=tiendas[j+1];
                    tiendas[j+1]=aux;
                }
            }
        }
        for(int k=0;k<tam;k++){
            tiendas[k].OrdenarProductos();
        }
        return;
    }
};
class Menu{
private:
    bool ok;
    string palabra;
    Asociacion A;
public:
    void InicioMenu(void){
        A.cargar();
        int eleccion;
        bool seguir=true;
        do{
            do{
                cout<<"----> MENU PRINCIPAL <----"<<endl;
                cout<<"1 Modificar Producto"<<endl;
                cout<<"2 Buscar extistencias "<<endl;
                cout<<"3 Ordenar"<<endl;
                cout<<"4 Listar tiendas y productos"<<endl;
                cout<<"5 Salir"<<endl;
                cin>>eleccion;
                if(eleccion<=0 || eleccion>=6){
                    cout<<"Error\n"<<endl;
                }
            }while(eleccion<=0 || eleccion>=6);
            switch(eleccion){
            case 1:
                system("cls");
                cin>>A;
                break;
            case 2:
                system("cls");
                A.BuscarProducto2();
                break;
            case 3:
                system("cls");
                A.OrdenarTiendayProd();
                break;
            case 4:
                system("cls");
                cout<<A;
                break;
            case 5:
                seguir=false;
            }
        } while(seguir);
        A.grabar();
        return;
    }
};
int main(void){
    Menu m;
    m.InicioMenu();
    return(0);
}
