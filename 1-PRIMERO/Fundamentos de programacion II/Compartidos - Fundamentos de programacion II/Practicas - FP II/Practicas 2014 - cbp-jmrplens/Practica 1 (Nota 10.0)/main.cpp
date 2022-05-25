/**************************************************************************
 * (C) Copyright 2014 Carlos Barrera Piqueres y Jose Manuel Requena Plens *
 * Universidad de Alicante. Grado en ingenieria en sonido e imagen.       *
 *                                                                        *
 * Asignatura: Fundamentos de programacion 2                              *
 *                                                                        *
 * PRACTICA 1                                                             *
 *                                                                        *
 * PROGRAMA QUE REALIZA EL CENSO DE LA UNIVERSIDAD                        *                                                      *
 *************************************************************************/
#include <iostream>
#include <fstream> // flujo de archivo
#include <stdlib.h> // Para la funcion system("cls") y la funcion atoi. Solo necesario para compilar en Windows.

using namespace std;//Atajo de nombres

void limpiar(){//Funcion universal para limpiar pantalla
    /*Estuvimos buscando un codigo universal para limpiar la pantalla ya que uno de nosotros programa sobre Windows y otro sobre Mac.
     *En esta web: http://forums.xkcd.com/viewtopic.php?f=11&t=13808#p338410 encontramos el codigo que usamos mas abajo.
     *Cada vez que queremos limpiar la pantalla llamamos a esta funcion.
     */
#ifdef WIN32 //si es windows
    system("cls");//limpia la pantalla
#else //sino realiza lo siguiente
    cout<< "\x1b[2J\x1b[1;1H";
    //Envia a pantalla: "\x1b[2J" Esto desplaza todos los caracteres en la pantalla hacia arriba
    // Y "\x1b[1;1H" mueve el cursor a la fila 1 columna 1 de la ventana en la que se esta ejecutando
#endif
}

class Alumno{//Clase alumno. Contiene 4 string: dni, nombre, apellido1 y apellido2
private:
    string dni, nombre, apellido1, apellido2;
public:
    Alumno(){//Constructor por defecto
        dni = nombre = apellido1 = apellido2 = "";//Inicializa todos los string si creamos el objeto sin recibir nada (string vacios)
    }

    Alumno(string d, string n, string a1, string a2){//Contructor recibiendo 4 string. Utilizado cuando se cargan datos de archivo
        dni = d;//Copia el string d que ha recibido al string DNI actual
        nombre = n;//Copia el string n que ha recibido al string nombre actual
        apellido1 = a1;//Copia el string a1 que ha recibido al string apellido1 actual
        apellido2 = a2;//Copia el string a2 que ha recibido al string apellido2 actual
    }

    Alumno &operator=(const Alumno &alu){//Sobrecarga del operador asignacion
        dni = alu.dni;//Copia el string DNI del objeto alumno recibido al string DNI actual
        nombre = alu.nombre;//Copia el string nombre del objeto alumno recibido al string nombre actual
        apellido1 = alu.apellido1;//Copia el string apellido1 del objeto alumno recibido al string apellido1 actual
        apellido2 = alu.apellido2;//Copia el string apellido2 del objeto alumno recibido al string apellido2 actual
        return *this;//Devuelve el actual
    }

    string getDNI()const{ return dni; }//Devuelve el contenido del DNI
    string getNombre(){ return nombre; }//Devuelve el contenido del nombre
    string getApellido1(){ return apellido1; }//Devuelve el contenido del apellido1
    string getApellido2(){ return apellido2; }//Devuelve el contenido del apellido2

    bool operator==(const Alumno &de) {//Sobrecarga del operador logico == para comparar el dni del objeto actual y el del que recibe
        bool iguales;
        if(dni == de.dni){//Si los DNI son iguales pone en true el booleano iguales
            iguales = true;
        }else{// Si no son iguales devuelve false
            iguales = false;
        }
        return iguales;
    }

    bool operator>(const Alumno &de){//Sobrecarga del operador aritmetico > para saber si el objeto alumno actual es mayor que el que recibe
        bool mayor = false;//Inicializamos el booleano en falso, si este no cambia querra decir que el alumno actual esta ordenado correctamente respecto al que recibe
        /* El objeto string ya tiene implementado el operador >, por lo que al realizar string2>string devuelve 1 si string esta
         * alfabeticamente por debajo de string 2. Es decir  ddd>aaa devolveria 0 y aaa>ddd devolveria 1.
         * En estos condicionales lo que hacemos es ordenar alfabeticamente los alumnos dando prioridad a los apellidos, despues
         * al nombre y por ultimo el DNI.
        */
        if(apellido1 > de.apellido1){//Si el apellido1 es menor que el recibido devuelve un true
            mayor = true;
        }else{//Si no lo es sigue comprobando
            if(apellido1 == de.apellido1){//Si el apellido1 (sabiendo ya que no es menor) es igual al recibido, sigue comprobando
                if(apellido2 > de.apellido2){//Si llegamos aqui quiere decir que apellido1 es igual, y si apellido2 es menor que el recibido devuelve true
                    mayor = true;
                }else{//Si no lo es sigue comprobando
                    if(apellido2 == de.apellido2){//Si el apellido2 (sabiendo ya que no es menor) es igual al recibido, sigue comprobando
                        if(nombre > de.nombre){//Si llegamos aqui quiere decir que apellido2 es igual, y si el nombre es menor que el recibido devuelve un true
                            mayor = true;
                        }else{//Si no lo es sigue comprobando
                            if(nombre == de.nombre){//Si el nombre (sabiendo ya que no es menor) es igual al recibido, sigue comprobando
                                if(dni > de.dni){//Por ultimo, si los apellidos y el nombre son iguales, compara los dos DNI, si el DNI es menor que el recibido devuelve un true
                                    mayor = true;
                                }
                            }
                        }
                    }
                }
            }
        }
        return mayor;//Devuelve el valor del booleano mayor
    }

    friend ostream &operator<<(ostream &medio, const Alumno &de){//Sobrecarga del operador flujo de salida para imprimir en pantalla o en archivo
        string nombreaux=de.nombre;//Copiamos el nombre (esta en private y no podemos modificar) a un string auxiliar para despues cambiar los espacios
        string apellido1aux=de.apellido1;//Copiamos elprimer apellido (esta en private y no podemos modificar) a un string auxiliar para despues cambiar los espacios
        string apellido2aux=de.apellido2;//Copiamos el segundo apellido (esta en private y no podemos modificar) a un string auxiliar para despues cambiar los espacios
        if(medio==cout){//Si lo utilizamos para un cout, se imprimira en pantalla, de esta forma:
            replace( nombreaux.begin(), nombreaux.end(), '_', ' ' );//Funcion de la clase string para recorrer el string desde el principio al final y sustituir las barras baja por espacios
            replace( apellido1aux.begin(), apellido1aux.end(), '_', ' ' );//Funcion de la clase string para recorrer el string desde el principio al final y sustituir las barras baja por espacios
            replace( apellido2aux.begin(), apellido2aux.end(), '_', ' ' );//Funcion de la clase string para recorrer el string desde el principio al final y sustituir las barras baja por espacios
            medio << "DNI: " << de.dni << endl;//Imprime el dni del objeto alumno recibido
            medio << "Nombre: " << nombreaux << endl;//Imprime el nombre del objeto alumno recibido
            medio << "Primer apellido: " << apellido1aux << endl;//Imprime el apellido1 del objeto alumno recibido
            medio << "Segundo apellido: " << apellido2aux << endl;//Imprime el apellido2 del objeto alumno recibido
            return (medio);
        }else{//Si no es para cout se imprimira de esta otra manera
            replace( nombreaux.begin(), nombreaux.end(), ' ', '_' );//Funcion de la clase string para recorrer el string desde el principio al final y sustituir los espacios por barra baja. Necesario para guardar/cargar correctamente
            replace( apellido1aux.begin(), apellido1aux.end(), ' ', '_' );//Funcion de la clase string para recorrer el string desde el principio al final y sustituir los espacios por barra baja. Necesario para guardar/cargar correctamente
            replace( apellido2aux.begin(), apellido2aux.end(), ' ', '_' );//Funcion de la clase string para recorrer el string desde el principio al final y sustituir los espacios por barra baja. Necesario para guardar/cargar correctamente

            medio <<de.dni<<' '<<nombreaux<<' '<<apellido1aux<<' '<<apellido2aux;
            return (medio);//Devuelve medio y volvemos donde se ha utilizado el operador <<
        }
    }

    friend istream &operator>>(istream &imedio, Alumno &aluin){//Sobrecarga del operador flujo de entrada >> para solicitar los datos de alumno
        unsigned int i;//Entero sin signo que utilizaremos para comparar la longitud (devuelve un entero sin signo) de los string dentro de los for
        bool error;//Creamos el booleano error para comprobar si se ha introducido un dni con letras o distinto de 8 caracteres
        do{
            error=false;//Asignamos false al booleano utilizado para saber si algun caracter del DNI no es un numero
            cout << "DNI: ";
            imedio>>aluin.dni;
            for(i=0; i<aluin.dni.length();i++){//Recorre el string de DNI en toda su longitud
                if(aluin.dni[i]<48 || aluin.dni[i]>57) error=true;//Si los caracteres no son numeros (48=0 y 57=9 en ASCII) pone el error en true
            }
            if(aluin.dni.length()!=8 || error==true) cout<<"DNI incorrecto, vuelve a intentarlo"<<endl;//si no ha introducido 8 caracteres se imprime un aviso
        }while(aluin.dni.length()!=8 || error==true);//Mientras no haya los 8 caracteres NUMERICOS del DNI seguira pidiendolo

        /*La siguiente linea realiza la division entre 23 del numero introducido y obtenemos el resto de la division (%23).
         * El numero introducido esta en un string, asi que lo convertimos a entero con la funcion atoi
         * Despues usamos la cadena de caracteres que se aplica a los DNI para generar la letra.
         * El resto de la division sera la posicion de la letra correcta dentRo de la cadena "TRWAGMYFPDXBNJZSQVHLCKE"
         * Esta letra la concatenamos en el string del DNI, asi tenemos los 8 caracteres introducidos mas la letra.
        */
        aluin.dni=aluin.dni+"TRWAGMYFPDXBNJZSQVHLCKE"[atoi(aluin.dni.c_str())%23];//Concatenacion de la letra del DNI con el numero introducido.
        cout<<"Letra: "<< aluin.dni[8]<<endl;//Imprime solo la letra generada, aunque el dni ya contiene los numeros y la letra

        cout << "Nombre: ";
        getline(imedio, aluin.nombre);
        aluin.nombre[0]= toupper (aluin.nombre[0]);//Pone la primera letra en mayusculas
        for (i = 1; i < aluin.nombre.length() ; i++){//Recorre el string en toda su longitud
            if (aluin.nombre[i-1]!=' '){//Si el caracter anterior no es un espacio pasa a minuscula
                aluin.nombre[i]= tolower (aluin.nombre[i]);
            }else{//Sino pasa el caracter a mayuscula
                aluin.nombre[i]=toupper (aluin.nombre[i]);
            }
        }

        cout << "Primer apellido: ";
        getline(imedio, aluin.apellido1);
        aluin.apellido1[0]= toupper (aluin.apellido1[0]);//Pone la primera letra en mayusculas
        for (i = 1; i < aluin.apellido1.length() ; i++)//Recorre el string en toda su longitud
        { aluin.apellido1[i]= tolower (aluin.apellido1[i]);}//A partir de la segunda letra en adelante, cambia mayusculas por minusculas si las hay
        for (i = 1; i < aluin.apellido1.length() ; i++){//Recorre el string en toda su longitud
            if (aluin.apellido1[i-1]!=' '){//Si el caracter anterior no es un espacio pasa a minuscula
                aluin.apellido1[i]= tolower (aluin.apellido1[i]);
            }else{//Sino pasa el caracter a mayuscula
                aluin.apellido1[i]=toupper (aluin.apellido1[i]);
            }
        }

        cout << "Segundo apellido: ";
        getline(imedio, aluin.apellido2);
        aluin.apellido2[0]= toupper (aluin.apellido2[0]);//Pone la primera letra en mayusculas
        for (i = 1; i < aluin.apellido2.length() ; i++)//Recorre el string en toda su longitud
        { aluin.apellido2[i]= tolower (aluin.apellido2[i]);}//A partir de la segunda letra en adelante, cambia mayusculas por minusculas si las hay
        for (i = 1; i < aluin.apellido2.length() ; i++){//Recorre el string en toda su longitud
            if (aluin.apellido2[i-1]!=' '){//Si el caracter anterior no es un espacio pasa a minuscula
                aluin.apellido2[i]= tolower (aluin.apellido2[i]);
            }else{//Sino pasa el caracter a mayuscula
                aluin.apellido2[i]=toupper (aluin.apellido2[i]);
            }
        }
        return imedio;//Devuelve imedio y volvemos donde se ha utilizado el operador >>
    }
};

class Titulacion{
private:
    string nombre;
    Alumno *alus; // Direccion de un vector de alumnos. vector dinamico
    int n;//numero de alumnos del objeto titulacion
    bool nuevo;//Utilizado para comprobar si es un nuevo alumno. El metodo anyadiralumno en Universidad consulta el valor para imprimir los datos o no
public:
    Titulacion(){//contructor por defecto de titulacion
        alus = NULL;//alus no apunta a nada
        n = 0;
        nombre = "";
    }
    ///Se puede quitar
    Titulacion(const Titulacion &t){//Constructor de titulacion recibiendo un objeto titulacion
        nombre = t.nombre;//Copia el nombre del objeto titulacion recibido al objeto actual
        if(t.alus == NULL){//Si el vector de alumnos contenido en el objeto titulacion recibido no apunta a nada, inicializa el numero de alumnos y el vector de alumnos
            n = 0;
            alus = NULL;//alus no apunta a nada
        }
        else{//Si tiene alumnos crea un vector de alumnos alu de longitud igual al vector de lumnos del objeto titulacion recibido
            alus = new Alumno [t.n];//Reserva memoria para el vector de alumnos actual tal que sea del mismo tamaño que el recibido (t.n)
            for(int i = 0; i < t.n; i++){//Recorre los vectores de alumnos contenido en el objeto titulacion recibido y el actual (que ahora es de la misma longitud)
                alus[i] = t.alus[i];//Copia el vector de alumnos recibido con el actual posicion por posicion
            }
            n = t.n;//Copia el numero de alumnos del objeto titulacion recibido al objeto actual
        }
    }
    ~Titulacion(){//destructor de titulacion
        if(alus != NULL){//Si el vector de alumnos no es un apuntador nulo ejecuta lo siguiente
            delete [] alus;//Libera la memoria reservada por el vector alumnos
            alus = NULL;//alus no apunta a nada
            n = 0;
        }
    }

    int buscar(string dni) {//Metodo para buscar dni
        int pos, i;
        pos = -1;//Inicializamos el valor de la posicion en -1, devolveremos -1 si no lo encuentra y si lo encuentra devolvera la posicion en el vector
        for(i = 0; i < n; i++){//Recorre el vector de alumnos
            if(dni == alus[i].getDNI()){// Ejecuta el metodo getDNI de cada alumno, el cual devuelve el DNI y lo compara con el recibido, si aparece uno igual ejecuta lo siguiente
                pos = i;//Si hay un DNI igual guarda en pos la posicion del alumno en el vector de alumnos
                cout << "El alumno ya esta en la titulacion: " << nombre << endl;//Imprime que el alumno con el nombre <nombre> ya esta
                cout << alus[pos] << endl;//Imprime los datos del alumno que ya estaba guardado en el vector en la posicion pos
            }
        }
        return pos;//Devuelve la posicion del alumno en el vector de alumnos
    }

    void insertar(const Alumno &a){//Metodo para añadir un alumno al vector de alumnos
        int pos, i;
        pos = buscar(a.getDNI());// Ejecuta el metodo buscar de esta clase enviando el DNI del alumno recibido
        if(pos == -1){ // Si no lo encuentra (El metodo buscar devolvera -1) ejecuta lo siguiente
            Alumno *aux;//Nuevo vector dinamico de alumnos
            aux = new Alumno [n + 1];//Reservamos memoria para el vector de alumnos aux con una posicion mas que el actual
            for(i = 0; i < n; i++)
                aux[i] = alus[i];//Recorremos los vectores y copiamos los alumnos del actual al auxiliar
            aux[n] = a; //Guarda en la posicion n del vector auxiliar el alumno a
            if(alus != NULL){//Si el vector de alumnos actual no es un apuntador nulo
                delete [] alus;//Libera la memoria reservada por el vector
                alus = NULL;//alus no apunta a nada
            }
            alus = aux; //Copiamos el vector auxiliar al actual
            n++; // Incrementa en uno el numero de alumnos
            nuevo=true;//Utilizado para comprobar si es un nuevo alumno. El metodo anyadiralumno en Universidad consulta el valor para imprimir los datos o no
        }else{
            nuevo=false;//Si el alumno no es nuevo, al booleano se le asigna false
        }
    }

    void ordenar(){//Metodo para ordenar los alumnos. Trabaja con el operador < para comparar los alumnos, este operador esta sobrecargado en la clase alumno.
        int i, j;
        Alumno aux;//Creamos un vector de alumno auxiliar

        for(i = 1; i < n; i++){//Metodo de ordenacion burbuja.
            for(j = 0; j < n-i; j++){//En la condicion restamos i a n para no comprobar los elementos ya ordenados al final del vector
                if(alus[j] > alus[j+1]){//Si el alumno en la posicion j es mayor que el de la posicion siguiente los intercambia.
                    //El operador > esta sobrecargado para el objeto alumno dentro de su clase. Compara primero apellido1, luego apellido2, despues nombre y por ultimo el DNI.
                    aux = alus[j];//Copia el alumno en la posicion j al auxiliar
                    alus[j] = alus[j+1];//Ahora copia el alumno de la posicion siguiente (j+1) a j
                    alus[j+1] = aux;//Por ultimo copia el alumno que estaba inicialmente en la posicion j a la posicion j+1
                }
            }
        }
    }

    int getAlumnos(){return n;}//Devuelve el numero de alumnos que hay en la titulacion
    bool getNuevo(){return nuevo;}//Devuelve un booleano indicando si el alumno creado es nuevo o no
    string getNombre(){return nombre;}//Devuelve el nombre de la titulacion
    void setNombre(string nombre){this->nombre = nombre;}//Asigna un nombre a esta titulacion recibiendo un string

    Titulacion &operator=(const Titulacion &t){//Sobrecarga del operador asignacion
        if(this != &t){ // Solo ejecuta estas lineas si el objeto actual es distinto al recibido. Si son iguales no serviria de nada ejecutar esta lineas
            nombre = t.nombre;//Copia el nombre de la titulacion recibida a esta
            if(alus != NULL){//Si el vector de alumnos no es un apuntador nulo, se libera la memoria
                delete [] alus;
            }
            if(t.alus == NULL){//Si el vector de alumnos del objeto titulacion recibido es un apuntador nulo, inicializa el numero de alumno n y los alumnos del actual
                n = 0;
                alus = NULL;//alus no apunta a nada
            }
            else{//Si el vector de alumnos del objeto titulacion recibido tiene alumnos realiza lo siguiente
                alus = new Alumno [t.n];//Crea el vector de alumnos con la cantidad de alumnos de la titulacion recibida
                for(int i = 0; i < t.n; i++){
                    alus[i] = t.alus[i];//Copia uno por uno cada alumno de la titulacion recibida
                }
                n = t.n;//Copia el numero de alumnos del objeto titulacion recibido al actual
            }
        }
        return *this;//Devuelve el objeto titulacion actual
    }

    bool operator>(const Titulacion &de) {return nombre > de.nombre;}//Devuelve un booleano true si el nombre del objeto titulacion actual es mayor al recibido, sino devuelve false

    friend ostream &operator<<(ostream &medio, const Titulacion &t){//Sobrecarga del operador flujo de salida para imprimir en pantalla o en archivo
        string nombreaux=t.nombre;//Copiamos el nombre de titulacion (esta en private y no podemos modificar) a un string auxiliar para despues cambiar los espacios
        if(medio==cout){//Si lo utilizamos para un cout, se imprimira asi
            int i;
            replace( nombreaux.begin(), nombreaux.end(), '_', ' ' );//Funcion de la clase string para recorrer el string desde el principio al final y sustituir las barras baja por espacios

            medio <<"***********************************"<<endl<<"Titulacion: " << nombreaux<< endl<<"-----------------------------------"<<endl;
            for(i = 0; i < t.n; i++){//Recorre el vector de alumnos del objeto de titulacion recibido.
                medio << t.alus[i] << endl;//Imprime los datos de cada alumno. Primero DNI, luego nombre, despues primer apellido y por ultimo segundo apellido
            }
            medio<<"-----------------------------------"<<endl<<"Alumnos en "<< nombreaux <<": "<< t.n << endl<<"***********************************"<<endl;
            return medio;
        }else{//Si no es para cout se imprimira de esta otra manera
            replace( nombreaux.begin(), nombreaux.end(), ' ', '_' );//Funcion de la clase string para recorrer el string desde el principio al final y sustituir los espacios por barra baja. Necesario para guardar/cargar correctamente
            for(int i = 0; i < t.n; i++){
                medio<< nombreaux<<' '<< t.alus[i]<<endl;//Datos de alumno. Son 4 datos cada alumno, DNI, Nombre, Apellido1, Apellido2.
            }
            return medio;//Devuelve medio y volvemos donde se ha utilizado el operador <<
        }
    }
};

class Universidad{
private:
    Titulacion *titulaciones;// Direccion de un vector de titulaciones. vector dinamico
    int nt;
    bool nuevo;//Booleano utilizado en el metodo anyadiralumno de este metodo. Lo utilizamos para imprimir o no determinados datos

public:
    Universidad(){//Constructor por defecto
        titulaciones = NULL;//Titulaciones no apunta a nada
        nt = 0;
    }
    ~Universidad(){//Destructor
        if(titulaciones != NULL){//Si titulaciones no es un apuntador nulo ejecuta lo siguiente
            delete [] titulaciones;//Libera la memoria resevada por titulaciones
            titulaciones = NULL;//Titulaciones no apunta a nada
            nt = 0;
        }
    }
    void anyadirAlumnofichero(string titulacion, string dni, string nombre, string apellido1, string apellido2){//Metodo para añadir alumno recibiendo los datos desde fichero. Metodo llamado desde la clase menu
        Alumno alu(dni,nombre,apellido1,apellido2);//Creamos un objeto alumno por parametros
        int posicion, i;
        posicion = -1;//Inicializamos posicion con el valor -1
        for(i = 0; i < nt && posicion == -1; i++){//Recorre el vector de titulacion en toda su longitud. Termina si llega al final o si posicion cambia de valor
            if(titulacion == titulaciones[i].getNombre()){//Si el nombre introducido es igual al de la posicion i del vector titulaciones realiza la siguiente linea
                posicion = i;//Si encuentra una titulacion igual guardara la posicion en la variable pos
            }
        }
        if(posicion == -1){//Si es una nueva titulacion ejecuta esto
            Titulacion *aux;//Creamos un puntero auxiliar de titulaciones
            aux = new Titulacion [nt + 1];//Reservamos memoria para el vector auxiliar, un objeto mas que el actual
            for(i = 0; i < nt; i++){
                aux[i] = titulaciones[i]; // Copia el vector de titulaciones actual al auxiliar
            }
            if(titulaciones !=	NULL){//Si titulaciones no es un apuntador nulo
                delete [] titulaciones;//Liberamos la memoria reservada para titulaciones
            }
            titulaciones = aux; // Ahora titulaciones apunta al vector auxiliar.
            titulaciones[nt].setNombre(titulacion);//Envia el nombre de titulacion introducido al metodo setNombre de la titulacion nueva

            titulaciones[nt].insertar(alu);//Llama al metodo para insertar un nuevo alumno en la titulacion
            nt++;//Aumenta en 1 el numero de titulaciones
            nuevo=true;//Indica que es una nueva titulacion
        }
        else{
            titulaciones[posicion].insertar(alu);//si la titulacion ya estaba en la base de datos, inserta el alumno en la posicion pos
            nuevo=false;//Indica que no es una nueva titulacion
        }
    }

    void anyadirAlumno(){//Metodo para añadir alumno
        Alumno alu;//Objeto alumno utilizado en las siguientes lineas para recibir los datos del nuevo alumno y despues enviarlo al vector de alumnos contenido en titulacion
        string nombreTitulacion;//String utilizado para recibir el nombre de la titulacion que despues se enviara al objeto titulacion mediante su metodo setNombre
        int posicion, i;

        cout << "Nombre de la titulacion: ";
        getline(cin, nombreTitulacion);
        nombreTitulacion[0]= toupper (nombreTitulacion[0]);//Pone la primera letra en mayusculas
        for (int unsigned j = 1; j < nombreTitulacion.length() ; j++)//Recorre el string en toda su longitud
        { nombreTitulacion[j]= tolower (nombreTitulacion[j]);}//A partir de la segunda letra en adelante, cambia mayusculas por minusculas si las hay


        cout << "Introduce los datos del nuevo alumno: " << endl;
        cin >> alu;//Ejecuta las funciones del operador >> sobrecargado en la clase alumno
        posicion = -1;//Inicializamos posicion con el valor -1
        for(i = 0; i < nt && posicion == -1; i++){//Recorre el vector de titulacion en toda su longitud. Termina si llega al final o si posicion cambia de valor
            if(nombreTitulacion == titulaciones[i].getNombre()){//Si el nombre introducido es igual al de la posicion i del vector titulaciones realiza la siguiente linea
                posicion = i;//Si encuentra una titulacion igual guardara la posicion en la variable pos
            }
        }
        limpiar();//limpia la pantalla

        if(posicion == -1){//Si es una nueva titulacion ejecuta esto
            Titulacion *aux;//Creamos un puntero auxiliar de titulaciones
            aux = new Titulacion [nt + 1];//Reservamos memoria para el vector auxiliar, un objeto mas que el actual
            for(i = 0; i < nt; i++){
                aux[i] = titulaciones[i]; // Copia el vector de titulaciones actual al auxiliar
            }
            if(titulaciones !=	NULL){//Si titulaciones no es un apuntador nulo
                delete [] titulaciones;//Liberamos la memoria reservada para titulaciones
            }
            titulaciones = aux; // Ahora titulaciones apunta al vector auxiliar.
            titulaciones[nt].setNombre(nombreTitulacion);//Envia el nombre de titulacion introducido al metodo setNombre de la titulacion nueva
            titulaciones[nt].insertar(alu);//Llama al metodo para insertar un nuevo alumno en la titulacion
            cout<<"Agregada nueva titulacion a la base de datos: "<<titulaciones[nt].getNombre()<<endl<<endl;//Imprime el nombre de la nueva titulacion introducida en la posicion nt
            nt++;//Aumenta en 1 el numero de titulaciones
            nuevo=true;//Indica que es una nueva titulacion
        }
        else{
            titulaciones[posicion].insertar(alu);//si la titulacion ya estaba en la base de datos, inserta el alumno en la posicion pos
            nuevo=false;//Indica que no es una nueva titulacion
        }
        if(titulaciones[posicion].getNuevo()==true || nuevo==true){//Si es un nuevo alumno en una titulacion existente o es una nueva titulacion, imprime lo siguiente
            cout<<"Alumno: "<<alu.getNombre()<<" "<<alu.getApellido1()<<" "<<alu.getApellido2()<<endl;//imprime el nombre completo
            cout<<"DNI: "<<alu.getDNI()<<endl;//imprime el dni
            cout<<"Añadido correctamente a la titulacion: "<<nombreTitulacion<<endl;//imprime el nombre de la titulacion donde el alumno ha sido añadido
        }


    }

    void buscarAlumno() {//Metodo para buscar un alumno por el DNI
        bool error, encontrado=false;
        string dni;//Creamos un string para recibir el DNI a buscar
        string letra;//String para almacenar la letra del DNI

        do{//Solicitamos el numero de DNI
            error=false;//Asignamos false al booleano utilizado para saber si algun caracter del DNI no es un numero
            cout << "Numero de DNI del alumno a buscar: ";
            getline(cin, dni);
            for(int unsigned i=0; i<dni.length();i++){//Recorre el string de DNI
                if(dni[i]<48 || dni[i]>57) error=true;//Si los caracteres no son numeros (48=0 y 57=9 en ASCII) pone el error en true
            }
            if(dni.length()!=8 || error==true) cout<<"DNI incorrecto, vuelve a intentarlo"<<endl;//si no ha introducido 8 caracteres numericos se imprime un aviso
        }while(dni.length()!=8 || error==true);//Mientras no haya los 8 caracteres NUMERICOS del DNI seguira pidiendolo

        do{//Ahora solicitamos la letra del DNI, si no introduce una unica letra debera repetirlo
            cout << "Introduce la letra: ";
            getline(cin, letra);
            letra[0]=toupper(letra[0]);//Pasamos la letra a mayuscula ya que esta almacenada asi en el objeto alumno

            if(letra.length()!=1 ||  (letra[0] < 'A' || letra[0] > 'Z' )) cout<<"Introduce una letra por favor."<<endl;//Si tiene mas de un caracter o no es una letra mayuscula imprime esto
        }while(letra.length()!=1 ||  (letra[0] < 'A' || letra[0] > 'Z' ));//Si tiene mas de un caracter o no es una letra mayuscula volvera a solicitar la letra
        dni=dni+letra;//Concatenamos la letra con el dni introducido ya que asi es como se guardo cuando se creo el alumno
        limpiar();
        for(int i = 0; i < nt; i++){//Recorremos todas las titulaciones
            //Llamamos al metodo buscar de titulacion para que compare los dni de los alumnos que contiene con el que buscamos e imprime el alumno si lo encuentra
            if (titulaciones[i].buscar(dni)!= -1)encontrado=true;//Si encuentra en alguna titulacion el alumno pondra true a encontrado
        }
        if(!encontrado)cout<<"El DNI introducido no coincide con ningun alumno"<<endl;//Si el booleano encontrado no es true imprime esto
    }

    void ordenar(){//Metodo para ordenar la titulaciones
        int i, j;
        Titulacion aux;//Creamos un objeto titulacion auxiliar
        for(i = 0; i < nt; i++){//Primero ordena a los alumnos que hay en cada titulacion
            titulaciones[i].ordenar();//Llama al metodo ordenar de titulaciones para ordenar los alumnos de cada titulacion
        }
        cout<<"Alumnos ordenados"<<endl;//Imprime un aviso al terminar la ordenacion de los alumnos

        for(i = 1; i < nt; i++){//Metodo de ordenacion burbuja.
            for(j = 0; j < nt-i ; j++){//En la condicion restamos i a nt para no comprobar los elementos ya ordenados al final del vector
                if(titulaciones[j] > titulaciones[j+1]){//Si la titulacion en la posicion j es mayor que el de la posicion siguiente los intercambia.
                    //El operador > esta sobrecargado para el objeto titulacion dentro de su clase. Compara el string nombre de las titulaciones
                    aux = titulaciones[j];//Copia la titulacion de la posicion j al auxiliar
                    titulaciones[j] = titulaciones[j+1];//Ahora copia la titulacion de la posicion siguiente (j+1) a j
                    titulaciones[j+1] = aux;//Por ultimo copia la titulacion que estaba inicialmente en la posicion j a la posicion j+1
                }
            }
        }
        cout<<"Titulaciones ordenadas"<<endl;//Imprime un aviso al terminar la ordenacion de las titulaciones
    }

    friend ostream &operator<<(ostream &medio, const Universidad &u){//sobrecarga del operador de flujo << para imprimir todas las titulacion, sus alumnos y el numero total de alumnos
        if(medio==cout){//Si lo utilizamos para un cout, se imprimira asi
            int alumnosTotales = 0;
            for(int i = 0; i < u.nt; i++){//Recorre el vector de titulaciones y las imprime todas con sus alumnos. Tambien recuenta los alumnos y realiza la suma total de alumnos sobre la variable alumnosTotales
                medio<< u.titulaciones[i] << endl;//Envia al operando donde ha sido utilizado este operador el nombre de titulacion y los alumnos de cada una
                alumnosTotales = alumnosTotales + u.titulaciones[i].getAlumnos();//Suma los alumnos de la titulacion [i] al total
            }
            medio<<"Alumnos totales: " << alumnosTotales << endl;//Envia al operando donde ha sido utilizado este operador el numero total de alumnos en la universidad
            return(medio);//Vuelve a la linea donde se le ha llamado
        }else{//Si no es para cout se imprimira de esta otra manera
            for(int i = 0; i < u.nt; i++){//Recorre el vector de titulaciones y las imprime todas con sus alumnos.
                medio<< u.titulaciones[i];//Envia al operando donde ha sido utilizado este operador el nombre de titulacion y los alumnos de cada una
            }
            return(medio);//Vuelve a la linea donde se le ha llamado
        }
    }
};

class Menu{
private:
    Universidad uni;//Creamos un objeto universidad

public:
    void imprimir(){//Imprime por pantalla el menu
        cout << "1. Añadir alumno a universidad" << endl;
        cout << "2. Buscar alumno por dni" << endl;
        cout << "3. Ordenar alumnos" << endl;
        cout << "4. Mostrar alumnos matriculados" << endl;
        cout << "5. Salir" << endl;
    }
    void ejecutar(){//Ejecuta el sistema del menu, se cargan los datos, se llama a el metodo imprimir para imprimir por pantalla el menu y se ejecutan las opciones, finalmente al salir se guarda todo
        cargar();//Llama al metodo cargar de esta clase
        int opcionnum;//Declaracion de una variable entera
        string opcion;//String utilizado para recibir la opcion del usuario, validar si es un numero y si lo es ejecutar la opcion
        do{
            limpiar();
            imprimir();//llama al metodo imprimir incluido en esta clase

            do{//Pediremos la opcion y comprobaremos si es un numero, si no lo es se volvera a solicitar
                cout << "Opcion: ";
                cin>>opcion;
                if(opcion.length()!=1 ||  (opcion[0] < '0' || opcion[0] > '5' )) cout<<"Introduce un numero correcto por favor."<<endl;//Si tiene mas de un caracter o no es un numero imprime un aviso
            }while(opcion.length()!=1 ||  (opcion[0] < '0' || opcion[0] > '5' ));//Si tiene mas de un caracter o no es numero volvera a solicitar
            cin.get();
            opcionnum=atoi(opcion.c_str());//Convierte a numero entero el numero almacenado en el string y lo copia en opcionnum

            switch(opcionnum){//Segun el valor de "opcionnum" realizara una de las siguientes opciones
            case 1:
                limpiar();
                uni.anyadirAlumno();//ejecuta el metodo añadir alumno en la clase universidad
                cout << endl<<"Pulse <ENTER> para continuar" << endl;
                cin.get();
                break;
            case 2:
                limpiar();
                uni.buscarAlumno();//ejecuta el metodo buscar alumno en la clase universidad
                cout << "Pulse <ENTER> para continuar" << endl;
                cin.get();
                break;
            case 3:
                limpiar();
                uni.ordenar();//ejecuta el metodo ordenar en la clase universidad
                cout << endl<<"Pulse <ENTER> para continuar" << endl;
                cin.get();
                break;
            case 4:
                limpiar();
                cout << uni << endl;//Imprime los datos de las titulaciones y los alumnos
                cout << "Pulse <ENTER> para continuar" << endl;
                cin.get();
                break;
            case 5://Sale del switch
                break;

            default://Salida por pantalla para cualquier valor no contemplado en el switch
                cout << "Error. Opcion incorrecta. Pulse ENTER para continuar" << endl;
                cin.get();
            }
        }while(opcionnum!=5);//Si "opcionnum" es distinto de 5 realiza el "do" pero si es igual a 5 sale
        guardar();//Llama al metodo guardar de esta clase
    }
    void guardar(){//Metodo para guardar los datos contenidos en el objeto universidad a un archivo de texto
        uni.ordenar();//Ordena los datos antes de guardarlo
        ofstream backup("fichero.txt");//Inicializamos el fichero para guardar
        backup<<uni;//Guardamos todos los datos contenidos en el objeto universidad utilizando la sobrecarga de operador << en la clase universidad
        backup.close();//Cerramos el archivo
    }
    void cargar(){//Metodo para cargar los datos contenidos en un archivo de texto al objeto universidad
        ifstream load("fichero.txt");//Inicializamos el archivo para cargar los datos
        string titulacion,dni,nombre,apellido1,apellido2;//Declaramos las variables string necesarias para recibir los datos del fichero
        //Este while se repite mientras continue la secuencia [palabra][palabra][palabra][palabra][palabra][fin de linea] y en cada repticion ejecuta el metodo añadir desde fichero de universidad
        while ( load >> titulacion >> dni >> nombre >> apellido1 >> apellido2 ) uni.anyadirAlumnofichero(titulacion,dni,nombre,apellido1,apellido2);//Enviamos los 5 string al metodo anyadirAlumnofichero de la clase universidad
        //Este metodo de leer el archivo, de modo secuencial, lo hemos aprendido del libro [C++ Como Programar - Deitel (Sexta edicion) - Tema 17]
        load.close();//Cerramos el archivo
    }

};

int main(){//Funcion principal del programa
    Menu menu;//Se crea un objeto "Menu"
    menu.ejecutar();//Llama al metodo ejecutar del objeto "Menu"
    return 0;//Sale del programa
}

