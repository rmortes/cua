/**************************************************************************
 * (C) Copyright 2014 Carlos Barrera Piqueres y Jose Manuel Requena Plens *
 * Universidad de Alicante. Grado en ingenieria en sonido e imagen.       *
 *                                                                        *
 * Asignatura: Fundamentos de programacion 2                              *
 *                                                                        *
 * PRACTICA 3                                                             *
 *                                                                        *
 * MARCOS CON CROMA                                                       *
 *************************************************************************/

#include "MainWindow/mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent):QMainWindow(parent),ui(new Ui::MainWindow)//Constructor
{
    ui->setupUi(this);
}

//METODO
void MainWindow::modificar(){//Carga y/o escala/desplaza las imagenes
    img = QPixmap(800, 600);//Creamos un mapa de pixeles de 800X600
    img.fill(Qt :: white);//Rellenamos la img con color blanco

    if(!imagen1.isNull()){
        QPainter p(&img);//Painter tiene metodos para modificar de la imagenes. Lo pasamos por referencia porque por valor se copiaria cada vez que pasaramos por aqui.
        float escala = (float) ui ->barraEscala ->value()/50; //Lo dividimos entre 50 para que sea el porcentaje entre 0 y 1.99 asi podremos ampliar la imagen hasta el 200%
        int horizontal = ui -> horizontalSlider -> value()*7;//Posicion horizontal. el valor oscila entre 0 y 700
        int vertical = ui -> verticalSlider -> value()*5;// Posicion vertial. el valor oscila entre 0 y 700

        //Con el metodo translate podemos mover la imagen en tiempo de ejecucion
        p.translate(horizontal, vertical);//Desplazamos la imagen
        p.scale (escala, escala); //Escalamos la imagen

        p.drawPixmap(0,0,imagen1); //Pintamos en el mapa de pixeles la imagen a partir desde el pixel 0x0
        p.end();//Finalizamos las modificaciones

    }

    if(!imagen2.isNull()){
        QImage marco = imagen2.scaled(800, 600).toImage();//Marco. la escalamos a 800x600 y convertimos la imagen que queremos modificar de tipo QPixmap a QImage
        QImage foto = img.toImage();//Imagen que sera enmarcada. Convertimos la imagen que queremos modificar de tipo QPixmap a QImage

        for(int x = 0; x<marco.width(); x++){//Recorremos la imagen pixel por pixel
            for(int y = 0; y<marco.height(); y++){
                QRgb c_foto = marco.pixel(x, y);//Descomponemos por colores RGB cada pixel
                if (qRed(c_foto)==0 && qGreen(c_foto)>200 && qBlue(c_foto)==0){//En los pixeles donde el marco no tiene rojo o azul y si tiene verde (mayor que 200 en este caso)
                    marco.setPixel(x,y, foto.pixel(x,y));//Copia un pixel de foto (x,y) a la posicion x e y del marco
                }
            }
        }

        img = QPixmap :: fromImage(marco);//Aplicamos los cambios
    }
    //Mostrar la imagen por pantalla
    ui-> label -> setPixmap (img);//Imprimimos la imagen img en el label
    ui->label->setFixedSize(img.width(), img.height());//Ajustamos el tamaño del label al de la imagen
    ui-> label ->repaint();//Actualizamos el label
    guardado=false;//Las ultimas modificaciones no estan guardadas, lo utilizaremos para cuando cerremos la app siempre tengamos guardado el trabajo

}

//SLIDERS
void MainWindow::on_horizontalSlider_actionTriggered()//Slider para desplazar la imagen horizontalmente
{
    modificar();
}

void MainWindow::on_verticalSlider_actionTriggered()//Slider para desplazar la imagen verticalmente
{
    modificar();
}

void MainWindow::on_barraEscala_actionTriggered()//Slider para modificar la escala
{
    modificar();
}

//BOTONES
void MainWindow::on_actionAutores_triggered(){//Boton about
    QMessageBox::information(this, "Autores", "Carlos B. y Jose R.", "Aceptar");
}

void MainWindow::on_actionSalir_triggered()//Boton salir
{
    qApp->exit();//Salimos de la aplicacion
}

void MainWindow::on_actionCargar_triggered(){//Boto cargar
    QString dir1 = QFileDialog::getOpenFileName(this, "Cargar imagen", QDir::homePath(), "*.bmp");//Copiamos la direccion la imagen a la que vamos a aplicar un marco en .bmp
    QString dir2 = QFileDialog::getOpenFileName(this, "Cargar marco", NULL, "*.bmp");//Copiamos la direccion del marco en .bmp
    if(!dir1.isEmpty()) imagen1.load(dir1);//Cargamos la imagen en la direccion guardada en dir1
    if(!dir2.isEmpty()) imagen2.load(dir2);//Cargamos la imagen en la direccion guardada en dir2
    modificar();
}

void MainWindow::on_actionGuardar_triggered()//Boton guardar
{

    if(!img.isNull()){
        QString fichero = QFileDialog::getSaveFileName(this,"Grabar imagen", NULL,"*.jpg" );//Guarda la imagen que tiene cargada con extension .jpg
        if(!fichero.isNull()){
            img.save(fichero);
            guardado=true;//Guardamos el estado, indicamos que la imagen ha sido guardada
        }
    }
}

void MainWindow::on_pushButton_clicked()//Boton reset. Reseteamos los sliders
{
    ui ->barraEscala ->setValue(50);
    ui -> horizontalSlider -> setValue(0);
    ui -> verticalSlider -> setValue(0);
    modificar();
}

void MainWindow::salir()//Metodo para confirmar la salida del programa sin guardar la imagen.
{
    if(!img.isNull() && !guardado){//Si las ultimas modificaciones no han sido guardadas, al salir del mainwindow te pedira guardar el archivo
        int op;

        do{//Hara lo siguiente y lo repetira mientras la opcion sea si, asi si el usuario da a cancelar en la ventana de guardar, se le volvera a preguntar antes de salir
            op=QMessageBox::question(this,"Guardar","Antes de salir, ¿Desea guardar la imagen?","Si","No");//Guardamos en un entero la opcion seleccionada 0=si 1=no
            if(op==0){
                QString fichero = QFileDialog::getSaveFileName(this,"Grabar imagen", NULL,"*.jpg" );//Guarda la imagen que tiene cargada con extension .jpg
                if(!fichero.isNull()){
                    img.save(fichero);//Guardamos la imagen en la ruta elegida en el QFileDialog
                    op=1;//despues de guardar el archivo ponemos op=1 para que salga del do-while
                }
            }
        }while(op==0);
    }
}

//DESTRUCTOR
MainWindow::~MainWindow()//Destructor
{
    salir();//Antes de destruir el objeto, llamamos al metodo salir por si el usuario quiere guardar el trabajo
    delete ui;
}
