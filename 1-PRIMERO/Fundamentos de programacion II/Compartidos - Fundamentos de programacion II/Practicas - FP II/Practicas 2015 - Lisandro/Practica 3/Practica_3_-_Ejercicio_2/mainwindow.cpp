#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QWidget::setWindowIcon(QIcon(":/Recursos/skull2.png"));
    QWidget::setWindowTitle("Practica 3 - Ejercicio 2");
    restart();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::restart(){
    ui->Brillo->setValue(0);
    ui->Contraste->setValue(0);
    ui->Gamma->setValue(100.0);
}

void MainWindow::on_actionOpen_image_triggered(){
    QString ruta = QFileDialog::getOpenFileName(this,"Cargar imagen",":/", "*.jpg");
    if(!ruta.isNull()){
        img.load(ruta);
        Redibujar();
    }
    restart();
}

void MainWindow::on_actionSave_triggered(){
    if(!Img.isNull()){
        QString ruta = QFileDialog::getSaveFileName(this,"Grabar Imagen",NULL,"*.jpg");
        if(!ruta.isNull()){
            Img.save(ruta);
        }
    }
}

void MainWindow::Redibujar(){
    if(!img.isNull()){
        Img = img.toImage();
        int I = ui->Brillo->value(); //factor de iluminacion
        float C = ui->Contraste->value();
        float F = (259.0*(C + 255.0))/(255.0*(259.0-C)); //factor de contraste
        float G = ui->Gamma->value()/100.0;
        int Levels[256];
        for(int i=0;i<256;i++){
            int lev=i;
            //brillo
            lev = T(lev+I);
            //contraste
            lev = T(F*(lev-128.0)+128.0);
            //gamma
            lev = T(255.0*pow(lev/255.0, 1.0/G));
            Levels[i]=lev;
        }
        for(int i=0;i<Img.width();i++){
            for(int j=0;j<Img.height();j++){
                QRgb color = Img.pixel(i,j);
                int rojo = Levels[qRed(color)];
                int verde = Levels[qGreen(color)];
                int azul = Levels[qBlue(color)];
                Img.setPixel(i,j,qRgb(rojo,verde,azul));
            }
        }
        ui->label_imagen->setPixmap(QPixmap::fromImage(Img));
        ui->label_imagen->repaint();
    }
}

void MainWindow::on_actionRebuild_triggered(){
    restart();
}

void MainWindow::on_actionAcercaUs_triggered(){
    //Acerca de
    QMessageBox::about(this,"Acerca de","Realizado por Lisandro Estrada Mendes");
}

void MainWindow::on_actionExit_triggered(){
    int close=QMessageBox::question(this,"Salir", "¿Está seguro que quiere salir?","Si","No");
    if(close==0){
        qApp->exit();
    }
}

int MainWindow::T(int n){
    int resultado=n;
    if(n>255)resultado=255;
    if(n<0)resultado=0;
    return (resultado);
}

void MainWindow::act_etiquetas(){
    //Convertir un numero entero en string
    QString s;
    //Cogemos el valor del Slider
    int b = ui->Brillo->value();
    //Printf contra una variable/cadena
    s.sprintf("%4d",b);
    //Modificamos el texto del label
    ui->label_brillo->setText(s);
    int c = ui->Contraste->value();
    s.sprintf("%4d",c);
    ui->label_contraste->setText(s);
    float g = ui->Gamma->value()/100.00;
    s.sprintf("%.2f",g);
    ui->label_gamma->setText(s);
}

void MainWindow::on_Brillo_valueChanged(){
    act_etiquetas();
    Redibujar();
}

void MainWindow::on_Contraste_valueChanged(){
    act_etiquetas();
    Redibujar();
}

void MainWindow::on_Gamma_valueChanged(){
    act_etiquetas();
    Redibujar();
}
