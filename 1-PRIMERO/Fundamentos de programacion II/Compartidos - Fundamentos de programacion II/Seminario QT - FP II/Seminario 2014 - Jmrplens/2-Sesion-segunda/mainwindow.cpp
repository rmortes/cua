#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pushButton->setText(
            ui->comboBox->currentText()
            );//Introduce el texto del desplegable al boton al iniciar
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_comboBox_currentIndexChanged(QString )
{
    ui->pushButton->setText(
            ui->comboBox->currentText()
            );//Introduce el texto del desplegable al boton
}

void MainWindow::on_pushButton_clicked()
{
    switch(ui->comboBox->currentIndex()){
    case 0:
        this->setWindowState(Qt::WindowMinimized);//Cambiamos el estado de la ventana a el caso 0 que es minimizar
        break;
    case 1:
        this->setWindowState(Qt::WindowMaximized);//Cambiamos el estado de la ventana a el caso 0 que es maximizar
        break;
    case 2:
        qApp->exit();//Salir del programa
        break;
    }
}

void MainWindow::on_lineEdit_editingFinished()
{
    this->setWindowTitle(ui->lineEdit->text());//Cambiamos el texto de la barra superior al terminar de escribir pulsando intro
    this->on_pushButton_clicked();//Llama al metodo de pulsar boton al terminar de editar el texto
}

void MainWindow::on_lineEdit_textChanged(QString )
{
    this->setWindowTitle("Escribiendo "+ui->lineEdit->text());//Cambiamos el texto de la barra superior mientras escribimos
    ui->comboBox->setCurrentIndex(rand()%3);//Cambia la opcion del desplegable de forma aleatoria al ir escribiendo texto
}

void MainWindow::on_spinBox_valueChanged(int )
{
    ui->horizontalSlider->setValue(ui->spinBox->value());//Cambiamos el valor del slider con el spin

}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    ui->spinBox->setValue(ui->horizontalSlider->value());//Cambiamos el valor del spin con el slider
    float opacidad = ui->horizontalSlider->value()/100.0;
    this->setWindowOpacity(opacidad);
}
