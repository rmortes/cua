#include <iostream>
#include <cstdlib>
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

template <class T>//Plantilla de datos tipo T
class MatrizT{//Matriz generica de datos tipo T
protected:
    T **M;//Puntero bidimensional de tipo T
    int NF, NC;//Numero de filas, Numero de columnas
public:
    MatrizT(){//Contructor por defecto
        M = NULL;
        NF = 0;
        NC = 0;
    }
    MatrizT(int nf, int nc){//Contructor por parametros. Dos enteros
        if(nf <= 0 || nc <= 0){//Si alguno de los enteros es 0 o menos la matriz será nula
            M = NULL;
            NF = 0;
            NC = 0;
        }
        else{//Sino asignamos los enteros al numero de filas y numero de columnas y rellenamos la matriz
            NF = nf;
            NC = nc;
            M = new T * [NF];//Reservamos memoria para un array de direcciones
            for(int i = 0; i <NF; i++){//Recorremos el array
                M[i] = new T [NC];//Para cada posicion reservamos una columna
            }
            for(int i = 0; i < NF; i++)//Recorremos la matriz para asignar numeros aleatorios.
                for(int j = 0; j < NC; j++)
                    M[i][j] = rand() % 100;
        }
    }
    MatrizT(int n){//Contructor por parametro. Un entero
        if(n <= 0){//Si alguna dimension esta vacia o es negativa se deja la matriz vacia
            M = NULL;
            NF = 0;
            NC = 0;
        }
        else{//Si no contruimos la matriz con los datos recibidos
            NF = n;
            NC = n;
            M = new T * [NF];//Reservamos memoria para un array de direcciones
            for(int i = 0; i <NF; i++){//Recorremos el array
                M[i] = new T [NC];//Para cada posicion reservamos una columna
            }
            for(int i = 0; i < NF; i++){//Recorremos la matriz para asignar numero enteros aleatorios
                for(int j = 0; j < NC; j++){
                    M[i][j] = rand() % 100;//Asignamos los numero a las posiciones de la matriz
                }
            }
        }
    }
    MatrizT(const MatrizT<T> &de){//Contructor de copia
        if(de.M == NULL){//Si esta vacia, copia vacia
            M = NULL;
            NF = NC = 0;
        }
        else{//Si no copia la matriz recibida en esta
            NF = de.NF;//Asigna el numero de filas de la matriz recibida a esta
            NC = de.NC;//Asigna el numero de columnas de la matriz recibida a esta
            M = new T * [NF];//Reservamos tanta memoria como la usada en la matriz recibida
            for(int i = 0; i <NF; i++){
                M[i] = new T [NC];//Creamos la cantidad de columnas  que tiene la matriz recibida
            }

            for(int i = 0; i < NF; i++){
                for(int j = 0; j < NC; j++)
                    M[i][j] = de.M[i][j];//Copiamos el contenido de la matriz recibida en esta posicion por posicion
            }
        }
    }
    ~MatrizT(){//Destructor
        if(M != NULL){//Si no esta vacia
            for(int i = 0; i < NF; i++){//Recorremos el array de direcciones
                delete [] M[i];//Borramos el vector asociado al array
            }
            delete [] M;//Borramos el array de direcciones
            M = NULL;
            NF = NC  = 0;
        }
    }

    MatrizT<T> &operator=(const MatrizT<T> &de){//Operador asignacion de matriz, volcamos la matriz recibida
        if(this != &de){//Comparamos las direcciones de las dos matrices, si no son iguales, son matrices distintas y se ejecuta lo siguiente, sino devolvera la misma ya que ya son iguales
            this->~MatrizT(); //Destruimos la matriz de la izquierda para contruirla con la recibida
            if(de.M != NULL){//Si la matriz recibida no esta vacia ejecuta esto
                NF = de.NF;
                NC = de.NC;
                M = new T *[NF];//Reservamos tanta memoria como la usada en la matriz recibida
                for(int i = 0; i < NF; i++)
                    M[i] = new T [NC];//Creamos la cantidad de columnas
                for(int i = 0; i < NF; i++)
                    for(int j = 0; j < NC; j++)
                        M[i][j] = de.M[i][j];//Copiamos el contenido de la matriz recibida en esta posicion por posicion
            }
        }
        return *this;//Devolvemos este objeto que es igual al recibido
    }
    MatrizT<T> operator+(const MatrizT<T> &de) const{//Suma de matrices
        MatrizT<T> aux;//Creamos una matriz auxiliar (al inicializar la matriz de aux sera nula 0x0)

        if(NF == de.NF && NC == de.NC && NF != 0){//Comprueba que tanto filas como las columnas sean del mismo tamaño y no sea nula
            MatrizT<T> resultado(NF, NC);//Crea una matriz del mismo tamaño que esta llamando al constructor
            for(int i = 0; i < NF; i++)//Recorremos las dos matrices, esta y la recibida
                for(int j = 0; j < NC; j++)
                    resultado.M[i][j] = M[i][j] + de.M[i][j];//sumamos posicion por posicion y lo asignamos a la matriz de Resul
            aux = resultado;//Volcamos matriz resul a matriz aux
        }

        return aux;//Si son compatibles devolvera el resultado de la suma, sino devolvera matriz nula
    }
    MatrizT<T> operator-(const MatrizT<T> &de) const{//Resta de matrices
        MatrizT<T> aux;//Creamos una matriz auxiliar (al inicializar la matriz de aux sera nula 0x0)

        if(NF == de.NF && NC == de.NC && NF != 0){//Comprueba que tanto filas como las columnas sean del mismo tamaño y no sea nula
            MatrizT<T> resultado(NF, NC);//Crea una matriz del mismo tamaño que esta llamando al constructor por parametos
            for(int i = 0; i < NF; i++)//Recorremos las dos matrices, esta y la recibida
                for(int j = 0; j < NC; j++)
                    resultado.M[i][j] = M[i][j] - de.M[i][j];//restamos posicion por posicion y lo asignamos a la matriz de Resul
            aux = resultado;//Volcamos matriz resul a matriz aux
        }

        return aux;//Si son compatibles devolvera el resultado de la resta, sino devolvera matriz nula
    }
    MatrizT<T> operator*(const MatrizT<T> &de) const{//Producto de matrices
        MatrizT<T> aux;//Creamos una matriz auxiliar (al inicializar la matriz de aux sera nula 0x0)

        if(NC == de.NF && NC != 0){//Comprobamos que las dimensiones sean compatibles para realizar el producto, numero de columnas de esta igual al numero de filas de la recibida
            MatrizT<T> resultado(NF, de.NC);//Crea una nueva matriz con el numero de filas de esta y el numero de columnas de la recibida llamando al contructor por parametros
            for(int i = 0; i < NF; i++){//Recorremos la matriz posicion por posicion
                for(int j = 0; j < de.NC; j++){
                    resultado.M[i][j] = 0;//Ponemos a cero la posicion en la que se va a volcar el producto de los vectores fila (m) y columna (de.m)
                    for(int k = 0; k < NC; k++){
                        resultado.M[i][j] += M[i][k]*de.M[k][j];//Vamos sumando los productos de los vectores fila (m) y columna (de.m). resultado.m = resultado.m + (m*de.m)

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
            MatrizT<T> resultado(NC, de.NF);//Crea una nueva matriz con el numero de filas de esta y el numero de columnas de la recibida llamando al contructor por parametros
            for(int i = 0; i < NC; i++){//Recorremos la matriz posicion por posicion
                for(int j = 0; j < de.NF; j++){
                    resultado.M[i][j] = 0;//Ponemos a cero la posicion en la que se va a volcar el producto de los vectores fila (m) y columna (de.m)
                    for(int k = 0; k < NF; k++){
                        resultado.M[i][j] += M[i][k]*de.M[k][j];//Vamos sumando los productos de los vectores fila (m) y columna (de.m). resultado.m = resultado.m + (m*de.m)

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
        return aux;//Si son compatibles devolvera el resultado de la resta, sino devolvera matriz nula
    }
    MatrizT<T> operator*(int n) const{//Matriz T por entero
        // hago una copia de this.
        MatrizT<T> resultado(*this);//Copia de esta
        for(int i = 0; i < resultado.NF; i++)//Recorremos la matriz copiada (Resul)
            for(int j = 0; j < resultado.NC; j++)
                resultado.M[i][j] *= n;// multiplico cada elemento de la copia por el entero y lo volcamos a la matriz de resul.

        return resultado;//Devolvemos el resultado del producto

    }

    void operator+=(const MatrizT<T> &de){//Sobrecarga de operador autosuma
        *this = *this + de;//Llama al operador suma y despues al de asignacion
    }
    void operator-=(const MatrizT<T> &de){//Sobrecarga de operador autoresta
        *this = *this - de;//Llama al operador resta y despues al de asignacion
    }
    void operator*=(const MatrizT<T> &de){//Sobrecarga del operdor autoproducto
        *this = *this *de;//Llama al operador producto y luego al asignacion
    }
    void operator*=(int valor){//Sobrecarga del operador autoproducto
        *this = *this*valor;// llama al operador producto de arriba
    }

    int getNF() { return NF; }//Devuelve el numero de filas
    int getNC() { return NC; }//Devuelve el numero de columnas

    friend MatrizT<T> operator*(int n, const MatrizT<T> &de){//Sobrecarga del operador producto por entero
        return de*n; // llama al operador producto de arriba
    }
    friend ostream &operator<<(ostream &os, const MatrizT<T> &de){//Sobrecarga del operador de flujo de salida
        int i, j;
        if(de.M == NULL)//Si la matriz es nula imprime esto
            os << "Matriz nula" << endl;
        else{//Sino imprime la matriz
            for(i = 0; i < de.NF; i++){//Recorremos la matriz
                for(j = 0; j < de.NC; j++){
                    os <<" [" <<  de.M[i][j] << "]";//imprime una posicion de la matriz
                }
                os << endl;//Cuando llega al final de una fila introduce un salto de linea y continua con la siguiente fila
            }
        }
        return os;//Devuelve el medio
    }
};

template <class T>//Plantilla de datos tipo T
class MatrizGT : public MatrizT<T>{
public:
    /* MatrizGT. Representa una matriz gruyere, esto es, una matriz en la que los ceros y
        * los elementos distintos de cero se alternan (si fila+columna es par la celda se
        * rellena con un 0 y con un número aleatorio entre 0 y 99 en otro caso). Se formará
        * por herencia directa de MatrizT.
        */
    MatrizGT(){}//Constructor por defecto
    MatrizGT(const MatrizT<T> &de):MatrizT<T>(de){//Constructor por parametros que recibe una matriz y envia esta al constructor por defecto de la clase base
    }
    MatrizGT(int nf, int nc):MatrizT<T>(nf, nc){//Constructor por parametros que recibe dos enteros y  los  al constructor por parametros de la clase base
        for(int i = 0; i < this->NF; i++)//Recorremos la matriz
            for(int j = 0; j < this->NC; j++){
                if((i + j) % 2 == 0){//Si el resto de la division de (i+j)/2 querra decir que la suma es par y se ejecutara lo siguiente
                    this->M[i][j] = 0;//Pondra a cero las posiciones donde i+j sea par
                }else{//sino introducira un numero aleatorio
                    this->M[i][j] = rand() % 100;//Numero aleatorio entre 0 y 99
                }
            }
    }
    MatrizGT(int n){//Constructor por parametros que recibe una matriz y envia esta al constructor por parametros de la clase base
        *this = MatrizGT(n,n);
    }

};
template <class T>//Plantilla de datos tipo T
class MatrizCT : public MatrizT<T>{
    /*MatrizCT. Representa una matriz cuadrada, esto es, una matriz cuyo número de filas y
         * columnas coincide. El constructor por parámetros de esta clase recibirá un solo
         * entero que representará tanto el número de filas como el de columnas. Al igual que
         * en Matriz, dicho constructor será el encargado de rellenar los elementos de la matriz
         * con números aleatorios entre 0 y 99. Se formará por herencia directa de Matriz.
         */
public:
    MatrizCT(){//Constructor por defecto
    }
    MatrizCT(const MatrizT<T> &de): MatrizT<T>(de.getNF(), de.getNC()){//Constructor por parametros. Recibe matriz y envia 2 enteros (NF y NC) al contructor por parametros de la clase base
    }
    MatrizCT(int n): MatrizT<T>(n, n){//Contructor por parametro. Recibe un entero y llama al contructor por parametro de la clase base para crear una matriz de N*N (Cuadrada)
    }
    MatrizCT(int nf, int nc){//Si enviamos dos enteros a matriz cuadrada y no son iguales, la matriz es nula ya que no es cuadrada
        if(nf==nc){//Si los dos enteros son iguales, la matriz sera cuadrada
            *this= MatrizCT(nf);
        }
    }
    MatrizCT(const MatrizCT<T> &de): MatrizT<T>(de){//Constructor de copia. Recibe una matriz y llama al contructor de copia de la clase base
    }
};
template <class T>//Plantilla de datos tipo T
class MatrizDT : public MatrizCT<T>{
public:
    /*MatrizDT. Representa una matriz diagonal y como tal, debe ser cuadrada, por lo que se
         * formará como herencia de MatrizCT. La matriz diagonal se caracteriza por tener todos
         * sus elementos a cero excepto los de la diagonal principal. Al igual que en MatrizCT,
         * el constructor de MatrizDT recibirá un solo número entero que simbolizará tanto filas
         * como columnas y, en este caso, rellenará las celdas de la diagonal de números aleatorios
         * entre 0 y 99 y el resto a cero.
         * */
    MatrizDT(const MatrizT<T> &de):MatrizCT<T>(de){//Constructor de copia. Recibe una matriz y la envia a la clase base
    }
    MatrizDT(int n):MatrizCT<T>(n){//Recibe un entero, lo envia a la clase base (MatrizC), esta lo envia a su clase base (Matriz) para crear una matriz cuadrada y ahora trabajamos con ella
        for(int i = 0; i < this->NF; i++)//Recorremos la matriz
            for(int j = 0; j < this->NC; j++)
                if(i == j)//Cuando las posiciones sean iguales ( [0,0] ó [1,1] o [2,2]) introducira un numero aleatorio
                    this->M[i][j] = rand() %100;
                else//Si no son iguales lo pone a 0
                    this->M[i][j] = 0;
    }
    MatrizDT(int nc, int nf){//Si enviamos dos enteros a matriz diagonal y no son iguales, la matriz es nula ya que no es cuadrada
        if(nc==nf){//Si los dos enteros son iguales, la matriz sera cuadrada
            *this= MatrizDT(nc);
        }
    }
    MatrizDT(const MatrizDT<T> &de):MatrizCT<T>(de){//Constructor de copia. Recibe una matriz y llama al contructor de copia de la clase base
    }
    MatrizDT(){}//Constructor por defecto
};
template <class T>//Plantilla de datos tipo T
class MatrizET : public MatrizDT<T>{
public:
    /*MatrizET. Representa una matriz escalar, esto es, una matriz cuadrada y diagonal donde
         * además todos los elementos de la diagonal son iguales. Esta clase se formará por
         * herencia a partir de MatrizDT y al igual que ésta el constructor por parámetros recibirá
         * un solo número entero que simbolizará tanto filas como columnas. En este caso rellenará
         * todas las celdas de la diagonal con un mismo número aleatorio entre 0 y 99 y el resto a cero.
         */
    MatrizET(){//Constructor por defecto
    }
    MatrizET(const MatrizET<T> &de):MatrizDT<T>(de) {//Constructor de copia. Recibe una matriz y llama al contructor de copia de la clase base

    }
    MatrizET(int n):MatrizDT<T>(n){//Contructor con un entero. Envia el entero a la clase base (MatrizDT) que esta a su vez la envia a su clase base (MatrizCT) y esta a la clase MatrizT.
        //Al terminar tendremos una matriz cuadrada y diagonal
        int aux = rand() % 100;//Creamos un entero con un numero aleatorio
        for(int i = 0; i < n; i++)//Como ya tenemos todas la posiciones no-diagonales a 0 (MatrizD), solo nos queda asignar el mismo numero a toda la diagonal
            this->M[i][i] = aux;
    }
    MatrizET(int nc, int nf){//Si enviamos dos enteros a matriz diagonal y no son iguales, la matriz es nula ya que no es cuadrada
        if(nc==nf){//Si los dos enteros son iguales, la matriz sera cuadrada
            *this = MatrizET(nc);
        }
    }
};
class Fraccion{//Objeto de tipo fraccion, contiene 2 enteros que representan el numerador y denominador de un cociente
private:
    int nume, den;
public:
    int MaximoDivisor(int a, int b) const{//Algorritmo de euclides para calcular el MCD (http://c.conclase.net/curso/?cap=024p  en el apartado 24.2 esta explicado)
        if(a<0 || b<0){//Si alguno de los numeros es negativo, lo pasamos a positivo
            if(a<0)a*=-1;//Si <a> es negativo lo hacemos positivo
            if(b<0)b*=-1;//Si <b> en negativo lo hacemos positivo
        }
        if(a < b){
            return MaximoDivisor(b,a);//Si a es menor que b, cambiamos de posicion las variables
        }else if(b == 0){
            //Si b es igual a 0, hemos llegado a la ultima iteracion donde el resto de la divison entera de a/b de la iteracion anterior ha dado 0
            //O en el caso de esta clase, la fraccion recibida es nula (ya que b representa el denominador en la primera iteracion)
            //Y devolvemos a
            return a;
        }else{
            return MaximoDivisor(b, a % b);
            //Si no se cumple ninguna de las condiciones anteriores, quiere decir que [a==b]y[b!=0] ó [a>b]
            //se envia el dato b en la primera posicion y en la segunda posicion se envia el resto de la division entera de a/b
        }
    }

    Fraccion(){//Contructor por defecto
        nume = 0;
        den = 1;//Ponemos uno para que la fraccion resultante no sea nula

    }
    Fraccion(int n, int d){//Contructor por parametros. Recibe dos enteros
        nume = n;
        if(d==0)d++;//Sumamos uno para que si el denominador es 0 la fraccion resultante no sea nula
        den = d;
    }
    Fraccion(int v){//Contructor con un entero. Descomponemos el entero para introducir las decenas en el numerador y las unidades en el denominador
        nume = v/10;//Al dividir el entero v (que en nuestro programa esta entre 0 y 99) entre 10, obtenemos las decenas
        den = v%10 +1;//Con el resto de la division entera del entero v obtenemo las unidades

    }
    Fraccion &operator=(const Fraccion &de){//Operacion asignacion con una fraccion.
        nume = de.nume;//Asignamos el numerador de la fraccion recibida a esta
        den = de.den;//Asignamos el denominador de la fraccion recibida a esta
        return *this;
    }
    Fraccion &operator=(int v){//Operacion asignacion con un entero. Descomponemos el entero para introducir las decenas en el numerador y las unidades en el denominador
        nume = v/10;//Al dividir el entero v (que en nuestro programa esta entre 0 y 99) entre 10, obtenemos las decenas
        den = v%10 +1;//Con el resto de la division entera del entero v obtenemo las unidades
        return *this;
    }
    Fraccion operator+(const Fraccion &de){//Suma de fracciones
        Fraccion resultado;//Fraccion donde se almacenara el resultado
        int MCD;//Entero donde se almacenara el mcd

        resultado.nume = nume*de.den + de.nume*den;//Para sumar, multiplicamos en cruz y sumamos, el resultado sera el numerador
        resultado.den = den * de.den;//Para sumar, los denominadores se multiplican

        // Simplificamos el resultado de la suma
        MCD = MaximoDivisor(resultado.nume, resultado.den);//Calculamos el MCD llamando al metodo mcd
        //Dividimos numerador y denominador el el mcd para reducir la fraccion al maximo
        resultado.nume = resultado.nume /MCD;
        resultado.den = resultado.den / MCD;
        return resultado;//Devolvemos el resultado de la suma
    }
    Fraccion operator-(const Fraccion &de){//Resta de fracciones
        Fraccion resultado;//Fraccion donde se almacenara el resultado
        int MCD;//Entero donde se almacenara el mcd

        resultado.nume = nume*de.den - de.nume*den;//Para restar, multiplicamos en cruz y restamos, el resultado sera el numerador
        resultado.den = den * de.den;//Para restar, los denominadores se multiplican

        // Simplificamos el resultado de la suma
        MCD = MaximoDivisor(resultado.nume, resultado.den);//Calculamos el MCD llamando al metodo mcd
        //Dividimos numerador y denominador el el mcd para reducir la fraccion al maximo
        resultado.nume = resultado.nume /MCD;
        resultado.den = resultado.den / MCD;

        return resultado;//Devolvemos el resultado de la resta
    }
    Fraccion operator*(const Fraccion &de) const{//Operador producto que recibe un objeto fraccion. Fraccion por fraccion
        Fraccion resultado;//Fraccion donde se almacenara el resultado
        int MCD;//Entero donde se almacenara el MCD

        resultado.nume = nume * de.nume;//Multiplicamos numeradores
        resultado.den = den * de.den;//Multiplicamos denominadores

        // Simplificamos el resultado del producto
        MCD = MaximoDivisor(resultado.nume, resultado.den);//Calculamos el MCD llamando al metodo mcd
        //Dividimos numerador y denominador el el mcd para reducir la fraccion al maximo
        resultado.nume = resultado.nume /MCD;
        resultado.den = resultado.den / MCD;
        return resultado;//Devolvemos el resultado del producto
    }
    Fraccion operator*(int n) const{//Operador producto. Fraccion por entero
        Fraccion resultado;//Fraccion donde se almacenara el resultado
        int MCD;//Entero donde se almacenara el MCD

        resultado.nume = nume * n;//Multiplicamos en numerador por el entero
        resultado.den=den;//Asignamos el valor del denominado de esta a la del resultado del producto
        // Simplificamos el resultado del producto
        MCD = MaximoDivisor(resultado.nume, resultado.den);//Calculamos el MCD llamando al metodo mcd
        //Dividimos numerador y denominador el el mcd para reducir la fraccion al maximo
        resultado.nume = resultado.nume /MCD;
        resultado.den = resultado.den / MCD;

        return resultado;//Devolvemos el resultado del producto
    }

    void operator+=(const Fraccion &de){//Sobrecarga del operador autosuma de fracciones
        *this = *this + de;
    }
    void operator-=(const Fraccion &de){//Sobrecarga del operador autoresta
        *this = *this - de;
    }
    void operator*=(const Fraccion &de){//Sobrecarga del operador autoproducto de fracciones
        *this = *this * de; // Llamamos al metodo anterior.
    }
    void operator*=(int n){//Sobrecarga del autoproducto de fraccion por entero
        *this = *this * n;
    }

    friend ostream &operator<<(ostream &os, const Fraccion &de){//Sobrecarga del operador de flujo de salida para imprimir las fracciones en formato a/b
        if(de.den==1 && de.nume==0){//Si el numerador es 0 y el denominador es 1, la fraccion sabemos que es nula ya que al construir la fraccion sumamos una unidad al denominador, si este es 1 cuando el numerador es 0, es que era 0
            os << 0 <<"/" << 0;//Imprimimos 0, una barra y 0
        }else{//Si no es nula imprimimos la fraccion tal como esta
            os << de.nume <<"/" << de.den;//Imprimimos el numerador, una barra y el denominador
        }
        return os;//Devolvemos el medio
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
        cout << "6. Atras" << endl;
        cout << "7. Salir de la aplicacion" << endl;
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
                if(opcion.length()!=1 ||  (opcion[0] < '0' || opcion[0] > '7' )) cout<<"Introduce un numero correcto por favor."<<endl;//Si tiene mas de un caracter o no es un numero imprime un aviso
            }while(opcion.length()!=1 ||  (opcion[0] < '0' || opcion[0] > '7' ));//Si tiene mas de un caracter o no es numero volvera a solicitar
            cin.get();
            opcionnum=atoi(opcion.c_str());//Convierte a numero entero el numero almacenado en el string y lo copia en opcionnum

            switch(opcionnum){//Segun el valor de "opcionnum" realizara una de las siguientes opciones
            case 1:
                limpiar();
                ///Matriz base
                cout<<"Matriz 3x3"<<endl<<endl;
                cout<<MatrizT<Fraccion>(3);
                cin.get();
                cout<<"Matriz 4x4"<<endl<<endl;
                cout<<MatrizT<Fraccion>(4);
                cin.get();

                cout<<"Matriz personalizada"<<endl<<endl;
                cout<<"Numero de filas"<<endl;
                cin>>NF;
                cout<<"Numero de columnas"<<endl;
                cin>>NC;
                cout<<endl<<MatrizT<Fraccion> (NF,NC);
                cin.get();
                cin.get();
                break;
            case 2:
                limpiar();
                ///Matriz gruyere
                cout<<"Matriz gruyere 3x3"<<endl<<endl;
                cout<<MatrizGT<Fraccion> (3);
                cin.get();
                cout<<"Matriz gruyere 4x4"<<endl<<endl;
                cout<<MatrizGT<Fraccion> (4);
                cin.get();

                cout<<"Matriz gruyere personalizada"<<endl<<endl;
                cout<<"Numero de filas"<<endl;
                cin>>NF;
                cout<<"Numero de columnas"<<endl;
                cin>>NC;
                cout<<endl<<MatrizGT<Fraccion> (NF,NC);
                cin.get();
                cin.get();
                break;
            case 3:
                limpiar();
                ///Matriz cuadrada
                cout<<"Matriz cuadrada 3x3"<<endl<<endl;
                cout<<MatrizCT<Fraccion> (3);
                cin.get();
                cout<<"Matriz cuadrada 4x4"<<endl<<endl;
                cout<<MatrizCT<Fraccion> (4);
                cin.get();

                cout<<"Matriz cuadrada personalizada"<<endl<<endl;
                cout<<"Numero de filas"<<endl;
                cin>>NF;
                cout<<"Numero de columnas"<<endl;
                cin>>NC;
                cout<<endl<<MatrizCT<Fraccion> (NF,NC);
                cin.get();
                cin.get();
                break;
            case 4:
                limpiar();
                ///Matriz diagonal
                cout<<"Matriz diagonal 3x3"<<endl<<endl;
                cout<<MatrizDT<Fraccion> (3);
                cin.get();
                cout<<"Matriz diagonal 4x4"<<endl<<endl;
                cout<<MatrizDT<Fraccion> (4);
                cin.get();

                cout<<"Matriz diagonal personalizada"<<endl<<endl;
                cout<<"Numero de filas"<<endl;
                cin>>NF;
                cout<<"Numero de columnas"<<endl;
                cin>>NC;
                cout<<endl<<MatrizDT<Fraccion> (NF,NC);
                cin.get();
                cin.get();
                break;

            case 5:
                limpiar();
                ///Matriz escalar
                cout<<"Matriz escalar 3x3"<<endl<<endl;
                cout<<MatrizET<Fraccion> (3);
                cin.get();
                cout<<"Matriz escalar 4x4"<<endl<<endl;
                cout<<MatrizET<Fraccion> (4);
                cin.get();

                cout<<"Matriz escalar personalizada"<<endl<<endl;
                cout<<"Numero de filas"<<endl;
                cin>>NF;
                cout<<"Numero de columnas"<<endl;
                cin>>NC;
                cout<<endl<<MatrizET<Fraccion> (NF,NC);
                cin.get();
                cin.get();
                break;

            case 6://Sale del switch
                break;

            case 7://Sale del aplicacion
                exit(0);

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
        cout << "3. Atras" << endl;
        cout << "4. Salir de la aplicacion" << endl;
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
                if(opcion.length()!=1 ||  (opcion[0] < '0' || opcion[0] > '4' )) cout<<"Introduce un numero correcto por favor."<<endl;//Si tiene mas de un caracter o no es un numero imprime un aviso
            }while(opcion.length()!=1 ||  (opcion[0] < '0' || opcion[0] > '4' ));//Si tiene mas de un caracter o no es numero volvera a solicitar
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

            case 4://Sale del switch
                exit(0);

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
        cout << "6. Atras" << endl;
        cout << "7. Salir de la aplicacion" << endl;

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
                if(opcion.length()!=1 ||  (opcion[0] < '0' || opcion[0] > '7' )) cout<<"Introduce un numero correcto por favor."<<endl;//Si tiene mas de un caracter o no es un numero imprime un aviso
            }while(opcion.length()!=1 ||  (opcion[0] < '0' || opcion[0] > '7' ));//Si tiene mas de un caracter o no es numero volvera a solicitar
            cin.get();
            opcionnum=atoi(opcion.c_str());//Convierte a numero entero el numero almacenado en el string y lo copia en opcionnum

            switch(opcionnum){//Segun el valor de "opcionnum" realizara una de las siguientes opciones
            case 1:
                limpiar();
                //Base por entero
                cout<<"Matriz base por entero"<<endl<<endl;
                cout<<MatrizT<Fraccion>(4,4)*3;
                cin.get();
                cin.get();
                break;
            case 2:
                limpiar();
                //Gruyere por entero
                cout<<"Gruyere por entero"<<endl<<endl;
                cout<<MatrizGT<Fraccion>(4)*3;
                cin.get();
                cin.get();
                break;
            case 3:
                limpiar();
                //Cuadrada por entero
                cout<<"Cuadrada por entero"<<endl<<endl;
                cout<<MatrizCT<Fraccion>(4)*3;
                cin.get();
                cin.get();
                break;
            case 4:
                limpiar();
                //Diagonal por entero
                cout<<"Diagonal por entero"<<endl<<endl;
                cout<<MatrizDT<Fraccion>(4)*3;
                cin.get();
                cin.get();
                break;
            case 5:
                limpiar();
                //Escalar por entero
                cout<<"Escalar por entero"<<endl<<endl;
                cout<<MatrizET<Fraccion>(4)*3;
                cin.get();
                cin.get();
                break;


            case 6://Sale del switch
                break;

            case 7://Sale del switch
                exit(0);

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
        cout << "6. Atras" << endl;
        cout << "7. Salir de la aplicacion" << endl;
    }
    void autoProducto(){
        int opcionnum;//Declaracion de una variable entera
        string opcion;//String utilizado para recibir la opcion del usuario, validar si es un numero y si lo es ejecutar la opcion
        do{
            limpiar();
            imprimirAutoproducto();//llama al metodo imprimir incluido en esta clase

            do{//Pediremos la opcion y comprobaremos si es un numero, si no lo es se volvera a solicitar
                cout << "Opcion: ";
                cin>>opcion;
                if(opcion.length()!=1 ||  (opcion[0] < '0' || opcion[0] > '7' )) cout<<"Introduce un numero correcto por favor."<<endl;//Si tiene mas de un caracter o no es un numero imprime un aviso
            }while(opcion.length()!=1 ||  (opcion[0] < '0' || opcion[0] > '7' ));//Si tiene mas de un caracter o no es numero volvera a solicitar
            cin.get();
            opcionnum=atoi(opcion.c_str());//Convierte a numero entero el numero almacenado en el string y lo copia en opcionnum

            switch(opcionnum){//Segun el valor de "opcionnum" realizara una de las siguientes opciones
            //En cada case hemos puesto corchetes porque Qt incicaba que estaba en "protected scope", al poner corchetes se ha solucionado
            case 1:
            {
                limpiar();
                //Base por entero
                cout<<"Base por entero"<<endl<<endl;
                MatrizT<Fraccion> base(4);
                base*=3;
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
                MatrizGT<Fraccion> a(4);
                a*=3;
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
                MatrizCT<Fraccion> b(4);
                b*=3;
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
                MatrizDT<Fraccion> c(4);
                c*=3;
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
                MatrizET<Fraccion> d(4);
                d*=3;
                cout<<d;
                cin.get();
                cin.get();
                break;
            }


            case 6://Sale del switch
                break;

            case 7://Sale del switch
                exit(0);

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
        cout << "3. Atras" << endl;
        cout << "4. Salir de la aplicacion" << endl;
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
                if(opcion.length()!=1 ||  (opcion[0] < '0' || opcion[0] > '4' )) cout<<"Introduce un numero correcto por favor."<<endl;//Si tiene mas de un caracter o no es un numero imprime un aviso
            }while(opcion.length()!=1 ||  (opcion[0] < '0' || opcion[0] > '4' ));//Si tiene mas de un caracter o no es numero volvera a solicitar
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

            case 4://Sale del switch
                exit(0);

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
        cout << "6. Atras" << endl;
        cout << "7. Salir de la aplicacion" << endl;

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
                if(opcion.length()!=1 ||  (opcion[0] < '0' || opcion[0] > '7' )) cout<<"Introduce un numero correcto por favor."<<endl;//Si tiene mas de un caracter o no es un numero imprime un aviso
            }while(opcion.length()!=1 ||  (opcion[0] < '0' || opcion[0] > '7' ));//Si tiene mas de un caracter o no es numero volvera a solicitar
            cin.get();
            opcionnum=atoi(opcion.c_str());//Convierte a numero entero el numero almacenado en el string y lo copia en opcionnum

            switch(opcionnum){//Segun el valor de "opcionnum" realizara una de las siguientes opciones
            case 1:
                limpiar();
                //Base
                cout<<"Matriz base 2x3 por matriz base 3x2"<<endl<<endl;
                cout<<MatrizT<Fraccion>(2,3)*MatrizT<Fraccion>(3,2)<<endl;
                cout<<"Matriz base 3x2 por matriz base 2x3"<<endl<<endl;
                cout<<MatrizT<Fraccion>(3,2)*MatrizT<Fraccion>(2,3);
                cin.get();
                cin.get();
                break;
            case 2:
                limpiar();
                //Gruyere
                cout<<"Matriz gruyere 2x3 por matriz gruyere 3x2"<<endl<<endl;
                cout<<MatrizGT<Fraccion>(2,3)*MatrizGT<Fraccion>(3,2)<<endl;
                cout<<"Matriz gruyere 3x2 por matriz gruyere 2x3"<<endl<<endl;
                cout<<MatrizGT<Fraccion>(3,2)*MatrizGT<Fraccion>(2,3);
                cin.get();
                cin.get();
                break;
            case 3:
                limpiar();
                //Cuadrada
                cout<<"Matriz cuadrada 3x3 por matriz cuadrada 4x4"<<endl<<endl;
                cout<<MatrizCT<Fraccion>(3,3)*MatrizCT<Fraccion>(4,4)<<endl;
                cout<<"Matriz cuadrada 3x2 por matriz cuadrada 2x3"<<endl<<endl;
                cout<<MatrizCT<Fraccion>(3,2)*MatrizCT<Fraccion>(2,3)<<endl;
                cout<<"Matriz cuadrada 3x3 por matriz cuadrada 3x3"<<endl<<endl;
                cout<<MatrizCT<Fraccion>(3,3)*MatrizCT<Fraccion>(3,3);
                cin.get();
                cin.get();
                break;
            case 4:
                limpiar();
                //Diagonal
                cout<<"Matriz diagonal 3x3 por matriz diagonal 4x4"<<endl<<endl;
                cout<<MatrizDT<Fraccion>(3,3)*MatrizDT<Fraccion>(4,4)<<endl;
                cout<<"Matriz diagonal 3x2 por matriz diagonal 2x3"<<endl<<endl;
                cout<<MatrizDT<Fraccion>(3,2)*MatrizDT<Fraccion>(2,3)<<endl;
                cout<<"Matriz diagonal 3x3 por matriz diagonal 3x3"<<endl<<endl;
                cout<<MatrizDT<Fraccion>(3,3)*MatrizDT<Fraccion>(3,3);
                cin.get();
                cin.get();
                break;
            case 5:
                limpiar();
                //Escalar
                cout<<"Matriz escalar 3x3 por matriz escalar 4x4"<<endl<<endl;
                cout<<MatrizET<Fraccion>(3,3)*MatrizET<Fraccion>(4,4)<<endl;
                cout<<"Matriz escalar 3x2 por matriz escalar 2x3"<<endl<<endl;
                cout<<MatrizET<Fraccion>(3,2)*MatrizET<Fraccion>(2,3)<<endl;
                cout<<"Matriz escalar 3x3 por matriz escalar 3x3"<<endl<<endl;
                cout<<MatrizET<Fraccion>(3,3)*MatrizET<Fraccion>(3,3);
                cin.get();
                cin.get();
                break;


            case 6://Sale del switch
                break;

            case 7://Sale del switch
                exit(0);

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
        cout << "6. Atras" << endl;
        cout << "7. Salir de la aplicacion" << endl;
    }
    void autoProducto(){
        int opcionnum;//Declaracion de una variable entera
        string opcion;//String utilizado para recibir la opcion del usuario, validar si es un numero y si lo es ejecutar la opcion
        do{
            limpiar();
            imprimirAutoproducto();//llama al metodo imprimir incluido en esta clase

            do{//Pediremos la opcion y comprobaremos si es un numero, si no lo es se volvera a solicitar
                cout << "Opcion: ";
                cin>>opcion;
                if(opcion.length()!=1 ||  (opcion[0] < '0' || opcion[0] > '7' )) cout<<"Introduce un numero correcto por favor."<<endl;//Si tiene mas de un caracter o no es un numero imprime un aviso
            }while(opcion.length()!=1 ||  (opcion[0] < '0' || opcion[0] > '7' ));//Si tiene mas de un caracter o no es numero volvera a solicitar
            cin.get();
            opcionnum=atoi(opcion.c_str());//Convierte a numero entero el numero almacenado en el string y lo copia en opcionnum

            switch(opcionnum){//Segun el valor de "opcionnum" realizara una de las siguientes opciones
            //En cada case hemos puesto corchetes porque Qt incicaba que estaba en "protected scope", al poner corchetes se ha solucionado
            case 1:
            {
                limpiar();
                //Base
                cout<<"Matriz base 2x3 por matriz base 3x2"<<endl<<endl;
                MatrizT<Fraccion> a(2,3), b(3,2);
                a*=b;
                cout<<a<<endl;
                cout<<"Matriz base 3x2 por matriz base 2x3"<<endl<<endl;
                MatrizT<Fraccion> c(3,2), d(2,3);
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
                MatrizGT<Fraccion> a(2,3), b(3,2);
                a*=b;
                cout<<a<<endl;
                cout<<"Matriz gruyere 3x2 por matriz gruyere 2x3"<<endl<<endl;
                MatrizGT<Fraccion> c(3,2), d(2,3);
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
                MatrizCT<Fraccion> a(2,3), b(3,2);
                a*=b;
                cout<<a<<endl;
                cout<<"Matriz cuadrada 3x2 por matriz cuadrada 2x3"<<endl<<endl;
                MatrizCT<Fraccion> c(3,2), d(2,3);
                c*=d;
                cout<<c<<endl;
                cout<<"Matriz cuadrada 3x3 por matriz cuadrada 3x3"<<endl<<endl;
                MatrizCT<Fraccion> e(3,3), f(3,3);
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
                MatrizDT<Fraccion> a(2,3), b(3,2);
                a*=b;
                cout<<a<<endl;
                cout<<"Matriz diagonal 3x2 por matriz diagonal 2x3"<<endl<<endl;
                MatrizDT<Fraccion> c(3,2), d(2,3);
                c*=d;
                cout<<c<<endl;
                cout<<"Matriz diagonal 3x3 por matriz diagonal 3x3"<<endl<<endl;
                MatrizDT<Fraccion> e(3,3), f(3,3);
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
                MatrizET<Fraccion> a(2,3), b(3,2);
                a*=b;
                cout<<a<<endl;
                cout<<"Matriz escalar 3x2 por matriz escalar 2x3"<<endl<<endl;
                MatrizET<Fraccion> c(3,2), d(2,3);
                c*=d;
                cout<<c<<endl;
                cout<<"Matriz escalar 3x3 por matriz escalar 3x3"<<endl<<endl;
                MatrizET<Fraccion> e(3,3), f(3,3);
                e*=f;
                cout<<e<<endl;
                cin.get();
                cin.get();
                break;
            }


            case 6://Sale del switch
                break;

            case 7://Sale del switch
                exit(0);

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
        cout << "3. Atras" << endl;
        cout << "4. Salir de la aplicacion" << endl;
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
                if(opcion.length()!=1 ||  (opcion[0] < '0' || opcion[0] > '4' )) cout<<"Introduce un numero correcto por favor."<<endl;//Si tiene mas de un caracter o no es un numero imprime un aviso
            }while(opcion.length()!=1 ||  (opcion[0] < '0' || opcion[0] > '4' ));//Si tiene mas de un caracter o no es numero volvera a solicitar
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

            case 4://Sale del switch
                exit(0);

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
        cout << "6. Atras" << endl;
        cout << "7. Salir de la aplicacion" << endl;

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
                if(opcion.length()!=1 ||  (opcion[0] < '0' || opcion[0] > '7' )) cout<<"Introduce un numero correcto por favor."<<endl;//Si tiene mas de un caracter o no es un numero imprime un aviso
            }while(opcion.length()!=1 ||  (opcion[0] < '0' || opcion[0] > '7' ));//Si tiene mas de un caracter o no es numero volvera a solicitar
            cin.get();
            opcionnum=atoi(opcion.c_str());//Convierte a numero entero el numero almacenado en el string y lo copia en opcionnum

            switch(opcionnum){//Segun el valor de "opcionnum" realizara una de las siguientes opciones
            case 1:
                limpiar();
                //Base
                cout<<"Suma de matrices base"<<endl<<endl;
                cout<<MatrizT<Fraccion>(4)+MatrizT<Fraccion>(4);
                cin.get();
                cin.get();
                break;
            case 2:
                limpiar();
                //Gruyere
                cout<<"Suma de matrices gruyere"<<endl<<endl;
                cout<<MatrizGT<Fraccion>(4)+MatrizGT<Fraccion>(4);
                cin.get();
                cin.get();
                break;
            case 3:
                limpiar();
                //Cuadrada
                cout<<"Suma de matrices cuadradas"<<endl<<endl;
                cout<<MatrizCT<Fraccion>(4)+MatrizCT<Fraccion>(4);
                cin.get();
                cin.get();
                break;
            case 4:
                limpiar();
                //Diagonal
                cout<<"Suma de matrices diagonales"<<endl<<endl;
                cout<<MatrizDT<Fraccion>(4)+MatrizDT<Fraccion>(4);
                cin.get();
                cin.get();
                break;
            case 5:
                limpiar();
                //Escalar
                cout<<"Suma de matrices escalares"<<endl<<endl;
                cout<<MatrizET<Fraccion>(4)+MatrizET<Fraccion>(4);
                cin.get();
                cin.get();
                break;


            case 6://Sale del switch
                break;

            case 7://Sale del switch
                exit(0);

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
        cout << "6. Atras" << endl;
        cout << "7. Salir de la aplicacion" << endl;
    }
    void autoSuma(){
        int opcionnum;//Declaracion de una variable entera
        string opcion;//String utilizado para recibir la opcion del usuario, validar si es un numero y si lo es ejecutar la opcion
        do{
            limpiar();
            imprimirAutosuma();//llama al metodo imprimir incluido en esta clase

            do{//Pediremos la opcion y comprobaremos si es un numero, si no lo es se volvera a solicitar
                cout << "Opcion: ";
                cin>>opcion;
                if(opcion.length()!=1 ||  (opcion[0] < '0' || opcion[0] > '7' )) cout<<"Introduce un numero correcto por favor."<<endl;//Si tiene mas de un caracter o no es un numero imprime un aviso
            }while(opcion.length()!=1 ||  (opcion[0] < '0' || opcion[0] > '7' ));//Si tiene mas de un caracter o no es numero volvera a solicitar
            cin.get();
            opcionnum=atoi(opcion.c_str());//Convierte a numero entero el numero almacenado en el string y lo copia en opcionnum

            switch(opcionnum){//Segun el valor de "opcionnum" realizara una de las siguientes opciones
            //En cada case hemos puesto corchetes porque Qt incicaba que estaba en "protected scope", al poner corchetes se ha solucionado
            case 1:
            {
                limpiar();
                //Base
                cout<<"Suma de matrices base"<<endl<<endl;
                MatrizT<Fraccion> base(4);
                base+=MatrizT<Fraccion>(4);
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
                MatrizGT<Fraccion> a(4);
                a+=MatrizGT<Fraccion>(4);
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
                MatrizCT<Fraccion> b(4);
                b+=MatrizCT<Fraccion>(4);
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
                MatrizDT<Fraccion> c(4);
                c+=MatrizDT<Fraccion>(4);
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
                MatrizET<Fraccion> d(4);
                d+=MatrizET<Fraccion>(4);
                cout<<d;
                cin.get();
                cin.get();
                break;
            }


            case 6://Sale del switch
                break;

            case 7://Sale del switch
                exit(0);

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
        cout << "3. Atras" << endl;
        cout << "4. Salir de la aplicacion" << endl;
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
                if(opcion.length()!=1 ||  (opcion[0] < '0' || opcion[0] > '4' )) cout<<"Introduce un numero correcto por favor."<<endl;//Si tiene mas de un caracter o no es un numero imprime un aviso
            }while(opcion.length()!=1 ||  (opcion[0] < '0' || opcion[0] > '4' ));//Si tiene mas de un caracter o no es numero volvera a solicitar
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

            case 4://Sale del switch
                exit(0);

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
        cout << "6. Atras" << endl;
        cout << "7. Salir del programa" << endl;

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
                if(opcion.length()!=1 ||  (opcion[0] < '0' || opcion[0] > '7' )) cout<<"Introduce un numero correcto por favor."<<endl;//Si tiene mas de un caracter o no es un numero imprime un aviso
            }while(opcion.length()!=1 ||  (opcion[0] < '0' || opcion[0] > '7' ));//Si tiene mas de un caracter o no es numero volvera a solicitar
            cin.get();
            opcionnum=atoi(opcion.c_str());//Convierte a numero entero el numero almacenado en el string y lo copia en opcionnum

            switch(opcionnum){//Segun el valor de "opcionnum" realizara una de las siguientes opciones
            case 1:
                limpiar();
                //Base
                cout<<"Resta de matrices base"<<endl<<endl;
                cout<<MatrizT<Fraccion>(4)-MatrizT<Fraccion>(4);
                cin.get();
                cin.get();
                break;
            case 2:
                limpiar();
                //Gruyere
                cout<<"Resta de matrices gruyere"<<endl<<endl;
                cout<<MatrizGT<Fraccion>(4)-MatrizGT<Fraccion>(4);
                cin.get();
                cin.get();
                break;
            case 3:
                limpiar();
                //Cuadrada
                cout<<"Resta de matrices cuadradas"<<endl<<endl;
                cout<<MatrizCT<Fraccion>(4)-MatrizCT<Fraccion>(4);
                cin.get();
                cin.get();
                break;
            case 4:
                limpiar();
                //Diagonal
                cout<<"Resta de matrices diagonales"<<endl<<endl;
                cout<<MatrizDT<Fraccion>(4)-MatrizDT<Fraccion>(4);
                cin.get();
                cin.get();
                break;
            case 5:
                limpiar();
                //Escalar
                cout<<"Resta de matrices escalares"<<endl<<endl;
                cout<<MatrizET<Fraccion>(4)-MatrizET<Fraccion>(4);
                cin.get();
                cin.get();
                break;


            case 6://Sale del switch
                break;

            case 7://Sale del programa
                exit(0);

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
        cout << "6. Atras" << endl;
        cout << "7. Salir del programa" << endl;
    }
    void autoResta(){
        int opcionnum;//Declaracion de una variable entera
        string opcion;//String utilizado para recibir la opcion del usuario, validar si es un numero y si lo es ejecutar la opcion
        do{
            limpiar();
            imprimirAutoresta();//llama al metodo imprimir incluido en esta clase

            do{//Pediremos la opcion y comprobaremos si es un numero, si no lo es se volvera a solicitar
                cout << "Opcion: ";
                cin>>opcion;
                if(opcion.length()!=1 ||  (opcion[0] < '0' || opcion[0] > '7' )) cout<<"Introduce un numero correcto por favor."<<endl;//Si tiene mas de un caracter o no es un numero imprime un aviso
            }while(opcion.length()!=1 ||  (opcion[0] < '0' || opcion[0] > '7' ));//Si tiene mas de un caracter o no es numero volvera a solicitar
            cin.get();
            opcionnum=atoi(opcion.c_str());//Convierte a numero entero el numero almacenado en el string y lo copia en opcionnum

            switch(opcionnum){//Segun el valor de "opcionnum" realizara una de las siguientes opciones
            //En cada case hemos puesto corchetes porque Qt incicaba que estaba en "protected scope", al poner corchetes se ha solucionado
            case 1:
            {
                limpiar();
                //Base
                cout<<"Resta de matrices base"<<endl<<endl;
                MatrizT<Fraccion> base(4);
                base-=MatrizT<Fraccion>(4);
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
                MatrizGT<Fraccion> a(4);
                a-=MatrizGT<Fraccion>(4);
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
                MatrizCT<Fraccion> b(4);
                b-=MatrizCT<Fraccion>(4);
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
                MatrizDT<Fraccion> c(4);
                c-=MatrizDT<Fraccion>(4);
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
                MatrizET<Fraccion> d(4);
                d-=MatrizET<Fraccion>(4);
                cout<<d;
                cin.get();
                cin.get();
                break;
            }


            case 6://Sale del switch
                break;

            case 7://Sale del programa
                exit(0);
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
        cout << "6. Salir del programa" << endl;
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
                exit(0);

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
