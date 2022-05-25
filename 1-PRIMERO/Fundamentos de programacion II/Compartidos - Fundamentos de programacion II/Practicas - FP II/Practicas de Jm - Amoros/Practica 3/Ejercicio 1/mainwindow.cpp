#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QMouseEvent>
#include <QRect>
#include <QPushButton>
#include <QMessageBox>
#include <QFileDialog>
#include <QImage>
#include <QPixmap>
#include <QSound>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{    
    ui->setupUi(this);

    M[0][0] = ui->pushButton_5;
    M[0][1] = ui->pushButton_6;
    M[0][2] = ui->pushButton_7;
    M[0][3] = ui->pushButton_8;
    M[1][0] = ui->pushButton_9;
    M[1][1] = ui->pushButton_10;
    M[1][2] = ui->pushButton_11;
    M[1][3] = ui->pushButton_12;
    M[2][0] = ui->pushButton_13;
    M[2][1] = ui->pushButton_14;
    M[2][2] = ui->pushButton_15;
    M[2][3] = ui->pushButton_19;
    M[3][0] = ui->pushButton_17;
    M[3][1] = ui->pushButton_18;
    M[3][2] = ui->pushButton_16;
    M[3][3] = ui->pushButton_20;

   QSound::play("La_Cancion_De_Bob_Esponja.wav"); //carga el sonido de la ruta dnd esta el proyecto!

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_16_clicked()

{
     BotonPulsado(3,2);
}

void MainWindow::on_pushButton_19_clicked()
{
    BotonPulsado(2,3);
}

void MainWindow::on_pushButton_15_clicked()
{
     BotonPulsado(2,2);
}

void MainWindow::on_pushButton_11_clicked()
{
     BotonPulsado(1,2);
}

void MainWindow::on_pushButton_12_clicked()
{
     BotonPulsado(1,3);
}

void MainWindow::on_pushButton_7_clicked()
{
     BotonPulsado(0,2);
}

void MainWindow::on_pushButton_8_clicked()
{
     BotonPulsado(0,3);
}

void MainWindow::on_pushButton_18_clicked()
{
    BotonPulsado(3,1);
}

void MainWindow::on_pushButton_17_clicked()
{
     BotonPulsado(3,0);
}

void MainWindow::on_pushButton_13_clicked()
{
     BotonPulsado(2,0);
}

void MainWindow::on_pushButton_14_clicked()
{
   BotonPulsado(2,1);
}

void MainWindow::on_pushButton_9_clicked()
{
     BotonPulsado(1,0);
}

void MainWindow::on_pushButton_10_clicked()
{
     BotonPulsado(1,1);
}

void MainWindow::on_pushButton_5_clicked()
{
     BotonPulsado(0,0);
}

void MainWindow::on_pushButton_6_clicked()
{
     BotonPulsado(0,1);
}


void MainWindow::on_pushButton_20_clicked()
{

    BotonPulsado(3,3);
}

void MainWindow::BotonPulsado(int fila, int columna){
    if(!M[fila][columna]->icon().isNull()){
        //arriba
        if(fila>0 && M[fila-1][columna]->icon().isNull()){
            M[fila-1][columna]->setIcon(M[fila][columna]->icon());
            M[fila][columna]->setIcon(QIcon());
            cont++;
        }

        ///izquierda,derecha arriba y abajo
    }
    //abajo
    if(!M[fila][columna]->icon().isNull()){
        if(fila<3 && M[fila+1][columna]->icon().isNull()){
            M[fila+1][columna]->setIcon(M[fila][columna]->icon());
            M[fila][columna]->setIcon(QIcon());
            cont++;
        }
    }
    //derecha
    if(!M[fila][columna]->icon().isNull()){
        if(columna>0 && M[fila][columna-1]->icon().isNull()){
            M[fila][columna-1]->setIcon(M[fila][columna]->icon());
            M[fila][columna]->setIcon(QIcon());
            cont++;
        }
    }
  //izkierda
        if(!M[fila][columna]->icon().isNull()){
            if(columna<3 && M[fila][columna+1]->icon().isNull()){
                M[fila][columna+1]->setIcon(M[fila][columna]->icon());
                M[fila][columna]->setIcon(QIcon());
                cont++;
            }
        }

}
void MainWindow::Desordena(){
    cont=0;
    do{
        int a =rand()%4;

        int b= rand()%4;
        BotonPulsado(a,b);

    }while(cont<50);

}



void MainWindow::on_actionOpciones_triggered()
{
    QString s = QFileDialog::getOpenFileName(this, "Cargar", NULL, "*.jpg");
    if(!s.isEmpty()) {
        Img.load(s);
    }

    if(!Img.isNull()) {

        QPixmap nuevo = Img.scaled(800,600);//escalo la imagen
       QPixmap icono = nuevo.copy(0.200,0.150,200,150);//corto y la guardo  en su posicion
        QIcon icon(icono);
        M[0][0]->setIcon(icon);
//fila 1
        QPixmap icono1 = nuevo.copy(200.400,0.150,200,150);//corto y la guardo  en su posicion
        QIcon icon1(icono1);
        M[0][1]->setIcon(icon1);

        QPixmap icono2 = nuevo.copy(400.600,0.150,200,150);//corto y la guardo  en su posicion
        QIcon icon2(icono2);
        M[0][2]->setIcon(icon2);

        QPixmap icono3 = nuevo.copy(600.800,0.150,200,150);//corto y la guardo  en su posicion
        QIcon icon3(icono3);
        M[0][3]->setIcon(icon3);

//fila 2
        QPixmap icono4 = nuevo.copy( 0.200,150.300,200,150);//corto y la guardo  en su posicion
        QIcon icon4(icono4);
        M[1][0]->setIcon(icon4);

        QPixmap icono5 = nuevo.copy( 200.400,150.300,200,150);//corto y la guardo  en su posicion
        QIcon icon5(icono5);
        M[1][1]->setIcon(icon5);

        QPixmap icono6 = nuevo.copy(400.600,150.300,200,150 );//corto y la guardo  en su posicion
        QIcon icon6(icono6);
        M[1][2]->setIcon(icon6);

        QPixmap icono7 = nuevo.copy(600.800,150.300,200,150);//corto y la guardo  en su posicion
        QIcon icon7(icono7);
        M[1][3]->setIcon(icon7);

 //fila 3

        QPixmap icono8 = nuevo.copy( 0.200,300.450,200,150);
        QIcon icon8(icono8);
        M[2][0]->setIcon(icon8);

        QPixmap icono9 = nuevo.copy( 200.400,300.450,200,150);
        QIcon icon9(icono9);
        M[2][1]->setIcon(icon9);

        QPixmap icono10 = nuevo.copy(400.600,300.450,200,150 );
        QIcon icon10(icono10);
        M[2][2]->setIcon(icon10);

        QPixmap icono11 = nuevo.copy(600.800,300.450,200,150);
        QIcon icon11(icono11);
        M[2][3]->setIcon(icon11);

//fila 4

        QPixmap icono12 = nuevo.copy( 0.200,450.600,200,150);
        QIcon icon12(icono12);
        M[3][0]->setIcon(icon12);

        QPixmap icono13= nuevo.copy( 200.400,450.600,200,150);
        QIcon icon13(icono13);
        M[3][1]->setIcon(icon13);

        QPixmap icono14 = nuevo.copy(400.600,450.600,200,150 );
        QIcon icon14(icono14);
        M[3][2]->setIcon(icon14);

       /* for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){

                QPixmap icono = nuevo.copy(j*200.j+1*200,150*i.i+1*150,200,150);//corto y la guardo  en su posicion
                        QIcon icon(icono);
                        M[i][j]->setIcon(icon);

            }
        }*/
        M[3][3]->setIcon(QIcon());//borro por si keda algo y me aseguro ke hay un hueco.

    }
}

void MainWindow::on_actionAbout_triggered()
{
     QMessageBox::information(NULL,"About","Realizado por J.M.A.M","Aceptar");
}

void MainWindow::on_actionSalir_triggered()
{
     qApp->exit();
}

void MainWindow::on_actionDesordenar_triggered()
{
     Desordena();
}
