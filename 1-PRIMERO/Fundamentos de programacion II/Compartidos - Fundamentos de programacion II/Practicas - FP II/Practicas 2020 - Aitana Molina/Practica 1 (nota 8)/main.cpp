#include <iostream>

using namespace std;

//clase item contiene un string y un booleano
class Item{
private:
    string item;//nombre de un alimento,objeto...
    bool validado;//si esta hecho/comprado o no
public:
    //constructor por defecto para inicializar atributos
    Item(){
        validado = false;
    }
    //pedir datos
    void SolicitarItem(){
        cout<<"Item: ";
        cin>>item;
        return;
    }
    void Validar(){//cambia el estado del booleano
        validado= !validado;
        return;
    }
    friend bool operator==(Item a1,Item a2){
        return a1.item==a2.item;
    }
    bool getValidado(void){
        return validado;
    }
    void MostrarItem(){
        if(validado==true){
            cout<<"\t[ok]";
        }else{
            cout<<"\t[  ]";
        }
        cout<<" "<<item<<endl;
        return;
    }
};

//clase que almacena items
class List{
private:
    string nombrelista;//nombre de una lista
    Item *L;//vector dinamico que contiene items
    int N;//numero de elementos del vector
public:
    //constructor por defecto
    List(){
        L = NULL;
        N = 0;
    }
    //constructor de copia ya que hay un atributo dinamico
    List(const List &l){
        nombrelista = l.nombrelista;// copia el nombre del objeto list recibido al objeto actual
        if (l.L== NULL){//si el vector contenido en el objeto list no apunta a nada, inicializa el numero de items y el vector de items
            N = 0;
            L = NULL; // no apunta a nada
        }else{// si tiene items crea un vector de items de longitud igual al vector de items del objeto list recibido
            L = new Item [l.N];//vector dinamico
            for(int i=0;i<l.N;i++){
                L[i]=l.L[i];//copia el vector de items recibido con el actual, posicion por posicion
            }
            N = l.N;//copia el numero de alumnos del objeto list recibido al objeto actual
        }
    }
    //destructor de list
    ~List(){
        if(L != NULL){//si el vector de items no es un apuntador nulo
            delete [] L;//libera la memoria reservada por el vector items
        }
    }
    //operador asignacion
    List operator=(List origen){
        //codigo destructor
        if(L != NULL){//si el vector de items no es un apuntador nulo
            delete [] L;//libera la memoria reservada por el vector items
        }
        //codigo constructor
        nombrelista = origen.nombrelista;// copia el nombre del objeto list recibido al objeto actual
        if (origen.L== NULL){//si el vector contenido en el objeto list no apunta a nada, inicializa el numero de items y el vector de items
            N = 0;
            L = NULL; // no apunta a nada
        }else{// si tiene items crea un vector de items de longitud igual al vector de items del objeto list recibido
            L = new Item [origen.N];//vector dinamico
            for(int i=0;i<origen.N;i++){
                L[i]=origen.L[i];//copia el vector de items recibido con el actual, posicion por posicion
            }
            N = origen.N;//copia el numero de alumnos del objeto list recibido al objeto actual
        }
        return *this;
    }
    string getNombreLista(){
        return nombrelista;
    }
    void Solicitar(){
        cout<<"Nombre lista: ";
        cin>>nombrelista;
        cout<<endl;
     /* Para una mejora estetica de la practica quise poner el nombre
     * de la lista con letras mayusculas, al buscar en internet encontre la funcion toupper
     * que permite pasar de minusculas a mayusculas */

        int largo=nombrelista.size();//longitud del nombre de la lista
        for(int i=0;i<largo;i++){
            nombrelista[i]=toupper(nombrelista[i]);//pasar todas las letras a mayuscula con bucle for
        }
    }
    void AddItem(){//ensanchar el vector vitems que esta lleno de items crear un nuevo vector mas grande donde copiar lo que hay en el vector original
        Item a;
        //pedir items
        a.SolicitarItem();
        bool nuevo = false;//comprueba si hay un item igual en la lista
        //si compruebo que hay dos items con el mismo nombre, no doy memoria al vector, no hago nada
        for(int i=0;i<N;i++){
            if(a==L[i]){
                nuevo = true;
            }
        }
        //si no existe un item que se llame igual en el vector, le doy memoria
        if(nuevo==false){
            Item *aux = new Item[N+1];//N+1 para darle un hueco mas del original
            //copiar vitems en aux
            for(int i=0;i<N;i++){
                aux[i]=L[i];
            }
            //rellenar el ultimo hueco
            aux[N]=a;
            //liberar vitems
            if(L!=NULL){
                delete []L;
            }
            //hacer que vitems apunte a aux
            L=aux;
            //incrementar N
            N++;
        }
        return;
    }
    //mostrar los items en el vector de lista
    void Mostrar(){
        for(int i=0;i<N;i++){
            L[i].MostrarItem();
        }
        return;
    }
    //compara un item introducido con el usuario con uno que este en la lista para checarlo
    void ValidarItem(){
        Item A;
        A.SolicitarItem();
        for(int i=0;i<N;i++){
            if(A==L[i]){
                L[i].Validar();
            }
        }
        return;
    }
    //elimina los elementos de una lista que esten validados
    void PurgarLista(){
        //contar los elementos que estan a false y guardarlos en una variable
        int falso=0;
        for(int i=0;i<N;i++){
            if(L[i].getValidado()==false){
                falso++;
            }
        }
        if(falso>0){//asegurar que hay alguno a false
            //vector auxiliar con tamaño de elementos a false
            Item *aux = new Item[falso];
            //copiar info de vitems en aux
            int contador=0;
            for(int i=0;i<N;i++){
                if(L[i].getValidado()==false){
                    aux[contador]=L[i];
                    contador++;
                }
            }
            //eliminar hueco
            if(L!=NULL){
                delete []L;
            }
            //volcar aux en vitems
            L=aux;
            //rellenar el hueco que deja un elemento eliminado
            N=falso;
        }else{
            //si falso es negativo, eliminar vector
            if(L!=NULL) delete[]L;
            L = NULL;
            N=0;
        }
        return;
    }
};
class CheckList{
private:
    List *v;
    int N;
public:
    CheckList(){
        v = NULL;
        N = 0;
    }
    //constructor de copia ya que hay un atributo dinamico
    CheckList(const CheckList &l){
        if (l.v== NULL){//si el vector contenido en el objeto list no apunta a nada, inicializa el numero de items y el vector de items
            N = 0;
            v = NULL;
        }else{
            v = new List [l.N];//vector dinamico
            for(int i=0;i<l.N;i++){
                v[i]=l.v[i];
            }
            N = l.N;
        }
    }
    //destructor de list
    ~CheckList(){
        if(v != NULL){
            delete [] v;
        }
    }
    //operador asignacion
    CheckList operator=(CheckList origen){
        //codigo destructor
        if(v != NULL){
            delete [] v;//libera la memoria reservada por el vector items
        }
        //codigo constructor
        if (origen.v== NULL){
            N = 0;
            v = NULL;
        }else{
            v = new List [origen.N];
            for(int i=0;i<origen.N;i++){
                v[i]=origen.v[i];
            }
            N = origen.N;
        }
        return *this;
    }
    //Solicitar la lista
    void SolicitarLista(){
        for(int i=0;i<N;i++){
            v[i].Solicitar();
        }
        return;
    }
    //añadir una lista al vector de checklist List *v
    void AddLista(){
        List L;
        //pedir listas
        L.Solicitar();
        bool nuevo = false;//ver si hay un item igual en la lista
        //si compruebo que hay dos listas con el mismo nombre, no doy memoria al vector, no hago nada
        for(int i=0;i<N;i++){
            if(L.getNombreLista()==v[i].getNombreLista()){
                v[i].AddItem();
                nuevo = true;
            }
        }
        //si no existe un item que se llame igual en el vector, le doy memoria
        if(nuevo==false){
            List *aux = new List[N+1];
            //copiar vitems en aux
            for(int i=0;i<N;i++){
                aux[i]=v[i];
            }
            //rellenar el ultimo hueco añadiendo items
            aux[N]=L;
            aux[N].AddItem();
            //liberar vitems
            if(v!=NULL){
                delete []v;
            }
            //hacer que vitems apunte a aux
            v=aux;
            //incrementar N
            N++;
        }
        return;
    }
    //mostrar las listas con sus items
    void MostrarCL(){
        for(int i=0;i<N;i++){
            cout<<v[i].getNombreLista()<<endl;
            v[i].Mostrar();
        }
        return;
    }
    void ValidarLista(){
        List L;
        L.Solicitar();
        for (int i=0;i<N;i++) {
            if(L.getNombreLista()==v[i].getNombreLista()){
                v[i].ValidarItem();

            }

        }
        return;
    }
    void PurgarList(){
        List A;
        A.Solicitar();
        for (int i=0;i<N;i++) {
            if(A.getNombreLista()==v[i].getNombreLista()){
                v[i].PurgarLista();
            }
        }
        return;
    }
};

class Menu{
private:
    CheckList c;
public:
    void Imprimir(){
        system("cls");
        c.MostrarCL();
        cout<<"-.-.-.-Menu-.-.-.-"<<endl;
        cout<<"Elija opcion "<<endl;
        cout<<"1) Nuevo item"<<endl;
        cout<<"2) Validar item"<<endl;
        cout<<"3) Purgar lista"<<endl;
        cout<<"4) Terminar"<<endl;
        cout<<"Opcion: ";
        return;
    }
    void ejecutar(){
        int opc;
        do{
            Imprimir();
            cin>>opc;
            switch (opc) {
            case 1://solicitar lista e items
                c.AddLista();
                break;
            case 2://validar item
                c.ValidarLista();
                break;
            case 3://prugar lista
                c.PurgarList();
                break;
            case 4:
                break;
            default://en ninguno de los casos anteriores
                cout<<"Introduzca numero correcto."<<endl;
                break;
            }
        }while(opc!=4);
    }
};
int main(void){
    Menu m;
    m.ejecutar();
    return 0;
}

