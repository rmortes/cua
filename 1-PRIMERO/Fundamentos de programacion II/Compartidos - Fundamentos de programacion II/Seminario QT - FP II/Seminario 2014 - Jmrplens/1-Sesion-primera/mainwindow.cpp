#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    RefrescarTexto();
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*void MainWindow::on_pushButton_clicked()
{
    //close();
    //this->close();
    //qApp->exit();
    this->setWindowTitle("Ha llegado el verano");
}*/

void MainWindow::on_pushButton_pressed()
{
    this->ui->label->setText("Puto calor!");
}

void MainWindow::on_pushButton_released()
{
    this->ui->label->setText("Hola mundo caluroso!");
}

void MainWindow::on_commandLinkButton_clicked()
{
    //Creamos la ventana en dinamica para que no se destruya
    //MainWindow ventana(this); en estatica
    MainWindow *ventana=new MainWindow (this); //dinamica
    //ventana.show(); en estatica
    ventana->show(); //dinamica
}

void MainWindow::on_checkBox_toggled(bool checked)
{
    //negrita
    RefrescarTexto();
    //QFont f = ui->label->font();
    //f.setBold(ui->checkBox->isChecked());

    //ui->label->setFont(f);


}

void MainWindow::on_checkBox_2_toggled(bool checked)
{
    RefrescarTexto();
    //cursiva
    //QFont f = ui->label->font();
    //f.setItalic(ui->checkBox_2->isChecked());

    //ui->label->setFont(f);
}

void MainWindow::RefrescarTexto(void){
    QFont f = ui->label->font();
    f.setBold(ui->checkBox->isChecked());
    f.setItalic(ui->checkBox_2->isChecked());
    ui->label->setFont(f);
    return;

}
