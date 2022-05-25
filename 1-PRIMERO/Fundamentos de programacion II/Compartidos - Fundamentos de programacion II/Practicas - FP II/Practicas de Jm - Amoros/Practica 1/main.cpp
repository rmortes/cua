#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <fstream>

using namespace std;

class fecha{
    friend class agenda; //amistad con la clase agenda para acceder a los atributos.
private:
    // atributos para almacenar la fecha y su comprobacion
    int dd,mm,aa;
    bool valido;
public:

    // operador de entrada,solicitamos al usuario los datos de fecha
    friend istream& operator >> (istream &medio, fecha &f2){
        do{
            cout << "Introduce el dia: "; medio >> f2.dd; medio.ignore();
            cout << "Introduce el mes: "; medio >> f2.mm; medio.ignore();
            cout << "Introduce el anyo: "; medio >> f2.aa; medio.ignore();
            //almacenamos el resultado booleano de la llamada al metodo comprobar
            f2.valido=f2.comprobar();
            //el bucle se repetirá hasta ingresar una fecha correcta
        }while (f2.valido==false);
        return(medio);
    }

    //operador de salida, mostramos al usuario los datos de fecha
    friend ostream& operator << (ostream &medio, fecha f2){
        medio << "Fecha nacimiento: " << f2.dd << "/" << f2.mm << "/" << f2.aa << endl;
        return(medio);
    }


    //metodo para comprobar que la fecha es correcta
    bool comprobar (){
        //inicializamos suponiendo que la fecha es correcta
        valido=true;
        //los condicionales determinaran si hay error
        if (dd<1 || dd>31) valido=false;
        if (mm<1 || mm>12) valido=false;
        if (aa<1950 || aa>2011) valido=false;
        return (valido);
    }

};




class direccion{
    //amistad con la clase agenda para esta pueda acceder a los atributos.
    friend class agenda;
private:
    //atributos para almacenar la direccion
    string calle, localidad;
    int numero;
public:

    //operador de entrada, solicitamos al usuario los datos de direccion
    friend istream& operator >> (istream &medio, direccion &d2){
        cout << "Introduce la calle: ";getline (medio,d2.calle);
        cout << "Introuce el numero: "; medio >> d2.numero; medio.ignore();
        cout << "Introduce la localidad: "; getline (medio,d2.localidad);
        return(medio);
    }

    //operador de salida, mostramos al usuario los datos de direccion
    friend ostream& operator << (ostream &medio, direccion d2){
        cout << "Calle: "; medio << d2.calle << endl;
        cout << "Numero: "; medio << d2.numero << endl;
        cout << "Localidad: "; medio << d2.localidad << endl;
        return(medio);
    }

};


class contacto{
    //amistad con la clase agenda para esta pueda acceder a los atributos.
    friend class agenda;
private:
    //atributos que almacenar los datos del contacto
    fecha f1;
    direccion d1;
    string nombre, apellidos;

public:

    //operador de entrada, solicitamos los datos del contacto
    friend istream& operator >> (istream &medio, contacto &c1){
        system("cls");
        cout <<"Introduce el nombre: "; getline (medio,c1.nombre);
        cout << "Introduce los apellidos: "; getline (medio,c1.apellidos);
        medio >> c1.f1;
        medio >> c1.d1;
        return(medio);
    }

    //operador de salida, mostramos los datos del contacto
    friend ostream& operator << (ostream &medio, contacto c1){
        cout << "Nombre: "; medio << c1.nombre<< endl;
        cout << "Apellidos: "; medio << c1.apellidos<< endl;
        medio << c1.f1;
        medio << c1.d1;
        cout << endl;
        return(medio);
    }
};



class agenda{
private:
    string buscarnombre;//atributos para almacenar el nombre que emplearemos en la busqueda,
    contacto *lista; // un puntero para crear la lista de contactos
    bool centinela; // un centinela para saber si existe o no ese contacto
    int n; // un entero para almacenar el numero de contactos
public:


    agenda (){//constructor de agenda que llama al metodo cargar
        cargar();
        return;
    }


    ~agenda (){ //destructor de agenda
        if (lista!=NULL){ // siempre que contenga algo la lista de contactos
            guardar();// se encargara de guardar y borrar la lista
            delete []lista;
        }
        return;
    }


    agenda (const agenda &copialista){ //constructor de copia
        n=copialista.n;
        lista= new contacto[n];
        //se encarga de copiar el contenido del objeto de la clase agenda
        for (int i=0; i<n; i++){
            lista[i]=copialista.lista[i];
        }
        return;
    }


    //añadir un contacto recibido como parametro a la agenda con autosuma
    void operator+=(contacto micontac){
        cin>>micontac; // solicitamos los datos para ese contacto que hemos recibido
        // creamos un objeto vector auxiliar de la clase contacto y le asignamos un
        // tamaño mayor que el actual de la lista de contactos
        contacto *aux=new contacto [n+1];
        //copiamos el contenido de la lista de contactos en el vector auxiliar
        for (int i=0;i<n;i++) aux[i]=lista[i];
        delete []lista; // borramos el vector de la lista de contactos
        lista=aux;//igualamos ambos vectores
        lista[n]=micontac; // introducimos el contacto añadido en la ultima posicion del vector
        n++;//incrementamos el numero de la lista de contactos para su proxima ejecucion
        return;
    }

    //metodo para guardar los datos de la lista de contactos
    void guardar (void){
        //creamos objeto ofstream para guardar los datos en un archivo de texto
        ofstream fichero ("datos.txt");
        //volcamos los datos de los atributos de la lista de contactos en el fichero
        fichero << n << endl;
        // para ello recorremos el vector de la lista de contactos
        // guardamos linea a linea el valor de los atributos del contacto
        for (int i=0;i<n;i++){
            fichero << lista[i].nombre << endl;
            fichero << lista[i].apellidos << endl;
            fichero << lista[i].f1.dd << endl;
            fichero << lista[i].f1.mm << endl;
            fichero << lista[i].f1.aa << endl;
            fichero << lista[i].d1.calle << endl;
            fichero << lista[i].d1.numero << endl;
            fichero << lista[i].d1.localidad;
            //tenemos en cuenta que el bucle podria guardar el salto de linea
            // y lo evitaremos cuando el incremento del bucle llegue a la ultima posicion
            if (i!=n-1) fichero << endl;
        }
        //cerramos el fichero
        fichero.close();
        return;
    }

    //metodo para cargar los datos de la lista de contactos
    void cargar (void){
        //creamos  objeto ifstream para abrir un archivo de texto y poder cargarlos
        ifstream fichero ("datos.txt");
        //si el fichero existe lo abre
        if(fichero.good()==true){
            //recorre el fichero hasta la ultima line escrita
            while (fichero.eof()==false){
                //carga el numero de contactos
                fichero >> n;
                fichero.ignore();
                //creamos el vector dinamico con el numero de contactos que acabamos de cargar
                lista=new contacto [n];
                //recorremos la lista de contactos cargando cada uno de sus atributos
                for (int i=0;i<n;i++){
                    getline(fichero,lista[i].nombre);
                    getline (fichero,lista[i].apellidos);
                    fichero >> lista[i].f1.dd;fichero.ignore();
                    fichero >> lista[i].f1.mm;fichero.ignore();
                    fichero >> lista[i].f1.aa;fichero.ignore();
                    getline (fichero,lista[i].d1.calle);
                    fichero >> lista[i].d1.numero;fichero.ignore();
                    getline (fichero,lista[i].d1.localidad);
                }
            }

        }else{ //si el fichero no existe no lo abre pero inicializa el vector
            n=0;// con cero contactos
            lista = NULL;// la lista vacia
            centinela=true;//inicializa el centinela para indicarnos que la lista esta vacia
        }
        fichero.close();//cierra el fichero
        return;
    }


    //operador de  salida, mostrar todos los contactos de la agenda
    friend ostream& operator << (ostream &medio, agenda ag1){

        //Concidional para saber si hay o no contactos y mostrarlos
        if (ag1.n==0){
            medio << "La lista de contactos esta vacia" << endl;
        }else{

            for (int i=0;i<ag1.n;i++)medio << ag1.lista[i];
        }
        cout << endl << "Presiona una tecla para volver al menu";
        getch();
        return(medio);
    }



    //metodo para ordenar la lista de contatos
    void ordenar (void){
        contacto aux; // variable empleada para hacer el swap
        //El primer bucle empezara cuando tengamos 2 contactos
        for (int i=0;i<n-1;i++){
            // el segundo bucle se encarga de llevar la cuenta
            // para comparar con el siguiente contacto
            for (int j=i+1;j<n;j++){
                // hacemos un swap de la ficha de cada contacto
                // segun su orden alfabetico
                if (lista[i].apellidos>lista[j].apellidos){
                    aux=lista[i];
                    lista[i]=lista[j];
                    lista[j]=aux;
                }
                // en caso de tener el mismo apellido
                if (lista[i].apellidos==lista[j].apellidos){
                    // hacemos un swap entre sus nombres que tambien
                    // se ordenaran alfabeticamente
                    if (lista[i].nombre>lista[j].nombre){
                        aux=lista[i];
                        lista[i]=lista[j];
                        lista[j]=aux;
                    }
                }
            }
        }
        return;
    }


    //metodo para buscar el contacto deseado
    void buscar (void){
        system ("cls");
        //si la lista no esta vacia
        if (lista!=NULL){
            //introduciremos un nombre que buscara en la lista de contactos
            cout << "Introduce el nombre del contacto: "; getline (cin,buscarnombre);
            // buscar un contacto en la agenda recorriendo todo el vector
            for (int i=0;i<n;i++){
                // mostrar todos los que coincidan
                if (lista[i].nombre==buscarnombre){
                    cout << endl;
                    cout << lista[i];
                    centinela=false;
                }
            }
            //si no lo encuentra nos lo indica (en el constructor lo inicializaba a true)
            if (centinela==true){
                cout << endl << "No existe ningun contacto con ese nombre";
            }
        }
        cout << endl << "Presiona una tecla para volver al menu";
        getch();
        return;
    }
};

class menu{
private:
    //atributos para la clase que almaceran  una agenda y de un contacto
    // tambien una variable para controlar la seleccion en el menu
    agenda miagenda;
    contacto micontacto;
    int eleccion;
public:
    //metodo para mostrar el menu y solicitar opcion a elegir
    int mostrarmenu (void){
        do{
            system("cls");
            cout << "1- Nuevo contacto" << endl;
            cout << "2- Listar contactos" << endl;
            cout << "3- Buscar contacto" << endl;
            cout << "4- Salir" << endl << endl;
            cout << "Introduce tu eleccion: ";
            cin >> eleccion; cin.ignore();
            system ("cls");
            // bucle se repetira mientras la eleccion no sea posible
        }while (eleccion<1 || eleccion>4);
        //devuelve la eleccion solicitada
        return (eleccion);
    }


    //metodo para realizar las intrucciones del programa
    void seleccion (void){
        do{
            // asignamos el valor  que nos devuelve la llamada al metodo para mostrar menu
            eleccion=mostrarmenu();
            //llamamos al metodo para ordenar la agenda  por si editamos el archivo txt
            miagenda.ordenar();
            switch(eleccion){
            case 1:
                //esta instruccion llamara al operador autosuma pasandole como parametro micontacto
                miagenda+=micontacto;
                break;
            case 2:
                //esta instruccion llamara al operador de salida de la clase agenda
                cout << miagenda;
                break;
            case 3:
                //llamada al metodo buscar de la clase agenda
                miagenda.buscar();
                break;
            }
            // el bucle se repetirá mientras la eleccion almacenada sea distita a salir
        }while (eleccion!=4);
        return;
    }
};

//inicializacion del programa
int main (void){
    menu m1;
    m1.seleccion();
    return(0);
}
