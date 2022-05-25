//Librerias
#include <iostream>
#include <fstream> //para ficheros
bool salidaPantalla=true;

//Espacio de nombres
using namespace std;

///Clases:

//Clase alumno bien
class Alumno{
private:
    //Atributos(no accesibles)
    string nombre, DNI;
    float calificacion;
public:
    //Constructor alumno
    Alumno(){
        nombre=DNI=".";
        calificacion=0;
        return;
    }

    void setNombre(string a){
        nombre=a;
        return;
    }
    void setDNI(string a){
        DNI=a;
        return;
    }
    void setCalificacion(float a){
        calificacion=a;
        return;
    }


    //Conseguir nombre
    string getNombre(){
        return nombre;
    }
    //Conseguir calificacion
    float getCalificacion(){
        return calificacion;
    }


    ///Solicitar ficha de un alumno(cin)
    friend istream& operator >> (istream &medio, Alumno &a) {


        cout<< "----Solicitud de un alumno-------" << endl;
        cout<< "Nombre: ";  medio>> a.nombre;
        cout << "DNI: "; medio >> a.DNI;
        cout <<"Calificacion: "; medio>> a.calificacion;
        return(medio); }
    /*  void SolicitarFicha(){
cout<< "----Solicitud de un alumno-------" << endl;
cout<< "Nombre: ";  cin>> nombre;
cout << "DNI: "; cin >> DNI;
cout <<"Calificacion: "; cin>> calificacion;


return;
}*/


    ///Mostrar ficha(cout)
    friend ostream& operator << (ostream &medio, Alumno a) {






        if(salidaPantalla){
            medio<< "Nombre: " << a.nombre <<"\t";
            medio << "DNI: " << a.DNI << "\t";
            medio <<"Calificacion: "<< a.calificacion <<endl;

        }else{
            medio<<a.nombre<<endl;
            medio<<a.DNI<<endl;
            medio<<a.calificacion<<endl;
        }
        return(medio);
    }
    /* void MostrarFicha(){
cout<< "Nombre: " << nombre << '\t';
cout << "DNI: " << DNI << '\t';
cout <<"Calificacion: "<< calificacion <<endl;
return;
}*/



    //Para ordenar a los alumnos
    bool operator>(Alumno a){
        return nombre>a.nombre;
    }

};

//Clase grupo por comprobar
class Grupo{
private:
    //Atributos(No accesibles)
    string nombre;
    //vector de alumnos
    Alumno *vectorAlumnos;
    int N;

public:
    //Constructor para inicializar
    Grupo(){
        vectorAlumnos=NULL;
        N=0;
        return;

    }

    //Contructor copia
    //Le pasamos por raferencia y ponemso constante para no poder modificar
    Grupo(const Grupo  &orig){
        N=orig.N;
        nombre=orig.nombre;
        vectorAlumnos=NULL;
        if(orig.vectorAlumnos != NULL){
            vectorAlumnos = new Alumno[N];
            for(int i=0;i<N;i++){
                vectorAlumnos[i]=orig.vectorAlumnos[i];
            }
        }
        return;
    }

    //Destructor
    ~Grupo(){
        //Si el vector contiene elementos
        if(vectorAlumnos != NULL){
            delete[]vectorAlumnos;
        }
        return;
    }

    Grupo operator=(Grupo orig){
        if(vectorAlumnos != NULL){
            delete[]vectorAlumnos;
        }
        N=orig.N;
        nombre=orig.nombre;
        vectorAlumnos=NULL;
        if(orig.vectorAlumnos != NULL){
            vectorAlumnos = new Alumno[N];
            for(int i=0;i<N;i++){
                vectorAlumnos[i]=orig.vectorAlumnos[i];
            }
        }
        return *this;
    }



    //metodos (accesibles)
    void setNalumnos(int a){
        N=a;
        return;
    }

    void setVectorAlumnos(Alumno *v){
        vectorAlumnos=v;

        return;
    }
    void setNombreGrupo( string a){
        nombre=a;
        return;
    }
    //Conseguimos el nombre del grupo
    string getNombreGrupo(){
        return nombre;
    }
    //Ponemos el nombre al grupo   
    //Sabemos los alumnos que hay en el grupo
    int getNAlumnos(){
        return N;
    }

    float SumaNotasGrupo(){

        //Hacemos un contador que comience ddesde cero y sume todas las notas
        float contadorNotas=0;

        //Recorremos el vector
        int i;
        for(i=0;i<N;i++){
            contadorNotas=contadorNotas+vectorAlumnos[i].getCalificacion();
        }
        //Tenemos el sumatorio de las notas de todos los alumnos del grupo
        return contadorNotas;


    }

    //Ordenar vector de alumnos
    void ordenarGrupo(){
        //Recorremos el vector
        Alumno aux;
        bool a=false;
        for(int j=0;j<N && a==false ;j++){
            a=true;
            for (int i=0;i<N-1;i++){
                if(vectorAlumnos[i]>vectorAlumnos[i+1]){
                    aux=vectorAlumnos[i];
                    vectorAlumnos[i]=vectorAlumnos[i+1];
                    vectorAlumnos[i+1]=aux;
                    //Si ha habido un cambio se mantiene se cambia a falso para que haga otra ronda
                    a=false;


                }
            }

        }
        return;
    }

    float MediaGrupo(){
        //Hacemos un contador que comience ddesde cero y sume todas las notas
        float contador=0;
        //Recorremos el vector
        int i;
        for(i=0;i<N;i++){
            contador=contador+vectorAlumnos[i].getCalificacion();
        }
        //La media del grupo es: Suma de notas/Alumnos

        if(N>0) contador/=N;

        return contador;
    }
    //Pedimos un alumno

    //Mostramos nombre del grupo
    void MostrarNombreGrupo(){
        //Se muestra el nombre del grupo
        cout<< nombre;
        return ;
    }

    //cin
    friend istream& operator >> (istream &medio, Grupo &gr){
        //Creamos un puntero que apunte al vector una posicion mas grrande
        Alumno *aux = new Alumno[gr.N+1];
        //Copiamos lo del antiguo vector al vector aux
        for(int i=0;i<gr.N;i++){

            aux[i] = gr.vectorAlumnos[i];
        }

        //Pide un alumno
        cin>>aux[gr.N];
        //Suma para introducir otro alumno más tarde
        gr.N++;

        if(gr.vectorAlumnos!=NULL){

            delete []gr.vectorAlumnos;
        }
        gr.vectorAlumnos = aux;

        //El grupo se ordena cada vez que se introduce un alumno
        gr.ordenarGrupo();

        return (medio);

    }
    /* void SolicitarAlumno(){
        //Creamos un puntero que apunte al vector una posicion mas grrande
        Alumno *aux = new Alumno[N+1];
        //Copiamos lo del antiguo vector al vector aux
        for(int i=0;i<N;i++){

            aux[i] = vectorAlumnos[i];
        }

        //Pide un alumno
        cin>>aux[N];
        //Suma para introducir otro alumno más tarde
        N++;

        if(vectorAlumnos!=NULL){

            delete []vectorAlumnos;
        }
        vectorAlumnos = aux;

        //El grupo se ordena cada vez que se introduce un alumno
        ordenarGrupo();

        return;
    }*/
    //Muestra todos los alumnos del grupo
    friend ostream& operator << (ostream &medio, Grupo gr ){
        //Muestra el listado de alumnos que hay en el grupo

        for(int i=0;i<gr.N;i++){

            medio<<gr.vectorAlumnos[i];


        }

        return(medio);


    }
    /* void ListarFichas(){
        //Muestra el listado de alumnos que hay en el grupo

        for(int i=0;i<N;i++){

            cout<<vectorAlumnos[i];
            cout<< endl;
        }
        return;
    }*/

    //Preciso para ordenar Vector
    bool operator > (Grupo g){
        return nombre>g.nombre;
    }

    void setNombreAlum(int pos,string nombre){
        vectorAlumnos[pos].setNombre(nombre);
        return;
    }
    void setDNIAlum(int pos,string dni){
        vectorAlumnos[pos].setDNI(dni);
        return;
    }
    void setNotaAlum(int pos,float nota){
        vectorAlumnos[pos].setCalificacion(nota);
        return;
    }

};


class Asignatura{
private:
    //Atributos no accesibles
    Grupo *vectorGrupos;
    int N;

public:
    //Atributos y procediminetos accesibles

    //Constructor para inicializar
    Asignatura(){

        vectorGrupos=NULL;
        N=0;
        return;

    }
    //Le pasamos por raferencia y ponemso constante para no poder modificar
    Asignatura(const Asignatura  &orig){
        N=orig.N;
        vectorGrupos=NULL;
        if(orig.vectorGrupos != NULL){
            vectorGrupos = new Grupo[N];
            for(int i=0;i<N;i++){
                vectorGrupos[i]=orig.vectorGrupos[i];
            }
        }
        return;
    }

    //Destructor
    ~Asignatura(){
        //Si el vector contiene elementos
        if(vectorGrupos != NULL){
            delete[]vectorGrupos;
        }
        return;
    }
    //Constructor copia
    Asignatura operator=(Asignatura orig){
        //destructor
        if(vectorGrupos != NULL){
            delete[]vectorGrupos;
        }
        //Constructor copia
        N=orig.N;
        vectorGrupos=NULL;
        if(orig.vectorGrupos != NULL){
            vectorGrupos = new Grupo[N];
            for(int i=0;i<N;i++){
                vectorGrupos[i]=orig.vectorGrupos[i];
            }
        }
        return *this;
    }

    int getNumeroGrupos(){
        return N;
    }
    //Obtenemos la media total de la asignatura

    void MediaPorGrupo(){

        //Recorremos el vector de Grupos
        int i;
        for (i=0;i<N;i++){
            //string a=vectorGrupos[i].getNombreGrupo();
            cout <<endl<< "El grupo: "; vectorGrupos[i].MostrarNombreGrupo();
            cout << " tiene de media: " << vectorGrupos[i].MediaGrupo() << endl;
        }
        cout<<endl;
        return;

    }
    void MediaTotal(){

        //Hacemos un contador que comience ddesde cero y sume todas las notas
        float contadorNotas=0;
        float  contadorAlumnos=0;
        //Recorremos el vector
        int i;
        for(i=0;i<N;i++){
            contadorAlumnos=contadorAlumnos+vectorGrupos[i].getNAlumnos();
            contadorNotas=contadorNotas+vectorGrupos[i].SumaNotasGrupo();
        }
        //La media total de la asignatura es Notas de todos los alumnos/numero de alumnos
        float mediaTotal=(contadorNotas/contadorAlumnos);
        cout<<"La media total de la asignatura: "<< mediaTotal << endl<< endl;

        return ;


    }
    //Operador de entrada

    friend istream& operator >>( istream &medio, Asignatura &a){
        //Variables

        bool coincide=false;
        int i;
        string comprobar;
        cout<<"Introduce nombre del grupo:"; cin>>comprobar;


        //Comprobamos que no exista el nombre del grupo:
        //Recorremos el vector de grupos
        for(i=0;i<a.N;i++){
            //Si coincide el nombre, nos quedamos con el mismo vector
            if(a.vectorGrupos[i].getNombreGrupo()==comprobar){
                ///vectorGrupos[i].SolicitarAlumno();
                //Metemos el grupo
                cin>>a.vectorGrupos[i];
                coincide=true;
            }

        }
        //Si no coincide el nuevo con uno anterior, el nuevo se llamara así, el vector crecerá
        if(coincide==false){
            //Creamos grupo auxiliar con una posicion mas y le ponemos el nombre
            Grupo *aux =new Grupo [a.N+1];

            aux[a.N].setNombreGrupo(comprobar);
            //Copiamos el contenido del antiguo grupo en el nuevo
            for(int i=0;i<a.N;i++){
                aux[i]=a.vectorGrupos[i];

            }
            //Guardamos al alumno en el nuevo grupo
            ///aux[N].SolicitarAlumno();

            //Metemos el grupo
            cin>>aux[a.N];
            //Si tiene contenido, se borra ese contenido
            if(a.vectorGrupos!=NULL){

                delete []a.vectorGrupos;
            }

            a.vectorGrupos = aux;
            //Copiamos el contenido del antiguo grupo en el nuevo
            for(int i=0;i<a.N;i++){
                a.vectorGrupos[i]=aux[i];
                cout<<endl;
            }



            //Como el vector crecerá,el nuevo se llamará asi

            a.N=a.N+1;
        }



        a.ordenarGrupos();

        return(medio);
    }

    /* void SolicitarGrupo(){
        //Variables

        bool coincide=false;
        int i;
        string comprobar;
        cout<<"Introduce nombre del grupo:"; cin>>comprobar;


        //Comprobamos que no exista el nombre del grupo:
        //Recorremos el vector de grupos
        for(i=0;i<N;i++){
            //Si coincide el nombre, nos quedamos con el mismo vector
            if(vectorGrupos[i].getNombreGrupo()==comprobar){
                ///vectorGrupos[i].SolicitarAlumno();
                //Metemos el grupo
                cin>>vectorGrupos[i];
                coincide=true;
            }

        }
        //Si no coincide el nuevo con uno anterior, el nuevo se llamara así, el vector crecerá
        if(coincide==false){
            //Creamos grupo auxiliar con una posicion mas y le ponemos el nombre
            Grupo *aux =new Grupo [N+1];

             aux[N].setNombreGrupo(comprobar);
            //Copiamos el contenido del antiguo grupo en el nuevo
            for(int i=0;i<N;i++){
                aux[i]=vectorGrupos[i];

            }
            //Guardamos al alumno en el nuevo grupo
            ///aux[N].SolicitarAlumno();

            //Metemos el grupo
            cin>>aux[N];
            //Si tiene contenido, se borra ese contenido
            if(vectorGrupos!=NULL){

                delete []vectorGrupos;
            }

            vectorGrupos = aux;
            //Copiamos el contenido del antiguo grupo en el nuevo
            for(int i=0;i<N;i++){
                vectorGrupos[i]=aux[i];
                cout<<endl;
            }



            //Como el vector crecerá,el nuevo se llamará asi

            N=N+1;
        }



        ordenarGrupos();

        return;
    }*/

    friend ostream& operator <<(ostream &medio, Asignatura a){

        //Para que muestre el vector de grupos
        int i;
        //Todos los grupos que conocemos
        for(i=0;i<a.N;i++){
            a.vectorGrupos[i].MostrarNombreGrupo();
            medio << endl;

            //Mostrar todas las fihas del grupo
            medio<<a.vectorGrupos[i];

        }

        return(medio);

    }

    //Muestra todos los grupos con sus alumnos e informacion
    /*void ListarTodosAlumnos(){

        //Para que muestre el vector de grupos
        int i;
        //Todos los grupos que conocemos
        for(i=0;i<N;i++){
            vectorGrupos[i].MostrarNombreGrupo();
            cout << endl;

            //Mostrar todas las fihas del grupo
            cout<<vectorGrupos[i];

        }

        return;

    }*/

    //Ordena el vector de grupos
    void ordenarGrupos(){
        //Recorremos el vector
        Grupo aux;
        bool ordenado=false;
        for(int j=0;j<N && ordenado==false;j++){
            ordenado=true;
            for (int i=0;i<N-1;i++){
                if(vectorGrupos[i]>vectorGrupos[i+1]){
                    aux=vectorGrupos[i];
                    vectorGrupos[i]=vectorGrupos[i+1];
                    vectorGrupos[i+1]=aux;
                    //Si se ha hecho algun cambio, que haga otra vez el recorrer vector
                    ordenado=false;
                }
            }
        }
        return;
    }
    ///
    /// FICHEROS
    ///
    ///

    void GuardarDatos(){
        //abrimos el fichero de escritura (ofstream)
        //si no existe lo crea y si existe lo inicializa
        ofstream fichero("datos.txt");
        //Sabemos cuántas grupos se desean grabar
        //Guardamos la cantidad en el fichero
        fichero<<N<<endl;
        //Recorro el vector de grupos
        for(int i=0;i<N;i++){
           fichero<<vectorGrupos[i].getNombreGrupo()<<endl;
           fichero<<vectorGrupos[i].getNAlumnos()<<endl;

           fichero<<vectorGrupos[i];
        }
        //cerramos el fichero
        fichero.close();
        return;
    }

    void Cargardatos(void){
        //abrimos el fichero de lectura (ifstream)

        ifstream fichero("datos.txt");
        if(fichero.is_open()){
            //Si hay algun fichero
            //Leemos el numero de grupos
            fichero>>N;
            //Tenemos que recorrer todos os grupos
            vectorGrupos=new Grupo [N];
            for(int i=0;i<N;i++){

                //Leemos cada grupo
                string nom;
                fichero>>nom;
                vectorGrupos[i].setNombreGrupo(nom);
                int numalum;
                fichero>>numalum;
                vectorGrupos[i].setNalumnos(numalum);
                //Crear vriabl vector alumnos y rellenar con los datos del fichero
                Alumno *v;
                v=new Alumno [numalum];
                vectorGrupos[i].setVectorAlumnos(v);

                for(int j=0;j<numalum;j++){
                    string nomAlu,DNIalum;
                    float nota;
                    fichero>>nomAlu;
                    vectorGrupos[i].setNombreAlum(j,nomAlu);
                    fichero>>DNIalum;
                    vectorGrupos[i].setDNIAlum(j,DNIalum);
                    fichero>>nota;
                    vectorGrupos[i].setNotaAlum(j,nota);
                }


            }
        }

        fichero.close();
        return;
    }

};

class Menu{
private:
    //Atributos no accesibles
    Asignatura A;

public:
    //Atributos y procediminetos accesibles
    void Empezar(){
        A.Cargardatos();
        int opc;
        do{

            //Muestra las posibilidades que hay
            cout<<"Elige opcion: "<< endl;
            cout << "1. Nueva calificacion" << endl;
            cout << "2. Lista calificacion" << endl;
            cout << "3. Media por grupo" << endl;
            cout << "4. Media total" << endl;
            cout << "5. Salir" << endl << endl;
            cout << "Opcion: "; cin>>opc;




            //Después de elegir hace:
            //system("cls");
            switch (opc){
            case 1: //A.SolicitarGrupo();
                cin>>A;
                break;
            case 2: //A.ListarTodosAlumnos();
                cout<<A;
                break;
            case 3: A.MediaPorGrupo();break;
            case 4: A.MediaTotal();break;
            }
        }while(opc!=5);
        //Booleano para saber si se mete en pantalla o no
        salidaPantalla=false;
        //Para crear fichero
        A.GuardarDatos();
        return;
    }
};





/// Main
int main(){

    Menu m;
    m.Empezar();


    return 0;

}
