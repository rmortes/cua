#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
#include <QFileDialog>
#include <QtCore>
#include <QtGui>
#include <time.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //Matriz de botones.
    M[0][0]=ui->pushButton;
    M[0][1]=ui->pushButton_2;
    M[0][2]=ui->pushButton_3;
    M[0][3]=ui->pushButton_4;

    M[1][0]=ui->pushButton_5;
    M[1][1]=ui->pushButton_6;
    M[1][2]=ui->pushButton_7;
    M[1][3]=ui->pushButton_8;

    M[2][0]=ui->pushButton_9;
    M[2][1]=ui->pushButton_10;
    M[2][2]=ui->pushButton_11;
    M[2][3]=ui->pushButton_12;

    M[3][0]=ui->pushButton_13;
    M[3][1]=ui->pushButton_14;
    M[3][2]=ui->pushButton_15;
    M[3][3]=ui->pushButton_16;

    //Asigna el boton sin icono en esa posicion
    Fvacia=Cvacia=3;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionSalir_triggered()
{
    qApp->exit();
}

void MainWindow::on_actionInformaci_n_sobre_el_programa_triggered()
{
    QMessageBox::information(this,"Información del programa", "Este programa ha sido realizado por:\nJorge Navarro Martinez\n\nVersión del programa 1.1","Ok");
}

void MainWindow::Tirar(int F, int C){
    //ese metodo gestiona un click sobre el botón en coordenadas (i,j)
    int o;
    if ((F + 1 == Fvacia && C == Cvacia) || (F - 1 == Fvacia && C == Cvacia) || (C + 1 == Cvacia && F == Fvacia) || (C- 1 == Cvacia && F == Fvacia)){
        QIcon aux = M[F][C]->icon();
        M[F][C]->setIcon(M[Fvacia][Cvacia]->icon());
        M[Fvacia][Cvacia]-> setIcon(aux);
        o = B[F][C];
        B[F][C] = B[Fvacia][Cvacia];
        B[Fvacia][Cvacia] = o;
        Fvacia = F;
        Cvacia = C;
    }
    return;
}

void MainWindow::on_actionCargar_Imagen_triggered()
{
    //Aquí muestra una ventana en la cual podemos seleccionar la imagen.
    QString imagen = QFileDialog::getOpenFileName(this, "Cargar imagen", NULL,"*.*");
    //En imagen definimos la ruta en la que se encuentra.
    QIcon icon();

    if(!imagen.isNull()){
        img.load(imagen);
        if(M[Fvacia][Cvacia]!=M[3][3]){
            Fvacia=Cvacia=3;
            M[3][3]->setIcon(QIcon());
        }
        //Medimos cada trozo en ancho y alto
        int alto, ancho;
        ancho = img.width() / 4;
        alto = img.height() / 4;
        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 4; j++){
                if(i != 3 || j != 3){
                    M[i][j]->setIcon(img.copy(j*ancho, i*alto, ancho, alto));
                    M[i][j]->setIconSize(QSize(M[i][j]->size().width(), M[i][j]->size().height()));
                }
                B[i][j] = i*4 + j;
            }
        }
    }
}

void MainWindow::on_actionAleatorio_triggered()
{
    int cord, afvacia, acvacia;
    int v = 0;
    bool t;
    while(v < 4){
        srand(time(NULL));
        cord = rand() % 4;
        afvacia = Fvacia;
        acvacia = Cvacia;
        t = false;
        switch(cord){
        case 0:
            if(Fvacia > 0){
                Fvacia--;
                t = true;
            }
            break;
        case 1:
            if(Fvacia < 3){
                Fvacia++;
                t = true;
            }
            break;
        case 2:
            if(Cvacia > 0){
                Cvacia--;
                t = true;
            }
            break;
        case 3:
            if(Cvacia < 3){
                Cvacia++;
                t = true;
            }
        }
        if(t == true){
            QIcon aux = M[afvacia][acvacia]->icon();
            M[afvacia][acvacia]->setIcon(M[Fvacia][Cvacia]->icon());
            M[Fvacia][Cvacia]->setIcon(aux);

            cord = B[afvacia][acvacia];
            B[afvacia][acvacia] = B[Fvacia][Cvacia];
            B[Fvacia][Cvacia] = cord;
            v++;
        }
    }
}

void MainWindow::on_pushButton_clicked()
{
    Tirar(0,0);
}

void MainWindow::on_pushButton_2_clicked()
{
    Tirar(0,1);
}


void MainWindow::on_pushButton_3_clicked()
{
    Tirar(0,2);
}

void MainWindow::on_pushButton_4_clicked()
{
    Tirar(0,3);
}

void MainWindow::on_pushButton_5_clicked()
{
    Tirar(1,0);
}

void MainWindow::on_pushButton_6_clicked()
{
    Tirar(1,1);
}

void MainWindow::on_pushButton_7_clicked()
{
    Tirar(1,2);
}

void MainWindow::on_pushButton_8_clicked()
{
    Tirar(1,3);
}

void MainWindow::on_pushButton_9_clicked()
{
    Tirar(2,0);
}

void MainWindow::on_pushButton_10_clicked()
{
    Tirar(2,1);
}

void MainWindow::on_pushButton_11_clicked()
{
    Tirar(2,2);
}

void MainWindow::on_pushButton_12_clicked()
{
    Tirar(2,3);
}

void MainWindow::on_pushButton_13_clicked()
{
    Tirar(3,0);
}

void MainWindow::on_pushButton_14_clicked()
{
    Tirar(3,1);
}

void MainWindow::on_pushButton_15_clicked()
{
    Tirar(3,2);
}

void MainWindow::on_pushButton_16_clicked()
{
    Tirar(3,3);
}
