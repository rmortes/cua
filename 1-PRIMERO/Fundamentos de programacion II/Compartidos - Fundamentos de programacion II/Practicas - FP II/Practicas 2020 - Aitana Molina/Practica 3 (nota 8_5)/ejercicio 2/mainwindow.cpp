#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ventana1 = new MainWindow2(this);
    ventana2 = new MainWindow2(this);
    resultad = new MainWindow2(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete ventana1;
    delete ventana2;
    delete resultad;

}
void MainWindow::CalculaImagen(int op)

{
    QRgb color,color1;
    int r,g,b,r1,g1,b1,Rr,Gr,Br;
    if(!nuevo.isNull()){
        imagen1= nuevo.toImage();
        imagen2= nuevo2.toImage();
        resul = imagen1;

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

                resul.setPixel(i,j,qRgb(Rr,Gr,Br));
            }
        }
        resultado = QPixmap::fromImage(resul);

    }
}

void MainWindow::on_actionCargar_imagen_1_triggered()
{
    QString im1 = QFileDialog::getOpenFileName(this,"Cargar imagen 1",NULL,"*.jpg");
    if(im1.isEmpty()==false){
        Img.load(im1);
    }
    if(!Img.isNull()){
        nuevo = Img.scaled(640,480); //escalo la imagen
    }

    MainWindow2 *ventana1 = new MainWindow2(this);
    ventana1->show();
    ventana1->VisualizarImagen(nuevo);
}

void MainWindow::on_actionCargar_imagen_2_triggered()
{
    QString im2 = QFileDialog::getOpenFileName(this,"Cargar imagen 2",NULL,"*.jpg");
    if(im2.isEmpty()==false){
        Img.load(im2);
    }
    if(!Img.isNull()){
        nuevo2 = Img.scaled(640,480); //escalo la imagen

    }
    MainWindow2 *ventana2 = new MainWindow2(this);
    ventana2->show();
    ventana2->VisualizarImagen(nuevo2);
}

void MainWindow::on_actionVisualizar_triggered()
{
    if(resultado.isNull()==false){
        QString nombre = QFileDialog::getSaveFileName(this,"Guardar imagen en: ","","*.jpg");
        if(nombre.isEmpty()==false){
            resultado.save(nombre);
        }
    }
}

void MainWindow::on_actionSuma_triggered()
{
    int op=1;//suma

    CalculaImagen(op);
    resultad->show();
    resultad->VisualizarImagen(resultado);
}

void MainWindow::on_actionResta_triggered()
{
    int op=2;//resta

    CalculaImagen(op);
    resultad->show();
    resultad->VisualizarImagen(resultado);
}

void MainWindow::on_actionMultiplicacion_triggered()
{
    int op=3;//multiplicacion

    CalculaImagen(op);
    resultad->show();
    resultad->VisualizarImagen(resultado);
}

void MainWindow::on_actionAcercaDe_triggered()
{
    QMessageBox::information(NULL,"AcercaDe","Realizado por Helena Iborra Miquel y Aitana Molina García","Aceptar");
}

void MainWindow::on_actionSalir_triggered()
{
    qApp->exit();
}




