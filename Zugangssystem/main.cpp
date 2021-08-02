#include "mainwindow.h"

#include <QApplication>

/*! \mainpage Zugangssystem Version 1.1
 *
 * \section intro_sec Introduction
 *
 * This project is for the entry system and the time saving of the employees
 */

int main(int argc, char *argv[])
{    
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
