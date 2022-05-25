#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    IniciarJuego();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::IniciarJuego(){
    M[0][0] = ui->m00; M[0][1] = ui->m01; M[0][2] = ui->m02;
    M[0][3] = ui->m03; M[0][4] = ui->m04; M[0][5] = ui->m05;
    M[0][6] = ui->m06; M[0][7] = ui->m07; M[0][8] = ui->m08;

    M[1][0] = ui->m10; M[1][1] = ui->m11; M[1][2] = ui->m12;
    M[1][3] = ui->m13; M[1][4] = ui->m14; M[1][5] = ui->m15;
    M[1][6] = ui->m16; M[1][7] = ui->m17; M[1][8] = ui->m18;

    M[2][0] = ui->m20; M[2][1] = ui->m21; M[2][2] = ui->m22;
    M[2][3] = ui->m23; M[2][4] = ui->m24; M[2][5] = ui->m25;
    M[2][6] = ui->m26; M[2][7] = ui->m27; M[2][8] = ui->m28;

    M[3][0] = ui->m30; M[3][1] = ui->m31; M[3][2] = ui->m32;
    M[3][3] = ui->m33; M[3][4] = ui->m34; M[3][5] = ui->m35;
    M[3][6] = ui->m36; M[3][7] = ui->m37; M[3][8] = ui->m38;

    M[4][0] = ui->m40; M[4][1] = ui->m41; M[4][2] = ui->m42;
    M[4][3] = ui->m43; M[4][4] = ui->m44; M[4][5] = ui->m45;
    M[4][6] = ui->m46; M[4][7] = ui->m47; M[4][8] = ui->m48;

    M[5][0] = ui->m50; M[5][1] = ui->m51; M[5][2] = ui->m52;
    M[5][3] = ui->m53; M[5][4] = ui->m54; M[5][5] = ui->m55;
    M[5][6] = ui->m56; M[5][7] = ui->m57; M[5][8] = ui->m58;

    M[6][0] = ui->m60; M[6][1] = ui->m61; M[6][2] = ui->m62;
    M[6][3] = ui->m63; M[6][4] = ui->m64; M[6][5] = ui->m65;
    M[6][6] = ui->m66; M[6][7] = ui->m67; M[6][8] = ui->m68;

    M[7][0] = ui->m70; M[7][1] = ui->m71; M[7][2] = ui->m72;
    M[7][3] = ui->m73; M[7][4] = ui->m74; M[7][5] = ui->m75;
    M[7][6] = ui->m76; M[7][7] = ui->m77; M[7][8] = ui->m78;

    M[8][0] = ui->m80; M[8][1] = ui->m81; M[8][2] = ui->m82;
    M[8][3] = ui->m83; M[8][4] = ui->m84; M[8][5] = ui->m85;
    M[8][6] = ui->m86; M[8][7] = ui->m87; M[8][8] = ui->m88;

    jugador = CRUZ; //predeterminar que la primera tirada sera una cruz
    ui->label->setText("Turno Jugador1 (rojas/cruces)");
    for(int i=0;i<9;i++){
        for(int j = 0;j<9;j++){
            //pintar el fondo del tablero de blanco
            M[i][j]->setStyleSheet("background-color:white;border:none");
            //indicar que todas las casillas estan vacias, a 0
            E[i][j] = VACIO;
        }
    }
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            J[i][j]=VACIO;
        }
    }
}

void MainWindow::Tirar(int i, int j){
    //juego sirve para saber en que 3 en raya estoy
    int juego_i=i/3, juego_j=j/3;
    //inic sirve para saber donde empieza el 3 en raya en el que estoy
    int inic_i = juego_i*3, inic_j = juego_j*3;

    //si el juego en el que estoy esta en vacio y no hay botones usados, puedo tirar
    //si no, no puedo tirar y se bloquea el juego
    if(J[juego_i][juego_j]==VACIO && E[i][j]==VACIO){
        if(jugador == CRUZ){
            //cambiar el icono de la casilla a una cruz
            M[i][j]->setIcon(QIcon(":/iconos/player1.png"));
            ui->label->setText("Turno Jugador2 (azules/circulos)");
            //ahora es estado de la casilla sera el de una cruz
            E[i][j] = CRUZ;
            //el entero jugador pasa a estar en estado circulo (cambia el turno)
            jugador = CIRCULO;
        }else{
            M[i][j]->setIcon(QIcon(":/iconos/player2.png"));
            ui->label->setText("Turno Jugador1 (rojas/cruces)");
            E[i][j] = CIRCULO;
            jugador = CRUZ;
        }
    }

    int ganador = VACIO; //todavia no hay ningun ganador
    //ver los estados de las posiciones para saber quien gana

    //primera fila
    if(E[inic_i][inic_j] !=VACIO && E[inic_i][inic_j]==E[inic_i][inic_j+1] && E[inic_i][inic_j+1]==E[inic_i][inic_j+2]){
        ganador = E[inic_i][inic_j];
    }
    //segunda fila
    if(E[inic_i+1][inic_j] !=VACIO && E[inic_i+1][inic_j]==E[inic_i+1][inic_j+1] && E[inic_i+1][inic_j+1]==E[inic_i+1][inic_j+2]){
        ganador = E[inic_i+1][inic_j];
    }
    //tercera fila
    if(E[inic_i+2][inic_j] !=VACIO && E[inic_i+2][inic_j]==E[inic_i+2][inic_j+1] && E[inic_i+2][inic_j+1]==E[inic_i+2][inic_j+2]){
        ganador = E[inic_i+2][inic_j];
    }
    //primera columna
    if(E[inic_i][inic_j]!=VACIO && E[inic_i][inic_j]==E[inic_i+1][inic_j]&& E[inic_i+1][inic_j]==E[inic_i+2][inic_j]){
        ganador = E[inic_i+2][inic_j];
    }
    //segunda columna
    if(E[inic_i][inic_j+1]!=VACIO && E[inic_i][inic_j+1]==E[inic_i+1][inic_j+1] && E[inic_i+1][inic_j+1]==E[inic_i+2][inic_j+1]){
        ganador = E[inic_i+1][inic_j+1];
    }
    //tercera columna
    if(E[inic_i][inic_j+2]!=VACIO && E[inic_i][inic_j+2]==E[inic_i+1][inic_j+2] && E[inic_i+1][inic_j+2]==E[inic_i+2][inic_j+2]){
        ganador = E[inic_i][inic_j+2];
    }
    //diagonal principal
    if(E[inic_i][inic_j] !=VACIO && E[inic_i][inic_j]==E[inic_i+1][inic_j+1] && E[inic_i+1][inic_j+1]==E[inic_i+2][inic_j+2]){
        ganador = E[inic_i+2][inic_j+2];
    }
    //diagonal secundaria
    if(E[inic_i][inic_j+2] !=VACIO && E[inic_i][inic_j+2]==E[inic_i+1][inic_j+1] && E[inic_i+1][inic_j+1]==E[inic_i+2][inic_j]){
        ganador = E[inic_i][inic_j+2];
    }

    //si hay un ganador
    if(ganador!=VACIO){
        //y el ganador es una cruz
        if(ganador == CRUZ){
            //bucle desde el inicio del juego en el que estoy hasta 3 posiciones mas alla
            for(int i=inic_i;i<inic_i+3;i++){
                for(int j = inic_j;j<inic_j+3;j++){
                    //pintar el fondo de rojo
                    M[i][j]->setStyleSheet("background-color:red;border:none");
                    //han ganado las CRUCES en ese juego
                    J[juego_i][juego_j] = CRUZ;
                }
            }
        }else{
            for(int i=inic_i;i<inic_i+3;i++){
                for(int j = inic_j;j<inic_j+3;j++){
                    //pintar el fondo de azul
                    M[i][j]->setStyleSheet("background-color:blue;border:none");
                    //han ganado los CIRCULOS en ese juego
                    J[juego_i][juego_j] = CIRCULO;
                }
            }
        }
    }else{//si no hay ganador
        //booleano que nos dice si hay algun hueco libre o no
        bool estaVacio = false;
        //recorrer el tablero
        for(int i=juego_i;i<juego_i+3;i++){
            for(int j=juego_j;j<juego_j+3;j++){
                //si el estado es vacio
                if(E[i][j]==VACIO){
                    //hay algun vacio
                    estaVacio = true;
                }
            }
        }
        if(estaVacio==false){//no hay ninguno vacio
            J[juego_i][juego_j] = EMPATE;
        }
    }
    //ganador supremo
    int ganador_total = VACIO;
    //primera fila
    if(J[juego_i][juego_j] !=VACIO && J[juego_i][juego_j]==J[juego_i][juego_j+1] && J[juego_i][juego_j+1]==J[juego_i][juego_j+2]){
        ganador_total = J[juego_i][juego_j];
    }
    //segunda fila
    if(J[juego_i+1][juego_j] !=VACIO && J[juego_i+1][juego_j]==J[juego_i+1][juego_j+1] && J[juego_i+1][juego_j+1]==J[juego_i+1][juego_j+2]){
        ganador_total = J[juego_i+1][juego_j];
    }
    //tercera fila
    if(J[juego_i+2][juego_j] !=VACIO && J[juego_i+2][juego_j]==J[juego_i+2][juego_j+1] && J[juego_i+2][juego_j+1]==J[juego_i+2][juego_j+2]){
        ganador_total = J[juego_i+2][juego_j+2];
    }
    //primera columna
    if(J[juego_i][juego_j]!=VACIO && J[juego_i][juego_j]==J[juego_i+1][juego_j]&& J[juego_i+1][juego_j]==J[juego_i+2][juego_j]){
        ganador_total = J[juego_i+2][juego_j];
    }
    //segunda columna
    if(J[juego_i][juego_j+1]!=VACIO && J[juego_i][juego_j+1]==J[juego_i+1][juego_j+1] && J[juego_i+1][juego_j+1]==J[juego_i+2][juego_j+1]){
        ganador_total = J[juego_i][juego_j+1];
    }
    //tercera columna
    if(J[juego_i][juego_j+2]!=VACIO && J[juego_i][juego_j+2]==J[juego_i+1][juego_j+2] && J[juego_i+1][juego_j+2]==J[juego_i+2][juego_j+2]){
        ganador_total = J[juego_i][juego_j+2];
    }
    //diagonal principal
    if(J[juego_i][juego_j] !=VACIO && J[juego_i][juego_j]==J[juego_i+1][juego_j+1] && J[juego_i+1][juego_j+1]==J[juego_i+2][juego_j+2]){
        ganador_total = J[juego_i+1][juego_j+1];
    }
    //diagonal secundaria
    if(J[juego_i][juego_j+2] !=VACIO && J[juego_i][juego_j+2]==J[juego_i+1][juego_j+1]&& J[juego_i+1][juego_j+1]==J[juego_i+2][juego_j]){
        ganador_total = J[juego_i][juego_j+2];
    }

    //si hay un ganador
    if(ganador_total!=VACIO){
        //y el ganador es una cruz
        if(ganador_total == CRUZ){
            //bucle desde el inicio del juego en el que estoy hasta 3 posiciones mas alla
            for(int i=inic_i;i<inic_i+3;i++){
                for(int j = inic_j;j<inic_j+3;j++){
                    //han ganado las CRUCES en ese juego
                    J[juego_i][juego_j] = CRUZ;
                }
            }
            QMessageBox::information(this,"SudoTicTacToe","Ganan las cruces","Aceptar");

        }else{
            for(int i=inic_i;i<inic_i+3;i++){
                for(int j = inic_j;j<inic_j+3;j++){
                    //han ganado los CIRCULOS en ese juego
                    J[juego_i][juego_j] = CIRCULO;
                }
            }
            QMessageBox::information(this,"SudoTicTacToe","Ganan los circulos","Aceptar");
        }
    }else{//si no hay ganador
        //booleano que nos dice si hay algun hueco libre o no
        bool estaVacio = false;
        //recorrer el tablero
        for(int i=juego_i;i<juego_i+3;i++){
            for(int j=juego_j;j<juego_j+3;j++){
                //si el estado es vacio
                if(E[i][j]==VACIO){
                    //hay algun vacio
                    estaVacio = true;
                }
            }
        }
        if(estaVacio==false){//no hay ninguno vacio
            J[juego_i][juego_j] = EMPATE;
        }
    }
    return;
}

void MainWindow::on_m00_clicked()
{
    Tirar(0,0);
}

void MainWindow::on_m01_clicked()
{
    Tirar(0,1);
}

void MainWindow::on_m02_clicked()
{
    Tirar(0,2);
}

void MainWindow::on_m03_clicked()
{
    Tirar(0,3);
}

void MainWindow::on_m04_clicked()
{
    Tirar(0,4);
}

void MainWindow::on_m05_clicked()
{
    Tirar(0,5);
}

void MainWindow::on_m06_clicked()
{
    Tirar(0,6);

}

void MainWindow::on_m07_clicked()
{
    Tirar(0,7);
}

void MainWindow::on_m08_clicked()
{
    Tirar(0,8);
}

void MainWindow::on_m10_clicked()
{
    Tirar(0,9);
}

void MainWindow::on_m11_clicked()
{
    Tirar(1,1);
}

void MainWindow::on_m12_clicked()
{
    Tirar(1,2);
}

void MainWindow::on_m13_clicked()
{
    Tirar(1,3);
}

void MainWindow::on_m14_clicked()
{
    Tirar(1,4);

}

void MainWindow::on_m15_clicked()
{
    Tirar(1,5);

}

void MainWindow::on_m16_clicked()
{
    Tirar(1,6);

}

void MainWindow::on_m17_clicked()
{
    Tirar(1,7);

}

void MainWindow::on_m18_clicked()
{
    Tirar(1,8);

}

void MainWindow::on_m20_clicked()
{
    Tirar(2,0);

}

void MainWindow::on_m21_clicked()
{
    Tirar(2,1);

}

void MainWindow::on_m22_clicked()
{
    Tirar(2,2);

}

void MainWindow::on_m23_clicked()
{
    Tirar(2,3);

}

void MainWindow::on_m24_clicked()
{
    Tirar(2,4);
}

void MainWindow::on_m25_clicked()
{
    Tirar(2,5);
}

void MainWindow::on_m26_clicked()
{
    Tirar(2,6);
}

void MainWindow::on_m27_clicked()
{
    Tirar(2,7);
}

void MainWindow::on_m28_clicked()
{
    Tirar(2,8);
}

void MainWindow::on_m30_clicked()
{
    Tirar(3,0);
}

void MainWindow::on_m31_clicked()
{
    Tirar(3,1);
}

void MainWindow::on_m32_clicked()
{
    Tirar(3,2);
}

void MainWindow::on_m33_clicked()
{
    Tirar(3,3);
}

void MainWindow::on_m34_clicked()
{
    Tirar(3,4);
}

void MainWindow::on_m35_clicked()
{
    Tirar(3,5);
}

void MainWindow::on_m36_clicked()
{
    Tirar(3,6);
}

void MainWindow::on_m37_clicked()
{
    Tirar(3,7);
}

void MainWindow::on_m38_clicked()
{
    Tirar(3,8);
}

void MainWindow::on_m40_clicked()
{
    Tirar(4,0);
}

void MainWindow::on_m41_clicked()
{
    Tirar(4,1);
}

void MainWindow::on_m42_clicked()
{
    Tirar(4,2);
}

void MainWindow::on_m43_clicked()
{
    Tirar(4,3);
}

void MainWindow::on_m44_clicked()
{
    Tirar(4,4);
}

void MainWindow::on_m45_clicked()
{
    Tirar(4,5);
}

void MainWindow::on_m46_clicked()
{
    Tirar(4,6);
}

void MainWindow::on_m47_clicked()
{
    Tirar(4,7);
}

void MainWindow::on_m48_clicked()
{
    Tirar(4,8);
}

void MainWindow::on_m50_clicked()
{
    Tirar(5,0);
}

void MainWindow::on_m51_clicked()
{
    Tirar(5,1);
}

void MainWindow::on_m52_clicked()
{
    Tirar(5,2);
}

void MainWindow::on_m53_clicked()
{
    Tirar(5,3);
}

void MainWindow::on_m54_clicked()
{
    Tirar(5,4);
}

void MainWindow::on_m55_clicked()
{
    Tirar(5,5);
}

void MainWindow::on_m56_clicked()
{
    Tirar(5,6);
}

void MainWindow::on_m57_clicked()
{
    Tirar(5,7);
}

void MainWindow::on_m58_clicked()
{
    Tirar(5,8);
}

void MainWindow::on_m60_clicked()
{
    Tirar(6,0);
}

void MainWindow::on_m61_clicked()
{
    Tirar(6,1);
}

void MainWindow::on_m62_clicked()
{
    Tirar(6,2);
}

void MainWindow::on_m63_clicked()
{
    Tirar(6,3);
}

void MainWindow::on_m64_clicked()
{
    Tirar(6,4);
}

void MainWindow::on_m65_clicked()
{
    Tirar(6,5);
}

void MainWindow::on_m66_clicked()
{
    Tirar(6,6);
}

void MainWindow::on_m67_clicked()
{
    Tirar(6,7);
}

void MainWindow::on_m68_clicked()
{
    Tirar(6,8);
}

void MainWindow::on_m70_clicked()
{
    Tirar(7,0);
}

void MainWindow::on_m71_clicked()
{
    Tirar(7,1);
}

void MainWindow::on_m72_clicked()
{
    Tirar(7,2);
}

void MainWindow::on_m73_clicked()
{
    Tirar(7,3);
}

void MainWindow::on_m74_clicked()
{
    Tirar(7,4);
}

void MainWindow::on_m75_clicked()
{
    Tirar(7,5);
}

void MainWindow::on_m76_clicked()
{
    Tirar(7,6);
}

void MainWindow::on_m77_clicked()
{
    Tirar(7,7);
}

void MainWindow::on_m78_clicked()
{
    Tirar(7,8);
}

void MainWindow::on_m80_clicked()
{
    Tirar(8,0);
}

void MainWindow::on_m81_clicked()
{
    Tirar(8,1);
}

void MainWindow::on_m82_clicked()
{
    Tirar(8,2);
}

void MainWindow::on_m83_clicked()
{
    Tirar(8,3);
}

void MainWindow::on_m84_clicked()
{
    Tirar(8,4);
}

void MainWindow::on_m85_clicked()
{
    Tirar(8,5);
}

void MainWindow::on_m86_clicked()
{
    Tirar(8,6);
}

void MainWindow::on_m87_clicked()
{
    Tirar(8,7);
}

void MainWindow::on_m88_clicked()
{
    Tirar(8,8);
}
void MainWindow:: Reestablecer(){
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            E[i][j] = VACIO;
            M[i][j]->setIcon(QIcon());
            M[i][j]->setStyleSheet("background-color:white;border:none");

        }
    }
    return;
}
void MainWindow::on_actionSalir_triggered()
{
    qApp->exit();
}

void MainWindow::on_actionVolver_a_jugar_triggered()
{
    Reestablecer();
    IniciarJuego();
}

void MainWindow::on_actionAcercaDe_triggered()
{
    QMessageBox::information(NULL,"AcercaDe","Realizado por Helena Iborra Miquel y Aitana Molina García","Aceptar");
}
