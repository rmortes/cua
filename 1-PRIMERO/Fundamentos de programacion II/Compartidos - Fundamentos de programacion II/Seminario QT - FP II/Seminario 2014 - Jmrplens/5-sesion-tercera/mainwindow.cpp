#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox> //Para ventanas emergente con mensajes
#include <math.h>
#include <QProgressDialog>
#include <QFileDialog>
#include <QImage>
#include <QPainter>

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionSalir_triggered()
{
    int boton=QMessageBox::question(this,"Preguntica","Esta seguro de finalizar?","si","no","a veces");//Guardamos en un entero la opcion seleccionada 0=si 1=no 2=a veces
    switch(boton){

    case 0:
        qApp->exit();//Salir de la aplicacion
        break;
    case 1:
        break;
    case 2:
        QMessageBox::information(this, "Atencion", "El usuario ha bebido");
        break;

    }
}



void MainWindow::on_actionAcerca_de_triggered()
{
    QMessageBox::information(this,"About","Esta aplicacion esta hecha por mi","Dale!!");
}

void MainWindow::on_actionMinimizar_triggered()
{
    this->setWindowState(Qt::WindowMinimized);//Minimizar ventana
}

void MainWindow::on_actionMaximizar_triggered()
{
    this->setWindowState(Qt::WindowMaximized);//Maximizar ventana+
}


void MainWindow::on_pushButton_clicked()
{

    MainWindow2 ventana(this);
    ventana.show();
    /*
     *Prueba de barra de progreso haciendo operacion
    QProgressDialog dialogo("Calculando...","Cancelar",0,100);//Barra de progreso de 0 a 100
    dialogo.setWindowTitle(" ");//Titulo de la ventana
    //dialogo.setModal(true);//No permite pulsar en otra ventana que no sea la "dialogo"
    dialogo.show();//Muestra barra de progreso
    for(int i=0;i<100 && dialogo.wasCanceled()==false;i++){//Mientras i sea menos que 100 y el boton cancelar no este pulsado
        dialogo.setValue(i);//Valor de la barra de progreso
        qApp->processEvents();//Actualiza la aplicacion (si mueves la ventana al pasar por aqui realizara la accion)
        for(int k=0;k<1000000;k++){
            double b =cos(k)*tan(k);
            b++;
        }
    }
    */
}
void MainWindow::RefrescarImagen(){
    if(!img.isNull()){
        ui->label->setPixmap(img);
    }
}

void MainWindow::on_actionCargar_triggered()
{
    QString fichero=QFileDialog::getOpenFileName(this,"Cargar imagen", NULL,"*.jpg");//Elegir una imagen con extension jpg y en la carpeta predeterminada NULL
    this->setWindowTitle(fichero);
    if(!fichero.isNull()){
        img.load(fichero);
        RefrescarImagen();

    }
}

void MainWindow::on_actionGraba_triggered()
{
    if(!img.isNull()){
        QString fichero = QFileDialog::getSaveFileName(this,"Grabar imagen", NULL,"*.jpg" );//Guarda la imagen que tiene cargada con extension .jpg
        if(!fichero.isNull()){
            img.save(fichero);
        }
    }
}

void MainWindow::on_actionEscalar_triggered()
{
    if(!img.isNull()){
        img = img.scaled(img.width()*0.9,img.height()*0.9);
        this->RefrescarImagen();
    }
}

void MainWindow::on_actionPasar_a_gris_triggered()
{
    if(!img.isNull()){
        QImage aux = img.toImage();//Convertimos de Pixmap a image
        for(int x=0;x<aux.width();x++){//Recorremos pixel por pixel la imagen
            for(int y=0;y<aux.height();y++){
                QRgb p = aux.pixel(x,y);
                int r = qRed(p); //Devuelve el valor del rojo
                int g = qGreen(p); //Devuelve el valor del verde
                int b = qBlue(p); //Devuelve el valor del azul
                int gris = (r+g+b)/3;
                p = qRgb(gris,gris,gris);
                aux.setPixel(x,y,p);

            }
        }
        img = QPixmap::fromImage(aux);
        RefrescarImagen();
    }
}

void MainWindow::on_actionCirculos_de_colores_triggered()
{
    if(!img.isNull()){
        QPainter painter(&img);
        for(int i=0;i<100;i++){
        int x = rand()%img.width();
        int y = rand()%img.height();
        int rx = rand()%100;
        int ry = rand()%100;
        QPen pen = painter.pen();
        pen.setWidth(rand()%10+1);
        pen.setColor(QColor(rand()%256,rand()%256,rand()%256));
        painter.setPen(pen);
        //painter.setPen(Qt::yellow);//Color borde
        painter.setBrush(Qt::NoBrush);//Sin relleno
        painter.drawEllipse(x,y,rx,ry);//Dibuja elipses
    }
        painter.end();
        RefrescarImagen();
    }
}
