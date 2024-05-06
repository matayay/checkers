/**
AUTHOR: Matayay Karuna
Project: Checkers
File: main.cpp
Description: Entry point for the Checkers game.
**/

#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
