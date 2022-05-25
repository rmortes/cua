#include <iostream>
#include <cstdlib>//Para utilizar el metodo rand(), generamos numeros aleatorios
using namespace std;

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
class Matriz{//Clase base
protected:
    int **M;//Puntero bidimensional de enteros
    int NF, NC;//Enteros que definen el tamaño de filas y columnas
public:
    Matriz(){//Contructor por defecto de matriz
        M = NULL;//Matriz vacia 0x0
        NF = 0;
        NC = 0;
    }
    Matriz(int nf, int nc){//Contructor por parametros de matriz

        if(nf <= 0 || nc <= 0){//Si alguna dimension esta vacia o es negativa se deja la matriz vacia
            M = NULL;
            NF = 0;
            NC = 0;
        }
        else{//Si no contruimos la matriz con los datos recibidos
            NF = nf;
            NC = nc;
            M = new int * [NF];//Reservamos memoria para un array de direcciones
            for(int i = 0; i <NF; i++)//Recorremos el array
                M[i] = new int [NC];//Para cada posicion reservamos una columna
            for(int i = 0; i < NF; i++)//Recorremos la matriz para asignar numero enteros aleatorios
                for(int j = 0; j < NC; j++)
                    M[i][j] = rand() % 100;//Asignamos los numero a las posiciones de la matriz
        }
    }
    Matriz(int n){//Contructor por parametro. Un entero
        if(n <= 0){//Si alguna dimension esta vacia o es negativa se deja la matriz vacia
            M = NULL;
            NF = 0;
            NC = 0;
        }
        else{//Si no contruimos la matriz con los datos recibidos
            NF = n;
            NC = n;
            M = new int * [NF];//Reservamos memoria para un array de direcciones
            for(int i = 0; i <NF; i++)//Recorremos el array
                M[i] = new int [NC];//Para cada posicion reservamos una columna
            for(int i = 0; i < NF; i++)//Recorremos la matriz para asignar numero enteros aleatorios
                for(int j = 0; j < NC; j++)
                    M[i][j] = rand() % 100;//Asignamos los numero a las posiciones de la matriz
        }
    }
    Matriz(const Matriz &de){//Contructor de copia
        if(de.M == NULL){//Si esta vacia, copia vacia
            M = NULL;
            NF = NC = 0;
        }
        else{//Si no copia la matriz recibida en esta
            NF = de.NF;//Asigna el numero de filas de la matriz recibida a esta
            NC = de.NC;//Asigna el numero de columnas de la matriz recibida a esta
            // reservamos la memoria.
            M = new int * [NF];//Reservamos tanta memoria como la usada en la matriz recibida
            for(int i = 0; i <NF; i++){
                M[i] = new int [NC];//Creamos la cantidad de columnas  que tiene la matriz recibida
            }

            for(int i = 0; i < NF; i++){
                for(int j = 0; j < NC; j++)
                    M[i][j] = de.M[i][j];//Copiamos el contenido de la matriz recibida en esta posicion por posicion
            }
        }
    }
    ~Matriz(){//Destructor
        if(M != NULL){//Si no esta vacia
            for(int i = 0; i < NF; i++){//Recorremos el array de direcciones
                delete [] M[i];//Borramos el vector asociado al array
            }
            delete [] M;//Borramos el array de direcciones
            M = NULL;
            NF = NC  = 0;
        }
    }

    Matriz &operator=(const Matriz &de){//Operador asignacion de matriz, volcamos la matriz recibida en esta
        if(this != &de){//Comparamos las direcciones de las dos matrices, si no son iguales, son matrices distintas y se ejecuta lo siguiente, sino devolvera la misma ya que ya son iguales
            this->~Matriz(); //Destruimos la matriz de la izquierda para contruirla con la recibida
            if(de.M != NULL){//Si la matriz recibida no esta vacia ejecuta esto
                NF = de.NF;
                NC = de.NC;
                M = new int *[NF];//Reservamos tanta memoria como la usada en la matriz recibida
                for(int i = 0; i < NF; i++)
                    M[i] = new int [NC];//Creamos la cantidad de columnas
                for(int i = 0; i < NF; i++)
                    for(int j = 0; j < NC; j++)
                        M[i][j] = de.M[i][j];//Copiamos el contenido de la matriz recibida en esta posicion por posicion
            }
        }
        return (*this);//Devolvemos este objeto que es igual al recibido
    }
    Matriz operator+(const Matriz &de) const{//Suma de matrices
        Matriz aux;//Creamos una matriz auxiliar (al inicializar la matriz de aux sera nula 0x0)

        if(NF == de.NF && NC == de.NC && NF != 0){//Comprueba que tanto filas como las columnas sean del mismo tamaño y no sea nula
            Matriz Resul(NF, NC);//Crea una matriz del mismo tamaño que esta llamando al constructor por parametos
            for(int i = 0; i < NF; i++)//Recorremos las dos matrices, esta y la recibida
                for(int j = 0; j < NC; j++)
                    Resul.M[i][j] = M[i][j] + de.M[i][j];//sumamos posicion por posicion y lo asignamos a la matriz de Resul
            aux = Resul;//Volcamos matriz resul a matriz aux
        }

        return (aux);//Si son compatibles devolvera el resultado de la suma, sino devolvera matriz nula
    }
    Matriz operator-(const Matriz &de) const{//Resta de matrices
        Matriz aux;//Creamos una matriz auxiliar (al inicializar la matriz de aux sera nula 0x0)

        if(NF == de.NF && NC == de.NC && NF != 0){//Comprueba que tanto filas como las columnas sean del mismo tamaño y no sea nula
            Matriz Resul(NF, NC);//Crea una matriz del mismo tamaño que esta llamando al constructor por parametos
            for(int i = 0; i < NF; i++)//Recorremos las dos matrices, esta y la recibida
                for(int j = 0; j < NC; j++)
                    Resul.M[i][j] = M[i][j] - de.M[i][j];//restamos posicion por posicion y lo asignamos a la matriz de Resul
            aux = Resul;//Volcamos matriz resul a matriz aux
        }

        return (aux);//Si son compatibles devolvera el resultado de la resta, sino devolvera matriz nula
    }
    Matriz operator*(const Matriz &de) const{//Producto de matrices
        Matriz aux;//Creamos una matriz auxiliar (al inicializar la matriz de aux sera nula 0x0)
        ///Producto por la derecha
        if(NC == de.NF && NC != 0){//Comprobamos que las dimensiones sean compatibles para realizar el producto, numero de columnas de esta igual al numero de filas de la recibida
            Matriz resultado(NF, de.NC);//Crea una nueva matriz con el numero de filas de esta y el numero de columnas de la recibida llamando al contructor por parametros
            for(int i = 0; i < NF; i++){//Recorremos la matriz posicion por posicion
                for(int j = 0; j < de.NC; j++){
                    resultado.M[i][j] = 0;//Ponemos a cero la posicion en la que se va a volcar el producto de los vectores fila (M) y columna (de.M)
                    for(int k = 0; k < NC; k++){
                        resultado.M[i][j] += M[i][k]*de.M[k][j];//Vamos sumando los productos de los vectores fila (M) y columna (de.M). Resul.M = Resul.M + (M*de.M)

                        ///Realizamos la siguiente operación:
                        /*    k= 0  1  2  |j= 0  1  2       |j=      0            1           2
                         *  i=0 [a][b][c]    [j][k][l] k=0     [a*j+b*m+c*p][a*k+b*n+c*q][a*l+b*o+c*r] i=0
                         *  i=1 [d][e][f] *  [m][n][o] k=1  =  [d*j+e*m+f*p][d*k+e*n+f*q][d*l+e*o+f*r] i=1
                         *  i=2 [g][h][i]    [p][q][r] k=2     [g*j+h*m+i*p][g*k+h*n+i*q][g*l+h*o+i*r] i=2 */
                        ///        (M)         (de.M)                       (resultado.M)
                    }
                }
            }
            aux = resultado;//Volcamos los datos del objeto matrix resul al aux

        }else if(NF == de.NC && NF != 0){//Comprobamos que las dimensiones sean compatibles para realizar el producto, numero de columnas de esta igual al numero de filas de la recibida
            ///Producto por la izquierda
            Matriz resultado(NC, de.NF);//Crea una nueva matriz con el numero de filas de esta y el numero de columnas de la recibida llamando al contructor por parametros
            for(int i = 0; i < NC; i++){//Recorremos la matriz posicion por posicion
                for(int j = 0; j < de.NF; j++){
                    resultado.M[i][j] = 0;//Ponemos a cero la posicion en la que se va a volcar el producto de los vectores fila (M) y columna (de.M)
                    for(int k = 0; k < NF; k++){
                        resultado.M[i][j] += M[i][k]*de.M[k][j];//Vamos sumando los productos de los vectores fila (M) y columna (de.M). Resul.M = Resul.M + (M*de.M)

                        ///Realizamos la siguiente operación:
                        /*    k= 0  1  2  |j= 0  1  2       |j=      0            1           2
                         *  i=0 [a][b][c]    [j][k][l] k=0     [a*j+b*m+c*p][a*k+b*n+c*q][a*l+b*o+c*r] i=0
                         *  i=1 [d][e][f] *  [m][n][o] k=1  =  [d*j+e*m+f*p][d*k+e*n+f*q][d*l+e*o+f*r] i=1
                         *  i=2 [g][h][i]    [p][q][r] k=2     [g*j+h*m+i*p][g*k+h*n+i*q][g*l+h*o+i*r] i=2 */
                        ///        (M)         (de.M)                       (resultado.M)
                    }
                }
            }
            aux = resultado;//Volcamos los datos del objeto matrix resul al aux
        }
        return (aux);//Si son compatibles devolvera el resultado de la resta, sino devolvera matriz nula
    }
    Matriz operator*(int n) const{//Matriz por entero
        Matriz resultado(*this);// hago una copia de esta
        for(int i = 0; i < resultado.NF; i++)//Recorremos la matriz copiada (Resul)
            for(int j = 0; j < resultado.NC; j++)
                resultado.M[i][j] = resultado.M[i][j] * n;// multiplico cada elemento de la copia por el entero y lo volcamos a la matriz de resul.

        return (resultado);//Devolvemos el resultado del producto
    }

    void operator+=(const Matriz &de){//Sobrecarga de operador +=
        *this = *this + de;//Llama al operador suma y despues al de asignacion
    }
    void operator-=(const Matriz &de){//Sobrecarga de operador -=
        *this = *this - de;//Llama al operador resta y despues al de asignacion
    }
    void operator*=(const Matriz &de){//Sobrecarga del operdor *=
        *this = *this *de;//Llama al operador producto y luego al asignacion
    }
    void operator*=(int valor){//Sobrecarga del operador autoproducto. Recibe entero
        *this = *this*valor;//Llama al operador producto y luego al asignacion
    }

    int getNF()const{//Devuelve el numero de filas
        return NF;
    }
    int getNC()const{//Devuelve el numero de columnas
        return NC;
    }

    friend Matriz operator*(int n, const Matriz &de){//Sobrecarga del operador producto. Recibe entero y matriz. Entero por matriz
        return de*n; // llamo al de arriba.
    }
    friend ostream &operator<<(ostream &os, const Matriz &de){//Sobrecarga del operador de flujo de salida
        int i,j;
        if(de.M == NULL){//Si la matriz es nula imprime esto
            os << "Matriz nula" << endl;
        }else{//Sino imprime la matriz
            for(i = 0; i < de.NF; i++){//Recorremos la matriz
                for(j = 0; j < de.NC; j++){
                    if(de.M[i][j]<=9 && de.M[i][j]>=-9)os<<" ";//introducimos un espacio antes de imprimir la posicion cuando el numero contenido en la posicion [i][j] tiene un digito
                    os <<"[" <<  de.M[i][j] << "]"<<" "<<" ";//imprime una posicion de la matriz
                    if(de.M[i][j]<=99)os<<" ";//introducimos un espacio cuando el numero contenido en la posicion [i][j] tiene 2 digitos
                    if(de.M[i][j]<=999)os<<" ";//introducimos un espacio cuando el numero contenido en la posicion [i][j] tiene 3 digitos
                    if(de.M[i][j]<=9999)os<<" ";//introducimos un espacio cuando el numero contenido en la posicion [i][j] tiene 4 digitos
                }

                os << endl;//Cuando llega al final de una fila introduce un salto de linea y continua con la siguiente fila
            }
        }
        return (os);//Devuelve el medio
    }

};
class MatrizG : public Matriz{
public:
    /* MatrizG. Representa una matriz gruyere, esto es, una matriz en la que los ceros y
     * los elementos distintos de cero se alternan (si fila+columna es par la celda se
     * rellena con un 0 y con un número aleatorio entre 0 y 99 en otro caso). Se formará
     * por herencia directa de Matriz.
     */
    MatrizG(){}//Contructor por defecto
    MatrizG(const Matriz &de):Matriz(de){//Constructor por parametros que recibe una matriz y envia esta al constructor por defecto de la clase base
    }
    MatrizG(int nf, int nc):Matriz(nf, nc){//Constructor por parametros que recibe dos enteros y  los  al constructor por parametros de la clase base
        for(int i = 0; i < NF; i++)//Recorremos la matriz
            for(int j = 0; j < NC; j++){
                if((i + j) % 2 == 0){//Si el resto de la division de (i+j)/2 querra decir que la suma es par y se ejecutara lo siguiente
                    M[i][j] = 0;//Pondra a cero las posiciones donde i+j sea par
                }else{//sino introducira un numero aleatorio
                    M[i][j] = rand() % 100;//Numero aleatorio entre 0 y 99
                }
            }
    }
    MatrizG(int n){//Constructor por parametros que recibe una matriz y envia esta al constructor por parametros de la clase base
        *this = MatrizG(n,n);
    }

};
class MatrizC : public Matriz{
public:
    /*MatrizC. Representa una matriz cuadrada, esto es, una matriz cuyo número de filas y
     * columnas coincide. El constructor por parámetros de esta clase recibirá un solo
     * entero que representará tanto el número de filas como el de columnas. Al igual que
     * en Matriz, dicho constructor será el encargado de rellenar los elementos de la matriz
     * con números aleatorios entre 0 y 99. Se formará por herencia directa de Matriz.
     */
    MatrizC(){//Constructor por defecto
    }
    MatrizC(const Matriz &de): Matriz(de.getNF(), de.getNC()){//Constructor por parametros. Recibe matriz y envia 2 enteros (NF y NC) al contructor por parametros de la clase base
    }
    MatrizC(int n): Matriz(n, n){//Contructor por parametro. Recibe un entero y llama al contructor por parametro de la clase base para crear una matriz de N*N (Cuadrada)
    }
    MatrizC(int nc, int nf){//Si enviamos dos enteros a matriz cuadrada y no son iguales, la matriz es nula ya que no es cuadrada
        if(nc==nf){//Si los dos enteros son iguales, la matriz sera cuadrada
            *this= Matriz(nc, nc);
        }
    }
    MatrizC(const MatrizC &de): Matriz(de){//Constructor de copia. Recibe una matriz y llama al contructor de copia de la clase base
    }
};
class MatrizD : public MatrizC{
public:
    /*MatrizD. Representa una matriz diagonal y como tal, debe ser cuadrada, por lo que se
     * formará como herencia de MatrizC. La matriz diagonal se caracteriza por tener todos
     * sus elementos a cero excepto los de la diagonal principal. Al igual que en MatrizC,
     * el constructor de MatrizD recibirá un solo número entero que simbolizará tanto filas
     * como columnas y, en este caso, rellenará las celdas de la diagonal de números aleatorios
     * entre 0 y 99 y el resto a cero.
     * */
    MatrizD(){}//Contructor por defecto
    MatrizD(const Matriz &de):MatrizC(de){//Recibe una matriz y la envia a la clase base
    }
    MatrizD(int n):MatrizC(n){//Recibe un entero, lo envia a la clase base (MatrizC), esta lo envia a su clase base (Matriz) para crear una matriz cuadrada y ahora trabajamos con ella
        for(int i = 0; i < NF; i++){//Recorremos la matriz
            for(int j = 0; j < NC; j++){
                if(i == j){//Cuando las posiciones sean iguales ( [0,0] ó [1,1] o [2,2]) introducira un numero aleatorio
                    M[i][j] = rand() %100;
                }else{//Si no son iguales lo pone a 0
                    M[i][j] = 0;
                }
            }
        }
    }
    MatrizD(int nc, int nf){//Si enviamos dos enteros a matriz diagonal y no son iguales, la matriz es nula ya que no es cuadrada
        if(nc==nf){//Si los dos enteros son iguales, la matriz sera cuadrada
            *this= MatrizD(nc);
        }
    }
    MatrizD(const MatrizD &de):MatrizC(de){//Constructor de copia. Recibe una matriz y llama al contructor de copia de la clase base
    }

};
class MatrizE : public MatrizD{
public:
    /*MatrizE. Representa una matriz escalar, esto es, una matriz cuadrada y diagonal donde
     * además todos los elementos de la diagonal son iguales. Esta clase se formará por
     * herencia a partir de MatrizD y al igual que ésta el constructor por parámetros recibirá
     * un solo número entero que simbolizará tanto filas como columnas. En este caso rellenará
     * todas las celdas de la diagonal con un mismo número aleatorio entre 0 y 99 y el resto a cero.
     */

    MatrizE(){//Contructor por defecto
    }
    MatrizE(const MatrizE &de):MatrizD(de) {//Constructor de copia. Recibe una matriz y llama al contructor de copia de la clase base
    }
    MatrizE(int n):MatrizD(n){//Contructor con un entero. Envia el entero a la clase base (MatrizD) que esta a su vez la envia a su clase base (MatrizC) y esta a la clase Matriz.
        //Al terminar tendremos una matriz cuadrada y diagonal

        int aux = rand() % 100;//Creamos un entero con un numero aleatorio
        for(int i = 0; i < n; i++){//Como ya tenemos todas la posiciones no-diagonales a 0 (MatrizD), solo nos queda asignar el mismo numero a toda la diagonal
            M[i][i] = aux;
        }
    }
    MatrizE(int nc, int nf){//Si enviamos dos enteros a matriz diagonal y no son iguales, la matriz es nula ya que no es cuadrada
        if(nc==nf){//Si los dos enteros son iguales, la matriz sera cuadrada
            *this = MatrizE(nc);
        }
    }
};
class tiposMatrices{//Menu para mostrar todos los tipos de matrices al usuario
public:
    void imprimir(){
        cout << "1. Matriz base" << endl;
        cout << "2. Matriz gruyere" << endl;
        cout << "3. Matriz cuadrada" << endl;
        cout << "4. Matriz diagonal" << endl;
        cout << "5. Matriz escalar" << endl;
        cout << "6. Salir" << endl;
    }
    void ejecutar(){

        int opcionnum;//Declaracion de una variable entera
        int NC,NF;
        string opcion;//String utilizado para recibir la opcion del usuario, validar si es un numero y si lo es ejecutar la opcion
        do{
            limpiar();
            imprimir();//llama al metodo imprimir incluido en esta clase

            do{//Pediremos la opcion y comprobaremos si es un numero, si no lo es se volvera a solicitar
                cout << "Opcion: ";
                cin>>opcion;
                if(opcion.length()!=1 ||  (opcion[0] < '0' || opcion[0] > '6' )) cout<<"Introduce un numero correcto por favor."<<endl;//Si tiene mas de un caracter o no es un numero imprime un aviso
            }while(opcion.length()!=1 ||  (opcion[0] < '0' || opcion[0] > '6' ));//Si tiene mas de un caracter o no es numero volvera a solicitar
            cin.get();
            opcionnum=atoi(opcion.c_str());//Convierte a numero entero el numero almacenado en el string y lo copia en opcionnum

            switch(opcionnum){//Segun el valor de "opcionnum" realizara una de las siguientes opciones
            case 1:
                limpiar();
                ///Matriz base
                cout<<"Matriz 3x3"<<endl<<endl;
                cout<<Matriz (3);
                cin.get();
                cout<<"Matriz 4x4"<<endl<<endl;
                cout<<Matriz (4);
                cin.get();

                cout<<"Matriz personalizada"<<endl<<endl;
                cout<<"Numero de filas"<<endl;
                cin>>NF;
                cout<<"Numero de columnas"<<endl;
                cin>>NC;
                cout<<endl<<Matriz (NF,NC);
                cin.get();
                cin.get();
                break;
            case 2:
                limpiar();
                ///Matriz gruyere
                cout<<"Matriz gruyere 3x3"<<endl<<endl;
                cout<<MatrizG (3);
                cin.get();
                cout<<"Matriz gruyere 4x4"<<endl<<endl;
                cout<<MatrizG (4);
                cin.get();

                cout<<"Matriz gruyere personalizada"<<endl<<endl;
                cout<<"Numero de filas"<<endl;
                cin>>NF;
                cout<<"Numero de columnas"<<endl;
                cin>>NC;
                cout<<endl<<MatrizG (NF,NC);
                cin.get();
                cin.get();
                break;
            case 3:
                limpiar();
                ///Matriz cuadrada
                cout<<"Matriz cuadrada 3x3"<<endl<<endl;
                cout<<MatrizC (3);
                cin.get();
                cout<<"Matriz gruyere 4x4"<<endl<<endl;
                cout<<MatrizC (4);
                cin.get();

                cout<<"Matriz cuadrada personalizada"<<endl<<endl;
                cout<<"Numero de filas"<<endl;
                cin>>NF;
                cout<<"Numero de columnas"<<endl;
                cin>>NC;
                cout<<endl<<MatrizC (NF,NC);
                cin.get();
                cin.get();
                break;
            case 4:
                limpiar();
                ///Matriz diagonal
                cout<<"Matriz diagonal 3x3"<<endl<<endl;
                cout<<MatrizD (3);
                cin.get();
                cout<<"Matriz diagonal 4x4"<<endl<<endl;
                cout<<MatrizD (4);
                cin.get();

                cout<<"Matriz diagonal personalizada"<<endl<<endl;
                cout<<"Numero de filas"<<endl;
                cin>>NF;
                cout<<"Numero de columnas"<<endl;
                cin>>NC;
                cout<<endl<<MatrizD (NF,NC);
                cin.get();
                cin.get();
                break;

            case 5:
                limpiar();
                ///Matriz escalar
                cout<<"Matriz escalar 3x3"<<endl<<endl;
                cout<<MatrizE (3);
                cin.get();
                cout<<"Matriz escalar 4x4"<<endl<<endl;
                cout<<MatrizE (4);
                cin.get();

                cout<<"Matriz escalar personalizada"<<endl<<endl;
                cout<<"Numero de filas"<<endl;
                cin>>NF;
                cout<<"Numero de columnas"<<endl;
                cin>>NC;
                cout<<endl<<MatrizE (NF,NC);
                cin.get();
                cin.get();
                break;

            case 6://Sale del switch
                break;

            default://Salida por pantalla para cualquier valor no contemplado en el switch
                cout << "Error. Opcion incorrecta. Pulse ENTER para continuar" << endl;
                cin.get();
            }
        }while(opcionnum!=6);//Si "opcionnum" es distinto de 5 realiza el "do" pero si es igual a 5 sale




    }
};
class productosMatricesEnteros{//Menu para mostrar todos los tipos de productos de matrices por entero al usuario
public:
    void imprimir(){
        cout << "1. Producto" << endl;
        cout << "2. Autoproducto" << endl;
        cout << "3. Salir" << endl;
    }
    void ejecutar(){

        int opcionnum;//Declaracion de una variable entera
        string opcion;//String utilizado para recibir la opcion del usuario, validar si es un numero y si lo es ejecutar la opcion
        do{
            limpiar();
            imprimir();//llama al metodo imprimir incluido en esta clase

            do{//Pediremos la opcion y comprobaremos si es un numero, si no lo es se volvera a solicitar
                cout << "Opcion: ";
                cin>>opcion;
                if(opcion.length()!=1 ||  (opcion[0] < '0' || opcion[0] > '3' )) cout<<"Introduce un numero correcto por favor."<<endl;//Si tiene mas de un caracter o no es un numero imprime un aviso
            }while(opcion.length()!=1 ||  (opcion[0] < '0' || opcion[0] > '3' ));//Si tiene mas de un caracter o no es numero volvera a solicitar
            cin.get();
            opcionnum=atoi(opcion.c_str());//Convierte a numero entero el numero almacenado en el string y lo copia en opcionnum

            switch(opcionnum){//Segun el valor de "opcionnum" realizara una de las siguientes opciones
            case 1:
                limpiar();
                producto();
                cout << "Pulse <ENTER> para continuar" << endl;
                cin.get();
                break;
            case 2:
                limpiar();
                autoProducto();
                cout << "Pulse <ENTER> para continuar" << endl;
                cin.get();
                break;

            case 3://Sale del switch
                break;

            default://Salida por pantalla para cualquier valor no contemplado en el switch
                cout << "Error. Opcion incorrecta. Pulse ENTER para continuar" << endl;
                cin.get();
            }
        }while(opcionnum!=3);//Si "opcionnum" es distinto de 5 realiza el "do" pero si es igual a 5 sale




    }
    void imprimirProducto(){
        cout << "1. Producto por entero de matriz base" << endl;
        cout << "2. Producto por entero de matriz gruyere" << endl;
        cout << "3. Producto por entero de matriz cuadrada" << endl;
        cout << "4. Producto por entero de matriz diagonal" << endl;
        cout << "5. Producto por entero de matriz escalar" << endl;
        cout << "6. Salir" << endl;

    }
    void producto(){

        int opcionnum;//Declaracion de una variable entera
        string opcion;//String utilizado para recibir la opcion del usuario, validar si es un numero y si lo es ejecutar la opcion
        do{
            limpiar();
            imprimirProducto();//llama al metodo imprimir incluido en esta clase

            do{//Pediremos la opcion y comprobaremos si es un numero, si no lo es se volvera a solicitar
                cout << "Opcion: ";
                cin>>opcion;
                if(opcion.length()!=1 ||  (opcion[0] < '0' || opcion[0] > '6' )) cout<<"Introduce un numero correcto por favor."<<endl;//Si tiene mas de un caracter o no es un numero imprime un aviso
            }while(opcion.length()!=1 ||  (opcion[0] < '0' || opcion[0] > '6' ));//Si tiene mas de un caracter o no es numero volvera a solicitar
            cin.get();
            opcionnum=atoi(opcion.c_str());//Convierte a numero entero el numero almacenado en el string y lo copia en opcionnum

            switch(opcionnum){//Segun el valor de "opcionnum" realizara una de las siguientes opciones
            case 1:
                limpiar();
                //Base por entero
                cout<<"Matriz base por entero"<<endl<<endl;
                cout<<Matriz(4)*5;
                cin.get();
                cin.get();
                break;
            case 2:
                limpiar();
                //Gruyere por entero
                cout<<"Gruyere por entero"<<endl<<endl;
                cout<<MatrizG(4)*5;
                cin.get();
                cin.get();
                break;
            case 3:
                limpiar();
                //Cuadrada por entero
                cout<<"Cuadrada por entero"<<endl<<endl;
                cout<<MatrizC(4)*5;
                cin.get();
                cin.get();
                break;
            case 4:
                limpiar();
                //Diagonal por entero
                cout<<"Diagonal por entero"<<endl<<endl;
                cout<<MatrizD(4)*5;
                cin.get();
                cin.get();
                break;
            case 5:
                limpiar();
                //Escalar por entero
                cout<<"Escalar por entero"<<endl<<endl;
                cout<<MatrizE(4)*5;
                cin.get();
                cin.get();
                break;


            case 6://Sale del switch
                break;

            default://Salida por pantalla para cualquier valor no contemplado en el switch
                cout << "Error. Opcion incorrecta. Pulse ENTER para continuar" << endl;
                cin.get();
            }
        }while(opcionnum!=6);//Si "opcionnum" es distinto de 5 realiza el "do" pero si es igual a 5 sale
    }
    void imprimirAutoproducto(){
        cout << "1. Autoproducto por entero de matriz base" << endl;
        cout << "2. Autoproducto por entero de matriz gruyere" << endl;
        cout << "3. Autoproducto por entero de matriz cuadrada" << endl;
        cout << "4. Autoproducto por entero de matriz diagonal" << endl;
        cout << "5. Autoproducto por entero de matriz escalar" << endl;
        cout << "6. Salir" << endl; }
    void autoProducto(){
        int opcionnum;//Declaracion de una variable entera
        string opcion;//String utilizado para recibir la opcion del usuario, validar si es un numero y si lo es ejecutar la opcion
        do{
            limpiar();
            imprimirAutoproducto();//llama al metodo imprimir incluido en esta clase

            do{//Pediremos la opcion y comprobaremos si es un numero, si no lo es se volvera a solicitar
                cout << "Opcion: ";
                cin>>opcion;
                if(opcion.length()!=1 ||  (opcion[0] < '0' || opcion[0] > '6' )) cout<<"Introduce un numero correcto por favor."<<endl;//Si tiene mas de un caracter o no es un numero imprime un aviso
            }while(opcion.length()!=1 ||  (opcion[0] < '0' || opcion[0] > '6' ));//Si tiene mas de un caracter o no es numero volvera a solicitar
            cin.get();
            opcionnum=atoi(opcion.c_str());//Convierte a numero entero el numero almacenado en el string y lo copia en opcionnum

            switch(opcionnum){//Segun el valor de "opcionnum" realizara una de las siguientes opciones
            //En cada case hemos puesto corchetes porque Qt incicaba que estaba en "protected scope", al poner corchetes se ha solucionado
            case 1:
            {
                limpiar();
                //Base por entero
                cout<<"Base por entero"<<endl<<endl;
                Matriz base(4);
                base*=5;
                cout<<base;
                cin.get();
                cin.get();
                break;
            }
            case 2:
            {
                limpiar();
                //Gruyere por entero
                cout<<"Gruyere por entero"<<endl<<endl;
                MatrizG a(4);
                a*=5;
                cout<<a;
                cin.get();
                cin.get();
                break;
            }
            case 3:
            {
                limpiar();
                //Cuadrada por entero
                cout<<"Cuadrada por entero"<<endl<<endl;
                MatrizC b(4);
                b*=5;
                cout<<b;
                cin.get();
                cin.get();
                break;
            }
            case 4:
            {
                limpiar();
                //Diagonal por entero
                cout<<"Diagonal por entero"<<endl<<endl;
                MatrizD c(4);
                c*=5;
                cout<<c;
                cin.get();
                cin.get();
                break;
            }
            case 5:
            {
                limpiar();
                //Escalar por entero
                cout<<"Escalar por entero"<<endl<<endl;
                MatrizE d(4);
                d*=5;
                cout<<d;
                cin.get();
                cin.get();
                break;
            }


            case 6://Sale del switch
                break;

            default://Salida por pantalla para cualquier valor no contemplado en el switch
                cout << "Error. Opcion incorrecta. Pulse ENTER para continuar" << endl;
                cin.get();
            }


        }while(opcionnum!=6);//Si "opcionnum" es distinto de 5 realiza el "do" pero si es igual a 5 sale
    }
};
class productosMatrices{//Menu para mostrar todos los tipos de productos de matrices por matrices al usuario
public:
    void imprimir(){
        cout << "1. Producto" << endl;
        cout << "2. Autoproducto" << endl;
        cout << "3. Salir" << endl;
    }
    void ejecutar(){

        int opcionnum;//Declaracion de una variable entera
        string opcion;//String utilizado para recibir la opcion del usuario, validar si es un numero y si lo es ejecutar la opcion
        do{
            limpiar();
            imprimir();//llama al metodo imprimir incluido en esta clase

            do{//Pediremos la opcion y comprobaremos si es un numero, si no lo es se volvera a solicitar
                cout << "Opcion: ";
                cin>>opcion;
                if(opcion.length()!=1 ||  (opcion[0] < '0' || opcion[0] > '3' )) cout<<"Introduce un numero correcto por favor."<<endl;//Si tiene mas de un caracter o no es un numero imprime un aviso
            }while(opcion.length()!=1 ||  (opcion[0] < '0' || opcion[0] > '3' ));//Si tiene mas de un caracter o no es numero volvera a solicitar
            cin.get();
            opcionnum=atoi(opcion.c_str());//Convierte a numero entero el numero almacenado en el string y lo copia en opcionnum

            switch(opcionnum){//Segun el valor de "opcionnum" realizara una de las siguientes opciones
            case 1:
                limpiar();
                producto();
                cout << "Pulse <ENTER> para continuar" << endl;
                cin.get();
                break;
            case 2:
                limpiar();
                autoProducto();
                cout << "Pulse <ENTER> para continuar" << endl;
                cin.get();
                break;

            case 3://Sale del switch
                break;

            default://Salida por pantalla para cualquier valor no contemplado en el switch
                cout << "Error. Opcion incorrecta. Pulse ENTER para continuar" << endl;
                cin.get();
            }
        }while(opcionnum!=3);//Si "opcionnum" es distinto de 5 realiza el "do" pero si es igual a 5 sale




    }
    void imprimirProducto(){
        cout << "1. Producto de matriz base por matriz base" << endl;
        cout << "2. Producto de matriz gruyere por matriz gruyere" << endl;
        cout << "3. Producto de matriz cuadrada por matriz cuadrada" << endl;
        cout << "4. Producto de matriz diagonal por matriz diagonal" << endl;
        cout << "5. Producto de matriz escalar por matriz escalar" << endl;
        cout << "6. Salir" << endl;

    }
    void producto(){

        int opcionnum;//Declaracion de una variable entera
        string opcion;//String utilizado para recibir la opcion del usuario, validar si es un numero y si lo es ejecutar la opcion
        do{
            limpiar();
            imprimirProducto();//llama al metodo imprimir incluido en esta clase

            do{//Pediremos la opcion y comprobaremos si es un numero, si no lo es se volvera a solicitar
                cout << "Opcion: ";
                cin>>opcion;
                if(opcion.length()!=1 ||  (opcion[0] < '0' || opcion[0] > '6' )) cout<<"Introduce un numero correcto por favor."<<endl;//Si tiene mas de un caracter o no es un numero imprime un aviso
            }while(opcion.length()!=1 ||  (opcion[0] < '0' || opcion[0] > '6' ));//Si tiene mas de un caracter o no es numero volvera a solicitar
            cin.get();
            opcionnum=atoi(opcion.c_str());//Convierte a numero entero el numero almacenado en el string y lo copia en opcionnum

            switch(opcionnum){//Segun el valor de "opcionnum" realizara una de las siguientes opciones
            case 1:
                limpiar();
                //Base
                cout<<"Matriz base 2x3 por matriz base 3x2"<<endl<<endl;
                cout<<Matriz(2,3)*Matriz(3,2)<<endl;
                cout<<"Matriz base 3x2 por matriz base 2x3"<<endl<<endl;
                cout<<Matriz(3,2)*Matriz(2,3);
                cin.get();
                cin.get();
                break;
            case 2:
                limpiar();
                //Gruyere
                cout<<"Matriz gruyere 2x3 por matriz gruyere 3x2"<<endl<<endl;
                cout<<MatrizG(2,3)*MatrizG(3,2)<<endl;
                cout<<"Matriz gruyere 3x2 por matriz gruyere 2x3"<<endl<<endl;
                cout<<MatrizG(3,2)*MatrizG(2,3);
                cin.get();
                cin.get();
                break;
            case 3:
                limpiar();
                //Cuadrada
                cout<<"Matriz cuadrada 3x3 por matriz cuadrada 4x4"<<endl<<endl;
                cout<<MatrizC(3,3)*MatrizC(4,4)<<endl;
                cout<<"Matriz cuadrada 3x2 por matriz cuadrada 2x3"<<endl<<endl;
                cout<<MatrizC(3,2)*MatrizC(2,3)<<endl;
                cout<<"Matriz cuadrada 3x3 por matriz cuadrada 3x3"<<endl<<endl;
                cout<<MatrizC(3,3)*MatrizC(3,3);
                cin.get();
                cin.get();
                break;
            case 4:
                limpiar();
                //Diagonal
                cout<<"Matriz diagonal 3x3 por matriz diagonal 4x4"<<endl<<endl;
                cout<<MatrizD(3,3)*MatrizD(4,4)<<endl;
                cout<<"Matriz diagonal 3x2 por matriz diagonal 2x3"<<endl<<endl;
                cout<<MatrizD(3,2)*MatrizD(2,3)<<endl;
                cout<<"Matriz diagonal 3x3 por matriz diagonal 3x3"<<endl<<endl;
                cout<<MatrizD(3,3)*MatrizD(3,3);
                cin.get();
                cin.get();
                break;
            case 5:
                limpiar();
                //Escalar
                cout<<"Matriz escalar 3x3 por matriz escalar 4x4"<<endl<<endl;
                cout<<MatrizE(3,3)*MatrizE(4,4)<<endl;
                cout<<"Matriz escalar 3x2 por matriz escalar 2x3"<<endl<<endl;
                cout<<MatrizE(3,2)*MatrizE(2,3)<<endl;
                cout<<"Matriz escalar 3x3 por matriz escalar 3x3"<<endl<<endl;
                cout<<MatrizE(3,3)*MatrizE(3,3);
                cin.get();
                cin.get();
                break;


            case 6://Sale del switch
                break;

            default://Salida por pantalla para cualquier valor no contemplado en el switch
                cout << "Error. Opcion incorrecta. Pulse ENTER para continuar" << endl;
                cin.get();
            }
        }while(opcionnum!=6);//Si "opcionnum" es distinto de 5 realiza el "do" pero si es igual a 5 sale
    }
    void imprimirAutoproducto(){
        cout << "1. Autoproducto de matriz base por matriz base" << endl;
        cout << "2. Autoproducto de matriz gruyere por matriz gruyere" << endl;
        cout << "3. Autoproducto de matriz cuadrada por matriz cuadrada" << endl;
        cout << "4. Autoproducto de matriz diagonal por matriz diagonal" << endl;
        cout << "5. Autoproducto de matriz escalar por matriz escalar" << endl;
        cout << "6. Salir" << endl; }
    void autoProducto(){
        int opcionnum;//Declaracion de una variable entera
        string opcion;//String utilizado para recibir la opcion del usuario, validar si es un numero y si lo es ejecutar la opcion
        do{
            limpiar();
            imprimirAutoproducto();//llama al metodo imprimir incluido en esta clase

            do{//Pediremos la opcion y comprobaremos si es un numero, si no lo es se volvera a solicitar
                cout << "Opcion: ";
                cin>>opcion;
                if(opcion.length()!=1 ||  (opcion[0] < '0' || opcion[0] > '6' )) cout<<"Introduce un numero correcto por favor."<<endl;//Si tiene mas de un caracter o no es un numero imprime un aviso
            }while(opcion.length()!=1 ||  (opcion[0] < '0' || opcion[0] > '6' ));//Si tiene mas de un caracter o no es numero volvera a solicitar
            cin.get();
            opcionnum=atoi(opcion.c_str());//Convierte a numero entero el numero almacenado en el string y lo copia en opcionnum

            switch(opcionnum){//Segun el valor de "opcionnum" realizara una de las siguientes opciones
            //En cada case hemos puesto corchetes porque Qt incicaba que estaba en "protected scope", al poner corchetes se ha solucionado
            case 1:
            {
                limpiar();
                //Base
                cout<<"Matriz base 2x3 por matriz base 3x2"<<endl<<endl;
                Matriz a(2,3), b(3,2);
                a*=b;
                cout<<a<<endl;
                cout<<"Matriz base 3x2 por matriz base 2x3"<<endl<<endl;
                Matriz c(3,2), d(2,3);
                c*=d;
                cout<<c<<endl;
                cin.get();
                cin.get();
                break;
            }
            case 2:
            {
                limpiar();
                //Gruyere
                cout<<"Matriz gruyere 2x3 por matriz gruyere 3x2"<<endl<<endl;
                MatrizG a(2,3), b(3,2);
                a*=b;
                cout<<a<<endl;
                cout<<"Matriz gruyere 3x2 por matriz gruyere 2x3"<<endl<<endl;
                MatrizG c(3,2), d(2,3);
                c*=d;
                cout<<c<<endl;
                cin.get();
                cin.get();
                break;
            }
            case 3:
            {
                limpiar();
                //Cuadrada
                cout<<"Matriz cuadrada 3x3 por matriz cuadrada 4x4"<<endl<<endl;
                MatrizC a(2,3), b(3,2);
                a*=b;
                cout<<a<<endl;
                cout<<"Matriz cuadrada 3x2 por matriz cuadrada 2x3"<<endl<<endl;
                MatrizC c(3,2), d(2,3);
                c*=d;
                cout<<c<<endl;
                cout<<"Matriz cuadrada 3x3 por matriz cuadrada 3x3"<<endl<<endl;
                MatrizC e(3,3), f(3,3);
                e*=f;
                cout<<e<<endl;
                cin.get();
                cin.get();
                break;
            }
            case 4:
            {
                limpiar();
                //Diagonal
                cout<<"Matriz diagonal 3x3 por matriz diagonal 4x4"<<endl<<endl;
                MatrizD a(2,3), b(3,2);
                a*=b;
                cout<<a<<endl;
                cout<<"Matriz diagonal 3x2 por matriz diagonal 2x3"<<endl<<endl;
                MatrizD c(3,2), d(2,3);
                c*=d;
                cout<<c<<endl;
                cout<<"Matriz diagonal 3x3 por matriz diagonal 3x3"<<endl<<endl;
                MatrizD e(3,3), f(3,3);
                e*=f;
                cout<<e<<endl;
                cin.get();
                cin.get();
                break;
            }
            case 5:
            {
                limpiar();
                //Escalar
                cout<<"Matriz escalar 3x3 por matriz escalar 4x4"<<endl<<endl;
                MatrizE a(2,3), b(3,2);
                a*=b;
                cout<<a<<endl;
                cout<<"Matriz escalar 3x2 por matriz escalar 2x3"<<endl<<endl;
                MatrizE c(3,2), d(2,3);
                c*=d;
                cout<<c<<endl;
                cout<<"Matriz escalar 3x3 por matriz escalar 3x3"<<endl<<endl;
                MatrizE e(3,3), f(3,3);
                e*=f;
                cout<<e<<endl;
                cin.get();
                cin.get();
                break;
            }


            case 6://Sale del switch
                break;

            default://Salida por pantalla para cualquier valor no contemplado en el switch
                cout << "Error. Opcion incorrecta. Pulse ENTER para continuar" << endl;
                cin.get();
            }
        }while(opcionnum!=6);//Si "opcionnum" es distinto de 5 realiza el "do" pero si es igual a 5 sale
    }
};
class sumasMatrices{//Menu para mostrar todos los tipos de sumas de matrices al usuario
public:
    void imprimir(){
        cout << "1. Suma" << endl;
        cout << "2. Autosuma" << endl;
        cout << "3. Salir" << endl;
    }
    void ejecutar(){

        int opcionnum;//Declaracion de una variable entera
        string opcion;//String utilizado para recibir la opcion del usuario, validar si es un numero y si lo es ejecutar la opcion
        do{
            limpiar();
            imprimir();//llama al metodo imprimir incluido en esta clase

            do{//Pediremos la opcion y comprobaremos si es un numero, si no lo es se volvera a solicitar
                cout << "Opcion: ";
                cin>>opcion;
                if(opcion.length()!=1 ||  (opcion[0] < '0' || opcion[0] > '3' )) cout<<"Introduce un numero correcto por favor."<<endl;//Si tiene mas de un caracter o no es un numero imprime un aviso
            }while(opcion.length()!=1 ||  (opcion[0] < '0' || opcion[0] > '3' ));//Si tiene mas de un caracter o no es numero volvera a solicitar
            cin.get();
            opcionnum=atoi(opcion.c_str());//Convierte a numero entero el numero almacenado en el string y lo copia en opcionnum

            switch(opcionnum){//Segun el valor de "opcionnum" realizara una de las siguientes opciones
            case 1:
                limpiar();
                suma();
                cout << "Pulse <ENTER> para continuar" << endl;
                cin.get();
                break;
            case 2:
                limpiar();
                autoSuma();
                cout << "Pulse <ENTER> para continuar" << endl;
                cin.get();
                break;

            case 3://Sale del switch
                break;

            default://Salida por pantalla para cualquier valor no contemplado en el switch
                cout << "Error. Opcion incorrecta. Pulse ENTER para continuar" << endl;
                cin.get();
            }
        }while(opcionnum!=3);//Si "opcionnum" es distinto de 5 realiza el "do" pero si es igual a 5 sale




    }
    void imprimirSuma(){
        cout << "1. Suma de matrices base" << endl;
        cout << "2. Suma de matrices gruyere" << endl;
        cout << "3. Suma de matrices cuadrada" << endl;
        cout << "4. Suma de matrices diagonal" << endl;
        cout << "5. Suma de matrices escalar" << endl;
        cout << "6. Salir" << endl;

    }
    void suma(){

        int opcionnum;//Declaracion de una variable entera
        string opcion;//String utilizado para recibir la opcion del usuario, validar si es un numero y si lo es ejecutar la opcion
        do{
            limpiar();
            imprimirSuma();//llama al metodo imprimir incluido en esta clase

            do{//Pediremos la opcion y comprobaremos si es un numero, si no lo es se volvera a solicitar
                cout << "Opcion: ";
                cin>>opcion;
                if(opcion.length()!=1 ||  (opcion[0] < '0' || opcion[0] > '6' )) cout<<"Introduce un numero correcto por favor."<<endl;//Si tiene mas de un caracter o no es un numero imprime un aviso
            }while(opcion.length()!=1 ||  (opcion[0] < '0' || opcion[0] > '6' ));//Si tiene mas de un caracter o no es numero volvera a solicitar
            cin.get();
            opcionnum=atoi(opcion.c_str());//Convierte a numero entero el numero almacenado en el string y lo copia en opcionnum

            switch(opcionnum){//Segun el valor de "opcionnum" realizara una de las siguientes opciones
            case 1:
                limpiar();
                //Base
                cout<<"Suma de matrices base"<<endl<<endl;
                cout<<Matriz(4)+Matriz(4);
                cin.get();
                cin.get();
                break;
            case 2:
                limpiar();
                //Gruyere
                cout<<"Suma de matrices gruyere"<<endl<<endl;
                cout<<MatrizG(4)+MatrizG(4);
                cin.get();
                cin.get();
                break;
            case 3:
                limpiar();
                //Cuadrada
                cout<<"Suma de matrices cuadradas"<<endl<<endl;
                cout<<MatrizC(4)+MatrizC(4);
                cin.get();
                cin.get();
                break;
            case 4:
                limpiar();
                //Diagonal
                cout<<"Suma de matrices diagonales"<<endl<<endl;
                cout<<MatrizD(4)+MatrizD(4);
                cin.get();
                cin.get();
                break;
            case 5:
                limpiar();
                //Escalar
                cout<<"Suma de matrices escalares"<<endl<<endl;
                cout<<MatrizE(4)+MatrizE(4);
                cin.get();
                cin.get();
                break;


            case 6://Sale del switch
                break;

            default://Salida por pantalla para cualquier valor no contemplado en el switch
                cout << "Error. Opcion incorrecta. Pulse ENTER para continuar" << endl;
                cin.get();
            }
        }while(opcionnum!=6);//Si "opcionnum" es distinto de 5 realiza el "do" pero si es igual a 5 sale
    }
    void imprimirAutosuma(){
        cout << "1. Autosuma de matrices base" << endl;
        cout << "2. Autosuma de matrices gruyere" << endl;
        cout << "3. Autosuma de matrices cuadrada" << endl;
        cout << "4. Autosuma de matrices diagonal" << endl;
        cout << "5. Autosuma de matrices escalar" << endl;
        cout << "6. Salir" << endl; }
    void autoSuma(){
        int opcionnum;//Declaracion de una variable entera
        string opcion;//String utilizado para recibir la opcion del usuario, validar si es un numero y si lo es ejecutar la opcion
        do{
            limpiar();
            imprimirAutosuma();//llama al metodo imprimir incluido en esta clase

            do{//Pediremos la opcion y comprobaremos si es un numero, si no lo es se volvera a solicitar
                cout << "Opcion: ";
                cin>>opcion;
                if(opcion.length()!=1 ||  (opcion[0] < '0' || opcion[0] > '6' )) cout<<"Introduce un numero correcto por favor."<<endl;//Si tiene mas de un caracter o no es un numero imprime un aviso
            }while(opcion.length()!=1 ||  (opcion[0] < '0' || opcion[0] > '6' ));//Si tiene mas de un caracter o no es numero volvera a solicitar
            cin.get();
            opcionnum=atoi(opcion.c_str());//Convierte a numero entero el numero almacenado en el string y lo copia en opcionnum

            switch(opcionnum){//Segun el valor de "opcionnum" realizara una de las siguientes opciones
            //En cada case hemos puesto corchetes porque Qt incicaba que estaba en "protected scope", al poner corchetes se ha solucionado
            case 1:
            {
                limpiar();
                //Base
                cout<<"Suma de matrices base"<<endl<<endl;
                Matriz base(4);
                base+=Matriz(4);
                cout<<base;
                cin.get();
                cin.get();
                break;
            }
            case 2:
            {
                limpiar();
                //Gruyere
                cout<<"Suma de matrices gruyere"<<endl<<endl;
                MatrizG a(4);
                a+=MatrizG(4);
                cout<<a;
                cin.get();
                cin.get();
                break;
            }
            case 3:
            {
                limpiar();
                //Cuadrada
                cout<<"Suma de matrices cuadradas"<<endl<<endl;
                MatrizC b(4);
                b+=MatrizC(4);
                cout<<b;
                cin.get();
                cin.get();
                break;
            }
            case 4:
            {
                limpiar();
                //Diagonal
                cout<<"Suma de matrices diagonales"<<endl<<endl;
                MatrizD c(4);
                c+=MatrizD(4);
                cout<<c;
                cin.get();
                cin.get();
                break;
            }
            case 5:
            {
                limpiar();
                //Escalar
                cout<<"Suma de matrices escalares"<<endl<<endl;
                MatrizE d(4);
                d+=MatrizE(4);
                cout<<d;
                cin.get();
                cin.get();
                break;
            }


            case 6://Sale del switch
                break;

            default://Salida por pantalla para cualquier valor no contemplado en el switch
                cout << "Error. Opcion incorrecta. Pulse ENTER para continuar" << endl;
                cin.get();
            }


        }while(opcionnum!=6);//Si "opcionnum" es distinto de 5 realiza el "do" pero si es igual a 5 sale
    }
};
class restasMatrices{//Menu para mostrar todos los tipos de restas de matrices al usuario
public:
    void imprimir(){
        cout << "1. Resta" << endl;
        cout << "2. Autoresta" << endl;
        cout << "3. Salir" << endl;
    }
    void ejecutar(){

        int opcionnum;//Declaracion de una variable entera
        string opcion;//String utilizado para recibir la opcion del usuario, validar si es un numero y si lo es ejecutar la opcion
        do{
            limpiar();
            imprimir();//llama al metodo imprimir incluido en esta clase

            do{//Pediremos la opcion y comprobaremos si es un numero, si no lo es se volvera a solicitar
                cout << "Opcion: ";
                cin>>opcion;
                if(opcion.length()!=1 ||  (opcion[0] < '0' || opcion[0] > '3' )) cout<<"Introduce un numero correcto por favor."<<endl;//Si tiene mas de un caracter o no es un numero imprime un aviso
            }while(opcion.length()!=1 ||  (opcion[0] < '0' || opcion[0] > '3' ));//Si tiene mas de un caracter o no es numero volvera a solicitar
            cin.get();
            opcionnum=atoi(opcion.c_str());//Convierte a numero entero el numero almacenado en el string y lo copia en opcionnum

            switch(opcionnum){//Segun el valor de "opcionnum" realizara una de las siguientes opciones
            case 1:
                limpiar();
                resta();
                cout << "Pulse <ENTER> para continuar" << endl;
                cin.get();
                break;
            case 2:
                limpiar();
                autoResta();
                cout << "Pulse <ENTER> para continuar" << endl;
                cin.get();
                break;

            case 3://Sale del switch
                break;

            default://Salida por pantalla para cualquier valor no contemplado en el switch
                cout << "Error. Opcion incorrecta. Pulse ENTER para continuar" << endl;
                cin.get();
            }
        }while(opcionnum!=3);//Si "opcionnum" es distinto de 5 realiza el "do" pero si es igual a 5 sale




    }
    void imprimirResta(){
        cout << "1. Resta de matrices base" << endl;
        cout << "2. Resta de matrices gruyere" << endl;
        cout << "3. Resta de matrices cuadrada" << endl;
        cout << "4. Resta de matrices diagonal" << endl;
        cout << "5. Resta de matrices escalar" << endl;
        cout << "6. Salir" << endl;

    }
    void resta(){

        int opcionnum;//Declaracion de una variable entera
        string opcion;//String utilizado para recibir la opcion del usuario, validar si es un numero y si lo es ejecutar la opcion
        do{
            limpiar();
            imprimirResta();//llama al metodo imprimir incluido en esta clase

            do{//Pediremos la opcion y comprobaremos si es un numero, si no lo es se volvera a solicitar
                cout << "Opcion: ";
                cin>>opcion;
                if(opcion.length()!=1 ||  (opcion[0] < '0' || opcion[0] > '6' )) cout<<"Introduce un numero correcto por favor."<<endl;//Si tiene mas de un caracter o no es un numero imprime un aviso
            }while(opcion.length()!=1 ||  (opcion[0] < '0' || opcion[0] > '6' ));//Si tiene mas de un caracter o no es numero volvera a solicitar
            cin.get();
            opcionnum=atoi(opcion.c_str());//Convierte a numero entero el numero almacenado en el string y lo copia en opcionnum

            switch(opcionnum){//Segun el valor de "opcionnum" realizara una de las siguientes opciones
            case 1:
                limpiar();
                //Base
                cout<<"Resta de matrices base"<<endl<<endl;
                cout<<Matriz(4)-Matriz(4);
                cin.get();
                cin.get();
                break;
            case 2:
                limpiar();
                //Gruyere
                cout<<"Resta de matrices gruyere"<<endl<<endl;
                cout<<MatrizG(4)-MatrizG(4);
                cin.get();
                cin.get();
                break;
            case 3:
                limpiar();
                //Cuadrada
                cout<<"Resta de matrices cuadradas"<<endl<<endl;
                cout<<MatrizC(4)-MatrizC(4);
                cin.get();
                cin.get();
                break;
            case 4:
                limpiar();
                //Diagonal
                cout<<"Resta de matrices diagonales"<<endl<<endl;
                cout<<MatrizD(4)-MatrizD(4);
                cin.get();
                cin.get();
                break;
            case 5:
                limpiar();
                //Escalar
                cout<<"Resta de matrices escalares"<<endl<<endl;
                cout<<MatrizE(4)-MatrizE(4);
                cin.get();
                cin.get();
                break;


            case 6://Sale del switch
                break;

            default://Salida por pantalla para cualquier valor no contemplado en el switch
                cout << "Error. Opcion incorrecta. Pulse ENTER para continuar" << endl;
                cin.get();
            }
        }while(opcionnum!=6);//Si "opcionnum" es distinto de 5 realiza el "do" pero si es igual a 5 sale
    }
    void imprimirAutoresta(){
        cout << "1. Autoresta de matrices base" << endl;
        cout << "2. Autoresta de matrices gruyere" << endl;
        cout << "3. Autoresta de matrices cuadrada" << endl;
        cout << "4. Autoresta de matrices diagonal" << endl;
        cout << "5. Autoresta de matrices escalar" << endl;
        cout << "6. Salir" << endl; }
    void autoResta(){
        int opcionnum;//Declaracion de una variable entera
        string opcion;//String utilizado para recibir la opcion del usuario, validar si es un numero y si lo es ejecutar la opcion
        do{
            limpiar();
            imprimirAutoresta();//llama al metodo imprimir incluido en esta clase

            do{//Pediremos la opcion y comprobaremos si es un numero, si no lo es se volvera a solicitar
                cout << "Opcion: ";
                cin>>opcion;
                if(opcion.length()!=1 ||  (opcion[0] < '0' || opcion[0] > '6' )) cout<<"Introduce un numero correcto por favor."<<endl;//Si tiene mas de un caracter o no es un numero imprime un aviso
            }while(opcion.length()!=1 ||  (opcion[0] < '0' || opcion[0] > '6' ));//Si tiene mas de un caracter o no es numero volvera a solicitar
            cin.get();
            opcionnum=atoi(opcion.c_str());//Convierte a numero entero el numero almacenado en el string y lo copia en opcionnum

            switch(opcionnum){//Segun el valor de "opcionnum" realizara una de las siguientes opciones
            //En cada case hemos puesto corchetes porque Qt incicaba que estaba en "protected scope", al poner corchetes se ha solucionado
            case 1:
            {
                limpiar();
                //Base
                cout<<"Resta de matrices base"<<endl<<endl;
                Matriz base(4);
                base-=Matriz(4);
                cout<<base;
                cin.get();
                cin.get();
                break;
            }
            case 2:
            {
                limpiar();
                //Gruyere
                cout<<"Resta de matrices gruyere"<<endl<<endl;
                MatrizG a(4);
                a-=MatrizG(4);
                cout<<a;
                cin.get();
                cin.get();
                break;
            }
            case 3:
            {
                limpiar();
                //Cuadrada
                cout<<"Resta de matrices cuadradas"<<endl<<endl;
                MatrizC b(4);
                b-=MatrizC(4);
                cout<<b;
                cin.get();
                cin.get();
                break;
            }
            case 4:
            {
                limpiar();
                //Diagonal
                cout<<"Resta de matrices diagonales"<<endl<<endl;
                MatrizD c(4);
                c-=MatrizD(4);
                cout<<c;
                cin.get();
                cin.get();
                break;
            }
            case 5:
            {
                limpiar();
                //Escalar
                cout<<"Resta de matrices escalares"<<endl<<endl;
                MatrizE d(4);
                d-=MatrizE(4);
                cout<<d;
                cin.get();
                cin.get();
                break;
            }


            case 6://Sale del switch
                break;

            default://Salida por pantalla para cualquier valor no contemplado en el switch
                cout << "Error. Opcion incorrecta. Pulse ENTER para continuar" << endl;
                cin.get();
            }


        }while(opcionnum!=6);//Si "opcionnum" es distinto de 5 realiza el "do" pero si es igual a 5 sale
    }
};
class Menu{//Menu principal
private:
    tiposMatrices tipos;
    productosMatricesEnteros productos;
    sumasMatrices sumas;
    restasMatrices restas;
    productosMatrices productosmatrices;
public:  
    void imprimir(){//Imprime por pantalla el menu
        cout << "1. Tipos de matrices" << endl;
        cout << "2. Matriz por entero (Producto y autoproducto)" << endl;
        cout << "3. Matriz por matriz (Producto y autoproducto)" << endl;
        cout << "4. Suma de matrices (Suma y autosuma)" << endl;
        cout << "5. Resta de matrices (Resta y autoresta)" << endl;
        cout << "6. Salir" << endl;
    }
    void ejecutar(){//Ejecuta el sistema del menu, se cargan los datos, se llama a el metodo imprimir para imprimir por pantalla el menu y se ejecutan las opciones, finalmente al salir se guarda todo

        int opcionnum;//Declaracion de una variable entera
        string opcion;//String utilizado para recibir la opcion del usuario, validar si es un numero y si lo es ejecutar la opcion
        do{
            limpiar();
            imprimir();//llama al metodo imprimir incluido en esta clase

            do{//Pediremos la opcion y comprobaremos si es un numero, si no lo es se volvera a solicitar
                cout << "Opcion: ";
                cin>>opcion;
                if(opcion.length()!=1 ||  (opcion[0] < '0' || opcion[0] > '6' )) cout<<"Introduce un numero correcto por favor."<<endl;//Si tiene mas de un caracter o no es un numero imprime un aviso
            }while(opcion.length()!=1 ||  (opcion[0] < '0' || opcion[0] > '6' ));//Si tiene mas de un caracter o no es numero volvera a solicitar
            cin.get();
            opcionnum=atoi(opcion.c_str());//Convierte a numero entero el numero almacenado en el string y lo copia en opcionnum

            switch(opcionnum){//Segun el valor de "opcionnum" realizara una de las siguientes opciones
            case 1:
                limpiar();
                tipos.ejecutar();
                cout << endl<<"Pulse <ENTER> para continuar" << endl;
                cin.get();
                break;
            case 2:
                limpiar();
                productos.ejecutar();
                cout << "Pulse <ENTER> para continuar" << endl;
                cin.get();
                break;
            case 3://Sale del switch
                limpiar();
                productosmatrices.ejecutar();
                cout << "Pulse <ENTER> para continuar" << endl;
                cin.get();
                break;

            case 4:
                limpiar();
                sumas.ejecutar();
                cout << endl<<"Pulse <ENTER> para continuar" << endl;
                cin.get();
                break;
            case 5:
                limpiar();
                restas.ejecutar();
                cout << "Pulse <ENTER> para continuar" << endl;
                cin.get();
                break;

            case 6://Sale del switch
                break;

            default://Salida por pantalla para cualquier valor no contemplado en el switch
                cout << "Error. Opcion incorrecta. Pulse ENTER para continuar" << endl;
                cin.get();
            }
        }while(opcionnum!=6);//Si "opcionnum" es distinto de 5 realiza el "do" pero si es igual a 5 sale

    }
};
int main(){
    Menu a;
    a.ejecutar();
    return 0;
}



