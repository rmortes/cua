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

#include <QtWidgets/QApplication>
#include "MainWindow/mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
