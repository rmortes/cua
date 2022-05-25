#include "mainwindow.h"
#include "ui_mainwindow.h"

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

void MainWindow::reiniciar_barras(){
    ui->horizontalSlider->setValue(0);
    ui->horizontalSlider_2->setValue(0);
    ui->horizontalSlider_3->setValue(0);
    ui->label_4->setText("0");
    ui->label_5->setText("0");
    ui->label_6->setText("0");
}

int MainWindow::truncamiento(float valor){
    if(valor > 255) valor = 255;
    if(valor<0) valor = 0;
    return valor;
}


void MainWindow::resolucion(){
    //Le damos a una variable B el valor del Slider Brillo
    int Brillo,Contraste,rojo,verde,azul,ancho, alto;
    float F,Gamma;
    ancho=img.width();
    alto=img.height();
    ui->label_imagen->setFixedHeight(alto);
    ui->label_imagen->setFixedWidth(ancho);
    Brillo = ui->horizontalSlider->value();
    ui->label_4->setText(QString::number(Brillo));
    //Le damos a C el valor del Slide Contraste
    Contraste = ui->horizontalSlider_2->value();
    ui->label_5->setText(QString::number(Contraste));
    //Calculamos F a partir de C
    F = (259.0*(Contraste+255.0))/(255.0*(259.0-Contraste));
    //Le damos a G el valor de Gamma
    Gamma = (ui->horizontalSlider_3->value())/100.0;
    ui->label_6->setText(QString::number(Gamma));
    int Lookup[256];
    for(int i=0;i<256;i++){
        int lkp;
        lkp=i;
        lkp= truncamiento(lkp+Brillo);
        lkp= truncamiento(F*(lkp-128)+128);
        lkp=truncamiento(255*pow((lkp/255.0),(1/Gamma)));
        Lookup[i]=lkp;
    }
    //Creamos una copia de img para modificarla
    //y no perder la original
    QImage foto= img.toImage();
    //Recorremos cada pixel de la imagen
    for(int x=0;x<foto.width();x++){
        for(int y=0;y<foto.height();y++){
            //Creamos un objeto QRgb que
            //guarda las intensidades
            //Rojo, Verde, Azul de cada pixel
            QRgb color = foto.pixel(x,y);
            //Para cada intensidad la identificamos
            //con el lookup donde ya está realizada
            //las operaciones de niveles
            rojo= Lookup[qRed(color)];
            verde= Lookup[qGreen(color)];
            azul= Lookup[qBlue(color)];
            //Rellenamos cada pixel con el color final
            foto.setPixel(x,y,qRgb(rojo,verde,azul));
        }
    }
    //Creamos un objeto QPixmap para mostras la imagen mejor
    QPixmap aux = QPixmap::fromImage(foto);
    ui->label_imagen->setPixmap(aux);
    ui->label_imagen->setGeometry(9,9,img.width(),img.height());
    ui->label_imagen->repaint();
}

void MainWindow::on_horizontalSlider_actionTriggered()
{
    resolucion();
}

void MainWindow::on_horizontalSlider_2_actionTriggered()
{
    resolucion();
}

void MainWindow::on_horizontalSlider_3_actionTriggered()
{
    resolucion();
}

void MainWindow::on_actionSalir_triggered()
{
    qApp->exit();
}

void MainWindow::on_actionRestaurar_triggered()
{
    reiniciar_barras();
    img = original;
    resolucion();
}

void MainWindow::on_actionAbrir_triggered()
{
    //Abre cualquier tipo de archivo, pero solo funcionará si es imagen.
    QString ruta = QFileDialog::getOpenFileName(this,"cargar imagen",NULL,"*.jpg ;;*.bmp;;*.png;;All Files(*.jpg *.png *.bmp)");
    if(!ruta.isNull()){
        original.load(ruta);
        img = original;
        reiniciar_barras();
        resolucion();
    }
}

void MainWindow::on_actionInformacion_del_programa_triggered()
{
    QMessageBox::information(this,"Información del programa", "Este programa ha sido realizado por:\nJorge Navarro Martinez\n\nVersión del programa 1.1","Ok");
}
