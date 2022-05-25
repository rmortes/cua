/**************************************************************************
 * (C) Copyright 2014 Carlos Barrera Piqueres y Jose Manuel Requena Plens *
 * Universidad de Alicante. Grado en ingenieria en sonido e imagen.       *
 *                                                                        *
 * Asignatura: Fundamentos de programacion 2                              *
 *                                                                        *
 * PRACTICA 3                                                             *
 *                                                                        *
 * JUEGO CONECTA 4                                                        *
 *************************************************************************/
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>//Para la ventana emergente informativa

MainWindow::MainWindow(QWidget *parent):QMainWindow(parent),ui(new Ui::MainWindow)//Constructor
{
    ui->setupUi(this);

    //Asignamos cada direccion de los push buton creados en la interfaz grafica a los creados por la matriz incluida en el .h
    //Fila 1
    ficha[0][0] = ui->btn00;
    ficha[0][1] = ui->btn01;
    ficha[0][2] = ui->btn02;
    ficha[0][3] = ui->btn03;
    ficha[0][4] = ui->btn04;
    ficha[0][5] = ui->btn05;
    ficha[0][6] = ui->btn06;
    //Fila 2
    ficha[1][0] = ui->btn10;
    ficha[1][1] = ui->btn11;
    ficha[1][2] = ui->btn12;
    ficha[1][3] = ui->btn13;
    ficha[1][4] = ui->btn14;
    ficha[1][5] = ui->btn15;
    ficha[1][6] = ui->btn16;
    //Fila 3
    ficha[2][0] = ui->btn20;
    ficha[2][1] = ui->btn21;
    ficha[2][2] = ui->btn22;
    ficha[2][3] = ui->btn23;
    ficha[2][4] = ui->btn24;
    ficha[2][5] = ui->btn25;
    ficha[2][6] = ui->btn26;
    //Fila 4
    ficha[3][0] = ui->btn30;
    ficha[3][1] = ui->btn31;
    ficha[3][2] = ui->btn32;
    ficha[3][3] = ui->btn33;
    ficha[3][4] = ui->btn34;
    ficha[3][5] = ui->btn35;
    ficha[3][6] = ui->btn36;
    //Fila 5
    ficha[4][0] = ui->btn40;
    ficha[4][1] = ui->btn41;
    ficha[4][2] = ui->btn42;
    ficha[4][3] = ui->btn43;
    ficha[4][4] = ui->btn44;
    ficha[4][5] = ui->btn45;
    ficha[4][6] = ui->btn46;
    //Fila 6
    ficha[5][0] = ui->btn50;
    ficha[5][1] = ui->btn51;
    ficha[5][2] = ui->btn52;
    ficha[5][3] = ui->btn53;
    ficha[5][4] = ui->btn54;
    ficha[5][5] = ui->btn55;
    ficha[5][6] = ui->btn56;

    for(int i = 0; i < 6; i++){//Ponemos a 0 todos los turnos
		for(int j = 0; j < 7; j++){
            turno[i][j] = 0;	// 0 sin ficha.

		}
	}
	
	// Turno de rojo.
    jugador = 1;
	ganador = false;
}

//Botones que rellenan las columnas
void MainWindow::on_pushButton_clicked(){//Metodo para el boton de la columna 0
    setFicha(0);//Llama al metodo poneFicha para la columna 0
}

void MainWindow::on_pushButton_2_clicked()//Metodo para el boton de la columna 1
{
    setFicha(1);//Llama al metodo poneFicha para la columna 1
}

void MainWindow::on_pushButton_3_clicked()//Metodo para el boton de la columna 2
{
    setFicha(2);//Llama al metodo poneFicha para la columna 2
}

void MainWindow::on_pushButton_4_clicked()//Metodo para el boton de la columna 3
{
    setFicha(3);//Llama al metodo poneFicha para la columna 3
}

void MainWindow::on_pushButton_5_clicked()//Metodo para el boton de la columna 4
{
    setFicha(4);//Llama al metodo poneFicha para la columna 4
}

void MainWindow::on_pushButton_7_clicked()//Metodo para el boton de la columna 5
{
    setFicha(5);//Llama al metodo poneFicha para la columna 5
}

void MainWindow::on_pushButton_8_clicked()//Metodo para el boton de la columna 6
{
    setFicha(6);//Llama al metodo poneFicha para la columna 6
}

//Metodos del juego
bool MainWindow::findGanador(int jugador, int fila, int columna){//Comprueba si ha ganado
    bool win = false;
	int cuantas = 0;
	
    //Comprueba la horizontal a partir del numero de columna recibido, recorriendo a derecha y a izquierda
    for(int i = columna; i < 7 && turno[fila][i] == jugador; i++){//Mientras no llegue al final del panel (derecha) y siga habiendo fichas del jugador, seguira el bucle
		cuantas++;
    }
    for(int i = columna - 1; i >= 0 && turno[fila][i] == jugador; i--){//Mientras no llegue al final del panel (izquierda) y siga habiendo fichas del jugador, seguira el bucle
		cuantas++;
    }
		
    if(cuantas >= 4){//Si hay 4 o mas en linea, se termina el juego
        win = true;
    }else{
        win = false;
    }
    if(!win){//Seguimos comprobando vertical si en la horizontal no hay ganador
		cuantas = 0;
        for(int i = fila; i < 6 && turno[i][columna] == jugador; i++){//Mientras recorre la vertical si encuentra fichas del jugador actual sigue con el bucle
			cuantas++;
		}
        if(cuantas >= 4){//Si ha encontrado 4 o mas en linea, termina el juego
            win = true;
        }else{
            win = false;
        }
	}
	
    if(!win){//Seguimos comprobando la diagonal si el resto de comprobaciones no han dado ganador
		cuantas = 0;
		int i = fila;
		int j = columna;
        while(i < 6 && j < 7 && turno[i][j] == jugador){//Recorremos la diagonal hacia arriba/derecha
			cuantas++; i++; j++;
		}
		i = fila - 1;
		j = columna - 1;
        while(i >= 0 && j >= 0 && turno[i][j] == jugador){//Recorremos la diagonal hacia abajo/izquierda
			cuantas++;
			i--; j--;
		}
        if(cuantas >= 4){
            win = true;
        }else{
            win = false;
        }
	}
    if(!win){//Otra direccion de la diagonal
		cuantas = 0;
		int i = fila;
		int j = columna;
        while(i >= 0 && j< 7 && turno[i][j] == jugador){//Recorremos la diagonal hacia abajo/derecha
			cuantas++;
			i--;
			j++;
		}
		
		i = fila + 1;
		j = columna - 1;
        while(i < 6 && j >= 0 && turno[i][j] == jugador){//Recorremos la diagonal hacia arriba/izquierda
			cuantas++;
			i++;
			j--;
		}
        if(cuantas >= 4){
            win = true;
        }else{
            win = false;
        }

	}
    return win;
}

bool MainWindow::findEmpate(){
	bool empatado = true;
    for(int i = 0; i < 7 && empatado; i++){//Recorremos toda la fila superior
        if(turno[0][i] == 0){//Si hay alguna posicion vacia, todavia no ha terminado el juego y no hay empate
			empatado = false;
		} 
	}
    return empatado;//Devuelve el valor del booleano
}

void MainWindow::setFicha(int columna){//Pone una ficha en la columna que indica el entero que recibe
	int i, fila;
	bool empate;
	
    if(ganador == false){//Si no hay ganador
		fila = -1;
        for(i = 5; i >= 0 && fila == -1; i--){//Recorremos la fila para saber cual es la primera vacia
            if(turno[i][columna] == 0) fila = i;//Cuando encuentre la vacia, guarda la posicion
		}
        if(fila != -1){//Si ha encontrado una posicion vacia (que puede poner ficha) colocamos ficha
            turno[fila][columna] = jugador;//Ponemos el jugador en la matriz de turno, en la fila que ha calculado y la columna recibida
            if(jugador == 1){
                ficha[fila][columna]->setIcon(QIcon(QPixmap(":/fichas/circle_red.png")));//Si el jugador es uno, pone el pushbutton de la posicion [fila][columna] con ficha roja
            }else{
                ficha[fila][columna]->setIcon(QIcon(QPixmap(":/fichas/circle_yellow.png")));//Si el jugador es dos, pone el pushbutton de la posicion [fila][columna] con ficha amarilla
            }
            ganador = findGanador(jugador, fila, columna);//Llamamos al metodo ganador enviando el jugador actual, y a partir de que fila y columna hay que comprobar
            if(ganador){//Si devuelve true
                if(jugador == 1){
                    QMessageBox::information(this, "Ganador", "Fichas rojas ganan");//Si el jugador es 1, ganan las roja y abre una ventana informativa indicandolo
                }else{
                    QMessageBox::information(this, "Ganador", "Fichas amarillas ganan");//Si el jugador es 2, ganan las amarillas y abre una ventana informativa indicandolo
                }
                on_actionReiniciar_triggered();//Reiniciamos el juego llamando al mismo metodo que llama el boton reiniciar al pulsar sobre el
            }else{
                empate = findEmpate();//Llamamos al metodo para comprobar si hay empate
                if(!empate){//Si no hay empate cambiamos el jugador
                    if(jugador == 1){
                        jugador = 2;

						ui->label->setText("Turno de las amarillas");
					}
					else{
                        jugador = 1;
						ui->label->setText("Turno de las rojas");
					}
                }else{//Si hay empate
                    QMessageBox::information(this, "Ganador", "Empate");//Si hay empate abre una ventana informativa indicandolo
                    on_actionReiniciar_triggered();//Reiniciamos el juego llamando al mismo metodo que llama el boton reiniciar al pulsar sobre el
				}
			}
		}
	}
}

//Botones del menu
void MainWindow::on_actionSalir_triggered()
{
    qApp->exit();//Cerramos la aplicacion
}

void MainWindow::on_actionReiniciar_triggered()//Reiniciar el juego
{
    for(int i = 0; i < 6; i++){//Recorremos tanto la matriz de turno como la matriz de los botones
		for(int j = 0; j < 7; j++){
            turno[i][j] = 0;	//Ponemos todos los turnos a 0, vacio
            ficha[i][j]->setIcon(QIcon(QPixmap(":/fichas/circle_grey.png")));//Cambiamos la imagen de todos los botones a la imagen de hueco
		}
    }
    //Comenzamos el turno con el rojo tal como pone en la practica
    jugador = 1;
	ganador = false;    
	ui->label->setText("Turno de las rojas");
}

void MainWindow::on_actionAutores_triggered()
{
    QMessageBox::information(this, "Autores", "Carlos B. y Jose R.");
}

//DESTRUCTOR
MainWindow::~MainWindow(){//Destructor
    delete ui;
}
