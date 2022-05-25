#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QSound::play("benvinguts.wav"); //carga el sonido de la ruta dnd esta el proyecto!


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionABRIR_triggered()
{
    QString s = QFileDialog::getOpenFileName(this, "Cargar", NULL, "*.jpg");
    if(!s.isEmpty()) {
        Img.load(s);
    }

    if(!Img.isNull()) {
         nuevo = Img.scaled(640,480);//escalo la imagen
         ui->label_2->setPixmap(nuevo);
    }

     s = QFileDialog::getOpenFileName(this, "Cargar", NULL, "*.jpg");
    if(!s.isEmpty()) {
        Img.load(s);
    }

    if(!Img.isNull()) {
         nuevo2 = Img.scaled(640,480);//escalo la imagen
         ui->label_3->setPixmap(nuevo2);
    }



}

void MainWindow::on_actionSALIR_triggered()
{
    qApp->exit();
}

void MainWindow::on_radioButton_clicked()
{
   int op=1;//suma

    MainWindow::CalculaImagen(op);


        ui->label_4->setPixmap(resultado);

}
void MainWindow::CalculaImagen(int op)

{
    if(!nuevo.isNull()){
        imagen1= nuevo.toImage();
        imagen2= nuevo2.toImage();
        resul=nuevo.toImage();

        for(int i=0;i<nuevo.width();i++){
            for(int j=0;j<nuevo.height();j++){
                color = imagen1.pixel(i,j);
                r = qRed(color);
                g = qGreen(color);
                b=  qBlue(color);

                color1 = imagen2.pixel(i,j);
                r1 = qRed(color1);
                g1 = qGreen(color1);
                b1=  qBlue(color1);

                if(op==1){//hacemos la suma
                Rr=(r+r1)/2;
                Gr=(g+g1)/2;
                Br=(b+b1)/2;
                 }
                if(op==2){//hacemos la resta
                Rr=(r-r1+255)/2;
                Gr=(g-g1+255)/2;
                Br=(b-b1+255)/2;
                 }
                if(op==3){//hacemos la multiplicacion
                Rr=(r*r1)/255;
                Gr=(g*g1)/255;
                Br=(b*b1)/255;
                 }
                if(op==4){//hacemos la And
                Rr=(r&r1)/2;
                Gr=(g&g1)/2;
                Br=(b&b1)/2;
                 }
                if(op==5){//hacemos la Or
                Rr=(r|r1)/2;
                Gr=(g|g1)/2;
                Br=(b|b1)/2;
                 }
                if(op==6){//hacemos la Xor
                Rr=(r1^r)/2;
                Gr=(g1^g)/2;
                Br=(b1^b)/2;
                 }







                resul.setPixel(i,j,qRgb(Rr,Gr,Br));

            }
        }
        resultado = QPixmap::fromImage(resul);

    }
}

void MainWindow::on_radioButton_2_clicked()
{
    int op=2;//resta

    CalculaImagen(op);


         ui->label_4->setPixmap(resultado);

}

void MainWindow::on_radioButton_3_clicked()
{
    int op=3;//multiplicacion

     MainWindow::CalculaImagen(op);


         ui->label_4->setPixmap(resultado);

}

void MainWindow::on_radioButton_4_clicked()
{
    int op=4;//and

     MainWindow::CalculaImagen(op);


         ui->label_4->setPixmap(resultado);
}

void MainWindow::on_radioButton_5_clicked()
{

    int op=5;//or

     MainWindow::CalculaImagen(op);


         ui->label_4->setPixmap(resultado);

}

void MainWindow::on_radioButton_6_clicked()
{

    int op=6;//xor

     MainWindow::CalculaImagen(op);


         ui->label_4->setPixmap(resultado);

}

void MainWindow::on_actionAcerca_triggered()
{
     QMessageBox::information(NULL,"About","Realizado por J.M.A.M","Aceptar");



}

void MainWindow::on_actionMOSAICO_triggered()
{

    ui->mdiArea->tileSubWindows();

}

void MainWindow::on_actionCASCADA_triggered()
{
     ui->mdiArea->cascadeSubWindows();
}
