#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QWidget::setWindowIcon(QIcon(":/Recursos/skull.png"));
    QWidget::setWindowTitle("Practica 3 - Ejercicio 1");
    //asignamos un boton a cada posicion de la matriz
    matriz[0][0]=ui->puzzle_00;
    matriz[0][1]=ui->puzzle_01;
    matriz[0][2]=ui->puzzle_02;
    matriz[0][3]=ui->puzzle_03;
    matriz[1][0]=ui->puzzle_10;
    matriz[1][1]=ui->puzzle_11;
    matriz[1][2]=ui->puzzle_12;
    matriz[1][3]=ui->puzzle_13;
    matriz[2][0]=ui->puzzle_20;
    matriz[2][1]=ui->puzzle_21;
    matriz[2][2]=ui->puzzle_22;
    matriz[2][3]=ui->puzzle_23;
    matriz[3][0]=ui->puzzle_30;
    matriz[3][1]=ui->puzzle_31;
    matriz[3][2]=ui->puzzle_32;
    matriz[3][3]=ui->puzzle_33;
    for(int i = 0;i<4;i++){
        for(int j = 0;j<4;j++){
            m_int[i][j]=((i*10)+j);
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionClose_triggered()
{
    int close=QMessageBox::question(this,"Salir", "¿Está seguro que quiere salir?","Si","No");
    if(close==0){
        qApp->exit();
    }
}

void MainWindow::on_actionAboutUs_triggered()
{
    //Acerca de
    QMessageBox::about(this,"Acerca de","Realizada por Lisandro Estrada Mendes");

}

void MainWindow::on_actionOpen_Image_triggered()
{
    //Cargar imagen
    QString s = QFileDialog::getOpenFileName(this, "Cargar", NULL, "*.jpg");
    if(!s.isEmpty()) {
        Img.load(s);
    }
    if(!Img.isNull()) {
        QPixmap nuevo = Img.scaled(800,600);//escalo la imagen
//fila 1
        QPixmap icono = nuevo.copy(0,0,200,150);//corto
        QIcon icon(icono);
        matriz[0][0]->setIcon(icon);//y asignamos a su posicion
        QPixmap icono1 = nuevo.copy(200,0,200,150);//corto
        QIcon icon1(icono1);
        matriz[0][1]->setIcon(icon1);//y asignamos a su posicion
        QPixmap icono2 = nuevo.copy(400,0,200,150);//corto
        QIcon icon2(icono2);
        matriz[0][2]->setIcon(icon2);//y asignamos a su posicion
        QPixmap icono3 = nuevo.copy(600,0,200,150);//corto
        QIcon icon3(icono3);
        matriz[0][3]->setIcon(icon3);//y asignamos a su posicion
//fila 2
        QPixmap icono4 = nuevo.copy(0,150,200,150);
        QIcon icon4(icono4);
        matriz[1][0]->setIcon(icon4);
        QPixmap icono5 = nuevo.copy(200,150,200,150);
        QIcon icon5(icono5);
        matriz[1][1]->setIcon(icon5);
        QPixmap icono6 = nuevo.copy(400,150,200,150);
        QIcon icon6(icono6);
        matriz[1][2]->setIcon(icon6);
        QPixmap icono7 = nuevo.copy(600,150,200,150);
        QIcon icon7(icono7);
        matriz[1][3]->setIcon(icon7);
//fila 3
        QPixmap icono8 = nuevo.copy(0,300,200,150);
        QIcon icon8(icono8);
        matriz[2][0]->setIcon(icon8);
        QPixmap icono9 = nuevo.copy(200,300,200,150);
        QIcon icon9(icono9);
        matriz[2][1]->setIcon(icon9);
        QPixmap icono10 = nuevo.copy(400,300,200,150);
        QIcon icon10(icono10);
        matriz[2][2]->setIcon(icon10);
        QPixmap icono11 = nuevo.copy(600,300,200,150);
        QIcon icon11(icono11);
        matriz[2][3]->setIcon(icon11);
//fila 4
        QPixmap icono12 = nuevo.copy(0,450,200,150);
        QIcon icon12(icono12);
        matriz[3][0]->setIcon(icon12);
        QPixmap icono13= nuevo.copy(200,450,200,150);
        QIcon icon13(icono13);
        matriz[3][1]->setIcon(icon13);
        QPixmap icono14 = nuevo.copy(400,450,200,150);
        QIcon icon14(icono14);
        matriz[3][2]->setIcon(icon14);
        matriz[3][3]->setIcon(QIcon());//asignamos un icono vacio por si hubiera algo

    }
    //reasignamos los valores del registro de las casillas
    for(int i = 0;i<4;i++){
        for(int j = 0;j<4;j++){
            m_int[i][j]=((i*10)+j);
        }
    }
}

void MainWindow::on_actionMess_triggered()
{    
    Mess();
}

void MainWindow::Mess(){//Desordenar
    int aux=0;
    while(aux<50){
        int mov=rand()%4;
        switch(mov){
        case 0://arriba
            Up();
            break;
        case 1://abajo
            Down();
            break;
        case 2://izquierda
            Left();
            break;
        case 3://derecha
            Right();
            break;
        }
        aux++;
    }
}

void MainWindow::Win(){ //verificar ganador
    bool win=true;
    for(int i=0;i<4&&win==true;i++){
        for(int j=0;j<4&&win==true;j++){
            if(m_int[i][j]!=((i*10)+j)){
                win=false;
            }
        }
    }
    if(win==true){
        int opc=QMessageBox::information(this,"Fin de la partida","Puzzle resuelto! ¿Qué quieres hacer?","Jugar otra vez","Cargar nueva imagen","Salir del juego");
        if(opc==0){
            Mess();
        }
        if(opc==1){
            on_actionOpen_Image_triggered();
        }
        if(opc==2){
            on_actionClose_triggered();
        }
    }
}

void MainWindow::Find(int *locx, int *locy){//buscar donde esta el hueco vacio
    bool stop=false;
    for(int i=0;i<4&&stop==false;i++){
        for(int j=0;j<4&&stop==false;j++){
            if(matriz[i][j]->icon().isNull()){
                *locx=j;
                *locy=i;
                stop=true;
            }
        }
    }
}

void MainWindow::Down(){//Mover abajo
    int locx=-1, locy=-1;
    Find(&locx, &locy);
    if(locy>0){
        int x;
        x=m_int[locy][locx];
        matriz[locy][locx]->setIcon(matriz[locy-1][locx]->icon());
        m_int[locy][locx]=m_int[locy-1][locx];
        matriz[locy-1][locx]->setIcon(QIcon());
        m_int[locy-1][locx]=x;
    }
}
void MainWindow::Up(){//Mover arriba
    int locx, locy;
    Find(&locx, &locy);
    if(locy<3){
        int x;
        x=m_int[locy][locx];
        matriz[locy][locx]->setIcon(matriz[locy+1][locx]->icon());
        m_int[locy][locx]=m_int[locy+1][locx];
        matriz[locy+1][locx]->setIcon(QIcon());
        m_int[locy+1][locx]=x;
    }
}
void MainWindow::Right(){//Mover derecha
    int locx=-1, locy=-1;
    Find(&locx, &locy);
    if(locx>0){
        int x;
        x=m_int[locy][locx];
        matriz[locy][locx]->setIcon(matriz[locy][locx-1]->icon());
        m_int[locy][locx]=m_int[locy][locx-1];
        matriz[locy][locx-1]->setIcon(QIcon());
        m_int[locy][locx-1]=x;
    }
}
void MainWindow::Left(){//Mover Izquierda
    int locx=-1, locy=-1;
    Find(&locx, &locy);
    if(locx<3){
        int x;
        x=m_int[locy][locx];
        matriz[locy][locx]->setIcon(matriz[locy][locx+1]->icon());
        m_int[locy][locx]=m_int[locy][locx+1];
        matriz[locy][locx+1]->setIcon(QIcon());
        m_int[locy][locx+1]=x;
    }
}



void MainWindow::on_actionUp_triggered(){
    Up();
    Win();
}
void MainWindow::on_actionDown_triggered(){
    Down();
    Win();
}
void MainWindow::on_actionLeft_triggered(){
    Left();
    Win();
}
void MainWindow::on_actionRight_triggered(){
    Right();
    Win();
}

void MainWindow::on_puzzle_00_clicked(){
    if(matriz[0][1]->icon().isNull())Right();
    else
        if(matriz[1][0]->icon().isNull()) Down();
    Win();
}
void MainWindow::on_puzzle_01_clicked(){
    if(matriz[0][2]->icon().isNull()) Right();
    else
        if(matriz[1][1]->icon().isNull()) Down();
        else
            if(matriz[0][0]->icon().isNull()) Left();
    Win();
}
void MainWindow::on_puzzle_02_clicked(){
    if(matriz[0][3]->icon().isNull()) Right();
    else
        if(matriz[1][2]->icon().isNull()) Down();
        else
            if(matriz[0][1]->icon().isNull()) Left();
    Win();
}
void MainWindow::on_puzzle_03_clicked(){
    if(matriz[1][3]->icon().isNull()) Down();
    else
        if(matriz[0][2]->icon().isNull()) Left();
    Win();
}
void MainWindow::on_puzzle_10_clicked(){
    if(matriz[0][0]->icon().isNull()) Up();
    else
        if(matriz[1][1]->icon().isNull()) Right();
        else
            if(matriz[2][0]->icon().isNull()) Down();
    Win();
}
void MainWindow::on_puzzle_11_clicked(){
    if(matriz[0][1]->icon().isNull()) Up();
    else
        if(matriz[1][2]->icon().isNull()) Right();
        else
            if(matriz[2][1]->icon().isNull()) Down();
            else
                if(matriz[1][0]->icon().isNull()) Left();
    Win();
}
void MainWindow::on_puzzle_12_clicked(){
    if(matriz[0][2]->icon().isNull()) Up();
    else
        if(matriz[1][3]->icon().isNull()) Right();
        else
            if(matriz[2][2]->icon().isNull()) Down();
            else
                if(matriz[1][1]->icon().isNull()) Left();
    Win();
}
void MainWindow::on_puzzle_13_clicked(){
    if(matriz[0][3]->icon().isNull()) Up();
    else
        if(matriz[2][3]->icon().isNull()) Down();
        else
            if(matriz[1][2]->icon().isNull()) Left();
    Win();
}
void MainWindow::on_puzzle_20_clicked(){
    if(matriz[1][0]->icon().isNull()) Up();
    else
        if(matriz[2][1]->icon().isNull()) Right();
        else
            if(matriz[3][0]->icon().isNull()) Down();
    Win();
}
void MainWindow::on_puzzle_21_clicked(){
    if(matriz[1][1]->icon().isNull()) Up();
    else
        if(matriz[2][2]->icon().isNull()) Right();
        else
            if(matriz[3][1]->icon().isNull()) Down();
            else
                if(matriz[2][0]->icon().isNull()) Left();
    Win();
}
void MainWindow::on_puzzle_22_clicked(){
    if(matriz[1][2]->icon().isNull()) Up();
    else
        if(matriz[2][3]->icon().isNull()) Right();
        else
            if(matriz[3][2]->icon().isNull()) Down();
            else
                if(matriz[2][1]->icon().isNull()) Left();
    Win();
}
void MainWindow::on_puzzle_23_clicked(){
    if(matriz[1][3]->icon().isNull()) Up();
    else
        if(matriz[3][3]->icon().isNull()) Down();
        else
            if(matriz[2][2]->icon().isNull()) Left();
    Win();
}
void MainWindow::on_puzzle_30_clicked(){
    if(matriz[2][0]->icon().isNull()) Up();
    else
        if(matriz[3][1]->icon().isNull()) Right();
    Win();
}
void MainWindow::on_puzzle_31_clicked(){
    if(matriz[2][1]->icon().isNull()) Up();
    else
        if(matriz[3][2]->icon().isNull()) Right();
        else
            if(matriz[3][0]->icon().isNull()) Left();
    Win();
}
void MainWindow::on_puzzle_32_clicked(){
    if(matriz[2][2]->icon().isNull()) Up();
    else
        if(matriz[3][3]->icon().isNull()) Right();
        else
            if(matriz[3][1]->icon().isNull()) Left();
    Win();
}
void MainWindow::on_puzzle_33_clicked(){
    if(matriz[2][3]->icon().isNull()) Up();
    else
        if(matriz[3][2]->icon().isNull()) Left();
    Win();
}
